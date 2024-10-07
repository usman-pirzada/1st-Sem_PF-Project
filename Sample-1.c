#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define FILENAME "inventory.dat"

// Define a structure to hold product information
struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

// Function prototypes
void addProduct(struct Product products[], int *count);
void updateStock(struct Product products[], int count);
void viewProduct(struct Product products[], int count);
void generateReport(struct Product products[], int count);
void saveToFile(struct Product products[], int count);
int loadFromFile(struct Product products[]);
int productExists(struct Product products[], int count, int id);

int main() {
    struct Product products[MAX_PRODUCTS]; // Array to store up to 100 products
    int count = 0; // Keeps track of the number of products
    int choice;

    // Load data from file
    count = loadFromFile(products);
    printf("%d products loaded from the file.\n", count);

    while(1) {
        // Main menu
        printf("\nInventory Management System\n");
        printf("1. Add a new product\n");
        printf("2. Update stock\n");
        printf("3. View product details\n");
        printf("4. Generate inventory report\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addProduct(products, &count);
                break;
            case 2:
                updateStock(products, count);
                break;
            case 3:
                viewProduct(products, count);
                break;
            case 4:
                generateReport(products, count);
                break;
            case 5:
                saveToFile(products, count);
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to check if a product exists (by ID)
int productExists(struct Product products[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Function to add a new product
void addProduct(struct Product products[], int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Error: Inventory is full.\n");
        return;
    }

    int id;
    printf("\nEnter product ID: ");
    scanf("%d", &id);

    if (productExists(products, *count, id)) {
        printf("Error: Product with ID %d already exists.\n", id);
        return;
    }

    products[*count].id = id;
    printf("Enter product name: ");
    scanf("%s", products[*count].name);
    printf("Enter product quantity: ");
    scanf("%d", &products[*count].quantity);
    printf("Enter product price: ");
    scanf("%f", &products[*count].price);

    (*count)++; // Increment the product count
    printf("Product added successfully!\n");
}

// Function to update stock quantity of an existing product
void updateStock(struct Product products[], int count) {
    int id, new_quantity, found = 0;
    printf("\nEnter product ID to update stock: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            printf("Enter new quantity: ");
            scanf("%d", &new_quantity);
            products[i].quantity = new_quantity;
            found = 1;
            printf("Stock updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Product not found!\n");
    }
}

// Function to view details of a specific product
void viewProduct(struct Product products[], int count) {
    int id, found = 0;
    printf("\nEnter product ID to view details: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            printf("\nProduct ID: %d\n", products[i].id);
            printf("Product Name: %s\n", products[i].name);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Price: $%.2f\n", products[i].price);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found!\n");
    }
}

// Function to generate an inventory report
void generateReport(struct Product products[], int count) {
    printf("\nInventory Report:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%d\t\t$%.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
}

// Function to save inventory data to a file
void saveToFile(struct Product products[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file); // Save the number of products
    fwrite(products, sizeof(struct Product), count, file); // Save the product data
    fclose(file);
    printf("Inventory saved to file successfully.\n");
}

// Function to load inventory data from a file
int loadFromFile(struct Product products[]) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return 0;
    }

    int count;
    fread(&count, sizeof(int), 1, file); // Read the number of products
    fread(products, sizeof(struct Product), count, file); // Read the product data
    fclose(file);
    return count;
}