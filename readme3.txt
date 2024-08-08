Readme file for project-3: Mustafa Yürük
Bisection, Secant and Hybrid Methods
The code's behaviour and logic is commented in the project3.cpp file as requested.

MSYS2 and Compilation:
To compile the c++ file, you can use MSYS2.
1- Ensure that the MSYS2 compiler is installed (You can download it from here:https://www.msys2.org/ if you are using Windows.)
Generally Mac and Linux devices have c++ compilers installed already.
2- You should add MSYS2 to your environment path. (For Windows users)
3- You can check if the compiler is installed with command "g++ --version". (For all OS)
4- In order to compile the .cpp file you can use this command "g++ project3.cpp -o <output_file_name>.exe.
For clarification, in the above command, g++ determines compiler, project3.cpp is the file that you want to compile, -o is the output flag, and the <output_file_name.exe> is the arbitrary executable name you want to create.
If you choose not to provide an output file name, it will create an executable named "a.exe" in Windows or "a.out" in Linux. (This situation may change according to the system you use, however it will not raise an error and create an executable anyway.).

How to run it:
After compiling the code you can run it with ".\<output_file_name.exe> 2 2 -7 1 -7 1.5 1.8 0.001" (2 2 -7 1 -7 1.5 1.8 0.001 is for example.)
The program will take n + 5 input arguments.
First one is the program name (c++ convention)
Last one is the tolerance value.
Second last is the x1 value.
Third last is the x0 value.
As requested x1 has to be bigger than the x0. Otherwise program will exit.
The remaining input arguments (n+1) will create a nth order polynomial.

Specifications:
If the appropriate type and numbers of arguments are given, program will create a polynomial then it will use bisect, secant and hybrid method, using the tolerance and limit values.
In order to prevent program running indefinitely, a limit number is added, if the program is unable to approach the tolerance value, it will exit that function after the number of limit iterations are reached. You can adjust the limit number of iterations from the cpp file (default 100).
Instead of creating a seperate hybrid function, I created a boolean for hybrid function, when this boolean value used while calling bisection and secant methods that functions will behave accordingly.
In order to transform bisection to secant in hybrid method, I used global iteration value, when a function returns a value, it will also reset this iteration to 0 so there will be no problem.
If you give x1 > x0, code will raise an error and exit.
