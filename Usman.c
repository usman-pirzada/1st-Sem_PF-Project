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
// #define usersCount 100   // count signups & file storing remaining

// Menu highlighting remaining by >> & arrow controlling
struct Account {
    char username[20];
    char password[15];
};
// struct Database;
// struct Stock;
struct reportData;

void enter(int, const char */*, int */);    // Enter to program by your account
void menu(int);
// int database();
int genReport(int);
// int stock();
// int selectAnimate();

int main() {
    int option;
    FILE *adminFile = NULL;
    FILE *userFile = NULL;
    system(""); // To enable formatting & colors
    printf(BOLD); // Without it, text appears very light

    printf(BLUE "\n\t\tMujtaba Super Mart");
    printf("\n\t\t================" WHITE);
    adminFile = fopen("Admins.bin", "rb");
    userFile = fopen("Users.bin", "rb");
    if(adminFile == NULL && userFile == NULL) {
        printf(RED "\nNo Account Created Yet!!");
        printf(YELLOW " Please Create an Account to Proceed:\n 1) Create Admin Account\n 2) Create User Account\n 3) Exit\n" WHITE);
        scanf("%d", &option);
        switch(option) {
            case 1:
                printf("\nNow SignUp below for Admin Account\n");
                enter(2, "Admins.bin"); // Pass 2 in parameter for admin signup & "Admins.bin" filename
                system("CLS");
                printf(GREEN"\n\tAdmin Account Added Successfully!\n" WHITE);
                break;
            case 2:
                printf("\nNow SignUp below for User Account\n");
                enter(2, "Users.bin");  // Pass 2 in parameter for user signup & "Users.bin" filename
                system("CLS");
                printf(GREEN "\n\tUser Account Added Successfully!\n" WHITE);
                break;
            case 3:
                exit(0);    // Exit Program
                break;
            default:
                system("CLS");
                printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
                main(); // repeat main
        }
    }
        
    fclose(adminFile); fclose(userFile);  // As the file was opened just to verify its existance

    while(1) {
        printf("\nWhich operation do you want to perform: \n");
        printf("\n 1) Admin Login\n 2) User Login\n 3) Add Admin\n 4) Add User\n 5) Exit\n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                enter(1, "Admins.bin");   // Send 1 with "Admins.bin" for Admins' Login
                system("CLS");
                printf(GREEN "\n\tAdmin Login Successful!\n" WHITE);
                menu(1);    // Admin Menu @1
                break;
            case 2:
                enter(1, "Users.bin");   // Send 1 with "Users.bin" filename for Users' Login
                system("CLS");
                printf(GREEN "\n\tUser Login Successful!\n" WHITE);
                menu(2);    // User Menu @2
                break; 
            case 3:
                enter(2, "Admins.bin");   // Send 2 with "Admins.bin" for SignUp
                system("CLS");
                printf(GREEN "\n\tNew Admin Added Successfully!\n" WHITE);
                break;
            case 4:
                enter(2, "Users.bin");   // Send 2 with "Users.bin" filename for Users' SignUp
                system("CLS");
                printf(GREEN "\n\tNew User Added Successfully!\n" WHITE);
                break;

            case 5:
                exit(0);
                break;

            default:
                system("CLS");
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
        FILE *fileRead = NULL;
        char username[20], password[15];
        accounts = (struct Account *) realloc(accounts, /*usersCount*/20 * sizeof(struct Account));   // * removed from beginning
        if(accounts == NULL) {
            printf(RED "\nError Allocating Memory!!" WHITE);
            main();
        }
        
        fileRead = fopen(filename, "rb");
        if (fileRead == NULL) {
            perror(RED "\n\tError Occured" WHITE);
            main();
        }

        int count = 0;  // count used here for different indexes of the instance: accounts
        while(fread(&accounts[count], sizeof(struct Account), 1, fileRead)) {  // Reading from file then storing users' login data to structure  // & removed
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
                // system("CLS");
                // printf(GREEN "\nLogin successful!!\n" WHITE);
                //free(accounts);
                // return;
            } else {
                system("CLS");
                printf(RED "\n\tInvalid Username or Password!!" WHITE);
                //free(accounts);
                main(); // while(attempts < 3) can be used from Input validation
            }
        }
        free(accounts);
    }
    else if(log == 2) {   // 2 for SignUp
        FILE *fileWrite = NULL;
        fileWrite = fopen(filename, "ab");  // Open file to append signUp data
        if(fileWrite == NULL) {
            perror(RED "\n\tError Occured" WHITE);
            main();
        }
        
        // Collect signup data in structure
        printf("\nSet Your Username: ");
        scanf("%19s", &accounts[0].username); // 19 or 20? added [0]; instead of -> . used
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%14s", &accounts[0].password); // 14 or 15? added [0]; instead of -> . used

        fwrite(accounts, sizeof(struct Account), 1, fileWrite);    // Write structure (signup data) to file // & removed
        fclose(fileWrite);
        free(accounts);
        // printf(GREEN "\nSignup successful!!\n" WHITE);    // prompt to be changed
    } //else {    // Unnecessary, just for clarification
    //   printf(RED "\n\n\tAn Unexpected Error Occured!!" WHITE);
    //   free(accounts);
    //   exit(1);
    // }
}

// -------------------Enter (Login & SignUp) Function HERE--------------------

void menu(int userType) {   // 1 for Admin & 2 for Ordinary User
    int option;

    if(userType == 1) { // 1 for Admin
        while(1) {  // do{...}while(option != 5) can also be used
            printf("\nWhat would you like to do now:\n");
            printf("\n 1) Add New Item to Stock\n 2) View Stock Status\n 3) Generate Report\n 4) LogOut\n 5) Exit Program & LogOut\n"); // Remove User/Admin
            scanf("%d", &option);
            switch(option) {
                case 1:
                    // Send control to Talal's function for Adding new item to Stock
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

    } else if(userType == 2) {  // 2 for User
        while(1) {  // do{...}while(option != 5) can also be used
            printf("\nWhat would you like to do now:\n");
            printf("\n 1) Add Item to Card\n 2) Remove Item from Card\n 3) Place Order\n 4) LogOut\n 5) Exit Program & Logout\n");
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
                    system("CLS");
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }

    }
}

// -------------------Report Generate  Function HERE--------------
struct reportData { // Reports
	char name[20];
    int qty;
    float price;
    unsigned int ordersPlaced;
    // items sort a/c to sale
} *sold, *stockRemain;  // sold: Sold Items' table & stockRemain: Stock Items Table

void genReport(/*int option, */int noOfItems) {     // noOfitems remaning
	int DD, MM, YYYY;
	FILE *reportBIN = NULL;
	FILE *reportTXT = NULL;	// For printing data at current time, not store each structure permanently & latest figures stored in a bin
	// if time left you should print table by double pointer
	printf("Enter current Date (Format: DD MM YYYY): ");	// To write date of Report generation before each report
	scanf("%d %d %d", &DD, &MM, &YYYY);

	/*
	// counter return all struct values & apply calculations with previous data
	//Calculations:
	for(int i = 0; i < no; i++) {
		sold[i].qty += // added to card finally;	// No. of items sold of each name
		// Revenue generated += (sold[i].qty * sold[i].price;
		// No. of items sold (total) += sold[i].qty;
	}
	*/
    
    // Storing Latest Report Data in Binary File
	reportBIN = fopen("reportData.bin", "ab");  // apply if file unable to open
    if(fileWrite == NULL) {
        perror(RED "\n\tError Processing Binary File" WHITE);
        return;
    }
	fwrite(reportBIN, struct Report sold, 1, sizeof(struct Report));	// Store one latest calculated struct for sold items in the bin
	fwrite(reportBIN, struct Report stockRemain, 1, sizeof(struct Report));	// Store one latest calculated struct for sold items in the bin
    fclose(reportBIN);  // DONE Storing in Binary

    // Generating Report (Text File)
    reportTXT = fopen("C:\\report.txt", "a");  // Chk if address work
    if(fileWrite == NULL) {
        perror(RED "\n\tError Processing Text File" WHITE);
        return;
    }
    fprintf("\n\t\tReport Generated on Date: %s/%s/%s", DD, MM, YYYY);
    // ----------------* SOLD *-----------------
	fprintf("\n\n****************** Sales ******************\n");	// remove first \n\n for file writing
	fprintf("-------------------------------------------\n");
	fprintf(" S.No.\tIems\tSold Qty\tPrice\n");
	// sorting not done yet, instead only highest & lowest sales can be printed
	for(int i = 0; i < noOfItems; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, sold[i].name, sold[i].qty, sold[i].price);
	}
	printf("-------------------------------------------\n");

    // --------------* REMAINING *-----------------
    printf("\n\n****************** Stock Level ******************\n");	// remove first \n\n for file writing
	printf("-------------------------------------------\n");
	printf(" S.No.\tIems\tRemaining Qty\tPrice\n");
	// Sorting not done yet
	for(int i = 0; i < noOfItems; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, stockRemain[i].name, stockRemain[i].soldQty, stockRemain[i].price);
	}
	printf("-------------------------------------------\n");
    fclose(reportTXT);  // DONE Appending in Text file

	// Generating Report (Terminal)
	printf("\n\n\t\tReport Generated on Date: %s/%s/%s", DD, MM, YYYY); // add color
    // ---------------SALES-------------------
	printf("\n\n****************** Sales ******************\n");	// remove first \n\n for file writing   // add color
	printf("-------------------------------------------\n");
	printf(" S.No.\tIems\tSold Qty\tPrice\n");
	// sorting not done yet, instead only highest & lowest sales can be printed
	for(int i = 0; i < noOfItems; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, sales[i].name, sales[i].soldQty, sales[i].price);
	}
	printf("-------------------------------------------\n");
    // ---------------STOCK LEVEL-------------------
    printf("\n\n****************** Stock Level ******************\n");	// remove first \n\n for file writing   // add color
	printf("-------------------------------------------\n");
	printf(" S.No.\tIems\tRemaining Qty\tPrice\n");
	// Sorting not done yet
	for(int i = 0; i < noOfItems; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, stockRemain[i].name, stockRemain[i].soldQty, stockRemain[i].price);
	}
	printf("-------------------------------------------\n");
    printf(GREEN "\n\n\t\tReport Generated at \"C:\\report.txt\"" WHITE);    // FINISHED Report on Terminal
	
    // file wali report open krwado system("cd C:\report.txt"); agr user view reports history
}

/*Not Used
	// Display Report by 2D Pointers
    for(int i = 0; i < 1; i++) {
        printf
    }
    for(int i = 0; i < totProd; i++) {
        for(int j = 0; j < col; j++) {
            printf
        }
    }
*/

/*Descreted fn
void report(int reprt) {
    struct Report *reports = (struct Report*) calloc(1, sizeof(struct Report));
    free(reports);
    FILE *repRead;
    FILE *repWrite;

    if(reprt == 1) {    // 1 for writing report
        freport = fopen("report.dat", "a");
        if(freport == NULL) {
            perror("\nUnable to generate report");
        }

        // fclose(freport);
    } else if(reprt == 2) { // 2 for reading report
        freport = fopen("report.dat", "r");
        if (freport == NULL) {
            printf("\n\tNo Reports Found!!");
        }
        
        // fclose(freport);
    } else {
        printf("\nUnable to Process Report!");
        ch = getch();
    }

    fclose(freport);
}
*/

// -----------------------Remaining Structures HERE↓----------------------
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
*/

// Report Structure is just above reportData function

/*struct Report { // Reports
    unsigned int sales;
    unsigned int stockLevel;
    unsigned int ordersPlaced;
    // unsigned int requied;
    // items sort a/c to sale
};*/