#include"train.h"
#include<unistd.h>
void Reserve_ticket()
{

	srand(getpid());

	TRAIN_I *DETAILS=NULL;
	//stores booking information
	PASSE *INFO=NULL;
	int tr_no,booking_id;
	//linked list for passenger details
	PASSE *PASSD=NULL,*temp=NULL;
	//load available trains information 
	DETAILS=sync_train_info(DETAILS);
	printf("enter the train no:");
	scanf("%d",&tr_no);
 	//check if entered train number exist or not
	if(!check_train_avai(DETAILS,tr_no))
       	{
        	printf("train is not available\n");
        	return;
    	}

	INFO=malloc(sizeof(PASSE));
	//terminate if memory is not allocated
	if(INFO==NULL)
	{
		printf("memory allocation failed\n");
		exit(0);
	}

	INFO->TR_NO=tr_no;
	printf("enter the date:");
	scanf("%d",&INFO->journey_date.day);
        printf("enter the month:");
	scanf("%d",&INFO->journey_date.month);
	printf("enter the year:");
	scanf("%d",&INFO->journey_date.year);
	//check booking date is valid and satisfy date is under 3 days from the current date
	if(!isBookingDateValid(INFO->journey_date.day,
				INFO->journey_date.month,
				INFO->journey_date.year))
	{
				printf("Booking denied: Reservation allowed only up to 3 days from the current date.\n");
				return;
	}

	printf("enter no of seats to reserve: "); 
	scanf("%d", &INFO->NO_SE);
	printf("--------------------------------------------------------------\n");
	//store passengers reservation details in sll
	PASSD=input_reservation_details(NULL,INFO->NO_SE);
	//generate booking id for reserved ticket
	booking_id=generate_booking_id();
	temp=PASSD;
	
	for(int i=0;((i<INFO->NO_SE )&&(temp!=NULL));i++)
	{

	        TRAIN_I *selected_train=find_train(DETAILS,INFO->TR_NO);

        	if(selected_train==NULL)
       		 {
            		printf("Train not found\n");
            		return;
       		 }
		//waiting list
                if(selected_train->available_seats<=0)
         	{
			temp->seat_no=-1;  
			int wl=get_waiting_count(INFO->TR_NO)+1;
			printf("%s added to WAITING LIST (WL%d)\n",temp->name,wl);
			temp->booking_id=booking_id;
			temp->TR_NO=INFO->TR_NO;
			temp->journey_date=INFO->journey_date;
			temp=temp->addr;
			continue;
		}
                //to display availabel seats in selected train
		display_available_seats(selected_train);
		printf("Choose seat number for %s: ",temp->name);
		scanf("%d",&temp->seat_no); 

		//check is selected seat is already reserved or not
		if(is_seat_reserved(INFO->TR_NO, temp->seat_no)) 
		{
			printf("Seat already taken! Choose another.\n"); 
			i--;
			// retry same passenger 
			continue;
		}

		selected_train->available_seats--;
		temp->booking_id=booking_id;
		temp->TR_NO=INFO->TR_NO;
		temp->NO_SE=INFO->NO_SE; 
		temp->journey_date=INFO->journey_date;
		temp=temp->addr;
		
	}
	printf("--------------------------------------------------------------\n");
	printf("Booking Successfull\nBooking Id:%d\n",booking_id);
	printf("--------------------------------------------------------------\n");

	//save booking details in file
	save_passengers_info_to_file(INFO,PASSD);

}
void save_passengers_info_to_file(PASSE *date_details,PASSE *pass_details)
{
	FILE *spif=NULL;
	PASSE *temp1=NULL,*temp2=NULL;
	temp1=date_details;
	temp2=pass_details;
	//open file that stores passenger booking details
	spif=fopen("passengers_info.txt","a");
	
	if(spif==NULL)
	{
		printf("file is failed to open\n");
		exit(0);
	}
	//traverse through the sll and stores in file
	while(temp2!=NULL)
	{
		fprintf(spif,"%d %d %d %d %d %d %s %d %s\n",temp2->booking_id,temp1->TR_NO,
			  				    temp2->seat_no,
						            temp1->journey_date.day,
			   			            temp1->journey_date.month,
						            temp1->journey_date.year,
						            temp2->name,
						            temp2->age,
						            temp2->gender);
					       	            temp2=temp2->addr;
	}

	fclose(spif);
	
}
TRAIN_I *sync_train_info(TRAIN_I *det)
{
	FILE *sync=NULL;
	int tstr;
	TRAIN_I *newnode=NULL,*temp=NULL;
	sync=fopen("all_train_info.txt","r");
	
	if(sync==NULL)
	{
		printf("file is failed to open\n");
		exit(0);
	}
	else
	{
		//extract train information from file and stores dynamically
		while(1)
		{
			newnode=calloc(1,sizeof(TRAIN_I));
		
			if(newnode==NULL)
			{
				printf("memory allocation failed\n");
				break;
			}       
	       		tstr=fscanf(sync,"%d %s %s %s %d %d",&newnode->train_no,
                    					      newnode->train_name,
            					              newnode->source,
                    					      newnode->destination,
          				        	      &newnode->no_of_seats,
                   				      	      &newnode->available_seats);
			if(tstr!=6)
			{
				free(newnode);
				break;
			}
			if(det==NULL)
			{
				det=newnode;
			}
			else
			{
				temp=det;

				while((temp->link)!=NULL)
				{
					temp=temp->link;
				}
				temp->link=newnode;
			}
		}
	}
	fclose(sync);
	return det;
}
int check_train_avai(TRAIN_I *cta,int t_no)
{
	TRAIN_I *t=NULL;
	t=cta;

	//condition to check train_no is matching with file data or not
	while(t!=NULL)
	{
		if(t->train_no==t_no)
		{
			return 1;
		}
		t=t->link;
	}
	return 0;
}
PASSE *input_reservation_details(PASSE *pd,int nos)
{
	PASSE *passnode=NULL,*temp=NULL;

	for(int i=nos;i!=0;i--)
	{
		passnode=calloc(1,sizeof(PASSE));
		printf("enter the name:");
		scanf("%s",passnode->name);//store all passengers details in heap area using sll in passenger structure
		printf("enter the age:");
		scanf("%d",&passnode->age);
		printf("enter the gender:");
		scanf("%s",passnode->gender);
		
		if(pd==NULL)
		{
			pd=passnode;
		}
		else
		{
			temp=pd;

			while((temp->addr)!=NULL)
			{
				temp=temp->addr;
			}
			temp->addr=passnode;
		}
	}
	printf("--------------------------------------------------------------\n");

	return pd;
}
void display_available_seats(TRAIN_I *train) 
{
    printf("Available seats:\n");
    int count =0;

    for(int i=1;i<=train->no_of_seats;i++)
    {
        if(!is_seat_reserved(train->train_no,i))
       	{
            printf("%d ",i);
            count++;

	    if(count%20==0)//for displaying the seats in matrix format
                printf("\n");
        }
    }

    if(count ==0)
    {
	
        printf("No seats available.\n");
    }

    printf("\n");
}
int is_seat_reserved(int train_no,int seat_no) 
{
	int tr,seat,day,month,year,age,b_id;
        char name[100],gender[10];
       	FILE *fp=fopen("passengers_info.txt","r"); 

	if(fp==NULL) 
	{
	       	return 0;
	       	// file not found, no reservations yet
	 }

	while(fscanf(fp,"%d %d %d %d %d %d %s %d %s",&b_id,&tr,&seat,&day,&month,&year,name,&age,gender)==9) 
	{
	       	if(tr ==train_no && seat == seat_no)
	       	{
		       	fclose(fp);
		       	return 1;
		       	// seat already reserved
		 }

	}

	fclose(fp); 
	return 0;
       	// seat is free
}

int generate_booking_id()
{
	//generate booking id
	return rand()%900000+100000;
}

TRAIN_I *find_train(TRAIN_I *head, int train_no)
{
    while (head != NULL)
    {
        if (head->train_no == train_no)
            return head;

        head = head->link;
    }

    return NULL;
}
int get_waiting_count(int train_no)
{
    FILE *fp=fopen("passengers_info.txt","r");

    if(fp==NULL) 
	    return 0;

    int b_id,tr,seat,d,m,y,age;
    char name[100],gender[10];
    int count=0;

    while(fscanf(fp,"%d %d %d %d %d %d %s %d %s",
                 &b_id,&tr,&seat,&d,&m,&y,name,&age,gender)==9)
    {
        if(tr==train_no && seat==-1)
            count++;
    }

    fclose(fp);
    return count;
}

int isBookingDateValid(int d,int m,int y)
{
    time_t now=time(NULL);

    struct tm today=*localtime(&now);//store current date and time
    today.tm_hour=0;
    today.tm_min=0;
    today.tm_sec=0;

    struct tm user={0};//store booking date 
    user.tm_mday=d;
    user.tm_mon=m-1;
    user.tm_year=y-1900;

    time_t today_time=mktime(&today);//convert date and time into seconds of today
    time_t user_time=mktime(&user);//convert date and time into seconds of booking date

    time_t last_allowed=today_time+(3*24*60*60);

    if (user_time>=today_time && user_time<=last_allowed)
        return 1;   // allowed
    else
        return 0;   // not allowed
}

