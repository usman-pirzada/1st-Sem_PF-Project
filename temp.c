#include <stdio.h>
#include <stdlib.h>

// Assuming RED, GREEN, etc., are predefined for colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define WHITE "\033[0m"
#define BOLD "\033[1m"

struct product {
    int ID;
    char name[30];
    int quantity;
    float price;
};


// Function prototypes
void enter(int mode, const char *filename);
void menu(int userType);
void menu(int userType);
void addInventory();
void removeInventory();
void viewInventory();
void addToCart(int *itemCount, float *totalCost);
void removeFromCart(float *totalCost);

int main() {
    int option;
    FILE *adminFile = fopen("Admins.bin", "rb");
    FILE *userFile = fopen("Users.bin", "rb");

    system(""); // To enable formatting & colors (Windows-specific)
    printf(BOLD BLUE "\n\t\tFAST Super Mart");
    printf("\n\t\t==================" WHITE);

    // Initial account check
    if (adminFile == NULL && userFile == NULL) {
        printf(RED "\nNo Account Created Yet!!");
        printf(YELLOW " Please Create an Account to Proceed:\n 1) Create Admin Account\n 2) Create User Account\n 3) Exit\n" WHITE);
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\nNow SignUp below for Admin Account\n");
                enter(2, "Admins.bin");
                printf(GREEN "\n\tAdmin Account Added Successfully!\n" WHITE);
                break;
            case 2:
                printf("\nNow SignUp below for User Account\n");
                enter(2, "Users.bin");
                printf(GREEN "\n\tUser Account Added Successfully!\n" WHITE);
                break;
            case 3:
                exit(0);
            default:
                printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
        }
    }
    if (adminFile) fclose(adminFile);
    if (userFile) fclose(userFile);

    // Main menu loop
    while (1) {
        printf("\nWhich operation do you want to perform: \n");
        printf("\n 1) Admin Login\n 2) User Login\n 3) Add Admin\n 4) Add User\n 5) Exit\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                enter(1, "Admins.bin");
                printf(GREEN "\n\tAdmin Login Successful!\n" WHITE);
                menu(1);
                break;
            case 2:
                enter(1, "Users.bin");
                printf(GREEN "\n\tUser Login Successful!\n" WHITE);
                menu(2);
                break;
            case 3:
                enter(2, "Admins.bin");
                printf(GREEN "\n\tNew Admin Added Successfully!\n" WHITE);
                break;
            case 4:
                enter(2, "Users.bin");
                printf(GREEN "\n\tNew User Added Successfully!\n" WHITE);
                break;
            case 5:
                exit(0);
            default:
                printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
        }
    }

    return 0;
}

// ------------------FUNCTIONS-----------------------------

void enter(int log, const char *filename) {
    struct Account *accounts = NULL;

    // Memory allocation for one account initially
    accounts = (struct Account *)malloc(sizeof(struct Account));
    if (accounts == NULL) {
        printf(RED "\nError Allocating Memory!!" WHITE);
        exit(1); // Exit instead of recursive call
    }

    if (log == 1) { // Login
        FILE *fileRead = fopen(filename, "rb");
        if (fileRead == NULL) {
            perror(RED "\n\tError Opening File" WHITE);
            free(accounts);
            exit(1);
        }

        // Determine number of accounts in the file
        fseek(fileRead, 0, SEEK_END);
        long fileSize = ftell(fileRead);
        rewind(fileRead);
        int accountCount = fileSize / sizeof(struct Account);

        // Resize accounts array based on file size
        accounts = (struct Account *)realloc(accounts, accountCount * sizeof(struct Account));
        if (accounts == NULL) {
            printf(RED "\nError Allocating Memory!!" WHITE);
            fclose(fileRead);
            exit(1);
        }

        // Read all accounts into memory
        fread(accounts, sizeof(struct Account), accountCount, fileRead);
        fclose(fileRead);

        // Login prompt
        char username[20], password[15];
        printf("\nEnter Your Username: ");
        scanf("%19s", username);
        printf("Enter Your Password: ");
        scanf("%14s", password);

        // Validate credentials
        int loginSuccess = 0;
        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
                printf(GREEN "\nLogin successful!!\n" WHITE);
                loginSuccess = 1;
                break;
            }
        }

        if (!loginSuccess) {
            printf(RED "\nInvalid Username or Password!!\n" WHITE);
        }

        free(accounts);
    } 
    else if (log == 2) { // Signup
        FILE *fileWrite = fopen(filename, "ab");
        if (fileWrite == NULL) {
            perror(RED "\n\tError Opening File" WHITE);
            free(accounts);
            exit(1);
        }

        // Collect signup data
        printf("\nSet Your Username: ");
        scanf("%19s", accounts[0].username);
        printf("Set Your Password (Length 8 to 20 digits): ");
        scanf("%14s", accounts[0].password);

        // Validate password length
        if (strlen(accounts[0].password) < 8 || strlen(accounts[0].password) > 14) {
            printf(RED "\nPassword length must be between 8 and 14 characters!\n" WHITE);
            fclose(fileWrite);
            free(accounts);
            return;
        }

        // Write signup data to file
        fwrite(accounts, sizeof(struct Account), 1, fileWrite);
        fclose(fileWrite);

        printf(GREEN "\nSignup successful!!\n" WHITE);
        free(accounts);
    } 
    else {
        printf(RED "\n\n\tInvalid Option!!\n" WHITE);
        free(accounts);
    }
}


void menu(int userType) {   // 1 for Admin & 2 for Ordinary User
    int option;

    if (userType == 1) { // Admin Menu
        while (1) {
            printf("\nAdmin Menu:\n");
            printf(" 1) Add New Item to Stock\n");
            printf(" 2) View Stock Status\n");
            printf(" 3) Generate Report\n");
            printf(" 4) LogOut\n");
            printf(" 5) Exit Program & LogOut\n");
            printf("Enter your choice: ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("\nAdding new item to stock...\n");
                    addInventory(); // Call function to add inventory
                    break;
                case 2:
                    printf("\nViewing stock status...\n");
                    viewInventory(); // Call function to view inventory
                    break;
                case 3:
                    printf("\nGenerating report...\n");
                    genReport(userType); // Call function to generate report for Admin
                    break;
                case 4:
                    printf("\nLogging out...\n");
                    return; // Return to main menu
                case 5:
                    printf("\nExiting program...\n");
                    exit(0); // Exit program
                default:
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }

    } else if (userType == 2) { // User Menu
        while (1) {
            printf("\nUser Menu:\n");
            printf(" 1) Add Item to Cart\n");
            printf(" 2) Remove Item from Cart\n");
            printf(" 3) Place Order\n");
            printf(" 4) LogOut\n");
            printf(" 5) Exit Program & Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("\nAdding item to cart...\n");
                    addToCart(0, 0.0); // Call function to add to cart
                    break;
                case 2:
                    printf("\nRemoving item from cart...\n");
                    removeFromCart(NULL); // Call function to remove from cart
                    break;
                case 3:
                    printf("\nPlacing order...\n");
                    // Function to place order and generate receipt
                    break;
                case 4:
                    printf("\nLogging out...\n");
                    return; // Return to main menu
                case 5:
                    printf("\nExiting program...\n");
                    exit(0); // Exit program
                default:
                    printf(RED "\n\tInvalid Input!! Try Again\n" WHITE);
            }
        }
    } else {
        printf(RED "\nInvalid user type!\n" WHITE);
    }
}

void addInventory() {
    FILE *file = fopen("inventory.txt", "a+"); // Open in append mode with read access
    if (!file) {
        printf(RED "Error opening inventory file.\n" WHITE);
        return;
    }

    // Check if the file is empty to add default products
    fseek(file, 0, SEEK_END); // Move to end of the file
    if (ftell(file) == 0) { // File is empty
        printf(YELLOW "File is empty. Adding default products...\n" WHITE);
        struct product defaultProducts[15] = {
            {100, "Bread", 100, 2.0},
            {101, "Milk", 50, 1.0},
            {102, "Eggs", 30, 3.0},
            {103, "Rice", 20, 10.0},
            {104, "Sugar", 20, 3.0},
            {105, "CookingOil", 25, 5.0},
            {106, "Salt", 50, 1.0},
            {107, "Tomatoes", 30, 2.0},
            {108, "Potatoes", 40, 1.0},
            {109, "Onions", 30, 1.0},
            {110, "CannedBeans", 20, 2.0},
            {111, "ToiletPaper", 40, 1.0},
            {112, "DishLiquid", 15, 2.0},
            {113, "Shampoo", 20, 3.0},
            {114, "Toothpaste", 25, 1.0}
        };
        for (int i = 0; i < 15; i++) {
            fprintf(file, "%d %s %d %.2f\n", defaultProducts[i].ID, defaultProducts[i].name, defaultProducts[i].quantity, defaultProducts[i].price);
        }
        printf(GREEN "Default products added successfully.\n" WHITE);
    }

    // Add new product
    struct product newProd;
    printf("\nEnter product name (max 29 chars): ");
    scanf("%29s", newProd.name);
    printf("Enter product quantity: ");
    scanf("%d", &newProd.quantity);
    printf("Enter product price: ");
    scanf("%f", &newProd.price);

    // Generate next product ID
    int lastID = 100; // Default starting ID
    fseek(file, 0, SEEK_SET); // Move to the start of the file
    struct product tempProd;
    while (fscanf(file, "%d %s %d %f", &tempProd.ID, tempProd.name, &tempProd.quantity, &tempProd.price) == 4) {
        lastID = tempProd.ID;
    }
    newProd.ID = lastID + 1;

    fprintf(file, "%d %s %d %.2f\n", newProd.ID, newProd.name, newProd.quantity, newProd.price);
    printf(GREEN "Product added successfully with ID: %d\n" WHITE, newProd.ID);

    fclose(file);
}

void removeInventory() {
    int id;
    printf("\nEnter product ID to remove: ");
    scanf("%d", &id);

    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf(RED "Error opening inventory file.\n" WHITE);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf(RED "Error creating temporary file.\n" WHITE);
        fclose(file);
        return;
    }

    struct product prod;
    int found = 0;
    while (fscanf(file, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) == 4) {
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
        printf(GREEN "Product with ID %d removed successfully.\n" WHITE, id);
    } else {
        remove("temp.txt");
        printf(YELLOW "Product ID %d not found.\n" WHITE, id);
    }
}

void viewInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf(RED "Error opening inventory file.\n" WHITE);
        return;
    }

    struct product prod;
    printf("\nProduct Inventory:\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");
    while (fscanf(file, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) == 4) {
        printf("%d\t%-15s\t%d\t\t%.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
    }

    fclose(file);
}

void addToCart(int *itemCount, float *totalCost) { // Passing pointers for updates
    FILE *db = fopen("products.txt", "r");
    if (db == NULL) {
        printf(RED "Error opening product database.\n" WHITE);
        return;
    }

    struct product *cart = NULL; // Dynamic memory allocation
    int count = *itemCount;     // Current number of items in cart

    while (1) {
        // Allocate memory for an additional item
        cart = (struct product *)realloc(cart, (count + 1) * sizeof(struct product));
        if (cart == NULL) {
            printf(RED "Memory Allocation Failed!\n" WHITE);
            fclose(db);
            return;
        }

        printf("\nEnter the name of the item (or type 'exit' to finish): ");
        scanf("%s", cart[count].name);

        if (strcmp(cart[count].name, "exit") == 0) {
            break;
        }

        printf("Enter Quantity: ");
        scanf("%d", &cart[count].quantity);

        // Search for the item in the database
        fseek(db, 0, SEEK_SET); // Reset file pointer
        int found = 0;
        struct product dbProduct;

        while (fscanf(db, "%s %d %f", dbProduct.name, &dbProduct.quantity, &dbProduct.price) == 3) {
            if (strcmp(cart[count].name, dbProduct.name) == 0) {
                found = 1;
                if (dbProduct.quantity <= 0) {
                    printf(RED "This item is out of stock.\n" WHITE);
                    break;
                } else if (dbProduct.quantity < cart[count].quantity) {
                    printf(YELLOW "Only %d %s available in stock.\n" WHITE, dbProduct.quantity, dbProduct.name);
                    break;
                }

                // Add to cart
                cart[count].price = dbProduct.price;
                *totalCost += cart[count].quantity * dbProduct.price;

                // Log order
                FILE *orderHistory = fopen("order_history.txt", "a");
                if (orderHistory == NULL) {
                    printf(RED "Error opening order history file.\n" WHITE);
                    free(cart);
                    fclose(db);
                    return;
                }
                fprintf(orderHistory, "%s Quantity: %d Price: $%.2f\n", cart[count].name, cart[count].quantity, dbProduct.price);
                fclose(orderHistory);

                printf(GREEN "Added to cart successfully!\n" WHITE);
                count++;
                break;
            }
        }

        if (!found) {
            printf(YELLOW "The item does not exist in the database.\n" WHITE);
        }
    }

    free(cart);
    fclose(db);

    printf("\nThe total cost of your cart is: $%.2f\n", *totalCost);
    *itemCount = count; // Update item count
}

void removeFromCart(float *totalCost) {
    char itemToRemove[30];
    int removeQuantity;

    printf("\nEnter the name of the item to remove: ");
    scanf("%s", itemToRemove);

    printf("Enter the quantity to remove: ");
    scanf("%d", &removeQuantity);

    FILE *orderHistory = fopen("order_history.txt", "r");
    FILE *tempFile = fopen("temp_order_history.txt", "w");
    if (orderHistory == NULL || tempFile == NULL) {
        printf(RED "Error opening files.\n" WHITE);
        return;
    }

    int found = 0;
    char name[30];
    int quantity;
    float price;

    while (fscanf(orderHistory, "%s Quantity: %d Price: %f", name, &quantity, &price) == 3) {
        if (strcmp(name, itemToRemove) == 0) {
            found = 1;
            if (removeQuantity >= quantity) {
                printf(GREEN "Removed all %s from the cart.\n" WHITE, name);
                *totalCost -= quantity * price;
            } else {
                printf(GREEN "Removed %d of %s from the cart.\n" WHITE, removeQuantity, name);
                *totalCost -= removeQuantity * price;
                quantity -= removeQuantity;
                fprintf(tempFile, "%s Quantity: %d Price: %.2f\n", name, quantity, price);
            }
        } else {
            fprintf(tempFile, "%s Quantity: %d Price: %.2f\n", name, quantity, price);
        }
    }

    fclose(orderHistory);
    fclose(tempFile);

    if (found) {
        remove("order_history.txt");
        rename("temp_order_history.txt", "order_history.txt");
    } else {
        remove("temp_order_history.txt");
        printf(YELLOW "Item not found in the cart.\n" WHITE);
    }

    printf("\nUpdated total cost: $%.2f\n", *totalCost);
}
