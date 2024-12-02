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