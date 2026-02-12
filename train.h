#ifndef TRAIN_H
#define TRAIN_H

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Structures*/
typedef struct Date_info{
        int day;
	int month;
	int year;
}DATE;

typedef struct seats_info{
        int total_seats;
        int waiting_list;
        int cur_bo_seat_no;//current booking seat number
}SEAT_I;

typedef struct train_info{
        char train_name[100];
        int train_no;
        char source[100];
        char destination[100];
        int no_of_seats;
        int available_seats;
        SEAT_I seats;
        struct train_info *link;
}TRAIN_I;

typedef struct passenger_info{
        char name[100];
        int age;
        char gender[10];
	int seat_no;
	int TR_NO;
	int NO_SE;
	int booking_id;
	DATE journey_date;
	struct passenger_info *addr;
}PASSE;

extern PASSE PASS;
extern TRAIN_I TRAIN;
extern SEAT_I SEAT;

/*main functions*/
void Reserve_ticket();
void Booking_details();
void Cancel_ticket();
void Login();

/*Reserve Functions*/
int is_seat_reserved(int train_no, int seat_no);
void display_available_seats(TRAIN_I *train);
void save_passengers_info_to_file(PASSE *date_details,PASSE *pass_details);
PASSE *input_reservation_details(PASSE *pd,int nos);
int check_train_avai(TRAIN_I *cta,int t_no);
TRAIN_I *sync_train_info(TRAIN_I *det);
void Reserve_ticket();
int get_waiting_count(int train_no);
int generate_booking_id();
TRAIN_I *find_train(TRAIN_I *head, int train_no);
int isBookingDateValid(int d,int m,int y);

/*Cancel Functions*/
PASSE *store_passenger_details_in_sll(PASSE *head);
void save_updated_passenger_details(PASSE *head);
PASSE *cancel_ticket_and_update(PASSE *DEL);

/*Booking Details Functions*/
void print_booking_details(PASSE *print);
PASSE *sync_passenger_details(PASSE *head);

#endif



