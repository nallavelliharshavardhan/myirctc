a.out:main.o login_menue.o train_menue.o sign_in.o sign_up.o print_train_info.o reserve_ticket.o booking_details.o cancel_ticket.o
	gcc main.o login_menue.o train_menue.o sign_in.o sign_up.o print_train_info.o reserve_ticket.o booking_details.o cancel_ticket.o -o myirctc
main3.o:main.c
	gcc -c main.c
menue.o:login_menue.c
	gcc -c login_menue.c
menue2.o:train_menue.c
	gcc -c train_menue.c
sign_in.o:sign_in.c
	gcc -c sign_in.c
sign_up.o:sign_up.c
	gcc -c sign_up.c
print_train_info.o:print_train_info.c
	gcc -c print_train_info.c
reserve_ticket.o:reserve_ticket.c
	gcc -c reserve_ticket.c
booking_details.o:booking_details.c
	gcc -c booking_details.c
cancel_ticket.o:cancel_ticket.c
	gcc -c cancel_ticket.c
