#include <iostream>
#include <string>

using namespace std;

struct user {                        //template
	string usernames;
	string passwords;
};

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
	string username;
};