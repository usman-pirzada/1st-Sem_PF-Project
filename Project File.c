#include <stdio.h>
#include <string.h>
#include <conio.h>

char login();
int database();
int report();
int stock();

struct Database();
struct Stock();
struct Report();

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
    int count = 0;

    if(log == 1) {  // 1 for login
        FILE *flogin;
        printf("\nEnter Your Username: ");
        scanf("%s15", &username);
        
        
        printf("Enter Your Password: ");
        scanf("%s20", &pass);
        flogin = fopen("firstlogin.dat", "r");
        if (flogin == NULL) {
            printf("\nYou must SignUp first to login!");
            return 'N';
        }
        do {
            if(getc(flogin) == (username % 10)) {   // here % & / logic will not work as it is char
                username = username / 10;
                validate = 1;
            } else {
                validate = 2;
                break;
            }
        } while(ch != EOF)
        fclose(flogin);
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
        FILE *fsignup;
        printf("\nSet Your Username: ");
        scanf("%s15", &username);
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%s20", &pass);   // there should be chk for pass len here
        fsignup = fopen("firstlogin.dat", "a");
        if(fsignup == NULL) {
            fsignup = fopen("firstlogin.dat", "w");
        }
        fprintf(fsignup, "username: %s\tpass: %s", username, pass);
        fclose(fsignup);
        // if successful written return 'Y', otherwise print error message & call login function again if user want otherwise exit
    } else if(log == 3) {   // 3 for Password only when performing sensitive action
        printf("\nEnter Your Password to proceed: ");
        scanf("%s", &pass);
        // validation process here
    }
}

// -------------------Monthly/Yearly Report Function HERE--------------
int report(int reprt) {
    FILE *freport;
    if(reprt == 1) {    // 1 for writing report
        freport = fopen("report.dat", "a");
        if(freport == NULL) {
            freport = fopen("report.dat", "w");
        }

        fclose(freport);
        return 'Y';
    } else if(reprt == 2) { // 2 for reading report
        freport = fopen("report.dat", "r");
        if (freport == NULL) {
            printf("\n\tNo Reports Found!!");
            return 'N';
        }
        
        fclose(freport);
        return 'Y';
    } else {
        printf("\nUnable to Process Report!");
        ch = getch();
        return 'N';
    }
}

// --------------------Stock Maintaining Function HERE-------------
int stock() {
    
    return 0;
}

// -------------------Database Function HERE---------------------
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

struct Database {   // Database for User purchase
    int ID;
    char Name[20];
    int Qty;
    int Price;
} data;

struct Stock {  // Stock of Mart
    int ID;
    char Name[20];
    int Qty;
    int Price;
} stock;

struct Report { // Monthly & Yearly Reports

} report;

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