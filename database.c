#include<stdio.h>

int database() {
    char product[3][3][20] = {
        {"Banana", "Apple", "Mango"},
        {"Tomato", "Potato", "Carrot"},
        {"Milk", "Yougurt", "Eggs"}
    }
    int productID[3][3] = {
        {100, 102, 103},
        {200, 201, 202},
        {300, 301, 302}
    }
    int quantity[3][3] = {
        {20, 15, 30},
        {20, 40, 15},
        {50, 15, 10}
    }
    int rates[3][3] = {
        {80, 170, 250},
        {150, 120, 70},
        {220, 320, 320}
    }

    return 0;
}