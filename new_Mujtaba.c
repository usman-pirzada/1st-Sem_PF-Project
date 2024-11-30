#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct product{
	char name[20];
	int quantity;
	float price;
};

float addToCart(int n, float *totalCost){

	FILE *db = fopen("products.txt", "r"); // db = database
    if(db == NULL){
        printf("\nError opening file");
        return 0;
    }
    
    struct product *cart = NULL;	// Dynamic memory allocation for products

    int count = n; 					// Counter for items 

    while(1){

        // Allocating memory for the rising no.of products

        cart = (struct product *)realloc(cart,(count + 1) * sizeof(struct product));
        if(cart == NULL){
            printf("Memory Allocation Failed!\n");
            fclose(db);
            return 0;
        }

        printf("\nEnter the name of the item (or type 'exit' to finish): ");
        fgets(cart[count].name,sizeof(cart[count].name),stdin);
        cart[count].name[strcspn(cart[count].name,"\n")] ='\0';

        if(strcmp(cart[count].name,"exit") == 0){
            return;
        }

        printf("Enter Quantity: ");
        scanf("%d",&cart[count].quantity);

		// A buufer variable to store and compare the name entered by user
		char *productName = (char *)malloc(100 * sizeof(char));
        if (productName == NULL) {
            printf("\nMemory Allocation Failed!");
            free(cart);
            fclose(db);
            return 0;
        }

        // Reset db pointer to beginning of file to search products.
        fseek(db, 0, SEEK_SET);
        int found = 0;
        int available;
        float price;

        while(fgets(productName,100,db) != NULL){

			productName[strcspn(productName,"\n")]='\0';
            sscanf(productName,"%s quantity: %d price: $%f",productName,&available,&price);

            if(strcmp(productName,cart[count].name) == 0){
                found = 1;
                if(available<=0){
                    printf("\nThis item is out of stock");
                    continue;
                }
                printf("\nAdded to cart successfully!\n");

                cart[count].price = price;
                totalCost += cart[count].quantity * price;

                // Append the item and its details to order history.txt
                FILE *orderHistory = fopen("order_history.txt","a");
                if(orderHistory == NULL){
                    printf("\nError opening order history file");
                    free(cart);
                    fclose(db);
                    return 0;
                }
                fprintf(orderHistory, "%s\tQuantity: %d\tPrice: $%.2f\n", cart[count].name, cart[count].quantity, price);
                fclose(orderHistory);
                break;
            }
        }
        if(!found){
            printf("\nThe item does not exist!");
        }else{
            count++;
        }
    }

    free(cart);
    fclose(db);

    printf("The total cost of your cart is: $%.2f\n", totalCost);
	n = count;
	return totalCost;
}

int removeFromCart(float *totalCost){
	
    char *itemToRemove=(char *)malloc(100 * sizeof(char));
    if(itemToRemove == NULL){
        printf("\nMemory Allocation Failed!\n");
        return;
    }

    printf("Enter the name of the product to remove: ");
    fgets(itemToRemove,100,stdin);
    itemToRemove[strcspn(itemToRemove,"\n")]='\0';

    int removeQuantity;
    printf("Enter the quantity to remove: ");
    scanf("%d",&removeQuantity);
   
    FILE *orderHistory = fopen("order_history.txt", "r");
    FILE *tempFile = fopen("temp_order_history.txt", "w");
    if(orderHistory == NULL || tempFile == NULL){
        printf("Error opening file\n");
        free(itemToRemove);
        return;
    }

	char *productName = (char *)malloc(100 * sizeof(char));  
    if (productName == NULL) {
        printf("Memory Allocation Failed for itemName!\n");
        free(itemToRemove);
        fclose(orderHistory);
        fclose(tempFile);
        return;
    }

    // buffer
    char *line = (char *)malloc(100 * sizeof(char));
    if (line == NULL) {
        printf("Memory Allocation Failed for line!\n");
        free(itemToRemove);
		free(productName);
        fclose(orderHistory);
        fclose(tempFile);
        return;
    }

    int found = 0;

    while(fgets(line,100,orderHistory) != NULL){
        int itemQuantity;
        float itemPrice;

        sscanf(line, "%s\tQuantity: %d\tPrice: %f", productName, &itemQuantity, &itemPrice);

        if(strcmp(itemName,itemToRemove) == 0){
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

int main()
{
	int choice, n=0;	// n = no.of products
	float totalCost = 0;

	do{
		printf("Press:\n");
		printf("1 to add to cart\n");
		printf("2 to remove from cart\n");
		printf("3 to exit\n");
		
		printf("Enter choice: ");
		scanf("%d",&choice);
		
		switch(choice){
			case 1:
				addToCart(n,&totalCost);
				break;
			case 2:
				reomveFromCart(&totalCost);
				break;
			case 3:
				printf("\nThank you for shopping. Please come again.");
				break;
			default:
				printf("\nInvalid Input");
				break;
		}
	
	}while(choice!=3);
	
	return 0;
}