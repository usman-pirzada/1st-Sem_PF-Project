void removeFromCart(float *totalCost){                           // remove from cart
	
    char itemToRemove[30];
    int removeQuantity;

    printf("\nEnter the name of the item to remove: ");
    scanf("%s", itemToRemove);

    printf("\nEnter the quantity to remove: ");
    scanf("%d", &removeQuantity);
   
    FILE *orderHistory = fopen("order_history.txt","r");
    FILE *tempFile = fopen("temp_order_history.txt","w");
    if(orderHistory == NULL || tempFile == NULL){
        printf("Error opening file\n");
        return;
    }

	char *productName = (char *)malloc(100 * sizeof(char));  
    if (productName == NULL) {
        printf("Memory Allocation Failed for itemName!\n");
        fclose(orderHistory);
        fclose(tempFile);
        return;
    }

    // buffer
    char *line = (char *)malloc(100 * sizeof(char));
    if (line == NULL) {
        printf("Memory Allocation Failed for line!\n");
		free(productName);
        fclose(orderHistory);
        fclose(tempFile);
        return;
    }

    int found = 0;

    while(fgets(line,100,orderHistory) != NULL){
		
        int itemQuantity;
        float itemPrice;

        sscanf(line, "%s Quantity: %d Price: %f", productName, &itemQuantity, &itemPrice);

        if(strcmp(productName,itemToRemove) == 0){
            found = 1;
            if(removeQuantity >= itemQuantity){
            	*totalCost -= itemQuantity * itemPrice;  // Update total cost
                printf("\nRemoved all %d of %s from the cart.\n", itemQuantity, productName);
//                printf("\nRemoved all %s from the cart.\n",productName);
//
//                *totalCost -= itemQuantity * itemPrice;
            }else{
            	*totalCost -= removeQuantity * itemPrice;  // Update total cost
                printf("\nRemoved %d of %s from the cart.\n", removeQuantity, productName);
//                printf("\nRemoved %d of %s from the cart.\n",removeQuantity,productName);
//
//                *totalCost -= removeQuantity * itemPrice;
////                itemQuantity -= removeQuantity;
//
//                fprintf(tempFile, "%s\tQuantity: %d\tPrice: %.2f\n",productName,itemQuantity,itemPrice);
            }
        }else{
            fprintf(tempFile,"%s",line);
        }
    }

    fclose(orderHistory);
    fclose(tempFile);

//    remove("order_history.txt");
//    rename("temp_order_history.txt", "order_history.txt");
//    
//    if(!found){
//        printf("Item not found in the cart.\n");
//    }
//    printf("\nUpdated total cost: $%.2f\n", *totalCost);
	if (found) {
        // Overwrite the original order history with the updated file
        remove("order_history.txt");
        rename("temp_order_history.txt", "order_history.txt");

        // Now update the inventory file to reflect the removal
        FILE *inventoryFile = fopen("inventory.txt", "r+");
        if (inventoryFile == NULL) {
            printf("Error opening inventory file.\n");
            return;
        }

        FILE *tempInventoryFile = fopen("temp_inventory.txt", "w");
        if (tempInventoryFile == NULL) {
            printf("Error opening temporary inventory file.\n");
            fclose(inventoryFile);
            return;
        }

        struct product prod;
        int inventoryUpdated = 0;

        // Loop through the inventory and adjust quantities
        while (fscanf(inventoryFile, "%d %s %d %f", &prod.ID, prod.name, &prod.quantity, &prod.price) != EOF) {
            if (strcmp(prod.name, itemToRemove) == 0) {
                if (prod.quantity >= removeQuantity) {
                    // Decrease the quantity of the product in the inventory
                    prod.quantity -= removeQuantity;
                    printf("\nUpdated inventory: Removed %d of %s from inventory.\n", removeQuantity, prod.name);
                } else {
                    printf("\nNot enough stock to remove %d of %s from inventory.\n", removeQuantity, prod.name);
                }
            }

            // Write the updated or unchanged product to the temporary file
            fprintf(tempInventoryFile, "%d %s %d %.2f\n", prod.ID, prod.name, prod.quantity, prod.price);
        }

        fclose(inventoryFile);
        fclose(tempInventoryFile);

        // Replace the old inventory file with the updated one
        remove("inventory.txt");
        rename("temp_inventory.txt", "inventory.txt");

    } else {
        remove("temp_order_history.txt");  // Clean up the temporary file if the item wasn't found
        printf("\nItem not found in the cart.\n");
    }
    // Free
	free(productName);
    free(line);
}