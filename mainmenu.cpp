#include "mainmenu.h"
#include "student.h"
#include <iostream>
#include <string>

using namespace std;

void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

void mainmenu::MainMenu()
{
	while (1)
	{
		system("CLS");
		int menuselect;
		gotoxy(60, 8);
		cout << "****************************************";
		gotoxy(60, 20);
		cout << "****************************************";
		gotoxy(75, 10);
		cout << "MAIN MENU";
		gotoxy(71, 11);
		cout << "-----------------";
		gotoxy(71, 14);
		cout << "1 -> Add student";
		gotoxy(71, 15);
		cout << "2 -> Take Attendance";
		gotoxy(71, 16);
		cout << "3 -> Delete Student";
		gotoxy(71, 17);
		cout << "4 -> View Students";
		gotoxy(71, 18);
		cout << "5 -> Export Data";

		cin >> menuselect;
		switch (menuselect)
		{
		case 1:
			student::add_student();
			break;

		case 2:
			//student::set_date();
			//student::is_present();
			student::output_attendance(0);
			break;

		case 3:
			student::delete_student();
			break;

		case 4:
			student::view_students();
			break;

		case 5:
			student::export_data(); 
			break;
		}
	}
}