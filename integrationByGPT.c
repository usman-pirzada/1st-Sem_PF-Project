#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Define product structure
struct product {
    int ID;
    char name[50];
    int quantity;
    float price;
};
struct Account {
    char username[20];
    char password[20];
};

// Function prototypes
void addInventory();
void removeInventory();
void viewInventory();
void addToCart(int n, float *totalCost);
void removeFromCart(float *totalCost);
void genReport(int noOfItems);
void enter(int log, const char *filename);
void menu(int userType);

int accountsCount;  // For accounts management

// Main function
int main() {
    int option;
    FILE *adminFile = NULL;
    FILE *userFile = NULL;

    system("");  // Enable formatting & colors (if needed on Windows)

    printf("\n\t\t\tSuper Mart System");
    printf("\n\t\t\t================\n");
    adminFile = fopen("Admins.bin", "rb");
    userFile = fopen("Users.bin", "rb");

    if (adminFile == NULL && userFile == NULL) {
        accountsCount = 2;  // Default accounts count
        printf("\n\n\t\tWELCOME to Your First Run!\n\n");
        printf("Please Create an Account to Proceed:\n");
        printf("1) Create Admin Account\n2) Create User Account\n3) Exit\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\nNow SignUp below for Admin Account\n");
                enter(2, "Admins.bin");
                break;
            case 2:
                printf("\nNow SignUp below for User Account\n");
                enter(2, "Users.bin");
                break;
            case 3:
                exit(0);
            default:
                printf("\nInvalid Input! Exiting...");
                exit(1);
        }
    }
    fclose(adminFile);
    fclose(userFile);

    while (1) {
        printf("\nWhich operation do you want to perform:\n");
        printf("1) Admin Login\n2) User Login\n3) Exit\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                enter(1, "Admins.bin");
                menu(1);  // Admin Menu
                break;
            case 2:
                enter(1, "Users.bin");
                menu(2);  // User Menu
                break;
            case 3:
                exit(0);
            default:
                printf("\nInvalid Input! Try Again.\n");
        }
    }
    return 0;
}

// Function to manage account creation and login
void enter(int log, const char *filename) {
    struct Account accounts[20];
    FILE *file = (log == 1) ? fopen(filename, "rb") : fopen(filename, "ab");
    if (!file) {
        printf("Error accessing file!\n");
        return;
    }

    if (log == 1) {
        char username[20], password[20];
        int valid = 0;

        printf("Enter username: ");
        scanf("%s", &username);
        printf("Enter password: ");
        scanf("%s", &password);

        while (fread(accounts, sizeof(accounts[0]), 1, file)) {
            if (strcmp(accounts->username, username) == 0 && strcmp(accounts->password, password) == 0) {
                valid = 1;
                break;
            }
        }
        fclose(file);
        if (!valid) {
            printf("Invalid credentials! Try again.\n");
            return;
        }
        printf("Login successful!\n");
    } else {
        struct product newAccount;
        printf("Set username: ");
        scanf("%s", newAccount.name);
        printf("Set password: ");
        scanf("%s", newAccount.price);

        fwrite(&newAccount, sizeof(newAccount), 1, file);
        fclose(file);
        printf("Account created successfully!\n");
    }
}

// Function for Admin and User menus
void menu(int userType) {
    int option;
    if (userType == 1) {  // Admin Menu
        while (1) {
            printf("\nAdmin Menu:\n");
            printf("1) Add Inventory\n2) View Inventory\n3) Remove Inventory\n4) Generate Report\n5) Logout\n");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    addInventory();
                    break;
                case 2:
                    viewInventory();
                    break;
                case 3:
                    removeInventory();
                    break;
                case 4:
                    genReport(10);  // Pass sample number of items
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid input! Try again.\n");
            }
        }
    } else {  // User Menu
        float totalCost = 0;
        int n = 0;

        while (1) {
            printf("\nUser Menu:\n");
            printf("1) Add to Cart\n2) Remove from Cart\n3) Logout\n");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    addToCart(n, &totalCost);
                    break;
                case 2:
                    removeFromCart(&totalCost);
                    break;
                case 3:
                    return;
                default:
                    printf("Invalid input! Try again.\n");
            }
        }
    }
}

void addInventory() {
    FILE *file = fopen("inventory.txt", "a");
    if (!file) {
        printf("Error opening inventory file.\n");
        return;
    }

    struct product prod;
    printf("Enter product name to add: ");
    scanf("%s", prod.name);
    printf("Enter product quantity: ");
    scanf("%d", &prod.quantity);
    printf("Enter product price: ");
    scanf("%f", &prod.price);

    // Assign product ID based on the last ID in the file
    fseek(file, -1, SEEK_END);
    int lastID = 0;
    if (ftell(file) > 0) {  // Check if file is not empty
        while (fscanf(file, "%d %s %d %f", &lastID, prod.name, &prod.quantity, &prod.price) != EOF);
    }
    prod.ID = lastID + 1;

    fprintf(file, "%d %s %d %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
    printf("Product added successfully.\n");
    fclose(file);
}

void removeInventory() {
    int id;
    printf("Enter product ID to remove: ");
    scanf("%d", &id);

    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening inventory file.\n");
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
        printf("Error opening inventory file.\n");
        return;
    }

    struct product prod;
    printf("\nProduct Inventory:\n");
    while (fscanf(file, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        printf("ID: %d | Name: %s | Quantity: %d | Price: $%.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
    }
    fclose(file);
}
void addToCart(int n, float *totalCost) {
    FILE *inventory = fopen("inventory.txt", "r");
    if (!inventory) {
        printf("Error opening inventory file.\n");
        return;
    }

    FILE *cart = fopen("cart.txt", "a");
    if (!cart) {
        printf("Error opening cart file.\n");
        fclose(inventory);
        return;
    }

    char itemName[50];
    int quantity;
    struct product prod;
    int found = 0;

    printf("Enter the name of the item to add to the cart: ");
    scanf("%s", itemName);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    while (fscanf(inventory, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        if (strcmp(prod.name, itemName) == 0) {
            found = 1;
            if (quantity > prod.quantity) {
                printf("Not enough stock available.\n");
            } else {
                fprintf(cart, "%d %s %d %.2f\n", prod.ID, prod.name, quantity, prod.price);
                *totalCost += quantity * prod.price;
                printf("Added to cart. Total cost: $%.2f\n", *totalCost);
            }
            break;
        }
    }

    if (!found) {
        printf("Item not found in inventory.\n");
    }

    fclose(inventory);
    fclose(cart);
}

void removeFromCart(float *totalCost) {
    FILE *cart = fopen("cart.txt", "r");
    if (!cart) {
        printf("Error opening cart file.\n");
        return;
    }

    FILE *temp = fopen("temp_cart.txt", "w");
    if (!temp) {
        printf("Error opening temporary file.\n");
        fclose(cart);
        return;
    }

    char itemName[50];
    int quantityToRemove;
    struct product prod;
    int found = 0;

    printf("Enter the name of the item to remove from the cart: ");
    scanf("%s", itemName);
    printf("Enter quantity to remove: ");
    scanf("%d", &quantityToRemove);

    while (fscanf(cart, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        if (strcmp(prod.name, itemName) == 0) {
            found = 1;
            if (quantityToRemove >= prod.quantity) {
                *totalCost -= prod.quantity * prod.price;
                printf("Removed all %s from the cart.\n", prod.name);
            } else {
                prod.quantity -= quantityToRemove;
                *totalCost -= quantityToRemove * prod.price;
                fprintf(temp, "%d %s %d %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
                printf("Removed %d of %s from the cart.\n", quantityToRemove, prod.name);
            }
        } else {
            fprintf(temp, "%d %s %d %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
        }
    }

    fclose(cart);
    fclose(temp);

    if (found) {
        remove("cart.txt");
        rename("temp_cart.txt", "cart.txt");
        printf("Updated total cost: $%.2f\n", *totalCost);
    } else {
        remove("temp_cart.txt");
        printf("Item not found in the cart.\n");
    }
}
void genReport(int noOfItems) {
    FILE *inventory = fopen("inventory.txt", "r");
    if (!inventory) {
        printf("Error opening inventory file.\n");
        return;
    }

    FILE *report = fopen("report.txt", "w");
    if (!report) {
        printf("Error opening report file.\n");
        fclose(inventory);
        return;
    }

    struct product prod;
    fprintf(report, "Inventory Report:\n");
    fprintf(report, "ID\tName\tQuantity\tPrice\n");
    fprintf(report, "---------------------------------\n");

    while (fscanf(inventory, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        fprintf(report, "%d\t%s\t%d\t$%.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
    }

    printf("Report generated successfully. Check 'report.txt'.\n");
    fclose(inventory);
    fclose(report);
}