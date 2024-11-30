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