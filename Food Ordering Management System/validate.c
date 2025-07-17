#include "schoolLib.h"
#include "ui.h"

void login(char role);
void roleMenu(){
    printf(YELLOW "Choose Your Role:\n" RESET);
    printf("1. 👥 Admin (A)\n");
    printf("2. Customer(C)\n");
    printf(BLUE "Enter Your Role: " RESET);
}
void validate(){
    Staff staff[2];
    staff[2] = { {"roth" , 1234} , {"sal" , 1234} };

    char nameE[100];
    char passE[100];
    bool check = 0;
    int attempt = 1;
    char role;
    asciiBanner();
        printf("\n" BLUE "=========== Food Ordering Management System ===========" RESET "\n");
        roleMenu();
        getchar();
        scanf("%c", &role);

        while(check == 0) {
            if(role =='C'){

            else if (role ==)
        }
    }
}

void login(role){
    printf(YELLOW "Username: " RESET);
    scanf("%s", nameE);
    printf(YELLOW "Password: " RESET);
    system("stty -echo"); // Hide password input
    scanf("%s", passE);
    system("stty echo");

    loadingDots("🔐 Verifying credentials");
    if(role == 'C'){
        if(strcmp(username, nameE) == 0 && strcmp(password, passE) == 0){
            printf(GREEN "\n  ✅  Login Successfully!\n" RESET);
            check = 1;
            sleep(1);
            system("clear");
            asciiBanner();
        }
        else {
            printf(RED "\n ❌ Access Denied! Try Again. Attempt %d/3\n" RESET, attempt);
            attempt += 1;
        }
        if(attempt > 3){
            printf(RED " 🚫 Too many failed attempts. Exiting...\n" RESET);
            exit(1);
        }
    }
    if(role == 'A'){
        if(strcmp(username, nameA) == 0 && strcmp(password, passA) == 0){
            printf(GREEN "\n  ✅  Login Successfully!\n" RESET);
            check = 1;
            sleep(1);
            system("clear");
            asciiBanner();
        }
        else {
            printf(RED "\n ❌ Access Denied! Try Again. Attempt %d/3\n" RESET, attempt);
            attempt += 1;
        }
        if(attempt > 3){
            printf(RED " 🚫 Too many failed attempts. Exiting...\n" RESET);
            exit(1);
        }
    }
}
