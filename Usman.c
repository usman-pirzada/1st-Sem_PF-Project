#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>      // For perror
#include <windows.h>    // For colors and formatting
#define BOLD "\e[1m"
#define WHITE "\e[0;37m"
#define RED "\e[0;31m"
#define YELLOW "\033[33m"
#define BLUE "\e[0;34m"
#define GREEN "\e[0;32m"
// #define usersCount 100

// Menu highlighting remaining

struct Account;
// struct Database;
// struct Stock;
// struct Report;

void enter(int, const char */*, int */);    // Enter to program by your account
void menu(int);
// int database();
// char report(int);
// int stock();

int main() {
    int option;
    FILE *adminFile = NULL;
    FILE *userFile = NULL;
    system(""); // To enable formatting & colors
    printf("BOLD"); // Without it, text appears very light

    printf(BLUE "\n\t\tFAST Super Mart");
    printf("\n\t\t==================" WHITE);
    adminFile = fopen("Admins.bin", "rb");
    userFile = fopen("Users.bin", "rb");
    if(adminFile == NULL && userFile == NULL) {
        printf(RED "\nNo Account Created Yet!!");
        printf(YELLOW "Please Add an Account to Proceed:\n 1) Add Admin Account\n 2) Add User Account\n" WHITE);
        scanf("%d", &option);
        switch(option) {
            case 1:
                printf("\nNow SignUp below for Admin Account\n");
                enter(2, "Admins.bin"); // Pass 2 for signup with Admins.bin file for Admin
                system("CLS");
                printf(GREEN"\n\tAdmin Account Added Successfully!\n" WHITE);
                break;
            case 2:
                printf("\nNow SignUp below for User Account\n");
                enter(2, "Users.bin");  // Pass 2 for signup with Users.bin file for User
                system("CLS");
                printf(GREEN "\n\tUser Account Added Successfully!\n" WHITE);
                break;
            case 3:
                exit(0);
                break;
            default:
                printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
                main(); // repeat main
        }
        
    fclose(adminFile); fclose(userFile);  // As the file was opened just to verify its existance

    while(1) {
        printf("\nWhich operation do you want to perform: \n");
        printf("\n 1) Admin Login\n 2) User Login\n 3) Add Admin\n 4) Add User\n 5) Exit\n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                enter(1, "Admins.bin");   // Send 1 with "Admins.bin" for Admins' Login
                printf(GREEN "\n\tAdmin Login Successful!\n" WHITE);
                menu(1);    // Admin Menu @1
                break;
            case 2:
                enter(1, "Users.bin");   // Send 1 with "Users.bin" filename for Users' Login
                printf(GREEN "\n\tUser Login Successful!\n" WHITE);
                menu(2);    // User Menu @2
                break; 
            case 3:
                enter(2, "Admins.bin");   // Send 2 with "Admins.bin" for SignUp
                printf(GREEN "\n\tNew Admin Added Successfully!\n" WHITE);
                break;
            case 4:
                enter(2, "Users.bin");   // Send 2 with "Users.bin" filename for Users' SignUp
                printf(GREEN "\n\tNew User Added Successfully!\n" WHITE);
                break;

            case 5:
                exit(0);
                break;

            default:
                printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
                main(); // continue;
        }
    }
    
    return 0;
}

// -------------------Enter (Login & SignUp) Function HERE--------------------

void enter(int log, const char *filename/*, int usersCount*/) {  // variable is global  // log is 1 for Login & 2 for SignUp
    struct Account *accounts = NULL;    // see for correction
    accounts = (struct Account *) malloc(sizeof(struct Account));  // This size is enough to store SignUp data for writing to binary file   // Removed *accounts
    if(accounts == NULL) {
        printf(RED "\nError Allocating Memory!!" WHITE);
        main();
    }

    if(log == 1) {  // 1 for login
        char username[20], password[15];
        /***/accounts = (struct Account *) realloc(accounts, /*usersCount*/20 * sizeof(struct Account));   // correction needed
        if(accounts == NULL) {
            printf(RED "\nError Allocating Memory!!" WHITE);
            main();
        }
        FILE *fileRead = NULL;
        fileRead = fopen(filename, "rb");
        if (fileRead == NULL) {
            perror(RED "\n\tError Occured" WHITE);
            main();
        }

        int count = 0;
        while(fread(&accounts[count], sizeof(struct Account), 1, fileRead)) {  // Reading & storing users' login data to structure  // & removed
            count++;
        }
        fclose(fileRead);

        // Input & Validation Below
        printf("\nEnter Your Username: ");
        scanf("%19s", &username);   // see correction 19 or 20
        printf("Enter Your Password: ");
        scanf("%14s", &password);   // see 14 or 15
        // validate here length of username & password

        for(int i = 0; i < count; i++) {
            if(strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
                printf("\nLogin successful!!\n");
                return;
            } else {
                printf(RED "\n\tInvalid Username or Password!!" WHITE);
                main();
            }
        }
    
    } else if(log == 2) {   // 2 for SignUp
        FILE *fileWrite = NULL;
        fileWrite = fopen(filename, "ab");  // Open file to append signUp data
        if(fileWrite == NULL) {
            perror(RED "\n\tError Occured" WHITE);
            main();
        }
        
        // Collect signup data in structure
        printf("\nSet Your Username: ");
        scanf("%19s", &accounts[0]->username); // 19 or 20? added [0]
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%14s", &accounts[0]->password); // 14 or 15? added [0]

        fwrite(accounts, sizeof(struct Account), 1, fileWrite);    // Write structure (signup data) to file // & removed
        fclose(fileWrite);
        
        printf(GREEN "\nSignup successful!! Now login to your created account\n" WHITE);
        enter(1, filename);   // removed &  // Go to login for created account
    } else {
        printf(RED "\n\n\tAn Unexpected Error Occured!!" WHITE);
        exit(1);
    }
}

// -------------------Enter (Login & SignUp) Function HERE--------------------

void menu(int user) {   // 1 for Admin & 2 for User
    int option;

    if(user == 1) { // 1 for Admin
        while(1) {
            printf("\nWhat would you like to do now: \n");
            printf("\n 1) Add New Item to Stock\n 2) View Stock Status\n 3) Generate Report\n 4) LogOut\n 5) LogOut & Exit Program");
            scanf("%d", &option);
            switch(option) {
                case 1:
                    // Send control to Talal's function for Adding new item to Stock
                    menu(1);    // Admin Menu @1
                    break;
                case 2:
                    // Send control to Talal's function for Viewing items of Stock
                    break; 
                case 3:
                    // Send control to my function for generating report
                    break;
                case 4:
                    return;     // Back to main as the user want to LogOut
                    break;

                case 5:
                    exit(0);    // Exit Program
                    break;

                default:
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }

    } else if(user == 2) {  // 2 for User
        while(1) {
            printf("\nWhat would you like to do now: \n");
            printf("\n 1) Add Item to Card\n 2) Remove Item from Card\n 3) Place Order\n 4) LogOut\n 5) LogOut & Exit Program");
            scanf("%d", &option);
            switch(option) {
                case 1:
                    // Send control to Mujtaba's function for Adding items to Card
                    break;
                case 2:
                    // Send control to Mujtaba's function for Removing items from Card
                    break; 
                case 3:
                    // Send control to Mujtaba's function to Place Order & generate receipt
                    break;
                case 4:
                    return;     // Back to main as the user want to LogOut
                    break;

                case 5:
                    exit(0);    // Exit Program
                    break;

                default:
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }

    }
}

// -------------------Report Generate  Function HERE--------------
/*
char report(int reprt) {
    FILE *freport;

    if(reprt == 1) {    // 1 for writing report
        freport = fopen("report.dat", "a");
        if(freport == NULL) {
            perror("\nUnable to generate report");
            return 'N';
        }

        // fclose(freport);
        return 'Y';
    } else if(reprt == 2) { // 2 for reading report
        freport = fopen("report.dat", "r");
        if (freport == NULL) {
            printf("\n\tNo Reports Found!!");
            return 'N';
        }
        
        // fclose(freport);
        return 'Y';
    } else {
        printf("\nUnable to Process Report!");
        ch = getch();
        return 'N';
    }

    fclose(freport);
}
*/

// ----------------------------Structures HERE↓----------------------
struct Account {
    char username[20];
    char password[15];
};
/*
struct Database {   // Database for User purchase
    int ID;
    char Name[20];
    int Qty;
    int Price;
};

struct Stock {  // Stock of Mart
    int ID;
    char Name[20];
    int Qty;
    int Price;
};

struct Report { // Reports

};
*/