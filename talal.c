#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for product details
struct product {
    int ID;
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
int login(int log);
void addToCart(struct cartItem cart[], int *cartSize);
void removeFromCart(struct cartItem cart[], int *cartSize);
void generateBill(struct cartItem cart[], int cartSize);
void viewInventory();
void addInventory();
void removeInventory();
void generateReport();

// Main function
int main() {
    int choice, cartSize = 0;
    struct cartItem cart[10];  // Cart to hold added items
   
    while (1) {
        printf("\n==========================\n");
        // printf("1. Login\n");
        // printf("2. Signup\n");
        printf("3. Employee Options\n");
        printf("4. Manager Options\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login(1) == 'Y') {
                    printf("Login successful.\n");
                } else {
                    printf("Login failed.\n");
                }
                break;

            // case 2:
            //     if (login(2) == 'Y') {
            //         printf("Signup successful.\n");
            //     } else {
            //         printf("Signup failed.\n");
            //     }
            //     break;

            case 3:
                printf("\nEmployee Options:\n");
                printf("1. Add to Cart\n");
                printf("2. Remove from Cart\n");
                printf("3. View Inventory\n");
                printf("4. Proceed to Order\n");
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
                break;

            case 4:
                printf("\nManager Options:\n");
                printf("1. Add Inventory\n");
                printf("2. Remove Inventory\n");
                printf("3. Track Product Stock\n");
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
                break;

            case 5:
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
    char username[16], pass[21];
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

// Function to add item to cart
void addToCart(struct cartItem cart[], int *cartSize) {
    FILE *inventoryFile = fopen("inventory.txt", "r");
    if (!inventoryFile) {
        printf("Error opening inventory.\n");
        return;
    }

    struct product prod;
    char productName[20];
    int quantityToAdd, availableQuantity;
   
    printf("Enter product name to add to cart: ");
    scanf("%s", productName);
    printf("Enter quantity to add: ");
    scanf("%d", &quantityToAdd);

    // Search the product in inventory
    int found = 0;
    while (fscanf(inventoryFile, "%s %d %d", prod.name, &prod.quantity, &prod.price) != EOF) {
        if (strcmp(prod.name, productName) == 0) {
            found = 1;
            availableQuantity = prod.quantity;
            if (availableQuantity >= quantityToAdd) {
                strcpy(cart[*cartSize].name, productName);
                cart[*cartSize].quantity = quantityToAdd;
                (*cartSize)++;
                printf("Item added to cart.\n");
            } else {
                printf("Not enough stock available.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Product not found in inventory.\n");
    }

    fclose(inventoryFile);
}

// Function to remove item from cart
void removeFromCart(struct cartItem cart[], int *cartSize) {
    if (*cartSize == 0) {
        printf("Your cart is empty.\n");
        return;
    }

    char productName[20];
    printf("Enter product name to remove from cart: ");
    scanf("%s", productName);

    int found = 0;
    for (int i = 0; i < *cartSize; i++) {
        if (strcmp(cart[i].name, productName) == 0) {
            for (int j = i; j < *cartSize - 1; j++) {
                cart[j] = cart[j + 1];
            }
            (*cartSize)--;
            printf("Item removed from cart.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found in cart.\n");
    }
}

// Function to generate bill
void generateBill(struct cartItem cart[], int cartSize) {
    if (cartSize == 0) {
        printf("Your cart is empty.\n");
        return;
    }

    int totalPrice = 0;
    printf("\nBill Summary:\n");
    for (int i = 0; i < cartSize; i++) {
        printf("%s - Quantity: %d\n", cart[i].name, cart[i].quantity);
        totalPrice += cart[i].quantity * 100;  // Example: assuming price is 100 per item
    }

    printf("Total Bill: %d\n", totalPrice);
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
    while (fscanf(file, "%s %d %d", prod.name, &prod.quantity, &prod.price) != EOF) {
        printf("%s - Quantity: %d - Price: %d\n", prod.name, prod.quantity, prod.price);
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

    struct product prod;
    printf("Enter product name to add: ");
    scanf("%s", prod.name);
    printf("Enter product quantity: ");
    scanf("%d", &prod.quantity);
    printf("Enter product price: ");
    scanf("%d", &prod.price);

    fprintf(file, "%s %d %d\n", prod.name, prod.quantity, prod.price);
    fclose(file);
    printf("Product added to inventory.\n");
}

// Function to remove inventory (Manager)
void removeInventory() {
    // Placeholder for removing inventory
    printf("Remove inventory functionality not implemented yet.\n");
}

// Function to generate report (Manager)
void generateReport() {
    // Placeholder for report generation
    printf("Generate report functionality not implemented yet.\n");
}