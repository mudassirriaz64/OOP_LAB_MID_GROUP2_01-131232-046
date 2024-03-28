#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

const string BOOKING_FILE = "bookings";

class bookings
{
public:
	string member_name;
	string date;
	string time;
	string serial_num;

	void bookings_system(string name, string date, string time, string serial_num)
	{
		member_name = name;
		this->date = date;
		this->time = time;
		this->serial_num = serial_num;
	}

	void display() const
	{
		cout << "Serial Number : " << serial_num << endl;
		cout << "Customer Name : " << member_name << endl;
		cout << "Booking Date : " << date << endl;
		cout << "Booking Time : " << time << endl;
	}
	string get_time() const
	{
		return time;
	}

};

vector<bookings>bookings_list;

class fitness_club
{
	string name;
public:
	fitness_club(string name)
	{
		this->name = name;
	}

	void add_bookings(const bookings& booking)
	{
		if (istimeslotavailable(booking.get_time()))
		{
			bookings_list.push_back(booking);
			cout << "Your Booking has been done\n";
		}
		else
		{
			cout << "Sorry, that time slot is already booked\n";
		}

	}
	bool istimeslotavailable(const string& time) const
	{
		for (auto& bookings : bookings_list)
		{
			if (bookings.get_time() == time)
				return false;
		}
		return true;
	}
	void view_bookings() const
	{
		cout << "All Bookings are : \n";
		for (auto& bookings : bookings_list)
		{
			bookings.display();
		}
	}

};

void savedata(vector<bookings>& booking_list);
void loaddata(vector<bookings>& booking_list);

int main()
{
	loaddata(bookings_list);
	int choice;
	string name, date, time;
	fitness_club fc1("MR Fitness Club");
main_menu:
	system("cls");
	cout << "\t\t MR Fitness Club\n\n";
	cout << "1. Book yourself\n";
	cout << "2. View all Bookings\n";
	cout << "3. Exit\n\n";
	cout << "Select your Option : ";
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case 1:
	{
		system("cls");
		cout << "Enter your Name : ";
		getline(cin, name);
		cout << "Enter Date : ";
		getline(cin, date);
		cout << "Enter Time Slot : ";
		getline(cin, time);
		string serial_num = "0";
		serial_num = serial_num + "1";
		bookings booking1;
		booking1.bookings_system(name, date, time, serial_num);
		fc1.add_bookings(booking1);
		savedata(bookings_list);
		system("pause");
		goto main_menu;
	}
	case 2:
	{
		system("cls");
		fc1.view_bookings();
		system("pause");
		goto main_menu;
	}
	case 3:
	{
		exit(0);
	}
	}
}

void savedata(vector<bookings>& booking_list)
{
	ofstream bookings_file(BOOKING_FILE);
	if (bookings_file.is_open())
	{
		for (const auto& bookings : booking_list)
		{
			bookings_file << bookings.member_name << endl;
			bookings_file << bookings.time << endl;
			bookings_file << bookings.date << endl;
			bookings_file << bookings.serial_num << endl;
		}
	}
	bookings_file.close();
}

void loaddata(vector<bookings>& booking_list)
{
	ifstream bookings_file(BOOKING_FILE);
	if (bookings_file.is_open())
	{
		string name;
		string date;
		string time;
		string serial_num;
		while (getline(bookings_file, name) && getline(bookings_file, date) && getline(bookings_file, time) && getline(bookings_file, serial_num))
		{
			bookings b1;
			b1.member_name = name;
			b1.date = date;
			b1.time = time;
			b1.serial_num = serial_num;
			booking_list.push_back(b1);
		}
	}
	bookings_file.close();
}
