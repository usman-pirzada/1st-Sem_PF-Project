#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define usersCount 100
// #include <conio.h>

void enter(int, const char *, int);    // Enter to program by your account
int database();
char report(int);
int stock();
// int takeNcount(int);

struct Account;
struct Database;
struct Stock;
struct Report;

int main() {
    FILE *adminFile = NULL;
    FILE *userFile = NULL;

    printf("\n\t\tFAST Super Mart");
    printf("\n\t\t==================");
    adminFile = fopen("Admins.bin", "rb");
    userFile = fopen("Admins.bin", "rb");
    if(adminFile == NULL || userFile == NULL) {
        printf("\nNo Account Created Yet!! Please signUp to proceed:\n 1) Add Admin Account\n 2) Add User Account\n");
        scanf("%d", &option);
        switch() {
            case 1:
                enter(1, "Admins.bin");
                system("CLS");
                main(); // continue;
                // break;
            case 2:
                enter(1, "Admins.bin");
                main(); // continue;
                system("CLS");
                // break;
            case 3:
                exit(0);
                system("CLS");
                // break;
            default:
                printf("\n\tInvalid Input!! Try Again\n");
                main(); // continue;
        }
        
    // } else {
    fclose(adminFile); fclose(userFile);  // File was opened just to verify its existance
    printf("\nWhich operation do you want to perform: \n")
    printf("\nPlease login or signUp to proceed:\n 1) Admin Login\n 2) User Login\n 3) Add Admin\n 4) Add User\n 5) Exit\n");
    scanf("%d", &option);
    switch(option) {
        case 1:
            enter(2, "Admins.bin");   // Send 1 with "Admins.bin" for Admins' Login
            menu(1);    // Admin Menu @1
            break;
        case 2:
            enter(1, "Users.bin");   // Send 1 with "Users.bin" filename for Users' Login
            menu(2);    // User Menu @2
            break; 
        case 3:
            enter(2, "Admins.bin");   // Send 2 with "Admins.bin" for SignUp
            printf("\n\tNew Admin added successfully!\n");
            break;
        case 4:
            enter(2, "Users.bin");   // Send 2 with "Users.bin" filename for Users' SignUp
            printf("\n\tNew User added successfully!\n");
            break;

        case 5:
            exit(0);
            break;

        default:
            printf("\n\tInvalid Input!! Try Again\n");
            main(); // continue;
    }
    // }
    
    return 0;
}

// -------------------Enter Function HERE--------------------
void enter(int log, const char *filename, int userCount) {
    struct Account *accounts = NULL;
    *accounts = (struct Account *) malloc(sizeof(struct Account));  // This size is enough to store SignUp data for writing to binary file
    if(accounts == NULL) {
        printf("\nError Allocating Memory!!");
        main();
    }

    if(log == 1) {  // 1 for login
        char username[20], password[15];
        *accounts = (struct Account *) realloc(userCount * sizeof(struct Account));
        if(accounts == NULL) {
            printf("\nError Allocating Memory!!");
            main();
        }
        FILE *fileRead = NULL;
        fileRead = fopen(filename, "rb");
        if (fileRead == NULL) {
            perror("\n\tError Occured");
            main();
        }

        int count = 0
        while(fread(&accounts[count], sizeof(struct Accounts), 1, fileRead)) {  // Reading & storing users' login data to structure
            count++;
        }
        fclose(fileRead);

        // Input & Validation Below
        printf("\nEnter Your Username: ");
        scanf("%s20", &username);
        printf("Enter Your Password: ");
        scanf("%s15", &password);
        // validate here length of username & password

        for(int i = 0; i < count; i++) {
            if(strcp(accounts[i]->username, username) == 0 && strcmp(accounts->password, password) == 0) {
                printf("\nLogin successful!!\n");
                return;
            } else {
                printf("\n\tInvalid Username or Password!!");
                main();
            }
        }
    
    } else if(log == 2) {   // 2 for SignUp
        FILE *fileWrite = NULL;
        fileWrite = fopen(filename, "ab");  // Open file to append signUp data
        if(fileWrite == NULL) {
            perror("\n\tError Occured");
            main();
        }
        
        // Collect signup data in structure
        printf("\nSet Your Username: ");
        scanf("%s20", &accounts->username);
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%s15", &accounts->password);

        fwrite(&accounts, sizeof(struct Account), 1, fileWrite);    // Write structure (signup data) to file
        fclose(fileWrite);
        
        printf("\nSignup successful!! Now login to your created account\n");
        enter(1, &filename);   // Go to login for created account
    } else {
        printf("\n\n\tAn Unexpected Error Occured!!");
        exit(1);
    }
}

// -------------------Monthly/Yearly Report Function HERE--------------
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
// --------------------Stock Maintaining Function HERE-------------
/*
int stock() {
    
    return 0;
}
*/
// -------------------Database Function HERE---------------------
/*
int database() {
    // char product[3][3][20] = {
    //     {"Banana", "Apple", "Mango"},
    //     {"Tomato", "Potato", "Carrot"},
    //     {"Milk", "Yougurt", "Eggs"}
    // };
    // int productID[3][3] = {
    //     {100, 102, 103},
    //     {200, 201, 202},
    //     {300, 301, 302}
    // };
    // int quantity[3][3] = {
    //     {20, 15, 30},
    //     {20, 40, 15},
    //     {50, 15, 10}
    // };
    // int rates[3][3] = {
    //     {80, 170, 250},
    //     {150, 120, 70},
    //     {220, 320, 320}
    // };

    // return 0;
}
*/
/*
// ---------------Verify length anywhere for String Input------------
int takeNcount(int limit) {
        int count = 0;

        do{
            count++;    // Count no. of characters of Password
        } while((username = getchar()) != '\n');
        if(count <= limit) {
            return 1;
        } else {
            return 0;
        }
}
*/
// ----------------------------Structures HERE↓----------------------
struct Account {
    char username[20];
    char password[15];
} account[100];
/*
struct Database {   // Database for User purchase
    int ID;
    char Name[20];
    int Qty;
    int Price;
} D1;

struct Stock {  // Stock of Mart
    int ID;
    char Name[20];
    int Qty;
    int Price;
} S1;

struct Report { // Reports

} R1;
*/