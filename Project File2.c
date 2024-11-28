#include<stdio.h>
#include<string.h>

struct Product{
	int id;
	char name[30];
	int quantity;
	float price;
};
struct Customer{
	int cust_id;
	char cust_name[30];
	char pin[5];
};
struct Order{
	int *prod_id;
	float *price;
	char *prod_name[30];
};

int numOfCustomers(){
	FILE *file = fopen("customers.txt", "r");
	if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
	
	int count=0;
	
	char line[256];
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    return count;
    fclose(file);
}

int login(){
	
	struct Customer customers[numOfCustomers()];
	
	
	FILE *file=fopen("customers.txt","r");
	if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    int i=0;
    while (fscanf(file,"ID : %d\tName : %s\tPIN : %s\n",&customers[i].cust_id,customers[i].cust_name,customers[i].pin) == 3) {
        i++;
    }
    
//    for(i=0;i<numOfCustomers();i++){
//    	printf("ID : %d\n",customers[i].cust_id);
//    	printf("Name : %s\n",customers[i].cust_name);
//    	printf("PIN : %s\n",customers[i].pin);
//    	printf("\n");
//	}

	int id;
	char pin[5];
	
	printf("\nEnter id : ");
	scanf("%d",&id);
	printf("\nEnter PIN : ");
	scanf("%4s",pin);
	
	for(i=0;i<numOfCustomers();i++){
		if(customers[i].cust_id==id){
			printf("Customer Exists!\n");
			if(strcmp(customers[i].pin,pin)==0){
				printf("\nLogin successful!");
				break;
			}
		}
	}
}

int signup(){
	int id;
	char name[30];
	char pin[5];
	
	printf("\nEnter your name : ");
	scanf("%s",name);
	
	printf("\nEnter Pin : ");
	scanf("%4s",pin);
    
    id=numOfCustomers()+1;
    
	FILE *file = fopen("customers.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "ID : %d\tName: %s\tPIN : %s\n", id, name, pin);

    fclose(file);	
    
    printf("\nSignup Successful!\n");
    printf("\nCustomer details!\n\n");
    printf("ID : %d\n",id);
    printf("Name : %s\n",name);
    printf("PIN : %s\n",pin);
}

int main()
{
	login();
//	signup();
//	int choice;
//	printf("PRESS:\n");
//	printf("1 if customer\n");
//	printf("2 if employee\n");
//	printf("3 if manager\n");
//	
//	printf("4 to quit\n");
//	scanf("%d",&choice);
//	
//	switch(choice){
//		case 1:
//			display();
//			break;
//		case 2:
//			login()
//			break;
//		case 3:
//			login();
//			break;
//		case 4:
//			printf("\nProgram Terminated");
//			break;
//		default:
//			printf("\nInvalid Input");
//			break;
//	}

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
		struct product *Name=(struct product *)malloc(n*sizeof(struct product));
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