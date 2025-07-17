#include "schoolLib.h"
#include "ui.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_STAFF 100

Staff staffs[MAX_STAFF];
int numberStaff = 2;

char usernameA[50];
char passwordA[50];
char current_username[50];

// === FUNCTION DECLARATIONS ===
void saveAdminsToFile();
int loginA();
void addRemoveAdmin();
void addAdmin();
void removeAdmin();
void changeAdminPassword();
void asciiBanner();
void signUp();
int login();
void logout();

// === Save admins to file ===
void saveAdminsToFile() {
    FILE *f = fopen("admin.txt", "w");
    if (!f) {
        printf("❌ Cannot write to admin.txt\n");
        return;
    }

    for (int i = 0; i < numberStaff; i++) {
        fprintf(f, "%s %s\n", staffs[i].name, staffs[i].password);
    }

    fclose(f);
}

#define MAX_CUSTOMERS 100

void signUp() {
    char username[50], password[50], confirm[50];
    FILE *fp;

    printf("+--------------------------------------------+\n");
    printf("|              🧑 Customer Sign Up           |\n");
    printf("+--------------------------------------------+\n");

    printf("| Enter new username: ");
    scanf("%s", username);

    // Check if username already exists
    fp = fopen("customer.txt", "r");
    if (fp != NULL) {
        char u[50], p[50];
        while (fscanf(fp, "%s %s", u, p) != EOF) {
            if (strcmp(u, username) == 0) {
                printf("| ❌ Username already exists. Try another.\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    printf("| Enter new password: ");
    scanf("%s", password);
    printf("| Confirm password: ");
    scanf("%s", confirm);

    if (strcmp(password, confirm) != 0) {
        printf("| ❌ Passwords do not match.\n");
        return;
    }

    // Save to file
    fp = fopen("customer.txt", "a");
    if (fp == NULL) {
        printf("| ❌ Failed to open file for writing.\n");
        return;
    }
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("| ✅ Account created successfully! Please log in.\n");
}

// === Admin Login ===

int loginA() {
    int attempt = 0, maxAttempt = 3;

    while (attempt < maxAttempt) {
        printf("\n🔐 Admin Login Portal\n");
        printf("=====================================\n");
        printf("👤 Username: ");
        scanf("%s", usernameA);
        printf("🔑 Password: ");
        scanf("%s", passwordA);
        printf("=====================================\n");

        FILE *f = fopen("admin.txt", "r");
        if (!f) {
            printf(RED "❌ Could not open admin.txt\n" RESET);
            return 0;
        }

        char storedUser[50], storedPass[50];
        bool found = false;

        while (fscanf(f, "%s %s", storedUser, storedPass) != EOF) {
            if (strcmp(usernameA, storedUser) == 0 && strcmp(passwordA, storedPass) == 0) {
                found = true;
                break;
            }
        }
        fclose(f);

        if (found) {
                printf(GREEN "✅ Login successful as %s\n" RESET, usernameA);
                getchar(); getchar();
            return 1;
        }

        printf(RED "❌ Invalid credentials!\n" RESET);
        attempt++;
        sleep(1);
    }

    printf(RED "🚫 Too many failed attempts. Exiting...\n" RESET);
    exit(0);
}

// // === Add Admin ===
// void addAdmin() {
//     if (numberStaff >= MAX_STAFF) {
//         printf(RED "❌ Admin list is full.\n" RESET);
//         return;
//     }

//     printf("Enter new admin username: ");
//     scanf("%s", staffs[numberStaff].name);
//     printf("Enter new admin password: ");
//     scanf("%s", staffs[numberStaff].password);

//     numberStaff++;
//     saveAdminsToFile();
//     printf(GREEN "✅ Admin added successfully!\n" RESET);
// }

// // === Remove Admin ===
// void removeAdmin() {
//     char name[50];
//     printf("Enter admin username to remove: ");
//     scanf("%s", name);

//     int found = 0;
//     for (int i = 0; i < numberStaff; i++) {
//         if (strcmp(staffs[i].name, name) == 0) {
//             for (int j = i; j < numberStaff - 1; j++) {
//                 staffs[j] = staffs[j + 1];
//             }
//             numberStaff--;
//             saveAdminsToFile();
//             printf(GREEN "✅ Admin removed.\n" RESET);
//             found = 1;
//             break;
//         }
//     }

//     if (!found)
//         printf(RED "❌ Admin not found.\n" RESET);
// }

// // === Change Admin Password ===
// void changeAdminPassword() {

//     char name[50], newPass[50];
//     printf("Enter admin username to change password: ");
//     scanf("%s", name);

//     for (int i = 0; i < numberStaff; i++) {
//         if (strcmp(staffs[i].name, name) == 0) {
//             printf("Enter new password: ");
//             scanf("%s", newPass);
//             strcpy(staffs[i].password, newPass);
//             saveAdminsToFile();
//             printf(GREEN "✅ Password updated.\n" RESET);
//             return;
//         }
//     }
//     printf(RED "❌ Admin not found.\n" RESET);
// }

// // === Admin Management Menu ===
// void addRemoveAdmin() {
//     int choice;
//     do {
//         system("clear");
//         asciiBanner();
//         printf(YELLOW "\n🔐 Admin Management Panel\n" RESET);
//         printf("==========================================\n");
//         printf(" [1] ➕ Add New Admin\n" RESET);
//         printf(" [2] ❌ Remove Admin\n" RESET);
//         printf(" [3] 🔑 Change Admin Password\n" RESET);
//         printf(" [0] 🔙 Back to Previous Menu\n" RESET);
//         printf("==========================================\n");
//         printf(GREEN "Choose an option: " RESET);
//         printf("Enter your choice: ");
//         scanf("%d", &choice);
//         getchar();

//         switch (choice) {
//             case 1: addAdmin(); break;
//             case 2: removeAdmin(); break;
//             case 3: changeAdminPassword(); break;
//             case 0: break;
//             default: printf(RED "❌ Invalid choice.\n" RESET);
//         }

//         if (choice != 0) {
//             printf("\n👉 Press Enter to continue...");
//             getchar();
//         }

//     } while (choice != 0);
// }

// // === Logout ===
// void logout() {
//     strcpy(current_username, "");
//     printf("| ✅ Logged out successfully.\n");
//     sleep(1);
//     system("clear");
//     exit(1);
// }
