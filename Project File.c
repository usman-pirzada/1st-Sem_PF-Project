#include <stdio.h>
#include <string.h>
#include <conio.h>

char login();
int database();
int report();
int stock();

int main() {
    printf("\t\tFAST Super Mart");
    printf("\n\t\t==================");
    // search for firstlogin.dat file & see if $FAST Super Mart$ is in its first line
    /*
    if(found) {
        if(login(1) == 'Y') {   // Passing 1 for login
            // will continue next operations
        }
    } else {
        if(login(2) == 'Y') {   // Passing 2 for SignUp
            // will continue next operations
        }
    }
    */
    
    return 0;
}

// -------------------Login Function HERE--------------------
char login(int log) {
    char username[16], pass[21];
    if(log == 1) {  // 1 for login
        printf("\nEnter Your Username: ");
        scanf("%s15", &username);
        printf("Enter Your Password: ");
        scanf("%s20", &pass);
        // strcmp after reading from file
        /* if(true) {
        return 'Y';
        } else {
            printf("\n\tINVALID Username or Password!!");
            if(attempt < 3) {
                attempt++;
                login(log);
            } else {
                printf("\n\tYou have entered wrong username or password 3 times!! Press any key to exit the program.");
                ch = getch();
                exit();
            }
        }*/
    } else if(log == 2) {   // 2 for SignUp
        printf("\nSet Your Username: ");
        scanf("%s15", &username);
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%s20", &pass);   // there should be chk for pass len here
        // now write/save username & password to firstlogin.dat file
        // if successful written return 'Y', otherwise print error message & call login function again if user want otherwise exit
    } else if(log == 3) {   // 3 for Password only when performing sensitive action
        printf("\nEnter Your Password to proceed: ");
        scanf("%s", &pass);
        // validation process here
    }
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