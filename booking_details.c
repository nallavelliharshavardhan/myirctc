#include"train.h"
void Booking_details()
{
	PASSE *BOOK=NULL;
	//store ticket booking details in linked list
	BOOK=sync_passenger_details(BOOK);
	//display booking details
	print_booking_details(BOOK);

}
void print_booking_details(PASSE *print)
{
	PASSE *temp=NULL;
	int booking_id;
	printf("Enter the booking id:");
	scanf("%d",&booking_id);
	temp=print;
	printf("--------------------------------------------------------------\n");
	printf("                      BOOKING DETAILS\n");
	printf("--------------------------------------------------------------\n");

	//search for matching booking_id in linked list
	while(temp!=NULL)
	{
		if((temp->booking_id==booking_id))
		{
			printf("Train Number     : %d\n"
				"Seat Number      : %d\n"
				"Journey Date     : %02d/%02d/%04d\n"
				"Name             : %s\n"
				"Age              : %d\n"
				"Gender           : %s\n",temp->TR_NO,
					  		temp->seat_no,
						        temp->journey_date.day,
							temp->journey_date.month,
							temp->journey_date.year,
							temp->name,
							temp->age,																		    temp->gender);

		}

		temp=temp->addr;
	}
	printf("--------------------------------------------------------------\n");
	
}

PASSE *sync_passenger_details(PASSE *head)
{
	PASSE *temp=NULL;
	FILE *spd=NULL;
	int total;
	PASSE *newnode=NULL;
	spd=fopen("passengers_info.txt","r");
	
	if(spd==NULL)
        {
                printf("error try again\n");
                exit(0);
        }
	else
	{
		//read file data and store in linked list
		while(1)
		{
			newnode=calloc(1,sizeof(PASSE));
			total=fscanf(spd,"%d %d %d %d %d %d %s %d %s",&newnode->booking_id,
								       &newnode->TR_NO,
								       &newnode->seat_no,
								       &newnode->journey_date.day,
								       &newnode->journey_date.month,
								       &newnode->journey_date.year,
								       newnode->name,
								       &newnode->age,
								       newnode->gender);
			if(total!=9)
			{
				free(newnode);
				break;
			}
			
			newnode->addr=NULL;
			
			if(head==NULL)
			{
				head=newnode;
			}
			else
			{
				temp=head;
			
				while((temp->addr)!=NULL)
				{
					temp=temp->addr;
				}
			
				temp->addr=newnode;

			}

		}
	}
	return head;
}

