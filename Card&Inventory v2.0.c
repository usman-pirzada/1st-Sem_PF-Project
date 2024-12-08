// By ChatGPT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100

typedef struct {
    char name[50];
    int quantity;
    float price;
} Item;

// Global inventory and cart
Item inventory[MAX_ITEMS];
Item cart[MAX_ITEMS];
int inventoryCount = 0;
int cartCount = 0;

// Function prototypes
void loadInventory();
void saveInventory();
void loadCart();
void saveCart();
void addInventory();
void removeInventory();
void viewInventory();
void addToCart();
void removeFromCart();
void viewCart();
void placeOrder();
int findItem(Item items[], int count, char name[]);

int main() {
    int choice;

    loadInventory();
    loadCart();

    do {
        printf("\nSupermart Sales/Inventory Management System:\n");
        printf("1. View Inventory\n");
        printf("2. Add Inventory\n");
        printf("3. Remove Inventory\n");
        printf("4. View Cart\n");
        printf("5. Add to Cart\n");
        printf("6. Remove from Cart\n");
        printf("7. Place Order\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                viewInventory();
                break;
            case 2:
                addInventory();
                break;
            case 3:
                removeInventory();
                break;
            case 4:
                viewCart();
                break;
            case 5:
                addToCart();
                break;
            case 6:
                removeFromCart();
                break;
            case 7:
                placeOrder();
                break;
            case 8:
                saveInventory();
                saveCart();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

// Load inventory from file
void loadInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No existing inventory file found. Starting fresh.\n");
        return;
    }
    while (fscanf(file, "%49[^,],%d,%f\n", inventory[inventoryCount].name, &inventory[inventoryCount].quantity, &inventory[inventoryCount].price) == 3) {
        inventoryCount++;
    }
    fclose(file);
}

// Save inventory to file
void saveInventory() {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save inventory.\n");
        return;
    }
    for (int i = 0; i < inventoryCount; i++) {
        fprintf(file, "%s,%d,%.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
    fclose(file);
}

// Load cart from file
void loadCart() {
    FILE *file = fopen("cart.txt", "r");
    if (file == NULL) {
        printf("No existing cart file found. Starting fresh.\n");
        return;
    }
    while (fscanf(file, "%49[^,],%d,%f\n", cart[cartCount].name, &cart[cartCount].quantity, &cart[cartCount].price) == 3) {
        cartCount++;
    }
    fclose(file);
}

// Save cart to file
void saveCart() {
    FILE *file = fopen("cart.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save cart.\n");
        return;
    }
    for (int i = 0; i < cartCount; i++) {
        fprintf(file, "%s,%d,%.2f\n", cart[i].name, cart[i].quantity, cart[i].price);
    }
    fclose(file);
}

// View inventory
void viewInventory() {
    printf("\nInventory:\n");
    if (inventoryCount == 0) {
        printf("No items in inventory.\n");
        return;
    }
    for (int i = 0; i < inventoryCount; i++) {
        printf("%d. %s - %d @ $%.2f each\n", i + 1, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

// Add items to inventory
void addInventory() {
    char name[50];
    int quantity;
    float price;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    printf("Enter price: ");
    scanf("%f", &price);
    getchar(); // Consume newline character

    int index = findItem(inventory, inventoryCount, name);
    if (index != -1) {
        inventory[index].quantity += quantity;
    } else {
        strcpy(inventory[inventoryCount].name, name);
        inventory[inventoryCount].quantity = quantity;
        inventory[inventoryCount].price = price;
        inventoryCount++;
    }

    saveInventory();
    printf("Item added to inventory successfully.\n");
}

// Remove items from inventory
void removeInventory() {
    char name[50];
    int quantity;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter quantity to remove: ");
    scanf("%d", &quantity);
    getchar(); // Consume newline character

    int index = findItem(inventory, inventoryCount, name);
    if (index != -1) {
        if (inventory[index].quantity >= quantity) {
            inventory[index].quantity -= quantity;
            if (inventory[index].quantity == 0) {
                // Shift items
                for (int i = index; i < inventoryCount - 1; i++) {
                    inventory[i] = inventory[i + 1];
                }
                inventoryCount--;
            }
            saveInventory();
            printf("Item removed from inventory successfully.\n");
        } else {
            printf("Error: Not enough stock.\n");
        }
    } else {
        printf("Error: Item not found.\n");
    }
}

// View cart
void viewCart() {
    printf("\nCart:\n");
    if (cartCount == 0) {
        printf("No items in cart.\n");
        return;
    }
    for (int i = 0; i < cartCount; i++) {
        printf("%d. %s - %d @ $%.2f each\n", i + 1, cart[i].name, cart[i].quantity, cart[i].price);
    }
}

// Add items to cart
void addToCart() {
    char name[50];
    int quantity;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter quantity to add to cart: ");
    scanf("%d", &quantity);
    getchar(); // Consume newline character

    int index = findItem(inventory, inventoryCount, name);
    if (index == -1 || inventory[index].quantity < quantity) {
        printf("Error: Not enough stock.\n");
        return;
    }

    int cartIndex = findItem(cart, cartCount, name);
    if (cartIndex != -1) {
        cart[cartIndex].quantity += quantity;
    } else {
        strcpy(cart[cartCount].name, name);
        cart[cartCount].quantity = quantity;
        cart[cartCount].price = inventory[index].price;
        cartCount++;
    }

    saveCart();
    printf("Item added to cart successfully.\n");
}

// Remove items from cart
void removeFromCart() {
    char name[50];
    int quantity;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter quantity to remove from cart: ");
    scanf("%d", &quantity);
    getchar(); // Consume newline character

    int cartIndex = findItem(cart, cartCount, name);
    if (cartIndex != -1) {
        if (cart[cartIndex].quantity >= quantity) {
            cart[cartIndex].quantity -= quantity;
            if (cart[cartIndex].quantity == 0) {
                // Shift items
                for (int i = cartIndex; i < cartCount - 1; i++) {
                    cart[i] = cart[i + 1];
                }
                cartCount--;
            }
            saveCart();
            printf("Item removed from cart successfully.\n");
        } else {
            printf("Error: Not enough quantity in cart.\n");
        }
    } else {
        printf("Error: Item not found in cart.\n");
    }
}

// Place order
void placeOrder() {
    for (int i = 0; i < cartCount; i++) {
        int index = findItem(inventory, inventoryCount, cart[i].name);
        if (index != -1 && inventory[index].quantity >= cart[i].quantity) {
            inventory[index].quantity -= cart[i].quantity;
            if (inventory[index].quantity == 0) {
                // Shift inventory items if stock is zero
                for (int j = index; j < inventoryCount - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                inventoryCount--;
            }
        } else {
            printf("Error: Insufficient stock for item '%s'. Order could not be placed.\n", cart[i].name);
            return;
        }
    }

    cartCount = 0; // Clear the cart after order placement
    saveInventory();
    saveCart();
    printf("Order placed successfully! All items deducted from inventory, and cart is now empty.\n");
}

// Find item by name in an array of items
int findItem(Item items[], int count, char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(items[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Not found
}
