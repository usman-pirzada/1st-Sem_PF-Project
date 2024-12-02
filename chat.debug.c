#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product {
    int ID;
    char name[30];
    int quantity;
    float price;
};

void addInventory() {  // Add inventory
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
            {100, "Bread", 100, 2.5},
            {101, "Milk", 50, 1.5},
            {102, "Eggs", 30, 3.0},
            {103, "Rice", 20, 10.0},
            {104, "Sugar", 20, 3.0},
            {105, "Cooking Oil", 25, 5.0},
            {106, "Salt", 50, 1.0},
            {107, "Tomatoes", 30, 2.0},
            {108, "Potatoes", 40, 1.0},
            {109, "Onions", 30, 1.0},
            {110, "Canned Beans", 20, 2.5},
            {111, "Toilet Paper", 40, 1.0},
            {112, "Dishwashing Liquid", 15, 2.5},
            {113, "Shampoo", 20, 3.5},
            {114, "Toothpaste", 25, 1.5}
        };

        // Write the products to the file
        for (int i = 0; i < 15; i++) {
            fprintf(file, "%d %s %d %.2f\n", prod[i].ID, prod[i].name, prod[i].quantity, prod[i].price);
        }

        printf("Default products added to inventory.\n");
    }

    struct product prod;
    printf("Enter product name to add: ");
    scanf("%s", prod.name);
    printf("Enter product quantity: ");
    scanf("%d", &prod.quantity);
    printf("Enter product price: ");
    scanf("%f", &prod.price);

    // Assign product ID based on last added product
    fseek(file, -1, SEEK_END);
    while (fscanf(file, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF);
    prod.ID += 1;

    // Add the new product
    fprintf(file, "%d %s %d %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);

    printf("Product added successfully.\n");

    fclose(file);
}

void removeInventory() {  // Remove inventory
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

void viewInventory() {  // View inventory
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening inventory.\n");
        return;
    }

    struct product prod;
    printf("\nProduct Inventory:\n");
    while (fscanf(file, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
        printf("%d %s - Quantity: %d - Price: %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
    }

    fclose(file);
}

float addToCart(int n, float totalCost) {  // Add to cart
    FILE *db = fopen("products.txt", "r"); // db = database
    if (db == NULL) {
        printf("\nError opening file");
        return 0;
    }

    struct product *cart = NULL;  // Dynamic memory allocation for products
    int count = n;  // Counter for items

    while (1) {
        cart = (struct product *) realloc(cart, (count + 1) * sizeof(struct product));
        if (cart == NULL) {
            printf("Memory Allocation Failed!\n");
            fclose(db);
            return 0;
        }

        printf("\nEnter the name of the item (or type 'exit' to finish): ");
        scanf("%s", cart[count].name);

        if (strcmp(cart[count].name, "exit") == 0) {
            break;
        }

        printf("Enter Quantity: ");
        scanf("%d", &cart[count].quantity);

        fseek(db, 0, SEEK_SET);  // Reset db pointer to beginning of file to search products.

        int found = 0;
        char productName[30];  // A buffer variable to store and compare the name entered by the user

        while (fgets(productName, 30, db) != NULL) {
            int available;
            float price;

            sscanf(productName, "%s Quantity: %d Price: %f", productName, &available, &price);

            if (strcmp(productName, cart[count].name) == 0) {
                found = 1;
                if (available <= 0) {
                    printf("\nThis item is out of stock");
                    continue;
                } else if (available < cart[count].quantity) {
                    printf("\nThere are only %d %s in the stock", available, productName);
                    continue;
                }
                printf("\nAdded to cart successfully!\n");

                cart[count].price = price;
                totalCost += cart[count].quantity * price;
                printf("\n\nTotal Cost: %.2f\n", totalCost);

                int fquantity = available - cart[count].quantity;

                // Append the item and its details to order_history.txt
                FILE *orderHistory = fopen("order_history.txt", "a");
                if (orderHistory == NULL) {
                    printf("\nError opening order history file");
                    free(cart);
                    fclose(db);
                    return 0;
                }
                fprintf(orderHistory, "%s\tQuantity: %d\tPrice: %.2f\n", cart[count].name, cart[count].quantity, price);
                fclose(orderHistory);
                break;
            }
        }
        if (found != 1) {
            printf("\nThe item does not exist!");
        } else {
            count++;
        }
    }

    free(cart);
    fclose(db);

    printf("\nThe total cost of your cart is: $%.2f\n", totalCost);
    n = count;
    return totalCost;
}

int removeFromCart(float *totalCost) {  // Remove from cart
    char itemToRemove[30];
    int removeQuantity;

    printf("\nEnter the name of the item to remove: ");
    scanf("%s", itemToRemove);

    printf("\nEnter the quantity to remove: ");
    scanf("%d", &removeQuantity);

    FILE *orderHistory = fopen("order_history.txt", "r");
    FILE *tempFile = fopen("temp_order_history.txt", "w");
    if (orderHistory == NULL || tempFile == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char *productName = (char *)malloc(100 * sizeof(char));
    if (productName == NULL) {
        printf("Memory Allocation Failed for itemName!\n");
        fclose(orderHistory);
        fclose(tempFile);
        return 0;
    }

    char *line = (char *)malloc(100 * sizeof(char));
    if (line == NULL) {
        printf("Memory Allocation Failed for line!\n");
        free(productName);
        fclose(orderHistory);
        fclose(tempFile);
        return 0;
    }

    int found = 0;

    while (fgets(line, 100, orderHistory) != NULL) {
        int itemQuantity;
        float itemPrice;

        sscanf(line, "%s Quantity: %d Price: %f", productName, &itemQuantity, &itemPrice);

        if (strcmp(productName, itemToRemove) == 0) {
            found = 1;
            if (removeQuantity >= itemQuantity) {
                printf("\nRemoved all %s from the cart.\n", productName);
                *totalCost -= itemQuantity * itemPrice;
            } else {
                printf("\nRemoved %d of %s from the cart.\n", removeQuantity, productName);
                *totalCost -= removeQuantity * itemPrice;
                itemQuantity -= removeQuantity;

                fprintf(tempFile, "%s\tQuantity: %d\tPrice: %.2f\n", productName, itemQuantity, itemPrice);
            }
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(orderHistory);
    fclose(tempFile);

    remove("order_history.txt");
    rename("temp_order_history.txt", "order_history.txt");

    if (!found) {
        printf("Item not found in the cart.\n");
    }
    printf("\nUpdated total cost: $%.2f\n", *totalCost);

    free(productName);
    free(line);
    return 0;
}
