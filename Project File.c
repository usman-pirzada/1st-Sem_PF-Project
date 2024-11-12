#include<stdio.h>

int login();
int database();
int report();
int stock();

int main() {
    printf("\tFAST Super Mart");
    printf("\n\t==================");
    
    return 0;
}

// -------------------Login Function HERE--------------------
int login() {
    
    return 0;
}

// -------------------Monthly/Yearly Report Function HERE--------------
int report() {
    
    return 0;
}

// --------------------Stock Maintaining Function HERE-------------
int stock() {
    
    return 0;
}

// -------------------Database Function HERE---------------------
int database() {
    char product[3][3][20] = {
        {"Banana", "Apple", "Mango"},
        {"Tomato", "Potato", "Carrot"},
        {"Milk", "Yougurt", "Eggs"}
    };
    int productID[3][3] = {
        {100, 102, 103},
        {200, 201, 202},
        {300, 301, 302}
    };
    int quantity[3][3] = {
        {20, 15, 30},
        {20, 40, 15},
        {50, 15, 10}
    };
    int rates[3][3] = {
        {80, 170, 250},
        {150, 120, 70},
        {220, 320, 320}
    };

    return 0;
}