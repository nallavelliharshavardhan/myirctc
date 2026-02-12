#include<stdio.h>
#include<stdlib.h>
#include"train.h"
TRAIN_I TRAIN;
void delete_train_details(){
}
void insert_train_details(){
	FILE *fptr=NULL;
	fptr=fopen("all_train_info.txt","a");
	if(fptr==NULL){
		printf("file is failed to open\n");
		exit(0);
	}
	printf("enter the train no:");
	scanf("%d",&TRAIN.train_no);
	printf("enter the train name:");
	scanf("%s",TRAIN.train_name);
	printf("enter the source:");
	scanf(" %s",TRAIN.source);
	printf("enter the destination:");
	scanf(" %s",TRAIN.destination);
	printf("enter total no of seats:");
	scanf("%d",&TRAIN.no_of_seats);
	TRAIN.available_seats=TRAIN.no_of_seats;
	fprintf(fptr,"%d %s %s %s %d %d\n",TRAIN.train_no,TRAIN.train_name,TRAIN.source,TRAIN.destination,TRAIN.no_of_seats,TRAIN.available_seats);
	fclose(fptr);
}

int main(){
	int choice;
	printf("1:insert train details\n2:delete train_details\n3:exit\n");
	while(1){
	scanf("%d",&choice);
	switch(choice){
		case 1:insert_train_details();
		       break;
		case 2:delete_train_details();
		       break;
		case 3:exit(0);
		default:printf("invalid choice");
	}
	}
}




