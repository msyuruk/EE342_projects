Readme file for project-1: Mustafa Yürük
Gaussian elimination using partial pivoting.

MSYS2 and Compilation:
To compile the c++ file, you can use MSYS2.
1- Ensure that the MSYS2 compiler is installed (You can download it from here:https://www.msys2.org/ if you are using Windows.)
Generally Mac and Linux devices have c++ compilers installed already.
2- You should add MSYS2 to your environment path. (For Windows users)
3- You can check if the compiler is installed with command "g++ --version". (For all OS)
4- In order to compile the .cpp file you can use this command "g++ project1.cpp -o <output_file_name>.exe.
For clarification, in the above command, g++ determines compiler, project1.cpp is the file that you want to compile, -o is the output flag, and the <output_file_name.exe> is the arbitrary executable name you want to create.
If you choose not to provide an output file name, it will create an executable named "a.exe" (This situation may change according to the system you use, however it will not raise an error and create an executable anyway.).

After successfully compilation, how to run:
-You can run it with ".\<program_name.exe> <matrix_file> <vector_file>". Using "Tab" key will automatically complete the file name, if you are on the correct path.
-The code takes 3 arguments, the first argument is the program itself (convention of c++), second argument is the matrix file and the third argument is the vector file.
-Any other number of arguments will result in error.

Specifications:
-Code's behaviour and logic is commented in the project1.cpp file as requested.
-If the provided files cannot opened, the code will raise an error.
-If the matrix you provided is singular, the code will raise an error.
-If the input matrix is 2x2, the code will calculate and print out the condition numbers of 1 and infinity.
-The matrix and the vector are stored in dynamically allocated memory as requested.
-Since there are 14 numbers after the decimal points in the example matrices, the precision is set for 15.
-IEEE standard for precision is 2^-52 (almost 10^-15) however in order to increase stability, any number absolutely smaller than 10^-14 is manually rounded to 0. (Which makes A8, A9 and A10 matrices singular.)

How this program works step by step unless it encounters an error:
1-Check number of arguments. (Failure returns 1)
2-Try to open the matrix file. (Failure returns 2)
3-Try to open the vector file. (Failure returns 3)
4-Read elements of matrix from file and store it in a temporary vector of vectors.
5-Move the elements from temporary vector of vectors to dynamic memory.
6-Store the vector elements in dynamic memory.
7-Check if matrix is 2x2 to print condition numbers.
8-Use Gaussian elimination
9-Check if the matrix is singular. (Singular matrix returns 4)
10-Try to open/create a solution file named x.txt. (Failure returns 5)
11-Write the solution vector to the solution file.
12-After successfully completion, deallocate memory. (Successful run returns 0)

The case of high condition numbers:
In this program, the example matrix of A = [1.000 1.000; 1.000 1.001] for b1 = [2.000; 2.000] and b2 = [2.000; 2.001] was ran.
The solutions were x1 = [2; 0] and x2= [1.000;1.000], these solutions can be viewed if the script is ran with these matrix and vector files.
This contrast demonstrates that matrices with high condition numbers are more susceptible to changes in the input vector. In contrast, matrices with lower condition numbers exhibit less sensitivity to such changes. 
This sensitivity poses challenges in numerical computations, as small errors or perturbations in input data can lead to significant discrepancies in the solution. 
Therefore, it's essential to consider the condition number of matrices when analyzing the stability and reliability of numerical algorithms.
