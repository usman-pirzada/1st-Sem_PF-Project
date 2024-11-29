#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for product details
struct product {
    int ID;        // Added product ID
    char name[20];
    int quantity;
    int price;
};

// Structure for handling the user's cart
struct cartItem {
    char name[20];
    int quantity;
};

// Function prototypes
int login(int log);      //usman
void addToCart(struct cartItem cart[], int *cartSize);        //mujtaba
void removeFromCart(struct cartItem cart[], int *cartSize);     //mujtaba
void generateBill(struct cartItem cart[], int cartSize);      //mujtaba
void viewInventory();             //talal
void addInventory();               //talal
void removeInventory();             //talal
void generateReport();   //usman

// Main function
int main() {
    int choice, cartSize = 0;
    struct cartItem cart[10];  // Cart to hold added items
   
    // Add default items to inventory when program starts
    addInventory();

    while (1) {
        printf("\n==========================\n");
        printf("1. Employee Options\n");
        printf("2. Manager Options\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int loggedIn = 0;
        int signedUp = 0;
        switch (choice) {
            case 1:
                printf("1. Login\n");
                printf("2. Signup\n");
                printf("Enter your choice: ");
                scanf("%d",&choice);
                switch(choice){
                    case 1:
                        if(login(1)){
                            printf("Login successful.\n");
                            loggedIn = 1;
                        }
                        else{
                            printf("Login Failed.\n");
                        }
                        break;
                    case 2:
                        if(login(2)){
                            printf("Signup successful.\n");
                            signedUp = 1;
                        }
                        else{
                            printf("Signup failed.\n");
                        }
                        break;
                    default:
                        printf("Invalid choice\n");        
                }

                if(loggedIn == 1 || signedUp == 1){
                    printf("\nEmployee Options:\n");
                    printf("1. Add to Cart\n");
                    printf("2. Remove from Cart\n");
                    printf("3. View Inventory\n");
                    printf("4. Place Order\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addToCart(cart, &cartSize);
                            break;
                        case 2:
                            removeFromCart(cart, &cartSize);
                            break;
                        case 3:
                            viewInventory();
                            break;
                        case 4:
                            generateBill(cart, cartSize);
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                }
                break;

            case 2:
                printf("1. Login\n");
                printf("2. Signup\n");
                printf("Enter your choice: ");
                scanf("%d",&choice);
                switch(choice){
                    case 1:
                        if(login(1)){
                            printf("Login successful.\n");
                            loggedIn = 1;
                        }
                        else{
                            printf("Login Failed.\n");
                        }
                        break;
                    case 2:
                        if(login(2)){
                            printf("Signup successful.\n");
                            signedUp = 1;
                        }
                        else{
                            printf("Signup failed.\n");
                        }
                        break;
                    default:
                        printf("Invalid choice\n");        
                }

                if(loggedIn == 1 || signedUp == 1){
                    printf("\nManager Options:\n");
                    printf("1. Add Inventory\n");
                    printf("2. Remove Inventory\n");
                    printf("3. View Inventory\n");
                    printf("4. Generate Report\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addInventory();
                            break;
                        case 2:
                            removeInventory();
                            break;
                        case 3:
                            viewInventory();
                            break;
                        case 4:
                            generateReport();
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                }    
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

// Login/Signup function
int login(int log) {
    char username[50], pass[21];  // Declare pass here
    FILE *file;
   
    if (log == 1) {  // Login
        printf("\nEnter Your Username: ");
        scanf("%s", username);
        printf("Enter Your Password: ");
        scanf("%s", pass);

        file = fopen("users.txt", "r");
        if (file == NULL) {
            printf("\nNo users found! Please sign up first.\n");
            return 'N';
        }

        char fileUsername[16], filePass[21];
        int found = 0;

        while (fscanf(file, "%s %s", fileUsername, filePass) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0) {
                found = 1;
                break;
            }
        }

        fclose(file);
        if (found) {
            return 'Y';
        } else {
            printf("\nInvalid credentials.\n");
            return 'N';
        }

    } else if (log == 2) {  // Signup
        printf("\nEnter a new username: ");
        scanf("%s", username);
        printf("Enter a new password: ");
        scanf("%s", pass);

        file = fopen("users.txt", "a");
        if (file == NULL) {
            printf("Error opening file for signup.\n");
            return 'N';
        }

        fprintf(file, "%s %s\n", username, pass);
        fclose(file);

        return 'Y';
    }

    return 'N';
}

// Function to view inventory
void viewInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening inventory.\n");
        return;
    }

    struct product prod;
    printf("\nProduct Inventory:\n");
    while (fscanf(file, "%d %s %d %d", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        printf("%d %s - Quantity: %d - Price: %d\n", prod.ID, prod.name, prod.quantity, prod.price);
    }

    fclose(file);
}

// Function to add inventory (Manager)
void addInventory() {
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

// Function to remove inventory (Manager)
void removeInventory() {
    printf("Remove Inventory functionality goes here.\n");
}

// Function to generate bill for the user (Employee)
void generateBill(struct cartItem cart[], int cartSize) {
    printf("Generating Bill...\n");
    // Implementation goes here
}

// Function to generate report (Manager)
void generateReport() {
    printf("Generating report functionality goes here.\n");
}
