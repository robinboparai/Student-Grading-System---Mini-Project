# Student Grade Management System 🎓

This is a C-based console application for my 1st Semester BCA project. It allows a user to manage student records (add, search, modify, and delete) which are saved to a `students.dat` file.

## Environment

* **Language:** C
* **Compiler:** GCC (MinGW on Windows)
* This code is standard C and should compile on any system with GCC.

## 🚀 How to Compile and Run

1.  **Clone the Repository**
    ```bash
    git clone https://github.com/robinboparai/Student-Grading-System---Mini-Project.git
    cd Student-Grading-System---Mini-Project
    ```

2.  **Compile the Program**
    Open a terminal (like in VS Code) and run the following command:
    ```bash
    gcc student.c -o student.exe
    ```
    *(On macOS or Linux, you might use `gcc student.c -o student`)*

3.  **Run the Program**
    Once compiled, run the executable:
    ```bash
    ./student.exe
    ```
    *(On macOS or Linux: `./student`)*

## Features

* **Add Student:** Saves a new student record to `students.dat`.
* **Display All Students:** Reads and displays all records from `students.dat`.
* **Search Student:** Finds a student by their Roll Number.
* **Modify Student:** Updates the record of an existing student.
* **Delete Student:** Removes a student's record from the file.
