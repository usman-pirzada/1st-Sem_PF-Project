#include<stdio.h>
#include<string.h>

struct Product{
	int prod_id;
	char prod_name[30];
	int quant;
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
	return 0;
}