#include "schoolLib.h"
#include "ui.h"
#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_DRINKS 100
Drink drinks[MAX_DRINKS];
Cart cart[20];
int drinkCount = 0;
int cartCount = 0;
int discount = 0;
char usernameA[50];

void displayAdminMenu();
int getAdminChoice();
void handleAdminChoice(int choice);
void displayCustomerMenu();
int getCustomerChoice();
void handleCustomerChoice(int choice);
void adminOperation();
void customerOperation();
void listDrink();
void orderDrink();
void saveOrderHistory();
void generateBill();
void getCurrentDate(Time* t);
bool checkCoupon(const char *coupon, int *discount);
void addRemoveItem();
void addItem();
void removeItem();
void report();

void adminOperation() {
    int choice;
    do {
        system("clear");
        displayAdminMenu();
        choice = getAdminChoice();
        handleAdminChoice(choice);

        if (choice != 0) {
            printf("\n👉 Press Enter to continue...");
            getchar();
            getchar();
        }
    } while (choice != 0);
}

void displayAdminMenu() {
    printf("\n");
    printf("==============================================\n");
    printCenter("💘 Bienvenue au romantique Café COUPLE 💘");
    printf("==============================================\n");
    printf("|  [1] 📜  View & Manage Café Menu / Orders     |\n");
    printf("|  [2] ✏️  Add / Remove Café Items             |\n");
    printf("|  [3] 📊  View Sales Report (Cups & $)         |\n");
    printf("|  [0] 🔒  Logout                               |\n");
    printf("==============================================\n");
}

int getAdminChoice() {
    int choice;
    printf("👉  Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void handleAdminChoice(int choice) {
    switch (choice) {
        case 1:
            printf("\n| 📋 Accessing the Café Menu & Order Board...\n");
            orderDrink();
            break;
        case 2:
            printf("\n| 🍽️  Opening Item Management Section...\n");
            addRemoveItem();
            break;
        case 3:
            printf("\n| 📊 Viewing Sales Report...\n");
            report();
            break;
        case 0:
            printf("\n| 🔒 Logging out... See you next time, Boss!\n");
            exit(1);
            break;
        default:
            printf("\n| ❌ Invalid choice! Please pick a valid one.\n");
    }
}

void customerOperation() {
    int choice;
    do {
        system("clear");
        displayCustomerMenu();
        choice = getCustomerChoice();
        handleCustomerChoice(choice);

        if (choice != 0) {
            printf("\n👉 Press Enter to continue...");
            getchar();
            getchar();
        }
    } while (choice != 0);
}

void displayCustomerMenu() {
    printf("\033[1;33m");
    printf("====== 🍽️ Food Hub 🥘 ======\n");
    printf("1️⃣  My Account\n");
    printf("2️⃣  📜 View Menu\n");
    printf("3️⃣  📢 Announcements\n");
    printf("4️⃣  📑 Order History\n");
    printf("0️⃣  🔒 Logout\n");
    printf("=============================\n");
}

int getCustomerChoice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void handleCustomerChoice(int choice) {
    switch (choice) {
        case 1:
            printf("| Customer: Viewing account details...\n");
            break;
        case 2:
            printf("| Customer: Viewing food menu...\n");
            break;
        case 3:
            printf("| Customer: Checking announcements...\n");
            break;
        case 4:
            printf("| Customer: Viewing order history...\n");
            break;
        case 0:
            printf("| Logging out. See you next time!\n");
            break;
        default:
            printf("| ❌ Invalid choice, please try again.\n");
    }
}

void listDrink() {
    system("clear");

    FILE *fp = fopen("drink.txt", "r");
    if (fp == NULL) {
        printf("❌ Unable to open drink.txt\n");
        return;
    }

    // Drink drinks[100];
    drinkCount = 0;

    while (fscanf(fp, "%s %s %f %s",
              drinks[drinkCount].ID,
              drinks[drinkCount].name,
              &drinks[drinkCount].price,
              drinks[drinkCount].type) == 4) {
        drinkCount++;
    }

    fclose(fp);

    printf("\n🍹🍵☕ Welcome to COUPLE Cafe 🍵🍹☕\n");

    const char* categories[] = {"Signature", "Tea", "Cafe"};
    const char* headers[] = {"🌟 Signature Drinks", "🍵 Tea Series", "☕ Coffee Series"};

    for (int c = 0; c < 3; c++) {
        printf(" %s:\n", headers[c]);
        printf("=====================================================\n");
        printf("┃ ID   │ Name               │ Price($) │ Type       ┃\n");
        printf("-----------------------------------------------------\n");

        int hasItem = 0;
        for (int i = 0; i < drinkCount; i++) {
            if (strcmp(drinks[i].type, categories[c]) == 0) {
                printf("┃ %-4s │ %-18s │ %-8.2f │ %-10s ┃\n",
                       drinks[i].ID, drinks[i].name, drinks[i].price, drinks[i].type);
                hasItem = 1;
            }
        }

        if (!hasItem) {
            printf("┃           No items available in this section       ┃\n");
        }

        printf("=====================================================\n");
    }

    printf("Total Drinks: %d 🍶\n", drinkCount);
}

void getCurrentDate(Time* t) {
    time_t now = time(NULL);
    struct tm* local = localtime(&now);
    t->year = local->tm_year + 1900;
    t->month = local->tm_mon + 1;
    t->day = local->tm_mday;
}

void orderDrink() {
    char drinkChoice[10];
    char addMore;
    int found, quantity;

    listDrink();
    cartCount = 0;

    int c;
    drawLine();
    printf("|🛍️  Would you like to continue?\n");
    printf("|1. Proceed to Order\n");
    printf("|2. Go Back\n");

    drawLine();
    printf("| 👉 Enter your choice (1 or 2): ");
    scanf("%d", &c);
    if(c == 2) adminOperation();
    
    else if(c == 1){
    
    do {
        drawLine();
        printf("🧃 Enter Drink ID to add to cart (e.g. S01, T02): ");
        printf("\n👉 Your choice: ");
        scanf("%s", drinkChoice);

        found = 0;
        for (int i = 0; i < drinkCount; i++) {
            if (strcmp(drinks[i].ID, drinkChoice) == 0) {
                printf("🔢 Enter quantity for %s: ", drinks[i].name);
                scanf("%d", &quantity);

                cart[cartCount].drink = drinks[i];
                cart[cartCount].quantity = quantity;
                getCurrentDate(&cart[cartCount].orderDate);
                cartCount++;

                printf(GREEN "✅ Added to cart: %s x%d\n" RESET, drinks[i].name, quantity);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf(RED "❌ Invalid drink selection. Please try again.\n" RESET);
        }

        drawLine();
        printf("➕ Do you want to add more drinks? (Y/N): ");
        scanf(" %c", &addMore);
    } while (addMore == 'Y' || addMore == 'y');

char couponCh;
drawLine();
printf("🎟️  Do you have a discount coupon? (Y/N): ");
scanf(" %c", &couponCh);

if (couponCh == 'Y' || couponCh == 'y') {
    char coupon[50];
    int chC = 0;

    while (chC == 0) {
        printf("🔖 Please enter your coupon code: ");
        scanf("%s", coupon);

        bool isCoupon = checkCoupon(coupon, &discount);

        if (!isCoupon) {
            printf(RED "❌ Coupon \"%s\" is not valid.\n" RESET, coupon);
            printf("👉 What do you want to do next?\n");
            printf("   [0] Try entering coupon again\n");
            printf("   [1] Continue without coupon\n");
            printf("🔄 Your choice: ");
            scanf("%d", &chC);
        } else {
            printf(GREEN "✅ Coupon applied! You get a %d%% discount.\n" RESET, discount);
            chC = 1;
        }
    }
    
}
drawLine();


    FILE *temp = fopen("order_temp.txt", "w");
    if (temp == NULL) {
        printf("Error opening order_temp.txt\n");
        return;
    }

    float total = 0;
    fprintf(temp, "============================================================\n");
    fprintf(temp, "║                  🧾 COUPLE Café Receipt                  ║\n");
    fprintf(temp, "===========================================================\n");
    strcpy(cart->staffName, usernameA);
    fprintf(temp, "Staff Name : %s \n", cart->staffName);
    fprintf(temp, "┃ %-4s │ %-18s │ %-8s │ %-8s ┃\n", "ID", "Name", "Price($)", "Qty");
    fprintf(temp, "===========================================================\n");

    for (int i = 0; i < cartCount; i++) {
        fprintf(temp, "┃ %-4s │ %-18s │ %-8.2f │ %-8d ┃\n",
                cart[i].drink.ID, cart[i].drink.name, cart[i].drink.price, cart[i].quantity);
        total += cart[i].drink.price * cart[i].quantity;
    }

    fprintf(temp, "===========================================================\n");
    fprintf(temp, "┃ %-33s │ Total: %-8.2f ┃\n", " ", total);

    float discountT = 0;
    if (discount > 0) {
        discountT = (total * discount) / 100.0;
        fprintf(temp, "┃ %-33s │ Coupon Discount: $%-8.2f ┃\n", " ", discountT);
    }
    total -= discountT;
    fprintf(temp, "┃ %-33s │ Grand Total: %-8.2f ┃\n", " ", total);

    fprintf(temp, "===========================================================\n");
    fclose(temp);

    printf("✅ Order saved temporarily to order_temp.txt\n");
    saveOrderHistory();

    int ch;
    printf("Click 1 to print the Bill: ");
    scanf("%d", &ch);
    if (ch == 1) {
        generateBill();
    }
}
else{
    printf("Invalid Choice (Only 0 or 1)");
}
}

void saveOrderHistory() {
    FILE *history = fopen("orders.txt", "a");
    if (history == NULL) {
        printf("Error opening orders.txt\n");
        return;
    }

    strcpy(cart->staffName, usernameA);
    float total = 0;
    fprintf(history, "Staff Name : %s \n", cart->staffName);

    for (int i = 0; i < cartCount; i++) {
        fprintf(history, "%s\t%s\t%.2f$\tx%d\t%04d/%02d/%02d\n",
                cart[i].drink.ID, cart[i].drink.name, cart[i].drink.price, cart[i].quantity,
                cart[i].orderDate.year, cart[i].orderDate.month, cart[i].orderDate.day);
        total += cart[i].drink.price * cart[i].quantity;
    }

    fprintf(history, "-------------------------\nTotal: %.2f$\n", total);

    float discountT = 0;
    if (discount > 0) {
        discountT = (total * discount) / 100.0;
        fprintf(history, "Coupon Discount: $%.2f\n", discountT);
    }

    fprintf(history, "Grand Total: $%.2f\n", total);
    fprintf(history, "=========================\n");
    fclose(history);
    printf("✅ Order saved to orders.txt for report/statistics.\n");
}

void generateBill() {
    FILE *tempF = fopen("order_temp.txt", "r");
    char line[200];
    if (tempF == NULL) {
        printf("Error opening order_temp.txt\n");
        return;
    }
    printf("\n\n");
    while (fgets(line, sizeof(line), tempF)) {
        printf("%s", line);
    }
    printf("               Thank you for your visit! ☕️\n");
    printf("                  See you again soon!\n");
    fclose(tempF);
}

bool checkCoupon(const char *coupon, int *discount) {
    FILE *file = fopen("coupons.txt", "r");
    if (file == NULL) {
        printf("Could not open coupons.txt\n");
        return false;
    }

    char code[50];
    int disc;

    while (fscanf(file, "%s %d", code, &disc) != EOF) {
        if (strcmp(code, coupon) == 0) {
            *discount = disc;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

void addRemoveItem() {
    int a;
    printf("\n1.Add item\n2. Remove item\n");
    printf("Choose: ");
    scanf("%d", &a);
    if (a == 1) {
        addItem();
    }
    else if (a == 2) {
        removeItem();
    }
}
void addItem() {
    FILE *fp = fopen("drink.txt", "a");
    if (fp == NULL) {
        printf("❌ Unable to open drink.txt\n");
        return;
    }

    Drink newDrink;

    printf("\n🆕 Add a New Drink\n");

    printf("🔢 Enter Drink ID: ");
    scanf(" %s", newDrink.ID);

    printf("🍹 Enter Drink Name (use _ instead of spaces): ");
    scanf(" %s", newDrink.name);

    printf("💵 Enter Price: ");
    while (scanf("%f", &newDrink.price) != 1 || newDrink.price < 0) {
        printf("❌ Invalid input. buffer
    }

    int choice;
    printf("\n📂 Select Drink Category:\n");
    printf("   1. Signature\n");
    printf("   2. Tea\n");Enter a valid price: ");
        while (getchar() != '\n'); // Clear 
    printf("   3. Coffee\n");
    printf("👉 Enter choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(newDrink.type, "Signature");
            break;
        case 2:
            strcpy(newDrink.type, "Tea");
            break;
        case 3:
            strcpy(newDrink.type, "Cafe");
            break;
        default:
            printf("❌ Invalid category. Drink not added.\n");
            fclose(fp);
            return;
    }

    fprintf(fp, "%s %s %.2f %s\n", newDrink.ID, newDrink.name, newDrink.price, newDrink.type);
    fclose(fp);

    printf("✅ Drink added successfully!\n");
}


void removeItem() {
    char idToRemove[10];
    int found = 0;

    printf("Enter ID of the item to remove: ");
    scanf("%s", idToRemove);

    FILE *file = fopen("drink.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf("⚠️ Error opening file.\n");
        return;
    }

    char id[10], name[50], type[20];
    float price;

    while (fscanf(file, "%s %s %f %s", id, name, &price, type) != EOF) {
        if (strcmp(id, idToRemove) != 0) {
            fprintf(temp, "%s %s %.2f %s\n", id, name, price, type);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("drink.txt");
    rename("temp.txt", "drink.txt");

    if (found) {
        printf("✅ Item with ID '%s' removed successfully!\n", idToRemove);
    } else {
        printf("❌ Item ID not found.\n");
    }
}

void report() {
    FILE *file = fopen("orders.txt", "r");
    if (!file) {
        printf("❌ Could not open orders.txt\n");
        return;
    }

    DailyReport reports[100];
    int reportCount = 0;

    char line[256];
    char id[10], name[50], date[11];
    float price;
    int qty;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %s %f$ x%d %10s", id, name, &price, &qty, date) == 5) {
            int found = 0;
            for (int i = 0; i < reportCount; i++) {
                if (strcmp(reports[i].date, date) == 0) {
                    reports[i].itemCount += 1;
                    reports[i].totalQty += qty;
                    reports[i].totalSales += price * qty;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                strcpy(reports[reportCount].date, date);
                reports[reportCount].itemCount = 1;
                reports[reportCount].totalQty = qty;
                reports[reportCount].totalSales = price * qty;
                reportCount++;
            }
        }
    }

    fclose(file);

    printf("\n📅 Daily Sales Report:\n");
    printf("=====================================================\n");
    printf("| Date       | Unique Items | Total Qty | Total $   |\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < reportCount; i++) {
        printf("| %-10s | %-13d | %-9d | $%-8.2f |\n",
               reports[i].date,
               reports[i].itemCount,
               reports[i].totalQty,
               reports[i].totalSales);
    }
    printf("=====================================================\n");
}