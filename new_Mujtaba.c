#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct product{
	int prod_id;
	char name[20];
	int quantity;
	float price;
};

int addToCart(int n){
	FILE *db=fopen("products.txt","r");
	if(db==NULL){
		printf("Error opening file");
		return 1;
	}
	
	char *buffer=(char *)malloc(100*sizeof(char));
	if(buffer==NULL){
		printf("\nMemory Allocation Failed!");
		return 1;
	}
	
	n+=1;
	
	if(n<1){
		struct product *Name=(struct product *)malloc((n+1)*sizeof(struct product));
		if(name==NULL){
			printf("\nMemory Allocation Failed!");
			return 1;
		}
	}
	
	for(int i=0;i<n;i++){
		printf("Enter the name of the item: ");
		scanf("%s",Name[i].name);
		printf("Enter Quantity: ");
		scanf("%d",Name[i].quantity);
		
		int available;
		
		fscanf(db,"%s quantity: %d",buffer,&available);
		if(strcmp(buffer,Name.name)==0){
			if(available<=0){
				printf("\nItem is out of stock");
				return;
			}
			printf("\nAdded to cart Successfully!");
			return;
		}
		printf("The item does not exist!");
	}
	
	FILE *orderHistory=fopen("order_history.txt","a");
	if(order_history==NULL){
		printf("Error opening file");
		return 1;
	}
	
	fprintf(order_history,"%s\tQuantity: %d",Name.name,Name.quantity);
	
	free(buffer);
	free(Name);
	fclose(db);
	fclose(order_history);
	return n;
}

int removeFromCart(int n){
	if(n<=0){
		printf("You have not added anything to the cart");
		return;
	}
	
	FILE *orderHistory=fopen("order_history.txt","a");
	if(order_history==NULL){
		printf("Error opening file");
		return 1;
	}
	
}

int main()
{
	int choice,n=0;	// n = no.of products
	do{
		printf("Press:\n");
		printf("1 to add to cart\n");
		printf("2 to remove from cart\n");
		printf("3 to exit\n");
		
		printf("Enter choice: ");
		scanf("%d",&choice);
		
		switch(choice){
		case 1:
			addToCart(n);
			break;
		case 2:
			reomveFromCart(n);
			break;
		case 3:
			printf("\nProgram Terminated!");
			break;
		default:
			printf("\nInvalid Input");
			break;
		}
	
	}while(choice!=3);
	
	return 0;
}