#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

void enter(int);
int database();
char report(int);
int stock();
int takeNcount(int);

struct Database;
struct Stock;
struct Report;

int main() {
    FILE *start = NULL;
    printf("\n\t\tFAST Super Mart");
    printf("\n\t\t==================");
    start = fopen("firstlogin.dat", "r");
    if(start == NULL) {
        printf("\nPlease signUp first to proceed:\n");
        enter(2);
    } else {
        printf("\nPlease login or signUp to proceed:\n 1) Login\n 2) SignUp\n 3) Exit\n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                enter(1);
                break;

            case 2:
                enter(2);
                break;

            case 3:
                exit(1);
                break;

            default:
                printf("\n\tInvalid Input!! Try Again\n");
                main();
        }
        fclose(start);
    }
    
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
void enter(int log) {
    char username[16], pass[21];
    int count = 0;
    FILE *fenter = NULL;
    // remember to close login data file
    fenter = fopen("firstlogin.dat", "r");  // Gaining login data from file
    if (fenter == NULL) {   // If login data NOT exist...
        printf("\n\tYou must SignUp first to login!\n");
        enter(2);   // ...then go for signUp
        return;
    }

    if(log == 1) {  // 1 for login
        printf("\nEnter Your Username: ");
        scanf("%s15", &username);
        
        
        printf("Enter Your Password: ");
        scanf("%s20", &pass);
        
        do {
            if(getc(fenter) == (username % 10)) {   // here % & / logic will not work as it is char
                username = username / 10;
                validate = 1;
            } else {
                validate = 2;
                break;
            }
        } while(ch != EOF);
        // fclose(fenter);
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
        fenter = fopen("firstlogin.dat", "a");  // Open file to append signUp data
        if(fenter == NULL) {
                perror("\nError Occured");
                return 'N';
        }

        printf("\nSet Your Username: ");
        scanf("%s15", &username);
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%s20", &pass);   // there should be chk for pass len here & " " ; not allowed
        
        fprintf(fenter, "%s;%s\n", username, pass); // Writing signUp data
        printf("\nSignup successful!! Now login to your created account\n");
        enter(1);   // Go to login for created account
    }
    // else if(log == 3) {   // 3 for Password only when performing sensitive action
    //     printf("\nEnter Your Password to proceed: ");
    //     scanf("%s", &pass);
    //     // validation process here
    // }

    fclose(fenter);
}

// -------------------Monthly/Yearly Report Function HERE--------------
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

// ----------------------------Structures HERE↓----------------------
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

struct Report { // Monthly & Yearly Reports

} R1;