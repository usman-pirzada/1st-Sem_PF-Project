#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct product{
	char name[20];
	int quantity;
	float price;
};

float addToCart(int n, float totalCost){

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
        scanf("%s",&cart[count].name);

        if(strcmp(cart[count].name,"exit") == 0){
            break;
        }

        printf("Enter Quantity: ");
        scanf(" %d",&cart[count].quantity);
        
        // Reset db pointer to beginning of file to search products.
        fseek(db, 0, SEEK_SET);
                
        int found = 0;
        char productName[30];	// A buufer variable to store and compare the name entered by user

        while(fgets(productName,30,db)!=NULL){
        	int available;
        	float price;
        	        	
        	sscanf(productName,"%s Quantity: %d Price: $%f",productName,&available,&price);
        	
        	printf("\nPrice: %.2f\n",price);
        	printf("Available: %d",available);
        	
            if(strcmp(productName,cart[count].name) == 0){
                found = 1;
                if(available<=0){
                	printf("%d",available);
                    printf("\nThis item is out of stock");
                    continue;
                }else if(available<cart[count].quantity){
					printf("\nThere are only %d %s in the stock",available,productName);
					continue;
				}
                printf("\nAdded to cart successfully!\n");

                cart[count].price = price;
                totalCost += cart[count].quantity * price;
                printf("\n\n%f\n",totalCost);

				int fquantity = available - cart[count].quantity;

                // Append the item and its details to order_history.txt
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
        if(found!=1){
            printf("\nThe item does not exist!");
        }else{
            count++;
        }
    }

    free(cart);
    fclose(db);

    printf("\nThe total cost of your cart is: $%.2f\n", totalCost);
	n = count;
	return totalCost;
}

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

int main()
{
	int choice, n=0;	// n = no.of products
	float totalCost;
	
	do{
		printf("Press:\n");
		printf("1 to add to cart\n");
		printf("2 to remove from cart\n");
		printf("3 to exit\n");
		
		printf("Enter choice: ");
		scanf("%d",&choice);
		
		switch(choice){
			case 1:
				totalCost = addToCart(n,0);
				break;
			case 2:
				removeFromCart(&totalCost);
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