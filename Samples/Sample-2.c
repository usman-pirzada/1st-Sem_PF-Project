#include <stdio.h>
#include <string.h>

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

int main() {
    struct Product products[100]; // Array to store up to 100 products
    int count = 0; // Keeps track of the number of products
    int choice;

    while(1) {
        // Main menu
        printf("\nInventory Management System\n");
        printf("1. Add a new product\n");
        printf("2. Update stock\n");
        printf("3. View product details\n");
        printf("4. Generate inventory report\n");
        printf("5. Exit\n");
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
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to add a new product
void addProduct(struct Product products[], int *count) {
    printf("\nEnter product ID: ");
    scanf("%d", &products[*count].id);
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

    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {
            printf("Enter new quantity: ");
            scanf("%d", &new_quantity);
            products[i].quantity = new_quantity;
            found = 1;
            printf("Stock updated successfully!\n");
            break;
        }
    }
    if(!found) {
        printf("Product not found!\n");
    }
}

// Function to view details of a specific product
void viewProduct(struct Product products[], int count) {
    int id, found = 0;
    printf("\nEnter product ID to view details: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {
            printf("\nProduct ID: %d\n", products[i].id);
            printf("Product Name: %s\n", products[i].name);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Price: $%.2f\n", products[i].price);
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("Product not found!\n");
    }
}

// Function to generate an inventory report
void generateReport(struct Product products[], int count) {
    printf("\nInventory Report:\n");
    printf("-------------------------------------------------\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");

    for(int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%d\t\t$%.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
}