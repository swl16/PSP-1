#include <iostream>
#include <string>
#include <iomanip>
#include<limits>
#include<chrono>
#include<ctime>
#include<cstdlib>
using namespace std;

const double process = 0.50;
const double tax = 0.06;
const int trainnum = 3;

int orderhistory[trainnum] = { 0 };

char choice;

int train_no[10];
int numofpax[100];
int dtime[] = { 10, 11, 12, 13, 14, 15, 16 };
double fare[] = { 50.00,56.00,96.00 };

struct Order {
	int trainno;
	int deptime;
	string date;
	int pax;
	double money;
	double total;
};

struct userinfor {
	string user_name;
	string email;
	string ic_number;
	int phone_number;
};

Order orders[100];   // store up to 100 orders
int orderCount = 0;

userinfor infor[100];
int inforCount = 0;

void Menu() {

	cout << "\nWelcome to TWD Train Ticket Booking System!\n";
	cout << "1. BUY TICKET \n";
	cout << "2. Order History \n";
	cout << "3. EXIT \n";
	cout << endl;
	cout << "Please choose. (1-3): \n";
}

userinfor user() {
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

	userinfor users;
	users.user_name = user_name;
	users.ic_number = ic_number;
	users.phone_number = phone_number;
	users.email = email;

	infor[inforCount++] = users;

	cout << "\nThis is the information.\n\n";
	cout << "Name : " << user_name << endl;
	cout << "IC Number / Passport Number : " << ic_number << endl;
	cout << "Phone Number : +60" << phone_number << endl;
	cout << "Email : " << email << endl;

	cout << "\nPress ENTER to continue.";
	cin.ignore();
	cin.get();

	return users;
}

Order ticket()
{
	int trainno, deptime, deptime1, deptime2, pax, time1 = 0;
	double money = 0.0;
	string date1;
	string ticketDetails[3];

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

	Order newOrder;
	newOrder.trainno = trainno;
	newOrder.deptime = deptime,deptime1,deptime2;
	newOrder.date = date1;
	newOrder.pax = pax;
	newOrder.money = money;

	orders[orderCount++] = newOrder;

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
	cout << "Price : RM " << money << " per person" << endl;

	ticketDetails[0] = to_string(trainno);
	ticketDetails[1] = to_string(pax);
	ticketDetails[2] = to_string(money);

	return newOrder;
}

double invoice(int start, int end)
{
	double total = 0.0, amount = 0.0, tax1 = 0.0, subtotal=0.0;
	int totalticket=0;

	for (int i = start;i < end;i++) {
		amount = orders[i].money * orders[i].pax;
		subtotal += amount;
		totalticket += orders[i].pax;
		tax1 = subtotal * tax;
		total = subtotal + process + tax1;

		cout << "Train No " << orders[i].trainno << "   x " << orders[i].pax << fixed << setprecision(2) << "   RM " << amount << endl;
	}
		cout << "---------------------------------------------------------\n";
		cout << left << setw(30) << "Subtotal : " << "RM " << subtotal << endl;
		cout << left << setw(30) << "Processing Fee : " << "RM " << fixed << setprecision(2) << process << endl;
		cout << left << setw(30) << "Tax : " << "RM " << fixed << setprecision(2) << tax1 << endl;
		cout << "---------------------------------------------------------\n";
		cout << left << setw(30) << "Total Ticket : " <<  totalticket << endl;
		cout << left << setw(30) << "Total : " << "RM " << fixed << setprecision(2) << total << endl;
	
	return total;
}



int main()
{
	int menu_choose;

	user();

	do {
		Menu();
		cin >> menu_choose;

		if (menu_choose == 1) {

			int start = orderCount;
			
			ticket();

			do {
				cout << "\nDo you need to add on?(Y/N) : ";
				cin >> choice;
				cout << endl;

				if (choice == 'y' || choice == 'Y') {
					ticket();
				}
				else if (choice == 'N' || choice == 'n') {
					break;
				}
				else {
					cout << "Invalid" << endl;
				}
			} while (choice != 'n' && choice != 'N');

			cout << "==================\n";
			cout << "INVOICE SUMMARY\n";
			cout << "==================\n";

			invoice(start,orderCount);

			int payment;
			string method;

			cout << "\nPlease select your payment menthod." << endl;
			cout << "1. E-wallet" << endl;
			cout << "2. Credit card" << endl;
			cout << "3. Debit card" << endl;
			cout << "\nPlease select : ";
			cin >> payment;
			if (payment == 1) {
				method = "E-wallet\n";
			}
			else if (payment == 2) {
				method = "Credit card\n";
			}
			else if (payment == 3) {
				method = "Debit card\n";
			}

			cout << endl;

			auto now = chrono::system_clock::now();
			time_t currentTime = chrono::system_clock::to_time_t(now);

			// Use localtime_s (safe version for MSVC)
			struct tm localTime;
			localtime_s(&localTime, &currentTime);

			int receipt;
			srand(time(0));
			receipt = rand()%9999 + 1000;

			cout << "===============================\n";
			cout << setw(10) << "RECEIPT" << endl;
			cout << "===============================\n";
			cout << "Receipt No : " << receipt << endl;
			cout << "Date : " << localTime.tm_mday << "/"
				<< (1 + localTime.tm_mon) << "/" << (1900 + localTime.tm_year) << " " << localTime.tm_hour << ":" << localTime.tm_min << endl;

			cout << endl;
			double total = invoice(start, orderCount);
			cout << "------------------------------------------------------------------------------------\n";
			cout << "Payment menthod : " << method << endl;
			cout << "Payment amount : RM " << fixed << setprecision(2) << total << endl;
			cout << "------------------------------------------------------------------------------------\n";
			cout << "Thank you. The QR code will be sent to your email after you complete the transaction.";
			cout << "If you do not receive the email, please contact our customer service +60123456789 or email to abc123@gmail.com\n";








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