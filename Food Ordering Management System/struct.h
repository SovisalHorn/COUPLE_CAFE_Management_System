#ifndef STRUCT_H
#define STRUCT_H

// Date structure
typedef struct {
    int day;
    int month;
    int year;
} Time;


// Drink item structure
typedef struct {
    char ID[10];
    char name[50];
    float price;
    char type[20]; // e.g., "Coffee", "Juice"
} Drink;

// Cart/order structure
typedef struct {
    char staffName[50]; // staff who served
    Drink drink;
    int quantity;
    Time orderDate;
} Cart;

// Coupon for discount
typedef struct {
    char name[50];   // Coupon code
    int discount;    // Discount in percent
} Coupon;

// Admin/Staff login structure
typedef struct {
    char name[50];
    char password[50];
} Staff;

// Daily report
typedef struct {
    char date[11];      // Format: "YYYY/MM/DD"
    int itemCount;      // Unique items sold
    int totalQty;       // Total quantity sold
    float totalSales;   // Total revenue
} DailyReport;


// User structure
typedef struct {
    char username[50];
    char password[50];
    char email[100];
    char phoneNumber[100];
    int point;
} User;


#endif // STRUCT_H
