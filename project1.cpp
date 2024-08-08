// EE342 Project-1 Mustafa Yürük 2020401204
#include <iostream> // For standard input/output
#include <fstream> // For file input/output
#include <vector> // For dynamic arrays
#include <sstream> // For string stream
#include <limits> // For numeric limits
#include <cmath> // For mathematical functions
#include <iomanip> // For setting precision

// The floating point precision is set accordingly, since there are 14 numbers after the decimal point.
int setprecision = 15;

// Define a small precision value for machine error. Any value smaller than this number is considered to be zero
long double precision = pow(10, -14);

// Function to check for machine precision to avoid numerical errors (the precision number is defined above)
long double epsilon(long double element){
    if (fabs(element) < precision){
        return 0;
    }
    return element;
}

// Function to deallocate memory for the matrix to avoid memory leaks
void deallocateMatrix(long double** matrix, int size) {
    for (int row = 0; row < size; ++row) {
        delete[] matrix[row];
    }
    delete[] matrix;
}

// Function to print matrix to check if it was read and stored correctly in dynamic memory
void printMatrix(long double** matrix, int size) {
    std::cout << "Matrix: " << std::endl;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            std::cout << std::fixed << std::setprecision(setprecision) << matrix[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to print vector to check if it was read correctly from the file
void printVector(long double* vector, int size) {
    std::cout << "Vector: " << std::endl;
    for (int row = 0; row < size; ++row) {
        std::cout << std::fixed <<std::setprecision(setprecision) << vector[row] << std::endl;
    }
}

// Function to calculate determinant of a square matrix recursively
long double determinant(long double** matrix, int size) {
    // Initialize the determinant as 0
    long double det = 0;
    // Basic formula for 2x2 matrix: ad - bc 
    if (size == 2) {
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        // Check for machine epsilon to avoid numerical errors
        det = epsilon(det);
        return det;
    }
    // Recursive case using submatrices in order to determine the determinant for larger matrices
    else {
        // Allocate memory for submatrix
        long double** submatrix = new long double*[size - 1];
        for (int row = 0; row < size - 1; ++row) {
            submatrix[row] = new long double[size - 1];
        }
        for (int col = 0; col < size; ++col) {
            int subrow = 0; // submatrix row index
            for (int m = 1; m < size; ++m) {
                int subcol = 0; // submatrix column index
                for (int n = 0; n < size; ++n) {
                    if (n == col) {
                        continue;
                    }
                    submatrix[subrow][subcol] = matrix[m][n];
                    // Check for machine epsilon to avoid numerical errors
                    submatrix[subrow][subcol] = epsilon(submatrix[subrow][subcol]);
                    ++subcol;
                }
                ++subrow;
            }
            // Add or subtract the determinant of the submatrix to the determinant of the current matrix
            if (col % 2 == 0) {
                det += matrix[0][col] * determinant(submatrix, size - 1);
            }
            else {
                det -= matrix[0][col] * determinant(submatrix, size - 1);
            }
        }
        // Deallocate memory for submatrix to avoid memory leaks
        deallocateMatrix(submatrix, size - 1);
        // Return the determinant
        return det;
    }
}

// Function to check if a matrix is singular
bool isMatrixSingular(long double** matrix, int size) {
    // Check if the determinant is zero
    long double det = determinant(matrix, size);
    // Check for machine epsilon to avoid numerical errors
    det = epsilon(det);
    // If the determinant is zero or NaN, the matrix is singular
    if (det == 0 || std::isnan(det)) {
        return true;
    }
    // Else, the matrix is not singular
    return false;
}

// Gaussian elimination function with partial pivoting
void gaussianElimination(long double** matrix, long double* vector, int size) {
    // Iterate over the rows of the matrix for forward elimination
    for (int currentRow = 0; currentRow < size - 1; ++currentRow) {
        // Find the pivot row for partial pivoting (row with the largest absolute value in the current column)
        // Initialize the pivot row as the current row
        int pivotRow = currentRow;
        // Initialize the maximum value as the absolute value of the current element
        long double maxVal = abs(matrix[currentRow][currentRow]);
        // Check for machine epsilon to avoid numerical errors
        maxVal = epsilon(maxVal);
        // Iterate over the rows below the current row to find the pivot row
        for (int rowBelow = currentRow + 1; rowBelow < size; ++rowBelow) {
            // If the current element has a greater absolute value, update the pivot row
            if (abs(matrix[rowBelow][currentRow]) > maxVal) {
                maxVal = abs(matrix[rowBelow][currentRow]);
                // Check for machine epsilon to avoid numerical errors
                maxVal = epsilon(maxVal);
                pivotRow = rowBelow;
            }
        }
        // Swap the current row with the pivot row if necessary
        if (pivotRow != currentRow) {
            std::swap(matrix[currentRow], matrix[pivotRow]);
            std::swap(vector[currentRow], vector[pivotRow]);
        }
        // Eliminate elements below the diagonal in the current column
        for (int rowToEliminate = currentRow + 1; rowToEliminate < size; ++rowToEliminate) {
            long double factor = matrix[rowToEliminate][currentRow] / matrix[currentRow][currentRow];
            // Check for machine epsilon to avoid numerical errors
            factor = epsilon(factor);
            for (int columnToUpdate = currentRow; columnToUpdate < size; ++columnToUpdate) {
                // Apply the elimination factor to each element in the row
                matrix[rowToEliminate][columnToUpdate] -= factor * matrix[currentRow][columnToUpdate];
                // Check for machine epsilon to avoid numerical errors
                matrix[rowToEliminate][columnToUpdate] = epsilon(matrix[rowToEliminate][columnToUpdate]);
            }
            // Update the corresponding element in the vector
            vector[rowToEliminate] -= factor * vector[currentRow];
            // Check for machine epsilon to avoid numerical errors
            vector[rowToEliminate] = epsilon(vector[rowToEliminate]);
        }
        // Print the matrix and vector after each step for debugging purposes
        /*
        printMatrix(matrix, size);
        printVector(vector, size);
        */
    }

    // Back substitution to find the solution vector
    for (int currentRow = size - 1; currentRow >= 0; --currentRow) {
        long double sum = 0.0;
        // Calculate the sum for the current row
        for (int column = currentRow + 1; column < size; ++column) {
            sum += matrix[currentRow][column] * vector[column];
        }
        // Solve for the current variable in the vector
        vector[currentRow] = (vector[currentRow] - sum) / matrix[currentRow][currentRow];
        // Check for machine epsilon to avoid numerical errors
        vector[currentRow] = epsilon(vector[currentRow]);
    }
}

// Function to calculate condition numbers for 2x2 matrices
void ConditionNumbers(long double** matrix) {
    // Extract the elements of the matrix. Assume matrix is [a b; c d]
    long double a = matrix[0][0];
    long double b = matrix[0][1];
    long double c = matrix[1][0];
    long double d = matrix[1][1];

    // Calculate the determinant using standard formula ad - bc
    long double det = a * d - b * c;

    // Extract the elements of the inverse matrix using the formula
    long double aInv = d / det;
    long double bInv = -b / det;
    long double cInv = -c / det;
    long double dInv = a / det;

    // 1 norm is the maximum column sum and infinity norm is the maximum row sum
    // Calculate the norms of the matrix
    long double oneNorm = std::max(std::abs(a) + std::abs(c), std::abs(b) + std::abs(d));
    long double infNorm = std::max(std::abs(a) + std::abs(b), std::abs(c) + std::abs(d));

    // Calculate the norms of the inverse matrix
    long double oneNormInv = std::max(std::abs(aInv) + std::abs(cInv), std::abs(bInv) + std::abs(dInv));
    long double infNormInv = std::max(std::abs(aInv) + std::abs(bInv), std::abs(cInv) + std::abs(dInv));

    // Calculate the condition numbers
    long double conditionNumber1 = oneNorm * oneNormInv;
    long double conditionNumberInf = infNorm * infNormInv;

    // Print out the condition numbers
    // https://www.omnicalculator.com/math/condition-number can be used to check the results
    std::cout << "Condition number (1-norm): " << conditionNumber1 << std::endl;
    std::cout << "Condition number (infinity-norm): " << conditionNumberInf << std::endl;
}

// Main function
int main(int argc, char* argv[]) {
    // Check if the number of CLI arguments is appropriate. It should be 3: the program name, the matrix file, and the vector file
    if (argc != 3) {
        std::cerr << "Invalid number of arguments." << std::endl;
        return 1;
    }

    // Initialize a singular flag to check if the matrix is singular
    bool Singularity = false;

    // Open the matrix file and check if it is opened successfully
    std::ifstream matrixFile(argv[1]);
    if (!matrixFile.is_open()) {
        std::cerr << "Failed to open matrix file: " << argv[1] << std::endl;
        return 2;
    }

    // Open the vector file and check if it is opened successfully
    std::ifstream vectorFile(argv[2]);
    if (!vectorFile.is_open()) {
        std::cerr << "Failed to open vector file: " << argv[2] << std::endl;
        return 3;
    }

    // Read the matrix elements from the file
    std::vector<std::vector<long double>> tempMatrix;
    std::string line;
    while (std::getline(matrixFile, line)) {
        // Parse the line and store the elements in a vector
        std::vector<long double> row;
        // Use istringstream to parse the line
        std::istringstream iss(line);
        // Read the elements from the line and store in the vector
        long double value;
        while (iss >> value) {
            // Store the elements in the vector
            row.push_back(value);
        }
        // Store the row vector in the matrix
        tempMatrix.push_back(row);
    }
    // Save the matrix size to a variable
    int matrixSize = tempMatrix.size();
    // Close the matrix file after reading the elements
    matrixFile.close();
    // Allocate memory for the matrix using dynamic memory allocation
    long double** matrixArray = new long double*[matrixSize];
    for (int currentRow = 0; currentRow < matrixSize; ++currentRow) {
        // Allocate memory for each row
        matrixArray[currentRow] = new long double[tempMatrix[currentRow].size()];
        for (int currentColumn = 0; currentColumn < tempMatrix[currentRow].size(); ++currentColumn) {
            // Copy the elements from the 2D vector to the dynamically allocated memory row by row
            matrixArray[currentRow][currentColumn] = tempMatrix[currentRow][currentColumn];
        }
    }

    // Read the vector elements from the file and store in dynamically allocated memory
    long double* vector = new long double[matrixSize]; // Matrix size is the same as the vector size since it is a requirement
    for (int i = 0; i < matrixSize; ++i) {
        // Read the elements from the file and store in the vector
        vectorFile >> vector[i];
    }

    // Close the vector file after reading the elements
    vectorFile.close();

    // Check if the matrix is 2x2 and print condition numbers if it is 2x2
    if (matrixSize == 2) {
        ConditionNumbers(matrixArray);
    }
    // Else, continue. The condition numbers are only calculated for 2x2 matrices.

    // Print the matrix and vector for debugging purposes to check if they were read correctly
    //printMatrix(matrixArray, matrixSize);
    //printVector(vector, matrixSize);

    // Gaussian elimination with partial pivoting
    gaussianElimination(matrixArray, vector, matrixSize);

    // Print the determinant of the matrix for debugging purposes
    //std::cout << "Determinant: " << determinant(matrixArray, matrixSize) << std::endl;

    // Check if the matrix is singular
    Singularity = isMatrixSingular(matrixArray, matrixSize);
    // If the matrix is singular, enter if block
    if (Singularity) {
        // Print an error message
        std::cerr << "Matrix is singular. Aborting program." << std::endl;
        // Deallocate memory for matrixArray in order to avoid memory leaks
        deallocateMatrix(matrixArray, matrixSize);
        return 4;
    }

    // Print the solution vector to check if it was calculated correctly for debugging purposes
    std::cout << "Solution ";
    printVector(vector, matrixSize);

    // Check if the solution file can be created
    std::ofstream solutionFile("x.txt");
    if (!solutionFile.is_open()) {
        // If the solution file cannot be created, print an error message
        std::cerr << "Failed to create a solution file." << std::endl;
        // Deallocate memory for matrixArray and vector to avoid memory leaks
        deallocateMatrix(matrixArray, matrixSize);
        delete[] vector;
        return 5;
    }

    // Write the solution vector to the solution file
    for (int i = 0; i < matrixSize; ++i) {
        solutionFile << std::fixed << std::setprecision(setprecision) << vector[i] << std::endl;
    }
    solutionFile.close();

    // Deallocate memory for matrixArray and vector to avoid memory leaks
    deallocateMatrix(matrixArray, matrixSize);
    delete[] vector;

    // Return 0 to indicate successful execution of the program
    return 0;
}
