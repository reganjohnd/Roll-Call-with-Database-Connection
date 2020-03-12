#pragma once
#pragma once

class student
{
public:
	static void export_data();
	static int count_att();
	static void is_present();
	static void output_attendance(int x);
	static int count();
	static void set_date();
	static void invalid(int vector_start, int iterator);

	static void add_student();

	static void delete_student();

	static void view_students();
};
