//1st Semester Project of a FAST's senior

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Accounts_Information{
	int account_number_r;
	char NIC_r[14];
	char name_r[30];
	int age_r;
	int PIN_r;
	float balance_r;
}Accounts;

typedef struct Transactions_Information{
	int sender_account_number;
    float amount;
    int reciever_account_number;
}Transactions;

void create_account(Accounts* ,int );
//----------------------------------//
int Number_Of_Accounts();
Accounts* Accounts_Reader(int );
//----------------------------------//
void balance_inquiry(Accounts* ,int );
void account_details(Accounts* ,int );
void delete_account(Accounts* ,int );
void update_account(Accounts* ,int );
void withdraw_amount(Accounts* ,int );
void transaction(Accounts* ,int );
//----------------------------------//
int Number_Of_Transactions();
Transactions* Transactions_Reader(int );
//----------------------------------//
void transaction_history(Accounts* ,int ,Transactions* ,int );

int main()
{
	int i,j;
	int choice;
	int numOfAcc,numOfTrans;
	Accounts* accountsInformation=NULL;
	Transactions* transactionsInformation=NULL;
	printf("\t\t\t      ---WELCOME TO OUR BANK---\n");
	for(i=0; ;i++){
	    printf("\nEnter '1' to CREATE ACCOUNT!\n");
	    printf("Enter '2' to DISPLAY ACCOUNT DETAILS!\n");
	    printf("Enter '3' to INQUIRE ABOUT BALANCE!\n");
	    printf("Enter '4' to UPDATE ACCOUNT!\n");
	    printf("Enter '5' to WITHDRAW AMOUNT!\n");
	    printf("Enter '6' to DELETE ACCOUNT!\n");
	    printf("Enter '7' to MAKE A TRANSACTION!\n");
	    printf("Enter '8' to DISPLAY TRANSACTION HISTORY!\n");
	    printf("Enter '9' to EXIT!\n");
	    printf("\nEnter : ");
	    for(j=0;j<3;j++){
	    scanf("%d",&choice);
	    switch(choice){
	    	case 1 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        create_account(accountsInformation,numOfAcc);
	    	        break;
	    	case 2 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        account_details(accountsInformation,numOfAcc);
	    	        break;
	    	case 3 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        balance_inquiry(accountsInformation,numOfAcc);
	    	        break;
	    	case 4 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        update_account(accountsInformation,numOfAcc);
	    	        break;
	    	case 5 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        withdraw_amount(accountsInformation,numOfAcc);
	    	        break;
	        case 6 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        delete_account(accountsInformation,numOfAcc);
	    	        break;
	    	case 7 : free(accountsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        transaction(accountsInformation,numOfAcc);
	    	        break;
	    	case 8 : free(accountsInformation);
	    	        free(transactionsInformation);
			        numOfAcc=Number_Of_Accounts();
	    	        accountsInformation=Accounts_Reader(numOfAcc);
	    	        numOfTrans=Number_Of_Transactions();
	    	        transactionsInformation=Transactions_Reader(numOfTrans);
	    	        transaction_history(accountsInformation,numOfAcc,transactionsInformation,numOfTrans);
	    	        break;
	    	case 9 : free(accountsInformation);
	    	         free(transactionsInformation);
			        exit(0);
			        break;
			default : printf("\n\t\t\t---Invalid Input---\n"); 
		}
		if(choice>0 && choice<=9){
			break;
		}else if((choice<=0 || choice>9) && j<2){
			printf("\nEnter again :  ");
		}
		if(j==2){
			exit(0);
		}
	}
	printf("-------------------------------------------------------------------------------\n");
}
	return 0;
}

void create_account(Accounts* accounts,int num_of){
	int account_number;
	char NIC[14];
	char name[30];
	int age;
	int PIN;
	float balance;
	int i;
//---------------------------------------------------------//
    printf("\nEnter Name : ");
    scanf("\n%s",name);
    printf("\nEnter NIC : ");
    for(i=0;i<14;i++){
    	scanf("\n%c",&NIC[i]);
	}
    printf("\nEnter Age : ");
    for(i=0;i<3;i++){
        scanf("\n%d",&age);
        if(age>=18){
        	break;
		}else if((age>0 && age<18) && i<2){
        	printf("\nAge must be 18!\n");
        	printf("\nEnter again : ");
		}else if(age<=0 && i<2){
			printf("\n\t\t\t---Invalid Input---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---Invalid Input---\n");
			exit(0);
		}
    }
    printf("\nEnter PIN : ");
    for(i=0;i<3;i++){
        scanf("\n%d",&PIN);
        if(PIN>=1111 && PIN<=9999){
        	break;
		}else if(PIN<0){
			printf("\n\t\t\t---Invalid Input---\n");
			printf("\nEnter again : ");
		}else if(PIN>9999){
			printf("\nPIN has exceeded the limit (i.e. 4 digits)!\n");
		}else if(i==2){
			printf("\n\t\t\t---Invalid Input---\n");
			exit(0);
		}
    }
    printf("\nEnter Balance : ");
    for(i=0;i<3;i++){
        scanf("\n%f",&balance);
        if(balance<0 && i<2){
        	printf("\n\t\t\t---Invalid Input---\n");
        	printf("\nEnter again : ");
		}else{
			break;
		}
		if(i==2){
			printf("\n\t\t\t---Invalid Input---\n");
			exit(0);
		}
    }
    if(num_of>0){
    account_number=accounts[num_of-1].account_number_r+1;
    }else if(num_of==0){
    	account_number=1;
	}
    FILE* ptr;
    ptr=fopen("Bank Accounts.txt","a");
//-----------------------------------------------------//
    fprintf(ptr,"Account Number : %d\t",account_number);
    fprintf(ptr,"NIC : ");
    for(i=0;i<14;i++){
    	fprintf(ptr,"%c",NIC[i]);
	}
	fprintf(ptr,"\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",name,age,PIN,balance);
//-----------------------------------------------------//
    fclose(ptr);
    printf("\nDear Customer, Your Account has been created!\n");
    printf("\n---Details of the Account---\n");
    printf("\nAccount Number : %d\n",account_number);
    printf("NIC : ");
    for(i=0;i<14;i++){
    	printf("%c",NIC[i]);
	}
	printf("\n");
    printf("Name : %s\n",name);
    printf("Age : %d\n",age);
    printf("PIN : %d\n",PIN);
    printf("Balance : %.2f Rs\n",balance);
//---------------------------------------------------------//
}

int Number_Of_Accounts(){
	int count=0;
	char ch;
	FILE* ptr;
	ptr=fopen("Bank Accounts.txt","r");
	while((ch=fgetc(ptr))!=EOF){
		if(ch=='\n'){
			count++;
		}
	}
	fclose(ptr);
	//printf("\nNumber Of Accounts : %d",count);
	return count;
}

Accounts* Accounts_Reader(int num_of){
	Accounts* information;
	information=(Accounts*)malloc(num_of*sizeof(Accounts));
	FILE* ptr;
	ptr=fopen("Bank Accounts.txt","r");
	int i,j;
	for(i=0;i<num_of;i++){
	    fscanf(ptr,"Account Number : %d\tNIC : %s\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",&information[i].account_number_r,information[i].NIC_r,information[i].name_r,&information[i].age_r,&information[i].PIN_r
		,&information[i].balance_r);
    }
    fclose(ptr);
//    for(i=0;i<num_of;i++){
//    	printf("Account Number : %d\n",information[i].account_number_r);
//    	printf("NIC : ");
//    	for(j=0;j<14;j++){
//    	    printf("%c",information[i].NIC_r[j]);
//        }
//        printf("\n");
//    	printf("Name : %s\n",information[i].name_r);
//    	printf("Age : %d\n",information[i].age_r);
//    	printf("PIN : %d\n",information[i].PIN_r);
//    	printf("Balance : %.2f Rs\n",information[i].balance_r);
//	}
    return information;
}
void balance_inquiry(Accounts* accounts,int num_of){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	int i,j,k,l;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0;
	int checks[14];
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
		for(j=0;j<num_of;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	printf("\nBalance : %.2fRs\n",accounts[j].balance_r);
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
void account_details(Accounts* accounts,int num_of){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	int i,j,k,l,m;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0;
	int checks[14];
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
		for(j=0;j<num_of;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	printf("\nAccount Details!\n");
		    			    	printf("\nAccount Number : %d\n",accounts[j].account_number_r);
    	                        printf("NIC : ");
     	                        for(m=0;m<14;m++){
    	                            printf("%c",accounts[j].NIC_r[m]);
                                }
                                printf("\n");
    	                        printf("Name : %s\n",accounts[j].name_r);
    	                        printf("Age : %d\n",accounts[j].age_r);
    	                        printf("PIN : %d\n",accounts[j].PIN_r);
		    			    	printf("Balance : %.2f Rs\n",accounts[j].balance_r);
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
void delete_account(Accounts* accounts,int num_of){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	int i,j,k,l,m,loop;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0;
	int checks[14];
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
//		printf("\n");
//		for(j=0;j<14;j++){
//			printf("%c",NIC[j]);
//		}
//		printf("\n");
		for(j=0;j<num_of;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	FILE* ptr;
		    			    	ptr=fopen("Bank Accounts.txt","w");
		    			    		for(m=0;m<num_of;m++){
		    			    			if(m==j){
		    			    				continue;
										}
									//-----------------------------------------------------//
										fprintf(ptr,"Account Number : %d\t",accounts[m].account_number_r);
										fprintf(ptr,"NIC : ");
										for(loop=0;loop<14;loop++){
										    fprintf(ptr,"%c",accounts[m].NIC_r[loop]);
									    }
										fprintf(ptr,"\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",accounts[m].name_r,accounts[m].age_r,accounts[m].PIN_r,accounts[m].balance_r);
									//-----------------------------------------------------//
									}
								fclose(ptr);
								printf("\nDear customer, Your Account has been deleted!\n");
								printf("\nDetails of the deleted Account!\n");
		    			    	printf("\nAccount Number : %d\n",accounts[j].account_number_r);
    	                        printf("NIC : ");
     	                        for(m=0;m<14;m++){
    	                            printf("%c",accounts[j].NIC_r[m]);
                                }
                                printf("\n");
    	                        printf("Name : %s\n",accounts[j].name_r);
    	                        printf("Age : %d\n",accounts[j].age_r);
    	                        printf("PIN : %d\n",accounts[j].PIN_r);
		    			    	printf("Balance : %.2f Rs\n",accounts[j].balance_r);
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
void withdraw_amount(Accounts* accounts,int num_of){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	float amount;
	float oldBalance;
	//---------------------------------------------------------//
	int i,j,k,l,m,n,loop;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0;
	int checks[14];
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
		for(j=0;j<num_of;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	printf("\nEnter Amount : ");
		    			    	for(m=0;m<3;m++){
		    			    	scanf("%f",&amount);
		    			    	if(amount>0 && amount<=accounts[j].balance_r){
		    			    		//-------------------------------------------------//
		    			    		oldBalance=accounts[j].balance_r;
		    			    		accounts[j].balance_r=accounts[j].balance_r-amount;
		    			    		//-------------------------------------------------//
		    			    		FILE* ptr;
		    			    		ptr=fopen("Bank Accounts.txt","w");
		    			    		for(n=0;n<num_of;n++){
		    			    		//-----------------------------------------------------//
										fprintf(ptr,"Account Number : %d\t",accounts[n].account_number_r);
										fprintf(ptr,"NIC : ");
										for(loop=0;loop<14;loop++){
										    fprintf(ptr,"%c",accounts[n].NIC_r[loop]);
									    }
										fprintf(ptr,"\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",accounts[n].name_r,accounts[n].age_r,accounts[n].PIN_r,accounts[n].balance_r);
									//-----------------------------------------------------//
								    }
                                    fclose(ptr);
		    			    		printf("\nDear user, the Amount you have entered has been WITHDRAWN successfully!\n");
		    			    		printf("\nOld Balance : %.2f Rs\n",oldBalance);
		    			    		printf("Amount withdrawn : %.2f Rs\n",amount);
		    			    		printf("New Balance : %.2f Rs\n",accounts[j].balance_r);
		    			    		break;
								}else if((amount<0 || amount>accounts[j].balance_r) && m<2){
									printf("\n\t\t\t---Invalid Amount---\n");
									if(amount>accounts[j].balance_r){
									    printf("\nDear user, Your current balance is %.2f Rs\n",accounts[j].balance_r);
								    }
									printf("\nEnter again : ");
								}else if(m==2){
									printf("\n\t\t\t---Invalid Amount---\n");
									exit(0);
								}
							}
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
void update_account(Accounts* accounts,int num_of){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	int i,j,k,l,m,n,loop;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0;
	int checks[14];
	//---------------------------------------------------------//
	int choice;
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
		for(j=0;j<num_of;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	printf("\nEnter '1' to update PIN!\n");
		    			    	printf("Enter '2' to update balance(i.e to deposit amount)!\n");
		    			    	printf("\nEnter : ");
		    			    	for(m=0;m<3;m++){
		    			    		scanf("%d",&choice);
		    			    		if(choice>0 && choice<=2){
		    			    			if(choice==1){
		    			    				int newPIN;
		    			    				int oldPIN;
		    			    				//-------------------------------------------------//
		    			    				printf("\nEnter new PIN : ");
		    			    				for(n=0;n<3;n++){
		    			    				    scanf("%d",&newPIN);
		    			    				    if(newPIN>=1111 && newPIN<=9999){
		    			    				    	break;
												}else if(newPIN>9999){
														printf("\nPIN has exceeded the limit (i.e. 4 digits)!\n");
														printf("\nEnter again : ");
												}else if(newPIN<0 && n<2){
													printf("\n\t\t\t---Invalid Input---\n");
													printf("\nEnter again : ");
												}
												
												if(n==2){
													printf("\n\t\t\t---Invalid Input---\n");
													exit(0);
												}
		    			    			    }
		    			    				//-------------------------------------------------//
		    			    				oldPIN=accounts[j].PIN_r;
		    			    				accounts[j].PIN_r=newPIN;
		    			    				//-------------------------------------------------//
		    			    		        FILE* ptr;
		    			    		        ptr=fopen("Bank Accounts.txt","w");
		    			    		        for(n=0;n<num_of;n++){
		    			    		        //-----------------------------------------------------//
										    fprintf(ptr,"Account Number : %d\t",accounts[n].account_number_r);
										    fprintf(ptr,"NIC : ");
										    for(loop=0;loop<14;loop++){
										    fprintf(ptr,"%c",accounts[n].NIC_r[loop]);
									        }
										    fprintf(ptr,"\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",accounts[n].name_r,accounts[n].age_r,accounts[n].PIN_r,accounts[n].balance_r);
									        //-----------------------------------------------------//
								    		}
                                    fclose(ptr);
                                    printf("\nDear user, Your PIN has been changed successfully!\n");
                                    printf("\nOld PIN : %d\n",oldPIN);
                                    printf("New PIN : %d\n",accounts[j].PIN_r);
                                    break;
								    }else if(choice==2){
								    	float oldBalance;
								    	float amount;
								    	printf("\nEnter Amount : ");
								    	for(n=0;n<3;n++){
								    	    scanf("%f",&amount);
											if(amount>=0){
												break;
											}else if(amount<0 && n<2){
												printf("\n\t\t\t---Invalid Amount---\n");
												printf("\nEnter again : ");
											}
											
											if(n==2){
												printf("\n\t\t\t---Invalid Amount---\n");
												exit(0);
											}	
										}
								    	oldBalance=accounts[j].balance_r;
								    	accounts[j].balance_r=accounts[j].balance_r+amount;
								    	//-------------------------------------------------//
		    			    		        FILE* ptr;
		    			    		        ptr=fopen("Bank Accounts.txt","w");
		    			    		        for(n=0;n<num_of;n++){
		    			    		        //-----------------------------------------------------//
										    fprintf(ptr,"Account Number : %d\t",accounts[n].account_number_r);
										    fprintf(ptr,"NIC : ");
										    for(loop=0;loop<14;loop++){
										    fprintf(ptr,"%c",accounts[n].NIC_r[loop]);
									        }
										    fprintf(ptr,"\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",accounts[n].name_r,accounts[n].age_r,accounts[n].PIN_r,accounts[n].balance_r);
									        //-----------------------------------------------------//
								    }
                                    fclose(ptr);
                                    printf("\nDear user, the Amount you have entered has been DEPOSITED successfully!\n");
                                    printf("\nOld Balance : %.2f Rs\n",oldBalance);
                                    printf("Amount deposited : %.2f Rs\n",amount);
                                    printf("New Balance : %.2f Rs\n",accounts[j].balance_r);
                                    break;
									}
									break;	
									}else if((choice<=0 || choice>2) && m<2){
										printf("\n\t\t\t---Invalid Input---\n");
										printf("\nEnter again : ");
									}else if(m==2){
										printf("\n\t\t\t---Invalid Input---\n");
										exit(0);
									}
								}
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
void transaction(Accounts* accounts,int num_of){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	int i,j,k,l,m,n,p,q,loop;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0,check4=0;
	int checks[14];
	//---------------------------------------------------------//
	int reciever_account_number;
	//---------------------------------------------------------//
	float amount;
	float oldBalance;
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
		for(j=0;j<num_of;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	if(accounts[j].balance_r==0){
		    			    		printf("\nDear user, since Your current Balance is : %.2f Rs.Therefore you can not make\n\t\t\t\t any transaction!\n");
		    			    		break;
								}
		    			    	printf("\nEnter reciever Account Number : ");
		    			    	for(m=0;m<3;m++){
		    			    		scanf("\n%d",&reciever_account_number);
		    			    	    for(n=0;n<num_of;n++){
		    			    		    if(n==j){
		    			    		    	continue;
										}
										if(reciever_account_number==accounts[n].account_number_r){
											check4=4;
											printf("\nReciever's Account Number Found!\n");
											printf("\nEnter Amount : ");
											for(p=0;p<3;p++){
												scanf("\n%f",&amount);
												if(amount>=0 && amount<=accounts[j].balance_r){
													oldBalance=accounts[j].balance_r;
													accounts[j].balance_r=accounts[j].balance_r-amount;
													accounts[n].balance_r=accounts[n].balance_r+amount;
													FILE* ptr;
													ptr=fopen("Bank Accounts.txt","w");
													for(q=0;q<num_of;q++){
														//-----------------------------------------------------//
										                fprintf(ptr,"Account Number : %d\t",accounts[q].account_number_r);
										                fprintf(ptr,"NIC : ");
										                for(loop=0;loop<14;loop++){
										                fprintf(ptr,"%c",accounts[q].NIC_r[loop]);
									                    }
										                fprintf(ptr,"\tName : %s\tAge : %d\tPIN : %d\tBalance : %f\n",accounts[q].name_r,accounts[q].age_r,accounts[q].PIN_r,accounts[q].balance_r);
									                    //-----------------------------------------------------//
													}
													fclose(ptr);
													//-----------------------------------------------------//
													ptr=fopen("Bank Transactions.txt","a");
													fprintf(ptr,"Sender Account Number : %d\tAmount sent : %f\tReciever's Account Number : %d\n",accounts[j].account_number_r,amount,accounts[n].account_number_r);
													fclose(ptr);
													//-----------------------------------------------------//
													printf("\nDear user, TRANSACTION has been made successfully!\n");
													printf("\nYour Account Number : %d\n",accounts[j].account_number_r);
													printf("Reciever's Account Number : %d\n",accounts[n].account_number_r);
													printf("\nYour Old Balance : %.2f Rs\n",oldBalance);
													printf("Amount sent : %.2f Rs\n",amount);
													printf("Your New balance : %.2f Rs\n",accounts[j].balance_r);
													break;
												}else if((amount<0 || amount>accounts[j].balance_r) && p<2){
													printf("\n\t\t\t---Invalid Amount---\n");
													if(amount>accounts[j].balance_r){
														printf("\nDear user, Your current Balance is : %.2f Rs\n",accounts[j].balance_r);
													}
													printf("\nEnter again : ");
												}
												if(p==2){
													printf("\n\t\t\t---Invalid Amount---\n");
											        exit(0);
												}
											}
										}
								    }
								    if(check4==4 ){
								    	break;
									}else if(check4!=4 && m<2){
										printf("\nReciever's Account Number not Found!\n");
										printf("\nEnter again : ");
									}
									if(m==2){
										printf("\nReciever's Account Number not Found!\n");
										exit(0);
									}
							    } 
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
int Number_Of_Transactions(){
	int count=0;
	char ch;
	FILE* ptr;
	ptr=fopen("Bank Transactions.txt","r");
	if(ptr==NULL){
		printf("\nCould not Open File!\n");
	}
	while((ch=fgetc(ptr))!=EOF){
		if(ch=='\n'){
			count++;
		}
	}
	//printf("\nNumber of Transactions : %d",count);
	fclose(ptr);
	return count;
}

Transactions* Transactions_Reader(int num_of){
	Transactions* information;
	information=(Transactions*)malloc(num_of*sizeof(Transactions));
	FILE* ptr;
	ptr=fopen("Bank Transactions.txt","r");
	int i;
	for(i=0;i<num_of;i++){
	    fscanf(ptr,"Sender Account Number : %d\tAmount sent : %f\tReciever's Account Number : %d\n",&information[i].sender_account_number,&information[i].amount,
		&information[i].reciever_account_number);
    }
    fclose(ptr);
//    for(i=0;i<num_of;i++){
//    	printf("\nTransaction Number %d\n",(i+1));
//    	printf("\nSender Account Number : %d\n",Information[i].sender_account_number);
//        printf("Amount Transferred : %.2f Rs\n",Information[i].amount);
//        printf("Reciever's Account Number : %d\n",Information[i].reciever_account_number);
//	}
    return information;
}
void transaction_history(Accounts* accounts,int numOfAcc,Transactions* transactions,int numOfTrans){
	//---------------------------------------------------------//
	char NIC[14];
	int account_number;
	int PIN;
	//---------------------------------------------------------//
	int i,j,k,l,m;
	//---------------------------------------------------------//
	int check1=0,check2=0,check3=0;
	int checks[14];
	//---------------------------------------------------------//
	int count=0;
	//---------------------------------------------------------//
	printf("\nEnter NIC : ");
	for(i=0;i<3;i++){
		for(j=0;j<14;j++){
			scanf("\n%c",&NIC[j]);
		}
		for(j=0;j<numOfAcc;j++){
			for(k=0;k<14;k++){
				if(NIC[k]==accounts[j].NIC_r[k]){
					//printf("Correct\n");
					checks[k]=1;
				}
			}
		    if(checks[0]==1&&checks[1]==1&&checks[2]==1&&checks[3]==1&&checks[4]==1&&checks[5]==1&&checks[6]==1&&checks[7]==1&&checks[8]==1&&checks[9]==1&&checks[10]==1&&checks[11]==1&&checks[12]==1&&checks[13]==1){
		    	check1=1;
		    	printf("\n\t\t\t---CORRECT NIC---\n");
		    	printf("\nEnter Account Number : ");
		    	for(k=0;k<3;k++){
		    		scanf("%d",&account_number);
		    		if(account_number==accounts[j].account_number_r){
		    			check2=2;
		    			printf("\n\t\t\t---CORRECT ACCOUNT NUMBER---\n");
		    			printf("\nEnter PIN : ");
		    			for(l=0;l<3;l++){
		    			    scanf("%d",&PIN);
		    			    if(PIN==accounts[j].PIN_r){
		    			    	check3=3;
		    			    	printf("\n\t\t\t---CORRECT PIN---\n");
		    			    	if(numOfTrans>0){
		    			    	for(m=0;m<numOfTrans;m++){
		    			    		if(accounts[j].account_number_r==transactions[m].sender_account_number){
		    			    			count++;
		    			    			printf("\nTransaction Number %d\n",count);
    	                                printf("\nSender Account Number : %d\n",transactions[m].sender_account_number);
                                        printf("Amount Transferred : %.2f Rs\n",transactions[m].amount);
                                        printf("Reciever's Account Number : %d\n",transactions[m].reciever_account_number);
									}
									if(m==(numOfTrans-1) && count==0){
										printf("\nNO TRANSACTION HISTORY!\n");
									}
								}
							}else{
								printf("\nNO TRANSACTION HISTORY!\n");
							}
		    			    	break;
							}
							if(check3==3){
						        break;
					        }else if(check3!=3 && l<2){
					           	printf("\n\t\t\t---INCORRECT PIN---\n");
				        		printf("\nEnter again : ");
					        }
							if(l==2){
						        printf("\n\t\t\t---INCORRECT PIN---\n");
						        exit(0);
					        }
		    		    }
		    		    break;
					}
					if(check2==2){
						break;
					}else if(check2!=2 && k<2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						printf("\nEnter again : ");
					}
					if(k==2){
						printf("\n\t\t\t---INCORRECT ACCOUNT NUMBER---\n");
						exit(0);
					}
				}
				break;
			}
	    }
	    if(check1==1){
	    	break;
		}else if(check1!=1 && i<2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			printf("\nEnter again : ");
		}
		if(i==2){
			printf("\n\t\t\t---INCORRECT NIC---\n");
			exit(0);
		}
	}
}
