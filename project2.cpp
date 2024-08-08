// EE342 Project 2: Normalized Power Iteration Method to Find Dominant Eigenvalues and Eigenvectors - Mustafa Yürük - 2020401204
#include <iostream>
#include <fstream> // File stream library
#include <sstream>// SS library to read file
#include <cmath>// Mathematic library
#include <random> // Random library to generate vector
#include <limits> // Numeric limit to use inf
#include <chrono>// Time library to use in vector

//Read a matrix from a file into a dynamically array
double** readMatrixFromFile(const std::string& filename, int& size) {
    std::ifstream matrixFile(filename);
    if (!matrixFile.is_open()) {
        std::cerr << "Failed to open matrix file: " << filename << std::endl;
        exit(2);}
    // First, calculate the size of the matrix by counting the number of lines in the file
    std::string line;
    size = 0;
    while (std::getline(matrixFile, line)) {
        ++size;
    }
    // Reset the file stream to read the data
    matrixFile.clear();
    matrixFile.seekg(0, std::ios::beg);
    double** matrix = new double*[size];   // Allocate memory for the matrix using dynamic memory allocation
    for (int i = 0; i < size; ++i) {
        matrix[i] = new double[size];
    }
    int row = 0;   // Read the matrix elements into the dynamically allocated array
    while (std::getline(matrixFile, line)) {
        std::istringstream iss(line);
        for (int column = 0; column < size; ++column) {
            iss >> matrix[row][column];
        }
        ++row;}
    matrixFile.close();
    return matrix;
}
// Function to avoid memory leak
void deallocateMatrix(double** matrix, int size) {
    for (int row = 0; row < size; ++row) {
        delete[] matrix[row];}
    delete[] matrix;
}

void printMatrix(double** matrix, int size) { // Function to see matrix (not necessary)
    std::cout << "Matrix: " << std::endl;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            std::cout << matrix[row][column] << " ";
        }std::cout << std::endl;}}

void printVector(double* vector, int size) { // Function to see vector
    for (int i = 0; i < size; ++i) {
        std::cout << vector[i] << " ";
    }std::cout << std::endl;
}

//Compute dot product
double dot_product(double* vector1, double* vector2, int size) {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += vector1[i] * vector2[i];}
    return result;
}

//Generate a random vector
double* generateRandomVector(int size) {
    double* randomVector = new double[size];
    std::random_device rd; // Generate seed
    // Use current moment
    std::mt19937 gen(rd() + std::chrono::steady_clock::now().time_since_epoch().count());
    // Generate numbers between 1.0 and 10.0
    std::uniform_real_distribution<double> dis(1.0, 10.0);
    for (int i = 0; i < size; ++i) {
        randomVector[i] = dis(gen);
    }return randomVector;
}

//matrix-vector multiplication
double* matrixVectorMultiply(double** matrix, double* vector, int len) {
    double* result = new double[len];
    for (int i = 0; i < len; ++i) {
        result[i] = 0.0;
        for (int j = 0; j < len; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }    }    return result;}
double normalize(double* vector, int size) { // Makes a vector's size 1
    double norm = 0.0;
    for (int ind = 0; ind < size; ++ind) {
        norm += vector[ind] * vector[ind];// Compute the squared sum
    }
    norm = std::sqrt(norm);
    for (int ele = 0; ele < size; ++ele) {
        vector[ele] /= norm;// Divide each element by norm
    }
    return norm;
}

//compute the Rayleigh quotient
double computeRayleighQuotient(double** matrix, double* vector, int size) {
    double* Av = matrixVectorMultiply(matrix, vector, size);
    double numerator = dot_product(vector, Av, size); // Compute numerator
    double denominator = dot_product(vector, vector, size); // Compute the denominato
    delete[] Av; // Clean up result
    return numerator / denominator;
}
//Find the dominant eigenvector using the power method
double Dominant(double** matrix, double* vector, int size, double tolerance, int limit = 20000) { // Avoid infinite loop
    double error = std::numeric_limits<double>::infinity();
    double previousEigenvalue = -std::numeric_limits<double>::infinity(); // Initialize the eigenvalue as small number
    int iteration = 0;
    while(error > tolerance){
        // Perform matrix-vector multiplication
        double* result = matrixVectorMultiply(matrix, vector, size); // Multiply the matrix
        normalize(result, size); // Normalize the result vector
        double eigenvalue = computeRayleighQuotient(matrix, result, size); // Compute Rayleigh quotient
        error = std::fabs(eigenvalue - previousEigenvalue);
        previousEigenvalue = eigenvalue; // Update eigenvalue
        for (int i = 0; i < size; ++i) {vector[i] = result[i];} // Update vector
        delete[] result;// Deallocate
        ++iteration;
        if (iteration == limit) // Check iteration limit
        {std::cerr << "Matrix is unable to converge to an eigenvalue within the given tolerance!"<<std::endl;
        exit(4);//Exit the program with an error code 4.
        }
    }return previousEigenvalue;
}

int main(int argc, char* argv[]) {// Check if CLI arguments is 4
    if (argc != 4) {
        std::cerr << "Wrong number of arguments."<< std::endl;return 1;}
    
    double tolerance = std::stod(argv[2]);  //Obtain the tolerance argv2
    int matrixSize;//Initialize a matrix size
    double** matrix = readMatrixFromFile(argv[1], matrixSize); //read the matrix
    double* randomVector1 = generateRandomVector(matrixSize);  //ınitialize a random vector
    double eigenvalue1 = Dominant(matrix, randomVector1, matrixSize, tolerance);// Find eigenvalue and eigenvector
    printVector(randomVector1, matrixSize);
    std::cout << "Eigenvalue#1: " << eigenvalue1 << std::endl;

    // Deflate matrix
    for (int row = 0; row < matrixSize; ++row) {
        for (int clo = 0; clo < matrixSize; ++clo) {
            matrix[row][clo] -= eigenvalue1 * randomVector1[row] * randomVector1[clo]; //subtract product
        }
    }

    // SECOND EIGENVALUE
    // Create a new random vector 
    double*randomVector2 = generateRandomVector(matrixSize);
    double eigenvalue2 = Dominant(matrix, randomVector2, matrixSize, tolerance); // Find the second dominant eigenvector and eigenvalue
    std::cout << "Eigenvalue#2: " << eigenvalue2 << std::endl;// Print the eigenvalue
    deallocateMatrix(matrix, matrixSize); // Deallocate memory

    std::ofstream outputFile(argv[3]); //Take argument3
    if (!outputFile.is_open()) { // Try to open the output file
        std::cerr << "Failed to open output file: " << argv[3] << std::endl;
        return 3;
    } // Write to the file.
    outputFile << "Eigenvalue#1: " << eigenvalue1 << std::endl;
    for (int row = 0; row < matrixSize; ++row) {outputFile << randomVector1[row] << std::endl;   }
    outputFile << "Eigenvalue#2: " << eigenvalue2 << std::endl;
    outputFile.close();

    if (fabs(eigenvalue1 - eigenvalue2) < 1)//Print a warning message if the eigenvalues too close
    {std::cerr << "Warning : Eigenvalues with close absolute values may cause inappropriate and/or irrelevant results." << std::endl;}
    delete[] randomVector1; //Deallocate memories
    delete[] randomVector2;
    return 0;
}
