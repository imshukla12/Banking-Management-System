#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>

void mainMenu(int);
void displayMenu(int);
void admin_functions(int);
void jointAccountLogin(int);
void jointDisplayMenu(int);


void deleteAccount(int sd)
{
	char uname[20],buffer[35];

	printf("\n\tEnter the username to be deleted: ");
	scanf(" %s", uname);

	write(sd, uname, sizeof(uname));
	read(sd, buffer, sizeof(buffer));
	
	printf("%s",buffer);
	admin_functions(sd);
}

void deleteJointAccount(int sd)
{
	char uname1[20], uname2[20], buffer[35];

	printf("\n\tEnter Username 1 to delete: ");
	scanf(" %s",uname1);
	printf("\n\tEnter Username 2 to delete: ");
	scanf(" %s",uname2);

	write(sd, uname1, sizeof(uname1));
	write(sd, uname2, sizeof(uname2));

	read(sd, buffer, sizeof(buffer));

	printf("%s",buffer);
	admin_functions(sd);
}

void newJointAccount(int sd, int flag)
{
	char uname1[20], pass1[20], uname2[20], pass2[20], buffer[30];
	printf("\n\tEnter first username: ");
	scanf(" %s", uname1);
	printf("\n\tEnter password: ");
	scanf(" %s", pass1);
	printf("\n\tEnter second username: ");
	scanf(" %s", uname2);
	printf("\n\tEnter password: ");
	scanf(" %s", pass2);

	write(sd, uname1, sizeof(uname1));
	write(sd, pass1, sizeof(pass1));
	write(sd, uname2, sizeof(uname2));
	write(sd, pass2, sizeof(pass2));

	read(sd, buffer, sizeof(buffer));
	printf("%s", buffer);
	if(flag==1)
		mainMenu(sd);
	else
		admin_functions(sd);
}

void signUp(int sd, int flag)
{
	int account_id;
	char uname[20],pass[20], buffer[30];

	printf("\n\tEnter username: ");
	scanf(" %s",uname);
	printf("\n\tEnter password: ");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));

	read(sd, buffer, sizeof(buffer));
	printf("%s", buffer);
	if(flag==1)
		mainMenu(sd);
	else
		admin_functions(sd);
}

void login(int sd)
{
	char buffer[50];
	char uname[20],pass[20];
	int flag;

	printf("\n\tEnter username: ");
	scanf(" %s",uname);
	printf("\n\tEnter password: ");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));

	read(sd, &flag, sizeof(flag));
	read(sd, buffer, sizeof(buffer));
	printf("%s",buffer);

	if(flag==1)
		displayMenu(sd);
	else
		mainMenu(sd);


}

void jointAccountLogin(int sd)
{
	char buffer[30];
	char uname1[20],pass[20],uname2[20];
	int flag;

	printf("\n\tEnter username: ");
	scanf(" %s",uname1);
	
	//printf("Enter second username: ");
	//scanf(" %s",uname2);
	
	printf("\n\tEnter password for user: ");
	scanf(" %s",pass);

	write(sd, uname1,sizeof(uname1));
	//write(sd, uname2,sizeof(uname2));
	write(sd, pass, sizeof(pass));

	read(sd, &flag, sizeof(flag));
	read(sd, buffer, sizeof(buffer));
	printf("%s",buffer);

	if(flag==1)
	{
		jointDisplayMenu(sd);
	}
	else
		mainMenu(sd);

}

void viewDetails(int sd)
{
	char uname[20];
	int acc_id, balance;

	read(sd,uname, sizeof(uname));
	read(sd,&acc_id, sizeof(acc_id));
	read(sd,&balance, sizeof(balance));

	printf("Username: %s,\t Account ID: %d,\t Balance: %d\n",uname,acc_id,balance);
	displayMenu(sd);
}

void viewJointDetails(int sd)
{
	char uname1[20], uname2[20];
	int acc_id, balance;

	read(sd,uname1, sizeof(uname1));
	read(sd,uname2, sizeof(uname2));
	read(sd,&acc_id, sizeof(acc_id));
	read(sd,&balance, sizeof(balance));

	printf("Username1: %s,\tUsername2: %s,\tAccount ID: %d,\tBalance: %d\n",uname1,uname2,acc_id,balance);
	jointDisplayMenu(sd);
}

void deposit(int sd)
{
	int amount;
	printf("\n\tEnter amount to deposit: ");
	scanf("%d",&amount);
	
	write(sd, &amount, sizeof(amount));
	read(sd, &amount, sizeof(amount));
	printf("\tNew Balance: %d",amount);
	
	displayMenu(sd);
}

void jointDeposit(int sd)
{
	int amount;
	printf("\n\tEnter amount to deposit: ");
	scanf("%d",&amount);
	
	write(sd, &amount, sizeof(amount));
	read(sd, &amount, sizeof(amount));
	printf("\tNew Balance: %d",amount);
	
	jointDisplayMenu(sd);
}

void jointWithdraw(int sd)
{
	int amount,flag;
	printf("\n\tEnter amount to withdraw: ");
	scanf("%d",&amount);

	write(sd, &amount, sizeof(amount));
	read(sd, &flag, sizeof(flag));
	
	if(flag==0)
	{
		printf("\tInsufficient Balance\n");
		read(sd, &amount, sizeof(amount));
		printf("\tBalance: %d",amount);
	}
	else
	{
		read(sd, &amount, sizeof(amount));
		printf(" \tNewBalance: %d",amount);

	}
	
	jointDisplayMenu(sd);
}





void withdraw(int sd)
{
	int amount,flag;
	printf("\n\tEnter amount to withdraw: ");
	scanf("%d",&amount);

	write(sd, &amount, sizeof(amount));
	read(sd, &flag, sizeof(flag));
	
	if(flag==0)
	{
		printf("\tInsufficient Balance\n");
		read(sd, &amount, sizeof(amount));
		printf("\tBalance: %d",amount);
	}
	else
	{
		read(sd, &amount, sizeof(amount));
		printf("\tNewBalance: %d",amount);

	}
	
	displayMenu(sd);
}

void jointPassChange(int sd)
{
	char pass[20];
	
	printf("\n\tEnter the new Password: ");
	scanf(" %s",pass);
    

	write(sd,pass,sizeof(pass));
	mainMenu(sd);
	
}



void passChange(int sd)
{
	char pass[20];
	
	printf("\n\tEnter the new Password: ");
	scanf(" %s",pass);

	write(sd,pass,sizeof(pass));
	mainMenu(sd);
	
}

void displayMenu(int sd)
{
	int choice;
	printf("\n\t1.View Details\n\t2.Deposit\n\t3.Withdraw\n\t4.Password Change\n\t5.EXIT\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: viewDetails(sd);
				break;
		case 2: deposit(sd);
				break;
		case 3: withdraw(sd);
				break;
		case 4: passChange(sd);
				break;
		case 5: mainMenu(sd);
				break;
		default: printf("Enter proper choice");
				break;

	}
}

void jointDisplayMenu(int sd)
{
	int choice;
	printf("\n\t1.View Details\n\t2.Deposit\n\t3.Withdraw\n\t4.Password Change\n\t5.EXIT\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: viewJointDetails(sd);
				break;
		case 2: jointDeposit(sd);
				break;
		case 3: jointWithdraw(sd);
				break;
		case 4: jointPassChange(sd);
				break;
		case 5: mainMenu(sd);
				break;
	

	}

}

void admin_functions(int sd)
{
	int choice;
	
	printf("\n\t1.Add Account\n\t2.Delete Account\n\t3.Search Account\n\t4.Add Joint Account\n\t5.Delete Joint Account\n\t6.Search Joint Account\n\t7.Exit\n\tEnter your choice: ");
	scanf("%d", &choice);
	
	char buffer[100], uname[20], pass[20], uname1[20], uname2[20];
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
		case 1:signUp(sd,0);
			break;
		case 2:deleteAccount(sd);
			break;
		case 3:printf("\n\tEnter username to search: ");
			scanf(" %s", uname);
			write(sd, uname, sizeof(uname));
			read(sd, &buffer, sizeof(buffer));
			printf(" %s", buffer);
			admin_functions(sd);
			break;
		case 4:newJointAccount(sd,0);
			break;
		case 5:deleteJointAccount(sd);
			break;
		case 6:printf("\n\tEnter username 1 to search: ");
			scanf(" %s", uname1);
			printf("\n\tEnter username 2 to search: ");
			scanf(" %s", uname2);
			write(sd, uname1, sizeof(uname1));
			write(sd, uname2, sizeof(uname2));
			read(sd, &buffer, sizeof(buffer));
			printf("%s", buffer);
			admin_functions(sd);
			break;
		case 7:mainMenu(sd);
	}
}

void adminLogin(int sd)
{
	char uname[20], pass[20], buffer[20];
	int flag;
	
	printf("\n\n\tEnter the admin username: ");
	scanf(" %s",uname);
	printf("\n\tEnter admin password: ");
	scanf(" %s",pass);
	
	write(sd, uname, sizeof(uname));
	write(sd, pass, sizeof(pass));
	read(sd, &flag, sizeof(flag));
	read(sd, buffer, sizeof(buffer));
	printf("\n");
	printf("%s",buffer);
	if(flag == 1)
		admin_functions(sd);
	else
		mainMenu(sd);
}

void mainMenu(int sd)
{
	int choice;
	printf("\n****************************************************************************\n");
	printf("\n-----------------------------||ONLINE BANKING||-----------------------------\n");
        printf("\n*****************************************************************************\n");
	printf("\n\t1.ADMIN LOGIN\n\t2.USER LOGIN\n\t3.JOINT ACCOUNT USER LOGIN\n\t4.EXIT\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: adminLogin(sd);
				break;
		case 2: login(sd);
				break;
		case 3: jointAccountLogin(sd);
				break;
		case 4: exit(0);
				break;

	}
}

int main(int argc,char *argv[])
{
	
	struct sockaddr_in server;
	int sd;
	char buffer[80];
	sd = socket(AF_INET, SOCK_STREAM,0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8081);

	connect(sd, (struct sockaddr *)(&server), sizeof(server));
	
	mainMenu(sd);
	close(sd);
	return 0;
}
