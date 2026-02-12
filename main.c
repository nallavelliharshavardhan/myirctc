#include"myheader.h"
#include"credintials.h"
#include"train.h"
int cnt=0;
CREDI CRED;
PASSE PASS;
TRAIN_I TRAIN;
SEAT_I SEAT;

int main()
{
	int choice;
	
	printf("==============================================================\n");
	printf("            MYIRCTC – TRAIN RESERVATION SYSTEM\n");
	printf("==============================================================\n\n");

	while(1)
	{
		//display main application menue(sign up,sign in,exit)
		menue();

		printf("Select option:");
		scanf("%d",&choice);
	
		switch(choice)
		{
			//handle new user registration
			case 1:sign_up();
			       break;
			//handle existing user 
			case 2:sign_in();
			       Login();
			       break;
			//terminate the application
			case 3:printf("--------------------------------------------------------------\n");
			       printf("Thank you for using MYIRCTC.\n");
			       printf("Application Closed Successfully.\n");
			       printf("--------------------------------------------------------------\n");
			       exit(0);
			default:printf("invalid choice");
		}
	}
}
	

void Login()
{
	char option;
	
	//display available trains
	print_train_info();

	while(1)
	{
		menue2();

		printf("select option:");
		scanf("  %c",&option);

		if((option=='R')||(option=='r'))
		{
			Reserve_ticket();
		}
		else if((option=='C')||(option=='c'))
		{

                      Cancel_ticket();
                }
		else if((option=='B')||(option=='b'))
		{

                        Booking_details();
                }
		else if((option=='Q')||(option=='q'))
		{

			printf("--------------------------------------------------------------\n");
			printf("Returning to Login Menu...\n");
    			printf("--------------------------------------------------------------\n");
                        break;
                }
		else
		{
			printf("select vaild option\n");
		}
         }
}


		



