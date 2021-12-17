+----------+
| Contents |
+----------+
input
This is a folder that contains 4 .txt files and some dummy C files.

sentiment_analysis.py
This is the python script that is called to perform the actual emotional analysis over each text file

sentiment_analysis.c
This is the main c file that takes the path to the directory, iterates and recurses through,
and starts a process for every txt file.

sentiment_analysis.h
A .h file that holds function declarations and structs.

Makefile
This allows user to compile the program with the make command.

+--------------+
| Instructions |
+--------------+
1. Compile the project with the make command

2. Run the program with a directory path as an argument
   e.g.
   ./sentiment_analysic input
   This is an example using the input folder that is in this project folder,
   so the argument does not require the entire path to the folder.

   ./sentiment Desktop/CSC213/lab
   This is an example of the path as an argument.

3. Many texts will appear in the terminal after running the program.
   After some time, the pie charts will start popping up in a new window.

4. Close all the windows of pie charts to exist the program.

+---------+
| Authors |
+---------+
Anil Alper, Haruko Okada, Leia Sohn
