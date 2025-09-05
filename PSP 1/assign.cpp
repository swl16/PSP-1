#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Structs.hpp"
using namespace std;

const double process = 0.50;
const double tax = 0.06;
const int MAX_ORDERS = 100;
const int MAX_USERS = 100;
int userCount = 0; 

string loggedInUser = "";

char choice;

int dtime[] = { 10, 11, 12, 13, 14, 15, 16 }; //departure time
double fare[] = { 50.00,56.00,96.00 };

int orderCount = 0;

void saveusers(user* users) {    // save users data to file
	const string filename = "users.txt";
	ofstream out(filename);

	if (!out) {
		cout << "Error opening file for saving users!" << endl;
		return;
	}
	for (int i = 0;i < userCount;i++)
	{
		out << users[i].usernames << "," << users[i].passwords << endl;
	}
	out.close();
}

void usersfromfile(user*users){          // reads users data from file
	const string filename = "users.txt";
	ifstream in(filename);
	user userinfor = user();

	if (!in) {
		return;
	}
	userCount = 0;
	string line;
	while (getline(in, line) && userCount < MAX_USERS) {
		stringstream ss(line);

		getline(ss, userinfor.usernames, ',');
		getline(ss, userinfor.passwords, ',');

		users[userCount] = userinfor;
		userCount++;
	}
	in.close();
}

void saveorders(Order*orders)  // save orders that ordered by the user to file
{
	const string filename = "orders.txt";
	ofstream out(filename);

	if (!out) {
		cout << "Error opening file for saving orders!" << endl;
		return;
	}
	for (int i = 0;i < orderCount;i++)
	{
		out << orders[i].trainno << "," << orders[i].origin << "," << orders[i].destination << ","
			<< orders[i].date << "," << orders[i].time << "," << orders[i].pax << "," << orders[i].money << "," << orders[i].username << endl;
	}
	out.close();
}

void ordersfromfile(Order*orders)  // reads user's orders from file
{
	const string filename = "orders.txt";
	ifstream in(filename);
	Order ordering = Order();
	if (!in) {
		cout << "Error opening orders.txt";
		return;
	}
	orderCount = 0;
	string line;
	string trainnostr, paxstr, moneystr, timestr;
	while (getline(in, line) && orderCount < MAX_ORDERS)
	{
		stringstream ss(line);
		getline(ss, trainnostr, ',');   // convert later
		getline(ss,ordering.origin,',');
		getline(ss,ordering.destination,',');
		getline(ss,ordering.date,',');
		getline(ss,timestr,',');   // time as string, convert later
		getline(ss,paxstr,',');    // pax, as string, convert later
		getline(ss,moneystr,',');  //money as string, convert later
		getline(ss,ordering.username,',');

		try {
			ordering.trainno = stoi(trainnostr); // string to int
			ordering.time = stoi(timestr);
			ordering.pax = stoi(paxstr);
			ordering.money = stod(moneystr);  //string to double
		}
		catch (...) {
			cout << "Error: Invalid data format in line " << orderCount + 1 << endl;
			continue; // Skip this line
		}
		orders[orderCount] = ordering;
		orderCount++;
	}
	in.close();
}

void displayMenu() {     // menu navigation for user to register/login
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


void registerUser(user*users) {   // user registration 

		cout << "\n--- User Registration ---\n";
		user registeringUser = user();

		string username, password;

		while (true) {
			cout << "Enter a new username (without space): ";
			cin >> username;

			bool usernameExists = false;
			for (int i = 0; i < userCount; i++) {
				if (users[i].usernames == username) {
					cout << "Username already exists. Please try again.\n";
					usernameExists = true;
					break;
				}
			}

			if (!usernameExists) {
				break; // Valid username found
			}
			cout << "\nPress ENTER to continue.";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Proper buffer clearing
			cin.get();
		}
		cout << "Enter a new password: ";
		cin >> password;
		
		registeringUser.usernames = username;
		registeringUser.passwords = password;
		users[userCount] = registeringUser;
		userCount++;

		cout << "Registration successful!\n";

}

int loginUser(user*users) {    // user login
	cout << "\n--- User Login ---\n";

	if (!loggedInUser.empty()) {
		cout << "You are already logged in as " << loggedInUser << ". Please log out first.\n";
		return 1;
	}

	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	bool found = false;
	for (int i = 0; i < userCount; ++i) {
		if (users[i].usernames == username && users[i].passwords == password) {
			loggedInUser = username;
			found = true;
			break;
		}
	}

	if (found) {
		cout << "Login successful. Welcome, " << loggedInUser << "!\n";
		return 1;
	}
	else {
		cout << "Invalid username or password. Please try again.\n\n";
		return 0;
	}
	return 0;
}

void clearScreen() {
#ifdef _WIN32 // Check if the system is Windows
	system("cls");	
#else // Otherwise, assume it's a POSIX-compliant system (like Linux or macOS)
	system("clear");
#endif
}

void logoutUser() {    //user logout
	cout << "\n--- User Logout ---\n";

	if (loggedInUser.empty()) {
		cout << "No user is currently logged in.\n";
	}
	else {
		cout << "User " << loggedInUser << " has been logged out successfully.\n";
		loggedInUser = "";
	}
}

void resetPassword(user*users) {   // user reset password
	cout << "\n--- Password Reset ---\n";

	string username;
	cout << "Enter your username to reset the password: ";
	cin >> username;

	int userIndex = -1;
	for (int i = 0; i < userCount; ++i) {
		if (users[i].usernames == username) {
			userIndex = i;
			break;
		}
	}

	if (userIndex != -1) {
		string newPassword;
		cout << "Enter your new password: ";
		cin >> newPassword;
		users[userIndex].passwords = newPassword;
		cout << "Password for user '" << username << "' has been reset successfully.\n";
	}
	else {
		cout << "Username not found. Cannot reset password.\n";
	}
}

void Menu() {     //menu navigation for user to buy train ticket/view order history

	cout << "\nWelcome to TWD Train Ticket Booking System!\n";
	cout << "1. BUY TICKET \n";
	cout << "2. ORDER HISTORY \n";
	cout << "3. EXIT OR BACK TO LOGIN SCREEN \n";
	cout << endl;
	cout << "Please choose. (1-3): \n";
}


Order ticket(Order*orders)   //function for ordering ticket 
{
	char dash1, dash2, tf; // tf=truefalse, dash is to store the '/' that input by user
	int trainno, deptime, deptime1, deptime2, pax ;
	int time1=0,day, month, year;
	double money = 0.0, price = 0.0;
	string date1,origin,destination;

	time_t timenow = time(0);
	struct tm now;
	localtime_s(&now, &timenow);

	int todayDay = now.tm_mday;
	int todayMonth = now.tm_mon + 1; // because it start at 0
	int todayYear = now.tm_year + 1900; // because it start at 1900
	int days_inMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; // put 0 at the 1st value to let the day store in correct month

	cout << "AVAILABLE TRAIN:\n\n";
	cout << left << setw(10) << "=========================================" << endl;
	cout << left << setw(10) << "| Train No | ORIGIN       | DESTINATION |" << endl;
	cout << left << setw(10) << "-----------------------------------------" << endl;
	cout << left << setw(10) << "| 001      | Kuala Lumpur | Butterworth |" << endl;
	cout << left << setw(10) << "| 002      | Kajang       | JB Sentral  |" << endl;
	cout << left << setw(10) << "| 003      | KL Sentral   | Ipoh        |" << endl;
	cout << left << setw(10) << "=========================================" << endl;
	do {
		cout << "\nPlease choose your train number : ";
		cin >> trainno;
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore();  //only ignores 1 character
		}
		if (trainno <1 || trainno > 3) {
			cout << "Invalid train number. Please try again. \n";
		}
	} while (trainno <= 0 || trainno > 3);
	cout << endl;

	switch (trainno) {
	case 1:
		do {
			tf = 0;
			cout << "Departure date (dd/mm/yyyy) : ";
			if (!(cin >> day >> dash1 >> month >> dash2 >> year)) {
				cout << "Invalid date.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				tf = 1;
				continue;
			}
			if (month < 1 || month > 12) tf = 1;
			if (year == 2028)
				days_inMonth[2] = 29; // In 2028, february has 29 days
			else {
				int maxDay = days_inMonth[month];
				if (day < 1 || day > maxDay || year > 2029) tf = 1;
			}
			if (tf)cout << "Invalid date\n";

			else if  (year < todayYear ||(year == todayYear && month < todayMonth) ||(year == todayYear && month == todayMonth && day < todayDay)) {
				cout << "The date can't be in the past.\n";
				tf = 1;
			}
		} while (tf != 0);

		cout << endl;

		origin = "Kuala Lumpur";
		destination = "Butterworth";
		cout << left << setw(5) << "==================================" << endl;
		cout << left << setw(5) << "| NO | DEPARTURE TIME | MIN.FARE |" << endl;
		cout << left << setw(5) << "----------------------------------" << endl;
		cout << left << setw(5) << "| 1  | 10:00AM        | RM 96.00 |" << endl;
		cout << left << setw(5) << "| 2  | 12:00PM        | RM 96.00 |" << endl;
		cout << left << setw(5) << "| 3  | 15:00PM        | RM 96.00 |" << endl;
		cout << left << setw(5) << "==================================" << endl;
		do {
			cout << "\nPlease choose your departure time : ";
			cin >> deptime;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
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
			else {
				cout << "Invalid time. Please try again.\n";
			}
		} while (deptime < 1 || deptime>3);
		break;
	case 2:
		do {
			tf = 0;
			cout << "Departure date (dd/mm/yyyy) : ";
			if (!(cin >> day >> dash1 >> month >> dash2 >> year)) {
				cout << "Invalid date.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				tf = 1;
				continue;
			}
			if (month < 1 || month > 12) tf = 1;
			if (year == 2028)
				days_inMonth[2] = 29;
			else {
				int maxDay = days_inMonth[month];
				if (day < 1 || day > maxDay || year > 2029) tf = 1;
			}
			if (tf)cout << "Invalid date\n";

			else if (year < todayYear || (year == todayYear && month < todayMonth) || (year == todayYear && month == todayMonth && day < todayDay)) {
				cout << "The date can't be at the past.\n";
				tf = 1;
			}
		} while (tf != 0);

		cout << endl;

		origin = "Kajang";
		destination = "JB Sentral";
		cout << left << setw(5) << "==================================" << endl;
		cout << left << setw(5) << "| NO | DEPARTURE TIME | MIN.FARE |" << endl;
		cout << left << setw(5) << "----------------------------------" << endl;
		cout << left << setw(5) << "| 1  | 10:00AM        | RM 50.00 |" << endl;
		cout << left << setw(5) << "| 2  | 13:00PM        | RM 50.00 |" << endl;
		cout << left << setw(5) << "| 3  | 16:00PM        | RM 50.00 |" << endl;
		cout << left << setw(5) << "==================================" << endl;
		do {
			cout << "\nPlease choose your departure time : ";
			cin >> deptime1;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
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
			else {
				cout << "Invalid time. Please try again.\n";
			}
		} while (deptime1 < 1 || deptime1>3);
		break;
	case 3:
		do {
			tf = 0;
			cout << "Departure date (dd/mm/yyyy) : ";
			if (!(cin >> day >> dash1 >> month >> dash2 >> year)) {
				cout << "Invalid date.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				tf = 1;
				continue;
			}
			if (month < 1 || month > 12) tf = 1;
			if (year == 2028)
				days_inMonth[2] = 29;
			else {
				int maxDay = days_inMonth[month];
				if (day < 1 || day > maxDay || year > 2029) tf = 1;
			}
			if (tf)cout << "Invalid date\n";

			else if (year < todayYear || (year == todayYear && month < todayMonth) || (year == todayYear && month == todayMonth && day < todayDay)) {
				cout << "The date can't be at the past.\n";
				tf = 1;
			}
		} while (tf != 0);

		cout << endl;

		origin = "KL Sentral";
		destination = "Ipoh";
		cout << left << setw(5) << "==================================" << endl;
		cout << left << setw(5) << "| NO | DEPARTURE TIME | MIN.FARE |" << endl;
		cout << left << setw(5) << "----------------------------------" << endl;
		cout << left << setw(5) << "| 1  | 11:00AM        | RM 56.00 |" << endl;
		cout << left << setw(5) << "| 2  | 14:00PM        | RM 56.00 |" << endl;
		cout << left << setw(5) << "| 3  | 16:00PM        | RM 56.00 |" << endl;
		cout << left << setw(5) << "==================================" << endl;
		do {
			cout << "\nPlease choose your departure time : ";
			cin >> deptime2;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
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
			else {
				cout << "Invalid time. Please try again.\n";
			}
		} while (deptime2 < 1 || deptime2>3);
		break;
	default:
		cout << "Invalid";
		break;
	}
	date1 = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	cout << endl;

	do {
		cout << "Number of pax : ";
		cin >> pax;
		if (pax > 30) {
			cout << "Maximum passenger is 30. Please try again.\n";
		}
	} while (pax > 30);

	Order newOrder;  
	newOrder.trainno = trainno;
	newOrder.date = date1;
	newOrder.pax = pax;
	newOrder.money = money;
	newOrder.time = time1;
	newOrder.origin = origin;
	newOrder.destination = destination;
	newOrder.username = loggedInUser;

	orders[orderCount++] = newOrder;

	cout << "\nTICKET CONFIRMATION" << endl;
	cout << "--------------------" << endl;
	cout << "Train No : " << trainno << endl;
	cout << "Departure Date : " << date1 << endl;
	cout << "Departure Time : " << time1 << ":00";
	if (time1 >= 12) {
		cout << " PM\n";
	}
	else {
		cout << " AM\n";
	}
	cout << "Number of pax : " << pax << endl;
	price = money * pax;
	cout << "Price : RM " << price << endl;

	return newOrder;
}

double invoice(int start, int end, Order*orders) // print invoice 
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


void orderhistory(Order*orders) // print order history
{
	int ordernum = 1;
	if (orderCount == 0) {
		cout << "\nNo previous orders found.\n";
		return;
	}
	cout << "=================\n";
	cout << "  ORDER HISTORY\n";
	cout << "=================\n";

	bool found = false;
	for (int i = 0;i < orderCount;i++) {
		// Only show orders belonging to the currently logged-in user
		if (orders[i].username == loggedInUser) {
			found = true;

			double subtotal = orders[i].money * orders[i].pax;
			double tax1 = subtotal * tax;
			double total = subtotal + process + tax1;
			cout << "Order #" << ordernum << endl;
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
			cout << "Price per ticket : RM " << fixed << setprecision(2) << orders[i].money << endl;
			cout << "Total payable amount : RM " << total << endl;
			cout << "---------------------------------\n";

			ordernum++;
		}
	}
	if (!found) {
		cout << "\nNo previous orders found for user: " << loggedInUser << endl;
	}
}



int main()
{
	char menu_choose = '0', choice1, choice2;
	user users[100];
	Order orders[100]; // store up to 100 orders

	cout << "    __________   ========  |      __      |   =====       \n";
	cout << "   / |        |     ||     |     |  |     |  |      \\      \n";
	cout << "  /--         |     ||     |    |    |    |  |       |   \n";
	cout << "  |           |     ||     |   |      |   |  |       |   \n";
	cout << "   -----------      ||     |__|        |__|  |______/    \n";
	cout << "    000   000                                          \n";

	cout << "\nWelcome to TWD Train Ticket Booking System!\n\n";

	usersfromfile(users);
	ordersfromfile(orders);

	do {
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice1;

		switch (choice1) {
		case '1':
			registerUser(users);
			saveusers(users);
		case '2':
			if (loginUser(users) == 1) {
				do {
					clearScreen();
					Menu();
					cin >> menu_choose;

					if (menu_choose == '1')
					{
						int start = orderCount;

						ticket(orders);
						saveorders(orders);

						do {
							cout << "\nDo you need to add on?(Y/N) : ";
							cin >> choice;
							cout << endl;

							if (choice == 'y' || choice == 'Y') {
								ticket(orders);
								saveorders(orders);
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

						invoice(start, orderCount, orders);

						int payment;
						string method;
						do {
							cout << "\nPlease select your payment menthod." << endl;
							cout << "1. E-wallet" << endl;
							cout << "2. Credit card" << endl;
							cout << "3. Debit card" << endl;
							cout << "\nPlease select : ";
							cin >> payment;
							if (cin.fail())
							{
								cin.clear();
								cin.ignore();
							}
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
								cout << "Invalid input! Please try again.\n";
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
						cout << "            RECEIPT" << endl;            //print receipt
						cout << "===============================\n";
						cout << "Receipt No : " << receipt << endl;
						cout << "Date : " << localTime.tm_mday << "/"
							<< (1 + localTime.tm_mon) << "/" << (1900 + localTime.tm_year) << " " << localTime.tm_hour << ":" << localTime.tm_min << endl;
						cout << endl;
						double total = invoice(start, orderCount, orders);
						cout << "---------------------------------------------------------\n";
						cout << "Payment menthod : " << method << endl;
						cout << "Payment amount : RM " << fixed << setprecision(2) << total << endl;
						cout << "---------------------------------------------------------\n";
						cout << "THANK YOU.\n";

						cout << "\nPress ENTER to continue.";
						cin.ignore();
						cin.get();

						menu_choose = '0';
					}
					else if (menu_choose == '2') {
						orderhistory(orders);

						cout << "Press ENTER to back to Main Menu.";
						cin.ignore();
						cin.get();

						menu_choose = '0';
					}
					else if (menu_choose == '3') {
						do {
							cout << "1. EXIT\n";
							cout << "2. GO BACK TO LOGIN SCREEN\n";
							cout << "Enter your choice : ";
							cin >> choice2;
							if (choice2 == '1') {
								cout << "\nTHANK YOU! Have a nice day.\n";
								return 0;
							}
							else if (choice2 == '2') {
								break;
							}
							else {
								cout << "Invalid input. Please try again.\n";
							}
						} while (choice2 != '1' && choice2 != '2');
					}
					else {
						cout << "Invalid Input! Going back to main menu.\n";
					}

				} while (menu_choose != '3');
				break;
			}
			else {
				break;
			}
		case '3':
			logoutUser();
			break;
		case '4':
			resetPassword(users);
			saveusers(users);
			break;
		case '5':
			cout << "\nThank you for using TWD Train Ticket System. Goodbye!\n";
			break;
		default:
			cout << "\nInvalid choice. Please try again.\n";
		}
	} while (choice1 != '5');

	return 0;
}