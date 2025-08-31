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

const int MAX_USERS = 100;
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;

string loggedInUser = "";

char choice;

int dtime[] = { 10, 11, 12, 13, 14, 15, 16 };
double fare[] = { 50.00,56.00,96.00 };

struct Order {
	int trainno;
	int time;
	int deptime;
	int deptime1;
	int deptime2;
	string date;
	int pax;
	double money;
	double total;
	string origin;
	string destination;
};

Order orders[100];   // store up to 100 orders
int orderCount = 0;


void displayMenu() {
	if (loggedInUser.empty()) {
		cout << "Status: Not Logged In\n";
	}
	else {
		cout << "Status: Logged in as " << loggedInUser << "\n";
	}
	cout << "1. Register\n";
	cout << "2. Login\n";
	cout << "3. Logout\n";
	cout << "4. Forgot Password\n";
	cout << "5. Exit\n";
	cout << "-----------------------------------\n";
}


void registerUser() {
	cout << "\n--- User Registration ---\n";

	if (userCount >= MAX_USERS) {
		cout << "Cannot register new user. System is full.\n";
		return;
	}

	string username, password;
	cout << "Enter a new username(without space): ";
	cin >> username;
	 cout << "Enter a new password: ";
	cin >> password;

	usernames[userCount] = username;
	passwords[userCount] = password;
	userCount++;

	cout << "Registration successful!\n";

	cout << "\nPress ENTER to continue.";
	cin.ignore();
	cin.get();
}

void loginUser() {
	cout << "\n--- User Login ---\n";

	if (!loggedInUser.empty()) {
		cout << "You are already logged in as " << loggedInUser << ". Please log out first.\n";
		return;
	}

	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	bool found = false;
	for (int i = 0; i < userCount; ++i) {
		if (usernames[i] == username && passwords[i] == password) {
			loggedInUser = username;
			found = true;
			break;
		}
	}

	if (found) {
		cout << "Login successful. Welcome, " << loggedInUser << "!\n";
	}
	else {
		cout << "Invalid username or password. Please try again.\n";
	}
}

void clearScreen() {
	// Check if the system is Windows
#ifdef _WIN32
	system("cls");
	// Otherwise, assume it's a POSIX-compliant system (like Linux or macOS)
#else
	system("clear");
#endif
}

void logoutUser() {
	cout << "\n--- User Logout ---\n";

	if (loggedInUser.empty()) {
		cout << "No user is currently logged in.\n";
	}
	else {
		cout << "User " << loggedInUser << " has been logged out successfully.\n";
		loggedInUser = "";
	}
}

void resetPassword() {
	cout << "\n--- Password Reset ---\n";

	string username;
	cout << "Enter your username to reset the password: ";
	cin >> username;

	int userIndex = -1;
	for (int i = 0; i < userCount; ++i) {
		if (usernames[i] == username) {
			userIndex = i;
			break;
		}
	}

	if (userIndex != -1) {
		string newPassword;
		cout << "Enter your new password: ";
		cin >> newPassword;
		passwords[userIndex] = newPassword;
		cout << "Password for user '" << username << "' has been reset successfully.\n";
	}
	else {
		cout << "Username not found. Cannot reset password.\n";
	}
}

void Menu() {

	cout << "\nWelcome to TWD Train Ticket Booking System!\n";
	cout << "1. BUY TICKET \n";
	cout << "2. ORDER HISTORY \n";
	cout << "3. EXIT OR BACK TO LOGIN SCREEN \n";
	cout << endl;
	cout << "Please choose. (1-3): \n";
}


Order ticket()
{
	char dash1, dash2, tf;
	int trainno, deptime, deptime1, deptime2, pax, time1 = 0, day, month, year;
	double money = 0.0;
	string date1,origin,destination;
	string ticketDetails[3];

	int days_inMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

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
	if (trainno < 1 || trainno > 3) {
		cout << "Invalid train number.\n";
		return Order{};
	}

	cout << endl;

	switch (trainno) {
	case 1:
		origin = "Kuala Lumpur";
		destination = "Butterworth";
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
		origin = "Kajang";
		destination = "JB Sentral";
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
		origin = "KL Sentral";
		destination = "Ipoh";
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

	do
	{
		try {
			tf = 0;
			cout << "Departure date (dd/mm/yyyy) : ";
			cin >> day >> dash1 >> month >> dash2 >> year;
			if (month < 1 || month >12) {
				cout << "Invalid Input\n";
				tf = 1;
			}
			else if (day <1 || day > days_inMonth[month]) {
				cout << "Invalid Input\n";
				tf = 1;
			}
			else if (year < 2025) {
				cout << "Invalid Input\n";
				tf = 1;
			}
		}
		catch(...){
			cout << "Invalid Input\n";
		}
	} while (tf != 0);

	date1 = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

	cout << "Number of pax : ";
	cin >> pax;

	Order newOrder;
	newOrder.trainno = trainno;
	newOrder.date = date1;
	newOrder.pax = pax;
	newOrder.money = money;
	newOrder.time = time1;
	newOrder.origin = origin;
	newOrder.destination = destination;

	orders[orderCount++] = newOrder;

	cout << "\nTICKET CONFIRMATION" << endl;
	cout << "--------------------" << endl;
	cout << "Train No : " << trainno << endl;
	cout << "Departure Time : " << time1 << ":00";
	if (time1 >= 12) {
		cout << " PM\n";
	}
	else {
		cout << " AM\n";
	}
	cout << "Departure Date : " << date1 << endl;
	cout << "Number of pax : " << pax << endl;
	cout << "Price : RM " << money << " per person" << endl;

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

		cout << "Train No " << orders[i].trainno << setw(15) << right << "   x " << orders[i].pax << fixed << setprecision(2) << setw(7) << "   RM " << amount << endl;
	}

	tax1 = subtotal * tax;
	total = subtotal + process + tax1;

		cout << "---------------------------------------------------------\n";
		cout << left << setw(30) << "Subtotal : " << "RM " << subtotal << endl;
		cout << left << setw(30) << "Processing Fee : " << "RM " << fixed << setprecision(2) << process << endl;
		cout << left << setw(30) << "Tax : " << "RM " << fixed << setprecision(2) << tax1 << endl;
		cout << "---------------------------------------------------------\n";
		cout << left << setw(30) << "Total Tickets : " <<  totalticket << endl;
		cout << left << setw(30) << "Total payable amount : " << "RM " << fixed << setprecision(2) << total << endl;
	
	return total;
}


void orderhistory()
{
	if (orderCount == 0) {
		cout << "\nNo previous orders found.\n";
		return;
	}
	cout << "=================\n";
	cout << "  ORDER HISTORY\n";
	cout << "=================\n";
	for (int i = 0;i < orderCount;i++) {
		double subtotal = orders[i].money * orders[i].pax;
		double tax1 = subtotal * tax;
		double total = subtotal + process + tax1;

		cout << "Order #" << (i + 1) << endl;
		cout << "Train No : " << orders[i].trainno << "  " << orders[i].origin << " --> " << orders[i].destination << endl;
		cout << "Departure Date : " << orders[i].date << endl;
		cout << "Departure Time : " << orders[i].time << ":00";
		if (orders[i].time >= 12) {
			cout << " PM\n";
		}
		else {
			cout << " AM\n";
		}
		cout << "Number of pax : " << orders[i].pax << endl;
		cout << "Price per ticket : RM " <<fixed <<setprecision(2)<< orders[i].money << endl;
		cout << "Total payable amount : RM" << total << endl;
		cout << "---------------------------------\n";
	}
}



int main()
{
	int menu_choose = 0;
	int choice1;

	cout << "    __________   ========  |      __      |   =====       \n";
	cout << "   / |        |     ||     |     |  |     |  |      \\      \n";
	cout << "  /--         |     ||     |    |    |    |  |       |   \n";
	cout << "  |           |     ||     |   |      |   |  |       |   \n";
	cout << "   -----------      ||     |__|        |__|  |______/    \n";
	cout << "    000   000                                          \n";

	cout << "\nWelcome to TWD Train Ticket Booking System!\n\n";


	do {
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice1;

		switch (choice1) {
		case 1:
		case 2:
			if (choice1 == 1) {
				registerUser();
			}
			else if (choice1 == 2) {
				loginUser();
			}

			do {
				clearScreen();
				Menu();
				cin >> menu_choose;

				if (menu_choose == 1)
				{
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

					invoice(start, orderCount);

					int payment;
					string method;
					do {
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
						else {
							method = "Invalid input! Please try again.\n";
						}
					} while (payment <= 0 || payment > 3);
					cout << endl;

					auto now = chrono::system_clock::now();
					time_t currentTime = chrono::system_clock::to_time_t(now);

					// Use localtime_s (safe version for MSVC)
					struct tm localTime;
					localtime_s(&localTime, &currentTime);

					int receipt;
					srand(time(0));
					receipt = rand() % 9999 + 1000;

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
					cout << "THANK YOU.\n";

					cout << "\nPress ENTER to continue.";
					cin.ignore();
					cin.get();

					menu_choose = 0;
				}
				else if (menu_choose == 2) {
					orderhistory();
					cout << "Press ENTER to back to Main Menu.";
					cin.ignore();
					cin.get();

					menu_choose == 0;
				}
				else if (menu_choose == 3) {
					cout << "1. EXIT\n";
					cout << "2. GO BACK TO LOGIN SCREEN\n";
					cout << "Enter your choice : ";
					cin >> choice1;
					if (choice1 == 1) {
						cout << "\nTHANK YOU! Have a nice day.\n";
						return 0;
					}
					else if (choice1 == 2) {
						break;
					}
				}
				else {
					cout << "Invalid Input! Going back to main menu.\n";
				}

			} while (menu_choose == 0);
			break;
		case 3:
			logoutUser();
			break;
		case 4:
			resetPassword();
			break;
		case 5:
			cout << "\nThank you for using TWD Train Ticket System. Goodbye!\n";
			break;
		default:
			cout << "\nInvalid choice. Please try again.\n";
		}
	} while (choice1 != 5);


	return 0;
}