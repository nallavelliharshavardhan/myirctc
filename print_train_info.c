#include<stdlib.h>
#include<stdio.h>
#include"train.h"
void print_train_info(){
        FILE *fptr=NULL;
        fptr=fopen("all_train_info.txt","r");
        if(fptr==NULL){
                printf("file is failed to open\n");
                exit(0);
        }
	printf("--------------------------------------------------------------\n");
        printf("                    TRAIN INFORMATION\n");
        printf("--------------------------------------------------------------\n");
        printf("--------------------------------------------------------------\n");
	printf("| %-2s | %-20s | %-10s | %-10s | %-4s |\n","ID", "Train Name", "From", "To", "Seat");

        while(fscanf(fptr,"%d%s%s%s%d%d",&TRAIN.train_no,
					TRAIN.train_name,
					TRAIN.source,
					TRAIN.destination,
					&TRAIN.no_of_seats,
					&TRAIN.available_seats)==6)
	{
		printf("--------------------------------------------------------------\n");
		printf("| %-2d | %-20s | %-10s | %-10s | %-4d |\n",TRAIN.train_no,
                                          		       TRAIN.train_name,
                                          		       TRAIN.source,
                                          		       TRAIN.destination,
                                         		       TRAIN.no_of_seats);

                /*printf("%d %s %s %s %d\n",TRAIN.train_no,
					  TRAIN.train_name,
					  TRAIN.source,
					  TRAIN.destination,
					  TRAIN.no_of_seats);*/
        }
	printf("--------------------------------------------------------------\n");
        fclose(fptr);
}

