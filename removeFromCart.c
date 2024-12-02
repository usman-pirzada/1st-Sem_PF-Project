int removeFromCart(float *totalCost){
	
    char itemToRemove[30];
    int removeQuantity;

    printf("\nEnter the name of the item to remove: ");
    scanf("%s",itemToRemove);

    printf("\nEnter the quantity to remove: ");
    scanf("%d",&removeQuantity);
   
    FILE *orderHistory = fopen("order_history.txt","r");
    FILE *tempFile = fopen("temp_order_history.txt","w");
    if(orderHistory == NULL || tempFile == NULL){
        printf("Error opening file\n");
        free(itemToRemove);
        return 1;
    }

	char *productName = (char *)malloc(100 * sizeof(char));  
    if (productName == NULL) {
        printf("Memory Allocation Failed for itemName!\n");
        fclose(orderHistory);
        fclose(tempFile);
        return 0;
    }

    // buffer
    char *line = (char *)malloc(100 * sizeof(char));
    if (line == NULL) {
        printf("Memory Allocation Failed for line!\n");
        free(itemToRemove);
		free(productName);
        fclose(orderHistory);
        fclose(tempFile);
        return 0;
    }

    int found = 0;

    while(fgets(line,100,orderHistory) != NULL){
		
        int itemQuantity;
        float itemPrice;

        sscanf(line, "%s Quantity: %d Price: %f", productName, &itemQuantity, &itemPrice);

        if(strcmp(productName,itemToRemove) == 0){
            found = 1;
            if(removeQuantity >= itemQuantity){
                printf("\nRemoved all %s from the cart.\n",productName);

                *totalCost -= itemQuantity * itemPrice;
            }else{
                printf("\nRemoved %d of %s from the cart.\n",removeQuantity,productName);

                *totalCost -= removeQuantity * itemPrice;
                itemQuantity -= removeQuantity;

                fprintf(tempFile, "%s\tQuantity: %d\tPrice: %.2f\n",productName,itemQuantity,itemPrice);
            }
        }else{
            fprintf(tempFile,"%s",line);
        }
    }

    fclose(orderHistory);
    fclose(tempFile);

    remove("order_history.txt");
    rename("temp_order_history.txt", "order_history.txt");

    if(!found){
        printf("Item not found in the cart.\n");
    }
    printf("\nUpdated total cost: $%.2f\n", *totalCost);

    // Free
    free(itemToRemove);
	free(productName);
    free(line);
}