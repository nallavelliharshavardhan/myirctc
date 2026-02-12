#include"myheader.h"
int lcnt=0;
int sign_in()
{
	FILE *fptr=NULL;
	
	char usr[100];
	char pass[100];
	//open file usr_logins.txt that stores login credintials
	fptr=fopen("usr_logins.txt","r");
	
	if(fptr==NULL)
	{
		//stop program if file cannot be opened
		printf("File is Failed to Open\n");
		exit(0);
	}
	//user is allowed only 3 login attempts
	while(++lcnt<=3)
	{
		printf("--------------------------------------------------------------\n");
		printf("enter username:");
		scanf("%s",usr);
		
		printf("enter password:");
		scanf("%s",pass);
		
		//check credintials valid or not
		if(check_usr_pass(usr,pass,fptr)==1)
		{
			printf("\nLogin Successful. Welcome, %s\n", usr);
			printf("--------------------------------------------------------------\n\n");
			//login success
			return 1;
		}
	}

	if(lcnt>3)
	{
		printf("You have reached max no.of attempts\n");
		printf("please wait for 5mins to login again\n");
		return 0;
	}
	
	fclose(fptr);
	//login failed
	return 0;

}
int check_usr_pass(char *user,char *paw,FILE *fptr)
{
	char usr[100];
	char pass[100];

	//read each username and password from the file
	while(fscanf(fptr,"%s %s",usr,pass)==2)
	{
		//compare file data with username and password
		if((strcmp(usr,user)==0)&&(strcmp(pass,paw)==0))
			//match found
			return 1;
	}
	
	printf("username or password is incorrect\n");
	//match not found login failed
	return 0;
}




