#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

// Structure for inventory items
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
void addInventory();
void removeInventory();
void addToCart();
void removeFromCart();
void placeOrder();
int findItem(Item items[], int count, char name[]);

int main() {
    int choice;

    do {
        printf("\nSupermart Sales/Inventory Management System:\n");
        printf("1. Add Inventory\n");
        printf("2. Remove Inventory\n");
        printf("3. Add to Cart\n");
        printf("4. Remove from Cart\n");
        printf("5. Place Order\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character after scanf

        switch (choice) {
            case 1:
                addInventory();
                break;
            case 2:
                removeInventory();
                break;
            case 3:
                addToCart();
                break;
            case 4:
                removeFromCart();
                break;
            case 5:
                placeOrder();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to find an item by name
int findItem(Item items[], int count, char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(items[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Add items to inventory
void addInventory() {
    char name[50];
    int quantity;
    float price;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    printf("Enter price: ");
    scanf("%f", &price);
    getchar(); // To consume newline character

    int index = findItem(inventory, inventoryCount, name);
    if (index != -1) {
        inventory[index].quantity += quantity;
    } else {
        strcpy(inventory[inventoryCount].name, name);
        inventory[inventoryCount].quantity = quantity;
        inventory[inventoryCount].price = price;
        inventoryCount++;
    }

    printf("Item added to inventory successfully.\n");
}

// Remove items from inventory
void removeInventory() {
    char name[50];
    int quantity;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter quantity to remove: ");
    scanf("%d", &quantity);
    getchar(); // To consume newline character

    int index = findItem(inventory, inventoryCount, name);
    if (index != -1) {
        if (inventory[index].quantity >= quantity) {
            inventory[index].quantity -= quantity;
            if (inventory[index].quantity == 0) {
                // Shift items if quantity is 0
                for (int i = index; i < inventoryCount - 1; i++) {
                    inventory[i] = inventory[i + 1];
                }
                inventoryCount--;
            }
            printf("Item removed from inventory successfully.\n");
        } else {
            printf("Error: Not enough stock of %s in inventory.\n", name);
        }
    } else {
        printf("Error: Item %s not found in inventory.\n", name);
    }
}

// Add items to cart
void addToCart() {
    char name[50];
    int quantity;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter quantity to add to cart: ");
    scanf("%d", &quantity);
    getchar(); // To consume newline character

    int invIndex = findItem(inventory, inventoryCount, name);
    if (invIndex == -1 || inventory[invIndex].quantity < quantity) {
        printf("Error: Not enough stock of %s in inventory to add to cart.\n", name);
        return;
    }
    int cartIndex = findItem(cart, cartCount, name);
    if (cartIndex != -1) {
        cart[cartIndex].quantity += quantity;
    } else {
        strcpy(cart[cartCount].name, name);
        cart[cartCount].quantity = quantity;
        cart[cartCount].price = inventory[invIndex].price;
        cartCount++;
    }

    printf("Item added to cart successfully.\n");
}

// Remove items from cart
void removeFromCart() {
    char name[50];
    int quantity;

    printf("Enter item name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter quantity to remove from cart: ");
    scanf("%d", &quantity);
    getchar(); // To consume newline character

    int cartIndex = findItem(cart, cartCount, name);
    if (cartIndex != -1) {
        if (cart[cartIndex].quantity >= quantity) {
            cart[cartIndex].quantity -= quantity;
            if (cart[cartIndex].quantity == 0) {
                // Shift items if quantity is 0
                for (int i = cartIndex; i < cartCount - 1; i++) {
                    cart[i] = cart[i + 1];
                }
                cartCount--;
            }
            printf("Item removed from cart successfully.\n");
        } else {
            printf("Error: Not enough quantity of %s in cart.\n", name);
        }
    } else {
        printf("Error: Item %s not found in cart.\n", name);
    }
}

// Place order: Deduct items from inventory and clear cart
void placeOrder() {
    for (int i = 0; i < cartCount; i++) {
        removeInventory(cart[i].name, cart[i].quantity);
    }
    cartCount = 0;
    printf("Order placed successfully! Cart is now empty.\n");
}