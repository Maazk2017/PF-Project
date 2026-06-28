#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void display_main_menu();

void student_log();
void student_menu();

void admin_log();
void AdminMainMenu();


int view_events();
int register_event(int choice);
void reviewRegistration();

void feedback();


void add_event();
void delete_event();
void load_events();


int main() {
    int choice;
    display_main_menu();
    return 0;
}


void display_main_menu() {
    int choice;
    printf("\n========================================\n");
    printf("  CAMPUS EVENT MANAGEMENT SYSTEM (CEMS)\n");
    printf("========================================\n");
    printf("1. Student Login \n");
    printf("2. Admin Login \n");
    printf("3. Exit \n");
    printf("========================================\n");

    printf("Enter your choice number: ");
    scanf("%d", &choice);

    if(choice == 1) {
        printf("You selected option 1.\n");
        student_log();
    } else if(choice == 2) {
        printf("You selected option 2.\n");
        admin_log();
    } else if(choice == 3) {
        printf("Exiting the program.\n");
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

void load_events() {
    printf("\n========================================\n");
    printf("---Available Events---\n");

    FILE *pfile = fopen("events.txt", "r");
    if (!pfile) {
        printf("Error: File not found!\n");
        return;
    }

    int code, fee;
    char name[50];

    while(fscanf(pfile, "%d %s %d", &code, name, &fee) != EOF) {
        printf("%d. %s - RS %d\n", code, name, fee);
    }
    fclose(pfile);
    printf("========================================\n");
}


void student_log() {
    int upper=0, lower=0, digit=0, special=0, length=0;
    char student_id[9];
    printf("---Student Login---\n");
    printf("Enter your 8-character alphanumeric Student ID: ");
    scanf("%s", &student_id[0]);
    // will do validation later

    for(int i = 0; i<8; i++) {
        if (student_id[i] >= 'A' && student_id[i] <= 'Z') {
            upper++;
        } else if (student_id[i] >= 'a' && student_id[i] <= 'z') {
            lower++;
        } else if (student_id[i] >= '0' && student_id[i] <= '9') {
            digit++;
        } else {
            special++;
        }
        length++;
    }

    if (upper >0 && lower >0 && digit >0 && special >0 && length == 8) {
        printf("Valid Student ID\n");
        printf("Login successful!\n");
        printf("\n");
        student_menu();
    } else {
        printf("Invalid Student ID\n");
    }

}

void student_menu() {
    int choice;
    
    while(1) {
        printf("\n========================================\n");
        printf("       STUDENT MENU\n");
        printf("========================================\n");
        printf("1. View and Register for Events\n");
        printf("2. Review My Registration\n");
        printf("3. Submit Feedback\n");
        printf("4. Logout\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            view_events();
        } else if(choice == 2) {
            reviewRegistration();
        } else if(choice == 3) {
            feedback();
        } else if(choice == 4) {
            printf("Logging out...\n");
            break;  // Exit student menu, go back to main menu
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void admin_log() {
    int attempts = 0;
    char admin_pass[20];
    char stored_pass[20];
    printf("---Admin Login---\n");
    // we are supposing all admins have the same password "
    // password will be stored in a file named "admin_pass.txt"

    FILE *pfile = fopen("admin_pass.txt", "r");
    if (!pfile) {
        printf("Error: File not found!\n");
        return;
    } else {
        fscanf(pfile, "%s", stored_pass);
        fclose(pfile);
        while(1) {  // strcmp gives 0 if both strings are equal
            printf("Enter admin access password: ");
            scanf("%s", &admin_pass[0]);
            attempts++;
            if(attempts >= 3) {
                printf("Too many incorrect attempts. Exiting...\n");
                break;
            }
            if(strcmp(admin_pass, stored_pass) == 0) {
                printf("Access Granted\n");
                AdminMainMenu();
                break;
            } else {
                printf("Incorrect password. Try again: \n");
            }
        }
    }
}

void AdminMainMenu() {
    int userinp;
    while (1) {
        printf("\n========================================\n");
        printf("         ADMIN MAIN MENU\n");
        printf("1. Add Events\n");
        printf("2. Delete Event\n");
        printf("3. View registered students\n");
        printf("4. View Feedbacks\n");
        printf("5. View Events\n");
        printf("6. Logout\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf(" %d", &userinp);

        if (userinp == 1) {
            add_event();
        } else if (userinp == 2) {
            delete_event();
        } else if (userinp == 3) {
            FILE *pfile = fopen("registrations.txt", "r");
            if (!pfile) {
                printf("Error: File not found!\n");
            } else{
                char lines[1000];
                printf("---Registered Students---\n");
                while (fgets(lines, sizeof(lines), pfile)) {
                    printf("%s", lines);
                }
                fclose(pfile);
            }

        } else if (userinp == 4) {
            FILE *pfile = fopen("feedback.txt", "r");
            if (!pfile) {
                printf("Error: File not found!\n");
            } else {
                char lines[10000];
                printf("---Feedbacks---\n");
                printf("\n");
                while(fgets(lines, sizeof(lines), pfile)) {
                    printf("%s", lines);
                }
                fclose(pfile);
            }

        } else if (userinp == 5) {
            load_events();
        } else if (userinp == 6) {
            printf("Logging out...\n");
            break;  // Exit admin menu, go back to main menu
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

}

void add_event() {
    printf("---Add Event---\n");
    char event_name[50];
    int event_fee;
    int event_code;
    printf("Enter Event Code: ");
    scanf("%d", &event_code);
    printf("Enter event name (no spaces, use - or _): ");
    scanf("%s", &event_name[0]);
    printf("Enter event fee b/w 0 - 2000: ");
    scanf("%d", &event_fee);

    if (event_fee > 0 && event_fee <=2000 && event_name != NULL) {
        FILE *pfile = fopen("events.txt", "a");
        if (!pfile) {
            printf("Error: File not found!\n");
        } else {
            fprintf(pfile, "%d %s %d\n", event_code, event_name, event_fee);
            fclose(pfile);
            printf("Event added successfully!\n");
            printf("Event Code: %d\n", event_code);
            printf("Event Name: %s\n", event_name);
            printf("Fee: RS %d\n", event_fee);
        }
    } else {
        printf("Invalid event details.\n");
    }

}

void delete_event() {
    printf("---Delete Event---\n");
    int delete_code;
    int found = 0;

    printf("Current Events:\n");
    FILE * pfile = fopen("events.txt", "r");
    if (!pfile) {
        printf("Error: File not found!\n");
    } else {
        int code, fee;
        char name[50];
        while(fscanf(pfile, "%d %s %d", &code, name, &fee) != EOF) {
            printf("Event Code: %d, Name: %s, Fee: RS %d\n", code, name, fee);
        }
        fclose(pfile);

        printf("Enter Event Code to delete:");
        scanf("%d", &delete_code);

        pfile = fopen("events.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        while(fscanf(pfile, "%d %s %d", &code, name, &fee) != EOF) {
            if (code != delete_code) {
                fprintf(temp, "%d %s %d\n", code, name, fee);
            } else {
                found = 1;
            }
        }

        fclose(pfile);
        fclose(temp);

        remove("events.txt");
        rename("temp.txt", "events.txt");

        if (found == 1) {
            printf("Event with code %d deleted successfully.\n", delete_code);
        } else {
            printf("Event with code %d not found.\n", delete_code);
        }
    }
}

int view_events() {
    int user_choice;
    
    load_events();  // Display events from file
    
    printf("\nSelect an event code to register (0 to quit): ");
    scanf("%d", &user_choice);

    if (user_choice == 0) {
        printf("Exiting...\n");
    }
    
    // Check if event exists
    FILE *pfile = fopen("events.txt", "r");
    if (!pfile) {
        printf("Error: File not found!\n");
        return 0;
    }
    
    int code, fee;
    char name[50];
    int found = 0;
    
    while (fscanf(pfile, "%d %s %d", &code, name, &fee) != EOF) {
        if (code == user_choice) {
            found = 1;
            printf("You have selected %s.\n", name);
            fclose(pfile);
            register_event(user_choice);
            return 0;
        }
    }
    
    fclose(pfile);
    
    if (!found) {
        printf("Invalid event code!\n");
    }
    
    return 0;
}

int register_event(int choice) {
    char username[30];
    char password[20];
    int seat_number;
    int fee = 0;
    int paid_amount;
    char event_name[30] = "";
    
    // Get event details from file
    FILE *pfile = fopen("events.txt", "r");
    if (!pfile) {
        printf("Error: File not found!\n");
        return 0;
    }
    
    int code, event_fee;
    char name[50];
    int found = 0;
    
    while (fscanf(pfile, "%d %s %d", &code, name, &event_fee) != EOF) {
        if (code == choice) {
            strcpy(event_name, name);
            fee = event_fee;
            found = 1;
            break;
        }
    }
    fclose(pfile);
    
    if (!found) {
        printf("Event not found!\n");
        return 0;
    }
    
    srand(time(NULL));
    seat_number = (rand() % 50) + 1;
    
    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password for registration: ");
    scanf("%s", password);

    int count = 0;
    while (1) {  
        printf("Please pay the fee of RS %d to register for %s: ", fee, event_name);
        scanf("%d", &paid_amount);
        count++;

        if (count >= 3) {
            printf("Too many incorrect attempts. Exiting...\n");
            return 0;
        }

        if(paid_amount != fee) {
            printf("Incorrect amount! Try again.\n");
        } else {
            printf("Payment successful! You are registered for %s.\n", event_name);
            break;
        }
    }

    printf("Your seat number is %d.\n", seat_number);

    pfile = fopen("registrations.txt", "a");
    if (pfile == NULL) {
        printf("Error: Could not save registration!\n");
    } else {
        fprintf(pfile, "%s %s %d %s %d\n", username, event_name, seat_number, password, paid_amount);
        fclose(pfile);
    }
    return 0;
}


void reviewRegistration() {
    printf("--Review Registration--\n");
    char name[30];
    char pass[30];
    char event_name[50];
    int seat_no, fee;
    char student_username[30];

    printf("Enter your username: ");
    scanf("%s", &student_username[0]);

    
    FILE *pfile = fopen("registrations.txt", "r");
    if (!pfile) {
        printf("Error: File not found!\n");
    } else {
        int found = 0;
        while (fscanf(pfile, "%s %s %d %s %d", name, event_name, &seat_no, pass, &fee) != EOF) {
            if (strcmp(name, student_username) == 0) {
                printf("Registration Details:\n");
                printf("Username: %s\n", name);
                printf("Event Name: %s\n", event_name);
                printf("Seat Nunmber: %d\n", seat_no);
                printf("Password: %s\n", pass);
                printf("Fee Paid: %d\n", fee);
                found = 1;
                break;
            }
        }

        if  (!found) {
            printf("No registration found for username: %s\n", student_username);
        }

        fclose(pfile);
    }
}


void feedback() {
    char feedback[200];

    getchar(); // Clear newline character from input buffer
    printf("---Feedback---\n");
    printf("Enter your feedback: ");
    fgets(feedback, sizeof(feedback), stdin);

    FILE *pfile = fopen("feedback.txt", "a");
    if (!pfile) {
        printf("Error: File not found!\n");
    } else {
        fprintf(pfile, "%s\n", feedback);
        fclose(pfile);
        printf("Thank you for your feedback!\n");
    }
}