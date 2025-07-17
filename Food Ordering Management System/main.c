#include "schoolLib.h"
#include "ui.h"
#include "loginSignUp.c"
#include "struct.h"
#include "menu.c"

char nameA[50];  

//#include ""
// Function declarations
void customer_menu();
void cafeAdminMenu();
void adminOperation();
void customerOperation();
void roleMenu();
// External functions from loginSignUp.c
int loginA();
void logout();
int login();
void signUp();

//Function from menu.c

// Function declarations
void displayAdminMenu();
int getAdminChoice();
void handleAdminChoice(int choice);

void displayCustomerMenu();
int getCustomerChoice();
void handleCustomerChoice(int choice);

// Wrappers for operations
void adminOperation();
void customerOperation();

// Role selection menu
void roleMenu() {
    drawLine();
    printf("|👥 Choose Your Role:\n");
    printf("| 1. 🛠️  Admin (A)\n");
    // printf("| 2. 🧑‍🍳 Customer (C)\n");
    printf("| 2. Exit Program\n");
    drawLine();
}

int main() {
    int choice;
    int is_logged_in;
    char user_role;

    while (1) {
        // Role selection menu
        do {
            system("clear");
            asciiBanner();
            roleMenu();
            printf("| Choose your role: ");
            scanf("%d", &choice);

            if (choice == 1) {
                user_role = 'A';
                break;
            }
            // } else if (choice == 2) {
            //     user_role = 'C';
            //     break;
            
            else if (choice == 2) {
                printf("| Program closed. Goodbye!\n");
                return 0;  // actually close program here
            } else {
                system("clear");
                printf(RED "| ❌ Invalid choice, please try again.\n" RESET);
            }
        } while (1);

        int menu_choice;

        // Main operation menu (for Admin or Customer)
        do {
            system("clear");
            asciiBanner();
            printf("| Selected Role: %s\n", user_role == 'A' ? "Admin/Staff" : "Customer");
            drawLine();

            if (user_role == 'A') {
                printCenter("🛠️  Admin/Staff Access Panel");
                drawLine();
                printf("┃ 1. 🔐 Log In as Admin/Staff\n");
                printf("┃ 2. 🔙 Back to Role Menu\n");
                printf("┃ 3. ❌ Exit Program\n");
                drawLine();
                printf("➡️  Enter your choice: ");
                scanf("%d", &menu_choice);

                switch (menu_choice) {
                    case 1:
                        system("clear");
                        is_logged_in = loginA();
                        if (is_logged_in) {
                            strcpy(nameA, usernameA);  // <-- move it here
                            system("clear");
                            printf(GREEN "| ✅ Welcome ! You are logged in.\n" RESET);
                            adminOperation();
                        }
                        break;

                    case 2:
                        goto backToRoleMenu;
                    case 3 :
                        printf("| Program closed. Goodbye!\n");
                        exit(0);
                    default:
                        system("clear");
                        printf(RED "| ❌ Invalid choice, please try again.\n" RESET);
                }
        //Customer Side
            } else {  // Customer
                printf("| 1. Sign Up\n");
                printf("| 2. Log In\n");
                printf("| 3. Back to Role Menu\n");
                printf("| 4. Exit\n");
                drawLine();
                printf("| Choose an option: ");
                scanf("%d", &menu_choice);

                switch (menu_choice) {
                    case 1:
                        system("clear");
                        signUp();
                        break;
                    case 2:
                        system("clear");
                        is_logged_in = login();
                        if (is_logged_in) {
                            system("clear");
                            printf(GREEN "| ✅ Welcome, %s! You are logged in as Customer.\n" RESET, current_username);
                            customerOperation();
                        }
                        break;
                    case 3:
                        goto backToRoleMenu;
                    case 4 :
                        printf("Exit The program Bye.\n");
                        exit(0);
                    default:
                        system("clear");
                        printf(RED "| ❌ Invalid choice, please try again.\n" RESET);
                }
            }


   } while (1);

    backToRoleMenu:
        continue;  // go back to role selection
    }

    return 0;
}
