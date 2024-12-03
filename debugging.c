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

struct product {
    int ID;
    char name[30];
    int quantity;
    float price;
};

struct reportData { // Reports
	char name[20];
    int qty;
    float price;
    unsigned int ordersPlaced;
    // items sort a/c to sale
} *sold, *stockRemain;  // sold: Sold Items' table & stockRemain: Stock Items Table // malloc not done // shift struct to top // es ka pointer bana kr phir dma kr lena

void enter(int, const char *);    // Enter to program by your account
void menu(int);
void genReport(/*int*/);
void addInventory();
void removeInventory();
void viewInventory();
void addToCart(int n, float totalCost);
void removeFromCart(float *totalCost);


int main() {
    int option;
    FILE *adminFile = NULL;
    FILE *userFile = NULL;
    system(""); // To enable formatting & colors
    printf(BOLD); // Without it, text appears very light

    printf(BLUE "\n\t\tFAST Super Mart");
    printf("\n\t\t==================" WHITE);
    adminFile = fopen("Admins.bin", "rb");
    userFile = fopen("Users.bin", "rb");
    if(adminFile == NULL && userFile == NULL) {
        printf(RED "\nNo Account Created Yet!!");
        printf(YELLOW " Please Create an Account to Proceed:\n 1) Create Admin Account\n 2) Create User Account\n 3) Exit\n" WHITE);
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
                //main(); // continue;
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
        scanf("%19s", username);   // see correction 19 or 20
        printf("Enter Your Password: ");
        scanf("%14s", password);   // see 14 or 15
        // validate here length of username & password

        for(int i = 0; i < /*count*/20; i++) {	// 20 users limit
            if(strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
//                 system("CLS");
//                 printf(GREEN "\nLogin successful!!\n" WHITE);
//                free(accounts);
                 return;
            } else {
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
    }

}

// -------------------Enter (Login & SignUp) Function HERE--------------------

void menu(int userType) {   // 1 for Admin & 2 for Ordinary User
    int option;

    if(userType == 1) { // 1 for Admin
        while(1) {  // do{...}while(option != 5) can also be used
            printf("\nWhat would you like to do now:\n");
            printf("\n 1) Add New Item to Inventory\n 2) Remove an Item from Inventory\n 3) View Inventory\n 4) Generate Report 5) LogOut\n 6) Exit Program\n"); // Remove User/Admin	//3) Generate Report\n 4) LogOut\n 5) Exit Program & LogOut
            scanf("%d", &option);
            switch(option) {
                case 1:
                	addInventory();
                    // Send control to Talal's function for Adding new item to Stock
                    break;
                case 2:
                	removeInventory();
                    break; 
                case 3:
                	viewInventory();
                    break;
                case 4:
                	genReport();
                    break;
				
				case 5:
					return;     // Back to main as the user want to LogOut
					
                case 6:
                    exit(0);    // Exit Program

                default:
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }

    } else if(userType == 2) {  // 2 for User
        while(1) {  // do{...}while(option != 5) can also be used
        	int choice, nP=0;	// n = no.of products
			float totalCost=0;
            printf("\nWhat would you like to do now:\n");
            printf("\n 1) Add Item to Card\n 2) Remove Item from Card\n 3) Place Order\n 4) LogOut\n 5) Exit Program\n");
            scanf("%d", &option);
            switch(option) {
                case 1:
                	addToCart(nP, totalCost);
                    break;
                case 2:
                	removeFromCart(&totalCost);
                    break; 
                case 3: //exit & auto place order
                	printf("\nThank you for shopping. Please come again.");
                	// should now start this function from beginning
                case 4:
                	return;	// return to login menu
                	
            	case 5:
            		exit(0);

                default:
                    system("CLS");
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }

    }
}

void addInventory() {                                         // add inventory
    FILE *file = fopen("inventory.txt", "a");
    if (!file) {
        printf("Error opening inventory.\n");
        return;
    }

    // Check if the file is empty to add default products
    fseek(file, 0, SEEK_END);  // Move to the end of the file
    long fileSize = ftell(file);  // Get the size of the file
    if (fileSize == 0) {  // If file is empty
        printf("File is empty. Adding default products...\n");

        struct product prod[15] = {
            {100, "Bread", 100, 2},
            {101, "Milk", 50, 1},
            {102, "Eggs", 30, 3},
            {103, "Rice", 20, 10},
            {104, "Sugar", 20, 3},
            {105, "Cooking Oil", 25, 5},
            {106, "Salt", 50, 1},
            {107, "Tomatoes", 30, 2},
            {108, "Potatoes", 40, 1},
            {109, "Onions", 30, 1},
            {110, "Canned Beans", 20, 2},
            {111, "Toilet Paper", 40, 1},
            {112, "Dishwashing Liquid", 15, 2},
            {113, "Shampoo", 20, 3},
            {114, "Toothpaste", 25, 1}
        };

        // Write the products to the file
        for (int i = 0; i < 15; i++) {
            fprintf(file, "%d %s %d %d\n", prod[i].ID, prod[i].name, prod[i].quantity, prod[i].price);
        }

        printf("Default products added to inventory.\n");
    }

    struct product prod;
    printf("Enter product name to add: ");
    scanf("%s", prod.name);
    printf("Enter product quantity: ");
    scanf("%d", &prod.quantity);
    printf("Enter product price: ");
    scanf("%d", &prod.price);

    // Assign product ID based on last added product
    fseek(file, -1, SEEK_END);
    while (fscanf(file, "%d %s %d %d", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF);
    prod.ID += 1;

    // Add the new product
    fprintf(file, "%d %s %d %d\n", prod.ID, prod.name, prod.quantity, prod.price);

    printf("Product added successfully.\n");

    fclose(file);
}

void removeInventory() {      //remove inventory
    int id;
    printf("Enter product ID to remove: ");
    scanf("%d", &id);

    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening inventory.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    struct product prod;
    int found = 0;
    while (fscanf(file, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        if (prod.ID != id) {
            fprintf(temp, "%d %s %d %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Product removed successfully.\n");
    } else {
        remove("temp.txt");
        printf("Product ID not found.\n");
    }
}

void viewInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening inventory.\n");
        return;
    }

    struct product prod;
    char line[100];  // Buffer to read a line

    printf("\nProduct Inventory:\n");
    while (fgets(line, sizeof(line), file)) {
        // Parse the line into the struct fields
        if (sscanf(line, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) == 4) {
            printf("ID: %d | Name: %s | Quantity: %d | Price: $%.2f\n",
                   prod.ID, prod.name, prod.quantity, prod.price);
        } else {
            printf("Error parsing line: %s", line);  // Debugging in case of invalid line
        }
    }

    fclose(file);
}


void addToCart(int n, float totalCost){                            // add to cart

	FILE *db = fopen("products.txt", "r"); // db = database
    if(db == NULL){
        printf("\nError opening file");
        return;
    }
    
    struct product *cart = NULL;	// Dynamic memory allocation for products

    int count = n; 					// Counter for items 

    while(1){

        // Allocating memory for the rising no.of products

        cart = (struct product *)realloc(cart,(count + 1) * sizeof(struct product));
        if(cart == NULL){
            printf("Memory Allocation Failed!\n");
            fclose(db);
            return;
        }

        printf("\nEnter the name of the item (or type 'exit' to finish): ");
        scanf("%s", cart[count].name);

        if(strcmp(cart[count].name,"exit") == 0){
            break;
        }

        printf("Enter Quantity: ");
        scanf(" %d",&cart[count].quantity);
        
        // Reset db pointer to beginning of file to search products.
        fseek(db, 0, SEEK_SET);
                
        int found = 0;
        char productName[30];	// A buufer variable to store and compare the name entered by user

        while(fgets(productName,30,db)!=NULL){
        	int available;
        	float price;
        	        	
        	sscanf(productName,"%s Quantity: %d Price: $%f",productName,&available,&price);
        	
        	printf("\nPrice: %.2f\n",price);
        	printf("Available: %d",available);
        	
            if(strcmp(productName,cart[count].name) == 0){
                found = 1;
                if(available<=0){
                    printf("\nThis item is out of stock");
                    continue;
                }else if(available<cart[count].quantity){
					printf("\nThere are only %d %s in the stock",available,productName);
					continue;
				}
                printf("\nAdded to cart successfully!\n");

                cart[count].price = price;
                totalCost += cart[count].quantity * price;
                printf("\n\n%f\n",totalCost);

				int fquantity = available - cart[count].quantity;

                // Append the item and its details to order_history.txt
                FILE *orderHistory = fopen("order_history.txt","a");
                if(orderHistory == NULL){
                    printf("\nError opening order history file");
                    free(cart);
                    fclose(db);
                    return;
                }
                fprintf(orderHistory, "%s\tQuantity: %d\tPrice: $%.2f\n", cart[count].name, cart[count].quantity, price);
                fclose(orderHistory);
                break;
            }
        }
        if(found!=1){
            printf("\nThe item does not exist!");
        }else{
            count++;
        }
    }

    free(cart);
    fclose(db);

    printf("\nThe total cost of your cart is: $%.2f\n", totalCost);
	n = count;
	return;
}

void removeFromCart(float *totalCost){                           // remove from cart
	
    char itemToRemove[30];
    int removeQuantity;

    printf("\nEnter the name of the item to remove: ");
    scanf("%s", itemToRemove);

    printf("\nEnter the quantity to remove: ");
    scanf("%d", &removeQuantity);
   
    FILE *orderHistory = fopen("order_history.txt","r");
    FILE *tempFile = fopen("temp_order_history.txt","w");
    if(orderHistory == NULL || tempFile == NULL){
        printf("Error opening file\n");
        return;
    }

	char *productName = (char *)malloc(100 * sizeof(char));  
    if (productName == NULL) {
        printf("Memory Allocation Failed for itemName!\n");
        fclose(orderHistory);
        fclose(tempFile);
        return;
    }

    // buffer
    char *line = (char *)malloc(100 * sizeof(char));
    if (line == NULL) {
        printf("Memory Allocation Failed for line!\n");
		free(productName);
        fclose(orderHistory);
        fclose(tempFile);
        return;
    }

    int found = 0;

    while(fgets(line,100,orderHistory) != NULL){
		
        int itemQuantity;
        float itemPrice;

        sscanf(line, "%s Quantity: %d Price: %f", productName, &itemQuantity, &itemPrice);

        if(strcmp(productName,itemToRemove) == 0){
            found = 1;
            if(removeQuantity >= itemQuantity){
                printf("\nRemoved all %s from the cart.\n",productName);

                *totalCost -= itemQuantity * itemPrice;
            }else{
                printf("\nRemoved %d of %s from the cart.\n",removeQuantity,productName);

                *totalCost -= removeQuantity * itemPrice;
                itemQuantity -= removeQuantity;

                fprintf(tempFile, "%s\tQuantity: %d\tPrice: %.2f\n",productName,itemQuantity,itemPrice);
            }
        }else{
            fprintf(tempFile,"%s",line);
        }
    }

    fclose(orderHistory);
    fclose(tempFile);

    remove("order_history.txt");
    rename("temp_order_history.txt", "order_history.txt");

    if(!found){
        printf("Item not found in the cart.\n");
    }
    printf("\nUpdated total cost: $%.2f\n", *totalCost);

    // Free
	free(productName);
    free(line);
}

// -------------------Report Generate  Function HERE--------------
//struct reportData { // Reports
//	char name[20];
//    int qty;
//    float price;
//    unsigned int ordersPlaced;
//    // items sort a/c to sale
//} *sold, *stockRemain;  // sold: Sold Items' table & stockRemain: Stock Items Table // malloc not done // shift struct to top

// -------------------Report Generate  Function HERE--------------

void genReport(/*int option, *//*int noOfItems or nP*/) {     // noOfitems remaning
	int DD, MM, YYYY;
	struct reportData *sold = malloc(3 * sizeof(struct reportData));
    struct reportData *stockRemain = malloc(3 * sizeof(struct reportData));
    
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
    if(reportBIN == NULL) {
        perror(RED "\n\tError Processing Binary File" WHITE);
        return;
    }
	fwrite(sold, sizeof(struct reportData), 1, reportBIN);	// Store one latest calculated struct for sold items in the bin
	fwrite(stockRemain, sizeof(struct reportData), 1, reportBIN);	// Store one latest calculated struct for sold items in the bin
    fclose(reportBIN);  // DONE Storing in Binary

    // Generating Report (Text File)
    reportTXT = fopen("U:\\report.txt", "a");  // Chk if address work
    if(reportTXT == NULL) {
        perror(RED "\n\tError Processing Text File" WHITE);
        return;
    }
    fprintf(reportTXT, "\n\t\tReport Generated on Date: %s/%s/%s", DD, MM, YYYY);
    // ----------------* SOLD *-----------------
	fprintf(reportTXT, "\n\n****************** Sales ******************\n");	// remove first \n\n for file writing
	fprintf(reportTXT, "-------------------------------------------\n");
	fprintf(reportTXT, " S.No.\tIems\tSold Qty\tPrice\n");
	// sorting not done yet, instead only highest & lowest sales can be printed
	for(int i = 0; i < 3/*noOfItems or nP*/; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, sold[i].name, sold[i].qty, sold[i].price);
	}
	printf("-------------------------------------------\n");

    // --------------* REMAINING *-----------------
    printf("\n\n****************** Stock Level ******************\n");	// remove first \n\n for file writing
	printf("-------------------------------------------\n");
	printf(" S.No.\tIems\tRemaining Qty\tPrice\n");
	// Sorting not done yet
	for(int i = 0; i < 3/*noOfItems*/; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, stockRemain[i].name, stockRemain[i].qty, stockRemain[i].price);
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
	for(int i = 0; i < 3/*noOfItems*/; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, sold[i].name, sold[i].qty, sold[i].price);
	}
	printf("-------------------------------------------\n");
    // ---------------STOCK LEVEL-------------------
    printf("\n\n****************** Stock Level ******************\n");	// remove first \n\n for file writing   // add color
	printf("-------------------------------------------\n");
	printf(" S.No.\tIems\tRemaining Qty\tPrice\n");
	// Sorting not done yet
	for(int i = 0; i < 3/*noOfItems*/; i++) {
		printf("%d\t%s %d\t$%d\n", i + 1, stockRemain[i].name, stockRemain[i].qty, stockRemain[i].price);
	}
	printf("-------------------------------------------\n");
    printf(GREEN "\n\n\t\tReport Generated at \"U:\\report.txt\"" WHITE);    // FINISHED Report on Terminal
	
    // file wali report open krwado system("cd C:\report.txt"); agr user view reports history
}