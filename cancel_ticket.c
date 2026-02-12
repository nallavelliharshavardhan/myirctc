#include"train.h"
void Cancel_ticket()
{
	PASSE *CANCEL=NULL;
	//load all passenger details from file to linkrd list
	CANCEL=store_passenger_details_in_sll(CANCEL);
	//remove cancelled ticket and update linket list
	CANCEL=cancel_ticket_and_update(CANCEL);
	//save updated passenger details back to file 
	save_updated_passenger_details(CANCEL);

}
void save_updated_passenger_details(PASSE *head)
{
	FILE *supd=NULL;
	PASSE *temp=NULL;
	temp=head;
	supd=fopen("passengers_info.txt","w");
	//write each passenger record to file
	while(temp!=NULL)
	{
		fprintf(supd,"%d %d %d %d %d %d %s %d %s\n",temp->booking_id,
							    temp->TR_NO,
							    temp->seat_no,
							    temp->journey_date.day,
							    temp->journey_date.month,
							    temp->journey_date.year,
							    temp->name,
							    temp->age,
							    temp->gender);
		temp=temp->addr;
	}

	fclose(supd);
}
PASSE *cancel_ticket_and_update(PASSE *DEL)
{
	PASSE *new=NULL,*prev=NULL;
	int found=0;
	int bkg_id,tr_no,seat_no,day,month,year;
	printf("--------------------------------------------------------------\n");
	printf("                     CANCEL TICKET\n");
	printf("--------------------------------------------------------------\n");
	printf("enter booking id:");
	scanf("%d",&bkg_id);
	printf("enter train no:");
	scanf("%d",&tr_no);
	printf("enter the seat_no:");
	scanf("%d",&seat_no);
	printf("--------------------------------------------------------------\n\n");
	new=DEL;

	//search for matching ticket and display
	while(new!=NULL)
	{
		if((new->booking_id==bkg_id)&&(new->TR_NO==tr_no)&&(new->seat_no==seat_no))
		{
			found=1;
			printf("Booking ID       : %d\n"
				"Train Number     : %d\n"
				"Seat Number      : %d\n"
				"Journey Date     : %02d-%02d-%04d\n"
				"Name             : %s\n"
				"Age              : %d\n"
				"Gender           : %s\n",new->booking_id,new->TR_NO,
                                                          new->seat_no,new->journey_date.day,
							  new->journey_date.month,
					      		  new->journey_date.year,
							  new->name,
                        				  new->age,new->gender);
			
			if(prev==NULL)
			{
				DEL=new->addr;
			}
			else
			{
				prev->addr=new->addr;
			}

			free(new);
			break;
		}

		prev=new;
		new=new->addr;

	}

	if(found)
	{
		printf("--------------------------------------------------------------\n\n");
		printf("Ticket cancelled successfully.\n");
		printf("--------------------------------------------------------------\n\n");
	}
	else
	{
		printf("--------------------------------------------------------------\n\n");
		printf("No matching ticket found\n");
		printf("--------------------------------------------------------------\n\n");
	}

	return DEL;
}
PASSE *store_passenger_details_in_sll(PASSE *head)
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
		//read file data store into linked list
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

	fclose(spd);
        return head;
}
