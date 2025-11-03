#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

const char* FILENAME = "students.dat";

// The 'struct' that defines our Student "schema" 
struct Student {
    int roll_no;
    char name[50];
    int marks_c;
    int marks_math;
    int marks_physics;
    int total;
    char grade;
};

//  Function Prototypes (Declarations) 
void add_student();
void display_all_students();
void search_student();
void modify_student();
void delete_student();
char calculate_grade(int total);
void clear_screen();
void press_enter_to_continue();
void clear_input_buffer();

// Main Function (The Menu) 
int main() {
    int choice;

    while (1) {
        clear_screen();
        printf("========================================\n");
        printf("   Student Grade Management System\n");
        printf("========================================\n");
        printf("   1. Add New Student\n");
        printf("   2. Display All Students\n");
        printf("   3. Search for a Student\n");
        printf("   4. Modify a Student's Record\n");
        printf("   5. Delete a Student's Record\n");
        printf("   0. Exit Program\n");
        printf("----------------------------------------\n");
        printf("   Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input
            printf("\nInvalid input. Please enter a number.\n");
            clear_input_buffer();
            press_enter_to_continue();
            continue;
        }

        // Clear the input buffer after scanf
        clear_input_buffer();

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_all_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                modify_student();
                break;
            case 5:
                delete_student();
                break;
            case 0:
                printf("\nThank you for using the system. Goodbye!\n");
                exit(0); // Exit the program
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        press_enter_to_continue();
    }
    return 0;
}

// Utility Functions 
char calculate_grade(int total) {
    float avg = (float)total / 3.0;
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

// 1 Add a New Student
void add_student() {
    struct Student s;
    FILE* fp;

    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }

    clear_screen();
    printf("--- Add New Student ---\n");
    
    printf("Enter Roll No: ");
    scanf("%d", &s.roll_no);
    clear_input_buffer(); // Clear buffer after scanf

    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0; 

    printf("Enter Marks in C: ");
    scanf("%d", &s.marks_c);

    printf("Enter Marks in Math: ");
    scanf("%d", &s.marks_math);

    printf("Enter Marks in Physics: ");
    scanf("%d", &s.marks_physics);

    // Calculate total and grade
    s.total = s.marks_c + s.marks_math + s.marks_physics;
    s.grade = calculate_grade(s.total);

    // Write the entire struct to the file
    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);
    printf("\nStudent record added successfully!\n");
}

// 2 Display All Students (READ)
void display_all_students() {
    struct Student s;
    FILE* fp;

    // Open file in "read binary" mode
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("File not found or no records exist.\n");
        return;
    }

    clear_screen();
    printf("--- All Student Records ---\n\n");
    
    // Print table header
    printf("%-10s %-20s %-5s %-5s %-7s %-7s %-5s\n", 
           "Roll No", "Name", "C", "Math", "Physics", "Total", "Grade");
    printf("----------------------------------------------------------------------\n");

    // Read and print every record from the file
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("%-10d %-20s %-5d %-5d %-7d %-7d %-5c\n",
               s.roll_no, s.name, s.marks_c, s.marks_math, 
               s.marks_physics, s.total, s.grade);
    }

    printf("----------------------------------------------------------------------\n");
    fclose(fp);
}

// 3 Search a Student (READ)
void search_student() {
    struct Student s;
    FILE* fp;
    int roll_to_search, found = 0;

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("File not found or no records exist.\n");
        return;
    }

    printf("Enter Roll No to search: ");
    scanf("%d", &roll_to_search);

    clear_screen();
    printf("--- Search Result ---\n");

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll_no == roll_to_search) {
            printf("\nRecord Found!\n\n");
            printf("Roll No: %d\n", s.roll_no);
            printf("Name: %s\n", s.name);
            printf("C Marks: %d\n", s.marks_c);
            printf("Math Marks: %d\n", s.marks_math);
            printf("Physics Marks: %d\n", s.marks_physics);
            printf("Total Marks: %d\n", s.total);
            printf("Grade: %c\n", s.grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRecord with Roll No %d not found.\n", roll_to_search);
    }

    fclose(fp);
}

// 4 Modify a Student (UPDATE)
void modify_student() {
    struct Student s;
    FILE* fp;
    int roll_to_modify, found = 0;
    long record_size = sizeof(struct Student);

    // Open in "read-write binary" mode
    fp = fopen(FILENAME, "r+b"); 
    if (fp == NULL) {
        printf("File not found or no records exist.\n");
        return;
    }

    printf("Enter Roll No to modify: ");
    scanf("%d", &roll_to_modify);
    clear_input_buffer();

    while (fread(&s, record_size, 1, fp) == 1) {
        if (s.roll_no == roll_to_modify) {
            found = 1;
            clear_screen();
            printf("--- Modifying Record for Roll No: %d ---\n", s.roll_no);
            printf("Old Name: %s\n", s.name);
            
            // Get new data
            printf("Enter New Name: ");
            fgets(s.name, 50, stdin);
            s.name[strcspn(s.name, "\n")] = 0; 

            printf("Enter New Marks in C: ");
            scanf("%d", &s.marks_c);

            printf("Enter New Marks in Math: ");
            scanf("%d", &s.marks_math);

            printf("Enter New Marks in Physics: ");
            scanf("%d", &s.marks_physics);

            // Recalculate
            s.total = s.marks_c + s.marks_math + s.marks_physics;
            s.grade = calculate_grade(s.total);

            // Move to the beginning of the record
            fseek(fp, -record_size, SEEK_CUR); 
            
            fwrite(&s, record_size, 1, fp); 

            printf("\nRecord updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\nRecord with Roll No %d not found.\n", roll_to_modify);
    }

    fclose(fp);
}

// 5. Delete a Student (DELETE)
void delete_student() {
    struct Student s;
    FILE *fp_original, *fp_temp;
    int roll_to_delete, found = 0;
    const char* TEMP_FILENAME = "temp.dat";

    // Open original file for reading
    fp_original = fopen(FILENAME, "rb");
    if (fp_original == NULL) {
        printf("File not found or no records exist.\n");
        return;
    }

    // Open temp file for writing
    fp_temp = fopen(TEMP_FILENAME, "wb");
    if (fp_temp == NULL) {
        printf("Error: Cannot create temporary file.\n");
        fclose(fp_original);
        return;
    }

    printf("Enter Roll No to delete: ");
    scanf("%d", &roll_to_delete);

    // Read records from original file and write to temp file
    while (fread(&s, sizeof(struct Student), 1, fp_original) == 1) {
        if (s.roll_no == roll_to_delete) {
            found = 1; // Mark as found, but DO NOT write to temp file
        } else {

            fwrite(&s, sizeof(struct Student), 1, fp_temp);
        }
    }

    fclose(fp_original);
    fclose(fp_temp);

    // Replace original file with temp file
    if (found) {
        remove(FILENAME);  
        rename(TEMP_FILENAME, FILENAME); 
        printf("\nRecord with Roll No %d deleted successfully.\n", roll_to_delete);
    } else {
        remove(TEMP_FILENAME); 
        printf("\nRecord with Roll No %d not found.\n", roll_to_delete);
    }
}


//Utility Functions 
void clear_screen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For macOS/Linux
    #endif
}


void press_enter_to_continue() {
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Wait for the Enter key
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
