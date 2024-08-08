// EE 342 - Project 3: Using Bisection, Secant, and Hybrid Methods to Find the Roots of a Polynomial
// Mustafa Yürük - 2020401204
#include <iostream> // Standard input/output stream
#include <cmath> // Mathematic functions

int limit = 100; // Limit for the number of iterations, you can adjust as needed otherwise program may run indefinitely
int element = 0; // Initiialize the number of coefficients so you can use it while taking command-line arguments
int iteration = 0; // Initialize the number of iterations so you can use it in hybrid after 2 iterations
bool Hybrid = true; // I initiliaze it as true so I will use it while calling bisect and secant function

// Function to implement a polynomial using CLI
double polynomial(double* coefficients, int degree, double x) {
    double result = 0; // Initialize result as 0 then sum coeffs
    for (int i = 0; i < degree; i++) { // Iterate over the coefficients and calculate the result just like a polynomial
        result += coefficients[i] * pow(x, degree - i - 1);
    }
    return result;
}

//secant method (I defined it above so I can call it in hybrid method)
double secant(double* coefficients, int n, double x0, double x1, double tolerance,int iterationNum, bool isHybrid) {
    double f0 = polynomial(coefficients, n, x0);
    double f1 = polynomial(coefficients, n, x1);
    double result = 0;
    while (std::fabs(x1 - x0) > tolerance) {
        result = x1 - f1 * (x1 - x0) / (f1 - f0); // Calculate the result using secant's algorithm
        double f2 = polynomial(coefficients, n, result); //Calculate f2 using polynom
        x0 = x1; // Update x0 for next iteration
        f0 = f1; // Update f0 for next iteration
        x1 = result; // Update x1 for next iteration
        f1 = f2;// Update f1 for next iteration
        iteration++;
        // If implementation is unable to converge with limit number of iterations then exit.
        if (iteration > limit) {
            std::cout << "Hybrid method is unable to converge" << std::endl;
            iteration = 0;
            return 0;
        }
    }
    if (!isHybrid) // If this is not hybrid then print secant result
    {
    std::cout << "Secant result: " << result << std::endl;
    iteration = 0;
    return result;}
    return 0;
}

//bisection method
double bisection(double* coefficients, int n, double x0, double x1, double tolerance, bool isHybrid) {
    double f0 = polynomial(coefficients, n, x0);
    double f1 = polynomial(coefficients, n, x1);
    double result = 0;
    while (std::fabs(x1 - x0) > tolerance) {
        result = (x0 + x1) / 2;
        double f2 = polynomial(coefficients, n, result);
        // Update x0, x1, and f0, f1 for next iteration
        if (f2 == 0) { // If f2 is zero then return the result
            return result;
        } else if (f0 * f2 < 0) { // If f0 and f2 have different signs then update x1 and f1
            x1 = result;
            f1 = f2;
        } else {
            x0 = result;
            f0 = f2;
        }
        if (isHybrid && iteration >= 2) { // If Hybrid is true and iteration is greater than 2 then use secant method
            secant(coefficients, n, x0, x1, tolerance, iteration, Hybrid);
            std::cout << "Hybrid result: " << result << std::endl;
            iteration = 0;
            return result;
            if(iteration > limit){
                std::cout << "Hybrid method is unable to converge" << std::endl;
                iteration = 0;
                return 0;
            }
        }
        iteration++;
        if (iteration > limit) { // If implementation is unable to converge with limit number of iterations then exit.
            std::cout << "Bisection method is unable to converge" << std::endl;
            iteration = 0;
            return 0;
        }
    }
    std::cout << "Bisection result: " << result << std::endl;
    iteration = 0;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc > 1) { // Check if command-line arguments are provided
        element = argc - 4; // Calculate the number of coefficients
        double* coefficients = new double[element];
        for (int i = 0; i < element; i++) {
            coefficients[i] = std::stod(argv[i + 1]);
        }
        double x0 = std::stod(argv[argc - 3]); // Second to last argument is x0
        double x1 = std::stod(argv[argc - 2]); // Third to last argument is x1
        double tolerance = std::stod(argv[argc - 1]); // Final argument is tolerance

        // As indicated in project pdf, x1 should be greater than x0
        if (x1 < x0) {
            std::cerr << "x1 should be greater than x0" << std::endl;
            return 1;
        }
        bisection(coefficients, element, x0, x1, tolerance, !Hybrid);// Bisection method, I used !Hybrid to make it false
        secant(coefficients, element, x0, x1, tolerance, 0, !Hybrid); // Secant method
        bisection(coefficients, element, x0, x1, tolerance, Hybrid); // Hybrid method, use Hybrid as true
        delete[] coefficients;// Deallocate the memory
    } else if (argc == 1){
    // If no command-line arguments are provided, exit.
        std::cerr << "No command-line arguments are provided" << std::endl;
    }
    return 0; //Successful exit
}
