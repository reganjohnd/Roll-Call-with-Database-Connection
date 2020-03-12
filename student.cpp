#include "student.h"

#include <mysql.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector <string> name, att;
string date;
string present;
int c{}, c_att{};

int student::count()
{
	system("CLS");

	int qstate;
	int count{};
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	string name;
	//string query = "SELECT * FROM student";
	const char* q = "SELECT * FROM student";
	qstate = mysql_query(conn, q);

	res = mysql_store_result(conn);
	
	while (row = mysql_fetch_row(res))
	{
		count++;
	}
	return count;
}

int student::count_att()
{
	system("CLS");
	c_att = 0;
	int qstate;
	int count{};
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	string name;
	//string query = "SELECT * FROM student";
	const char* q = "SELECT * FROM attendance";
	qstate = mysql_query(conn, q);

	res = mysql_store_result(conn);

	while (row = mysql_fetch_row(res))
	{
		c_att++;
	}
	return c_att;
}

void student::set_date()
{
	cin.ignore();
	system("CLS");
	cout << "Date: ";
	getline(cin, date);
	cout << endl;
}

void student::is_present()
{

	system("CLS");

	int qstate;
	MYSQL* conn;
	MYSQL_ROW row{};
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	for (int i = 0; i < student::count(); i++)
	{
		string query = "SELECT * FROM student";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);

		res = mysql_store_result(conn);

		string id, name;
		cout << "ID\t\t\t\t" << "NAME" << endl;
		while (row = mysql_fetch_row(res))
		{
			cout << row[0, 1] << endl; //"\t\t\t\t" << row[1,2] << endl;
		}
		mysql_free_result(res);
		system("pause");
	}
}

void student::output_attendance(int x)
{
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	const char* q = "SELECT * FROM student";
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);

	

	while (row = mysql_fetch_row(res))
	{
		name.push_back(row[1]);
	}
	//mysql_free_result(res);

	cout << "Date: ";
	cin.ignore();
	getline(cin, date);

	for (int i = 0; i < student::count(); i++)
	{
		cout << name[i] << ": ";
		cin>> present;
		if (present == "A" || present == "a" || present == "H" || present == "h")
		{
			string query = "INSERT INTO rollcall.attendance (date, name, attendance) VALUES ('" + date + "', '" + name[i] + "', '" + present + "')";
			q = query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			c += 1;
		}
		else if (present != "A" || present != "a" || present != "H" || present != "h")
		{
			cout << "Please enter a valid input!" << endl << endl;
			mysql_free_result(res);
			invalid(c, count());
			return;
		}
	}
}

void student::invalid(int vector_start, int iterator)
{
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row{};
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	const char* q = "SELECT * FROM student";
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res))
	{
		name.push_back(row[1]);
	}
	
	
	for (static int i = vector_start; i < iterator; i++)
	{
		cout << name[i] << ": ";
		getline(cin, present);
		if (present == "A" || present == "a" || present == "H" || present == "h")
		{
			string query = "INSERT INTO rollcall.attendance (date, name, attendance) VALUES ('" + date + "', '" + name[i] + "', '" + present + "')";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			c = c + 1;
		}
		else if (present != "A" || present != "a" || present != "H" || present != "h")
		{
			cout << "Please enter a valid input!" << endl << endl;
			invalid(c, count());
		}
	}
}

void student::add_student()
{
	system("CLS");
	int qstate;
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	string id, name;
	cout << "ID: ";
	cin.ignore();
	getline(cin,id);
	cout << "Name: ";
	getline(cin, name);

	string query = "INSERT INTO rollcall.student(id, FullName) VALUES (" + id + ", '" + name + "')";

	const char* q = query.c_str();
	cout << "Query is: " << q << endl;
	qstate = mysql_query(conn, q);

	if (qstate)
	{
		cout << "Success!" << endl;
		system("pause");
	}
	else if(!qstate)
	{
		cout << "Failure!" << endl;
		system("pause");
	}
}

void student::delete_student()
{
	system("CLS");

	int qstate;
	MYSQL* conn;
	MYSQL_ROW row{};
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	string id;
	cout << "ID: ";
	cin.ignore();
	getline(cin, id);

	string query = "DELETE FROM student WHERE id = " + id + "";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	mysql_free_result(res);
}

void student::view_students()
{
	system("CLS");

	int qstate;
	MYSQL* conn;
	MYSQL_ROW row{};
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);
	
	const char* q = "SELECT * FROM student";
	qstate = mysql_query(conn, q);

		res = mysql_store_result(conn);

		vector<string> id, name;
		cout << "ID\t\t\t\t" << "NAME" << endl;
		while(row = mysql_fetch_row(res))
		{
			cout << row[0] << "\t\t\t\t" << row[1] << endl;
		}

		cout << endl; system("pause");
		mysql_free_result(res);
}

void student::export_data()
{
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row{};
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "rollcall", 3306, NULL, 0);

	string query = "SELECT * FROM attendance";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);

	res = mysql_store_result(conn);

	vector<string> date, name, att;

	while (row = mysql_fetch_row(res))
	{
		date.push_back(row[0]);
		name.push_back(row[1]);
		att.push_back(row[2]);
	}

	ofstream output;
	output.open("C:/Dev/attendance.txt", ios::trunc);

	for (int i = 0; i < student::count_att(); i++)
	{
		// cout << date.size() << name.size() << att.size() << student::count_att();
		output << date[i] << "," << name[i] << "," << att[i] << endl;
	}
	output.close();
}