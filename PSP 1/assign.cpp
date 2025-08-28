#include <iostream>
#include <string>
#include <iomanip>
#include<limits>
#include<cctype>
#include<ctime>
using namespace std;

const double process = 0.50;
const double tax = 0.06;
const int trainnum = 3;

int orderhistory[trainnum] = { 0 };

char choice;

int train_no[3] = { 1,2,3 };
int dtime[] = { 10, 11, 12, 13, 14, 15, 16 };
double fare[] = { 50,56,96 };


void Menu() {

	cout << "\nWelcome to TWD Train Ticket Booking System!\n";
	cout << "1. BUY TICKET \n";
	cout << "2. Order History \n";
	cout << "3. EXIT \n";
	cout << endl;
	cout << "Please choose. (1-3): \n";
}

void user() {
	cout << "    __________   ========  |      __      |   =====       \n";
	cout << "   / |        |     ||     |     |  |     |  |      \\      \n";
	cout << "  /--         |     ||     |    |    |    |  |       |   \n";
	cout << "  |           |     ||     |   |      |   |  |       |   \n";
	cout << "   -----------      ||     |__|        |__|  |______/    \n";
	cout << "    000   000                                          \n";

	cout << "\nWelcome to TWD Train Ticket Booking System!\n\n";

	string user_name, email, ic_number;
	int phone_number;

	cout << "Please fill in your personal's information before you book your train ticket. \n\n";
	cout << "---------------------------------------------------------------------------------\n";
	cout << "PASSENGER INFORMATION  \n";
	cout << "User Name (as per IC) : ";
	getline(cin, user_name);
	cout << "IC Number / Passport Number (without -) : ";
	cin >> ic_number;

	cout << "\nCONTACT INFORMATION\n";
	cout << "Phone number (without -) : +60";
	cin >> phone_number;
	cout << "Email : ";
	cin >> email;

	char choice;
	do {
		cout << "\nPlease confirm that the information is correct.";

		cout << "Y/N?";
		cin >> choice;
		if (choice == 'N' || choice == 'n') {
			cout << "\nGoing back to menu.\n\n";
			cout << "PASSENGER INFORMATION  \n";
			cout << "User Name (as per IC) : ";
			cin.ignore();
			getline(cin, user_name);
			cout << "IC Number / Passport Number (without -) : ";
			cin >> ic_number;

			cout << "\nCONTACT INFOMATION\n";
			cout << "Phone number (without -) : +60";
			cin >> phone_number;
			cout << "Email : ";
			cin >> email;
		}
		else if (choice == 'Y' || choice == 'y') {
			break;
		}
		else {
			cout << "Invalid Input!";
		}
	} while (choice != 'Y' && choice != 'y');



	cout << "\nThis is the information.\n\n";
	cout << "Name : " << user_name << endl;
	cout << "IC Number / Passport Number : " << ic_number << endl;
	cout << "Phone Number : +60" << phone_number << endl;
	cout << "Email : " << email << endl;

	cout << "\nPress ENTER to continue.";
	cin.ignore();
	cin.get();
}

void ticket()
{
	int trainno, trainno1, deptime, deptime1, deptime2, pax, pax1, time1 = 0;
	double money = 0.0;
	string date1;

	cout << "AVAILABLE TRAIN:\n\n";
	cout << left << setw(10) << "=========================================" << endl;
	cout << left << setw(10) << "| Train No | ORIGIN       | DESTINATION |" << endl;
	cout << left << setw(10) << "-----------------------------------------" << endl;
	cout << left << setw(10) << "| 001      | Kuala Lumpur | Butterworth |" << endl;
	cout << left << setw(10) << "| 002      | Kajang       | JB Sentral  |" << endl;
	cout << left << setw(10) << "| 003      | KL Sentral   | Ipoh        |" << endl;
	cout << left << setw(10) << "=========================================" << endl;

	cout << "\nPlease choose your train number : ";
	cin >> trainno;
	cout << endl;

	switch (trainno) {
	case 1:
		cout << left << setw(5) << "==================================" << endl;
		cout << left << setw(5) << "| NO | DEPARTURE TIME | MIN.FARE |" << endl;
		cout << left << setw(5) << "----------------------------------" << endl;
		cout << left << setw(5) << "| 1  | 10:00AM        | RM 96.00 |" << endl;
		cout << left << setw(5) << "| 2  | 12:00PM        | RM 96.00 |" << endl;
		cout << left << setw(5) << "| 3  | 15:00PM        | RM 96.00 |" << endl;
		cout << left << setw(5) << "==================================" << endl;
		cout << "\nPlease choose your departure time : ";
		cin >> deptime;
		if (deptime == 1) {
			time1 = dtime[0];
			money = fare[2];
		}
		else if (deptime == 2) {
			time1 = dtime[2];
			money = fare[2];
		}
		else if (deptime == 3) {
			time1 = dtime[5];
			money = fare[2];
		}
		break;
	case 2:
		cout << left << setw(5) << "==================================" << endl;
		cout << left << setw(5) << "| NO | DEPARTURE TIME | MIN.FARE |" << endl;
		cout << left << setw(5) << "----------------------------------" << endl;
		cout << left << setw(5) << "| 1  | 10:00AM        | RM 50.00 |" << endl;
		cout << left << setw(5) << "| 2  | 13:00PM        | RM 50.00 |" << endl;
		cout << left << setw(5) << "| 3  | 16:00PM        | RM 50.00 |" << endl;
		cout << left << setw(5) << "==================================" << endl;
		cout << "\nPlease choose your departure time : ";
		cin >> deptime1;
		if (deptime1 == 1) {
			time1 = dtime[0];
			money = fare[0];
		}
		else if (deptime1 == 2) {
			time1 = dtime[3];
			money = fare[0];
		}
		else if (deptime1 == 3) {
			time1 = dtime[6];
			money = fare[0];
		}
		break;
	case 3:
		cout << left << setw(5) << "==================================" << endl;
		cout << left << setw(5) << "| NO | DEPARTURE TIME | MIN.FARE |" << endl;
		cout << left << setw(5) << "----------------------------------" << endl;
		cout << left << setw(5) << "| 1  | 11:00AM        | RM 56.00 |" << endl;
		cout << left << setw(5) << "| 2  | 14:00PM        | RM 56.00 |" << endl;
		cout << left << setw(5) << "| 3  | 16:00PM        | RM 56.00 |" << endl;
		cout << left << setw(5) << "==================================" << endl;
		cout << "\nPlease choose your departure time : ";
		cin >> deptime2;
		if (deptime2 == 1) {
			time1 = dtime[1];
			money = fare[1];
		}
		else if (deptime2 == 2) {
			time1 = dtime[4];
			money = fare[1];
		}
		else if (deptime2 == 3) {
			time1 = dtime[6];
			money = fare[1];
		}
		break;
	default:
		cout << "Invalid";
		break;
	}
	cout << endl;
	cout << "Departure date : ";
	cin >> date1;
	cout << "Number of pax : ";
	cin >> pax;

	cout << "\nTICKET CONFIRMATION" << endl;
	cout << "--------------------" << endl;
	cout << "Train No : " << trainno << endl;
	cout << "Departure Time : " << time1 << ":00";
	if (time1 >= 12) {
		cout << "PM\n";
	}
	else {
		cout << "AM\n";
	}
	cout << "Departure Date : " << date1 << endl;
	cout << "Number of pax : " << pax << endl;
}



int main()
{
	int menu_choose;

	user();

	do {
		Menu();
		cin >> menu_choose;

		if (menu_choose == 1) {

			ticket();

			do {
				cout << "\nPlease confirm your ticket is correct(Y/N) : ";
				cin >> choice;
				cout << endl;

				if (choice == 'n' || choice == 'N') {
					ticket();
				}
				else if (choice == 'y' || choice == 'Y') {
					break;
				}
				else {
					cout << "Invalid" << endl;
				}
			} while (choice != 'Y' && choice != 'y');

			do {
				cout << "Do you need to add on?(Y/N) : ";
				cin >> choice;
				cout << endl;

				if (choice == 'y' || choice == 'Y') {
					ticket();

				}
			} while (choice != 'n' && choice != 'N');


















		}
		else if (menu_choose == 2) {

		}
		else if (menu_choose == 3) {
			cout << "THANK YOU! Have a nice day.";
			return 1;
		}
		else {
			cout << "Invalid Input! \n";
			cout << "Going back to main menu.\n";
		}

	} while (menu_choose != 3);
	
	return 0;
}