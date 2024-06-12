# Task Management System Documentation

This Task Management System is a C program that allows users to sign up, log in, add tasks, view tasks, and delete their accounts. The program uses text files to store user credentials and task information.

## Table of Contents

1. [Features](#features)
2. [File Structure](#file-structure)
3. [Functions](#functions)
    - [sign_up](#sign_up)
    - [login](#login)
    - [add_task](#add_task)
    - [view_tasks](#view_tasks)
    - [delete_account](#delete_account)
4. [Main Function](#main-function)
5. [Usage](#usage)
6. [Example](#example)

## Features

- User Registration (Sign Up)
- User Login
- Add Task
- View Tasks
- Delete Account

## File Structure

- `signup.txt`: Stores user credentials in the format `username password`.
- `tasks.txt`: Stores tasks in the format `username date task_description`.

## Functions

### sign_up

```c
void sign_up();
```

Prompts the user to enter a username and password, then saves these credentials to `signup.txt`.

### login

```c
int login(char *username, char *password);
```

Prompts the user to enter their username and password, then checks if the entered credentials match any in `signup.txt`. If successful, it returns 1 and stores the credentials in the provided pointers. Otherwise, it returns 0.

### add_task

```c
void add_task(char *username);
```

Prompts the user to enter a date and task description, then saves the task to `tasks.txt` with the associated username.

### view_tasks

```c
void view_tasks(char *username);
```

Prompts the user to enter a date, then displays all tasks for that date associated with the logged-in username.

### delete_account

```c
void delete_account(char *username, char *password);
```

Prompts the user to re-enter their username and password. If the credentials match, the function removes the user's entry from `signup.txt`.

## Main Function

### main

```c
int main();
```

The entry point of the program. Provides a menu-driven interface for users to sign up, log in, add tasks, view tasks, and delete their accounts. The program runs in a loop until the user chooses to exit.

## Usage

1. **Compile the Program**

   ```sh
   gcc task_management.c -o task_management
   ```

2. **Run the Program**

   ```sh
   ./task_management
   ```

3. **Main Menu Options**

   - **Sign Up**: Create a new account.
   - **Login**: Log in to an existing account.
   - **Exit**: Exit the program.

4. **Logged-In Menu Options**

   - **Add Task**: Add a task for the logged-in user.
   - **View Tasks**: View tasks for a specific date.
   - **Delete Account**: Delete the logged-in user's account.
   - **Exit**: Log out and return to the main menu.

## Example

### Sign Up

```
Enter your username: user1
Enter your password: pass1
Sign up successful!
```

### Login

```
Enter your username: user1
Enter your password: pass1
Login successful!
```

### Add Task

```
Enter the date (DD/MM/YYYY): 12/06/2024
Enter the task description: Task1
Task added successfully!
```

### View Tasks

```
Enter the date to view tasks (DD/MM/YYYY): 12/06/2024
Task: 12/06/2024 Task1
```

### Delete Account

```
Enter your username: user1
Enter your password: pass1
Account deleted successfully.
```

## Notes

- The program reads and writes to text files (`signup.txt` and `tasks.txt`) in the same directory.
- Ensure proper file handling and check for potential errors in file operations.
- The program assumes usernames and passwords do not contain spaces.
This program allows users to sign up, log in, add tasks, view tasks, and delete their accounts. Below is a detailed explanation of each part of the code:

## Code Explanation

### Includes and Function Prototypes
The code includes the necessary standard libraries for input/output operations and string manipulation. It defines the function prototypes for the functions used in the program.

```c
#include <stdio.h>
#include <string.h>

// Function prototypes
void sign_up();
int login(char *username, char *password);
void add_task(char *username);
void view_tasks(char *username);
void delete_account(char *username, char *password);
```

### Sign-Up Function
The `sign_up` function allows users to create a new account by entering a username and password. The credentials are then saved to the `signup.txt` file.

```c
void sign_up() {
    char username[50], password[50];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    FILE *file = fopen("signup.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
        printf("Sign up successful!\n");
    } else {
        printf("Error in sign up. Please try again.\n");
    }
}
```

### Login Function
The `login` function checks if the entered username and password match any existing credentials in the `signup.txt` file. If a match is found, it returns 1 indicating a successful login; otherwise, it returns 0.

```c
int login(char *username, char *password) {
    char input_username[50], input_password[50];
    printf("Enter your username: ");
    scanf("%s", input_username);
    printf("Enter your password: ");
    scanf("%s", input_password);

    FILE *file = fopen("signup.txt", "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char *token1 = strtok(line, " ");
            char *token2 = strtok(NULL, " ");
            token2[strcspn(token2, "\n")] = 0;

            if (strcmp(token1, input_username) == 0 && strcmp(token2, input_password) == 0) {
                strcpy(username, input_username);
                strcpy(password, input_password);
                fclose(file);
                printf("Login successful!\n");
                return 1;
            }
        }
        fclose(file);
    }
    printf("Invalid credentials. Please try again.\n");
    return 0;
}
```

### Add Task Function
The `add_task` function allows logged-in users to add a task by providing a date and a task description. The task is saved in the `tasks.txt` file.

```c
void add_task(char *username) {
    char date[20], task_description[100];
    printf("Enter the date (DD/MM/YYYY): ");
    scanf("%s", date);
    printf("Enter the task description: ");
    scanf("%s", task_description);

    FILE *file = fopen("tasks.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s\n", username, date, task_description);
        fclose(file);
        printf("Task added successfully!\n");
    } else {
        printf("Error in adding task. Please try again.\n");
    }
}
```

### View Tasks Function
The `view_tasks` function allows users to view tasks for a specific date. It reads the tasks from the `tasks.txt` file and displays those that match the entered date and username.

```c
void view_tasks(char *username) {
    char date[20];
    printf("Enter the date to view tasks (DD/MM/YYYY): ");
    scanf("%s", date);

    FILE *file = fopen("tasks.txt", "r");
    if (file != NULL) {
        char line[150];
        int tasks_found = 0;
        while (fgets(line, sizeof(line), file)) {
            char *token1 = strtok(line, " ");
            char *token2 = strtok(NULL, " ");
            char *token3 = strtok(NULL, " ");
            token3[strcspn(token3, "\n")] = 0;

            if (strcmp(token1, username) == 0 && strcmp(token2, date) == 0) {
                printf("Task: %s %s\n", token2, token3);
                tasks_found = 1;
            }
        }
        fclose(file);
        if (!tasks_found) {
            printf("No tasks found for this date.\n");
        }
    } else {
        printf("Error in viewing tasks. Please try again.\n");
    }
}
```

### Delete Account Function
The `delete_account` function allows users to delete their account. It verifies the username and password, then removes the account information from the `signup.txt` file.

```c
void delete_account(char *username, char *password) {
    char input_username[50], input_password[50];
    printf("Enter your username: ");
    scanf("%s", input_username);
    printf("Enter your password: ");
    scanf("%s", input_password);

    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        FILE *file = fopen("signup.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (file != NULL && temp != NULL) {
            char line[100];
            while (fgets(line, sizeof(line), file)) {
                char *token1 = strtok(line, " ");
                char *token2 = strtok(NULL, " ");
                token2[strcspn(token2, "\n")] = 0;

                if (strcmp(token1, input_username) != 0) {
                    fprintf(temp, "%s %s\n", token1, token2);
                }
            }
            fclose(file);
            fclose(temp);

            remove("signup.txt");
            rename("temp.txt", "signup.txt");
            printf("Account deleted successfully.\n");
        } else {
            printf("Error in deleting account. Please try again.\n");
        }
    } else {
        printf("Invalid credentials. Account deletion failed.\n");
    }
}
```

### Main Function
The `main` function provides a menu-driven interface for users to sign up, log in, and perform various operations like adding tasks, viewing tasks, and deleting their accounts.

```c
int main() {
    char username[50] = "";
    char password[50] = "";

    while (1) {
        printf("1. \tSign Up\n");
        printf("2. \t\tLogin\n");
        printf("3. \t\t\tExit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sign_up();
                break;
            case 2:
                if (login(username, password)) {
                    int logged_in = 1;
                    while (logged_in) {
                        printf("\n1. \tAdd Task\n");
                        printf("2. \t\tView Tasks\n");
                        printf("3. \t\t\tDelete Account\n");
                        printf("4. \t\t\t\tExit\n");
                        printf("Enter your option: ");

                        int option;
                        scanf("%d", &option);

                        switch (option) {
                            case 1:
                                add_task(username);
                                break;
                            case 2:
                                view_tasks(username);
                                break;
                            case 3:
                                delete_account(username, password);
                                logged_in = 0;
                                break;
                            case 4:
                                logged_in = 0;
                                break;
                            default:
                                printf("Invalid option. Please try again.\n");
                        }
                    }
                }
                break;
            case 3:
                printf("Thank you for using the Task Management System!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
```

## Summary
This program implements a simple task management system with functionalities for user registration, login, task management, and account deletion. Each function interacts with text files to store and retrieve user and task data. The main function provides a user-friendly menu to navigate through these operations.
  
