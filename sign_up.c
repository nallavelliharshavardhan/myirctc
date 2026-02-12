#include"myheader.h"
#include"credintials.h"
extern int cnt;
int sign_up(){
	FILE *fptr=NULL;
	
	char usr[100];
	char pass[100];
	char str[100];
	//open file usr_logins.txt to store new user credintials
	fptr=fopen("usr_logins.txt","a");
	
	if(fptr==NULL)
	{
		//stop execution if file not opened
		printf("file is failed to open");
		exit(0);
	}
	else
	{
		printf("--------------------------------------------------------------\n");
                printf("Create a new user account\n");
                printf("--------------------------------------------------------------\n");		
		printf("enter username:");
		scanf("%s",usr);
	
		//check username is exist already or not
		if(check_usrname(usr)==1)
			strcpy(CRED.username,usr);
		else
			return 0;

		//user is allowed to enter password only 5 times
		while(++cnt<=5)
		{
			printf("enter password:");
               		scanf("%s",pass);

			//check password is exist or not
			if(check_pass(pass)==1)
			{
				strcpy(CRED.password,pass);
				break;
			}
			else
			{
				printf("--------------------------------------------------------------\n");
				printf("error:password contain atleast 1 uppercase,1 lowecase,1 numeric and 1 special symbol\n");
				printf("--------------------------------------------------------------\n");
			}
		}

		if(cnt>5)
		{
			printf("Time out \n");
			exit(0);
		}
		//stores the user credintials in file

		fprintf(fptr,"%s %s\n",CRED.username,CRED.password);

		
	}
	printf("--------------------------------------------------------------\n");
        printf("Account Created Successfully.\n");
	printf("Please login again.\n");
        printf("--------------------------------------------------------------\n");
	
	fclose(fptr);
	return 1;
}
int check_pass(char *pas)
{
        int UP=0,lw=0,dg=0,sp=0;

	//password must contain atleast 8 characters
	//it must contain 1 uppercase 1 lowecase and one special character 
	if(strlen(pas)>=8)
	{
		for(int i=0;pas[i];i++){
			if((pas[i]>=65)&&(pas[i]<=90))
				UP=1;
			else if((pas[i]>=97)&&(pas[i]<=122))
				lw=1;
			else if((pas[i]>=48)&&(pas[i]<=57))
				dg=1;
			else
				sp=1;
		}
		if((UP==1)&&(lw==1)&&(dg==1)&&(sp==1))
			return 1;
        }
        return 0;
}
int check_usrname(char *un)
{
        char temp[100];
        FILE *usr=NULL;
        usr=fopen("usr_logins.txt","r");

	if(usr==NULL)
	{
                printf("failed to open");
                exit(0);
        }

	//read username data from file
        while(fscanf(usr,"%s ",temp)!=EOF)
	{
		//check username already exist in file or not
                if(strcmp(un,temp)==0)
		{
			printf("--------------------------------------------------------------\n");
                        printf("Username already exist\n");
                        printf("Try another username\n");
		 	printf("--------------------------------------------------------------\n");
                        return 0;
                }
        }

        fclose(usr);
        return 1;
}

