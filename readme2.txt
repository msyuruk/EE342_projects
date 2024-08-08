Readme file for project-2: Mustafa Yürük
Normalized Power Iteration together with Deflation 

MSYS2 and Compilation:
To compile the c++ file, you can use MSYS2.
1- Ensure that the MSYS2 compiler is installed (You can download it from here:https://www.msys2.org/ if you are using Windows.)
Generally Mac and Linux devices have c++ compilers installed already.
2- You should add MSYS2 to your environment path. (For Windows users)
3- You can check if the compiler is installed with command "g++ --version". (For all OS)
4- In order to compile the .cpp file you can use this command "g++ project2.cpp -o <output_file_name>.exe.
For clarification, in the above command, g++ determines compiler, project2.cpp is the file that you want to compile, -o is the output flag, and the <output_file_name.exe> is the arbitrary executable name you want to create.
If you choose not to provide an output file name, it will create an executable named "a.exe" in Windows or "a.out" in Linux. (This situation may change according to the system you use, however it will not raise an error and create an executable anyway.).

After successfully compilation, how to run:
-You can run it with ".\<program_name.exe> <matrix_file> <tolerance> <output_file".
-The code takes 4 arguments, the first argument is the program itself (convention of c++), second argument is the matrix file, the third argument is the tolerance value which will determine the iteration limit and the fourth argument is the output file name which eigenvectors 1 and 2 and the eigenvalue will be written.
-Any other number of arguments will result in error.

Specifications:
-If you do not provide 4 arguments, the code will not execute.
-If the provided files cannot opened, the code will raise an error.
-The matrix is stored in dynamically allocated memory as requested.
-printMatrix and printVector functions are not necessary but they can be used to check the process.
-If the iteration does not converge in 20000 multiplication, the program will be forced to stop. You can adjust this limit in the Dominant function.
-Corollary of power iteration method, if there is no significantly dominant eigenvalue, the program will warn as eigenvectors might be irrelevant.

How this program works step by step unless it encounters an error:
1- Begin by checking number of arguments, if it is not 4 returns 1 and exits.
2- Obtain the tolerance value from input arguments and store it also initialize a matrixsize variable to use later.
3- Try to open matrix file, if it fails returns 2 and exits.
4- After opening matrix file, store the number of lines.
5- Using number of lines create dynamic arrays and store the matrix as array of arrays.
6- Initialize a random vector in order to use later to find the dominant eigenvector of the matrix.
7- Initialize the error as infinity and eigenvalue as -infinity, then enter into a loop that multiplies dynamically stored matrix and the random vector.
8- In the loop, normalize and compute Rayleigh quotient (I used this quotient because it gives appropriate signs for eigenvalues) to obtain the result until the difference between eigenvalues is lesser than tolerance value. If the tolerance value is reached obtain eigenvalue and eigenvector.
9- In Step 8 if the matrix is unable to converge for example a matrix with imaginary eigenvalues, force quit, print error message and return 4.
10- After finding both eigenvalue and eigenvector deflate the matrix by subtracting them.
11- Return to step 7 to find second eigenvalue with same procedure.
12- After finding second eigenvalue, deallocate memory for the matrix.
13- Try to open the output file, if it fails returns 3 and exits.
14- Write the results to the output file and close the file.
15- Successful run returns 0 and exits.
