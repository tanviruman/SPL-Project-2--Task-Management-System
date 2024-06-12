#include <stdio.h>
#include <string.h>


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

