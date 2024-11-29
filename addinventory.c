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