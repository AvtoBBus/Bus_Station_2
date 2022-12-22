#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <complex>
#include <string.h>
#include "Errors.h"
#include "Matrix.h"

using namespace std;

template <class T>
T check_input() {
	T number;
	while (!(cin >> number) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error" << endl;
	}
	return number;
}

int get_key() {
	int key = _getch();
	return key;
}

int check_and_input()
{
	char NUM[] = { '0','1','2','3','4','5','6','7','8','9' };
	int number = 0;
	while (number <= 0)
	{
		while (!(cin >> number) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "\nIncorrect value...\n";
		}
		if (number <= 0) cout << "\nOnly > 0\n";

	}

	return number;
}

template <class T>
Matrix<T> result_of_operation(Matrix<T> first_obj, Matrix<T> second_obj, const char* operation) {
	Matrix<T> help_obj;
	help_obj = first_obj;
	if (strcmp("add", operation) == 0) {
		if (first_obj.get_size_x() == second_obj.get_size_x() && first_obj.get_size_y() == second_obj.get_size_y()) {
			help_obj + second_obj;
			return help_obj;
		}
		else throw E_Different_Size();
	}
	else if (strcmp("sub", operation) == 0) {
		if (first_obj.get_size_x() == second_obj.get_size_x() && first_obj.get_size_y() == second_obj.get_size_y()) return help_obj - second_obj;
		else throw E_Different_Size();
	}
	else if (strcmp("mul", operation) == 0) {
		return help_obj * second_obj;
	}
	else if (strcmp("mul_scalar", operation) == 0) {
		T scalar = 0;
		int choose = 0;
		do {
			cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
			choose = check_and_input();
		} while (choose < 1 || choose > 2);
		cout << "Input scalar: ";
		scalar = check_and_input();
		if (choose == 2) help_obj = second_obj;
		return help_obj * scalar;
	}
	else if (strcmp("div_scalar", operation) == 0) {
		T scalar = 0;
		int choose = 0;
		do {
			cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
			choose = check_and_input();
		} while (choose < 1 || choose > 2);
		cout << "Input scalar: ";
		scalar = check_and_input();
		if (choose == 2) help_obj = second_obj;
		return help_obj / T(scalar);
	}
	else if (strcmp("inverted", operation) == 0) {
		int choose = 0;
		do {
			cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
			choose = check_and_input();
		} while (choose < 1 || choose > 2);
		if (choose == 2) help_obj = second_obj;
		help_obj.search_invers_matrix();
		//return help_obj.search_invers_matrix();
	}
	return help_obj;
}

template <class T>
void menu_interaction(Matrix<T> first_obj, Matrix<T> second_obj) {
	T input_value;
	int x_size_input = 0, y_size_input = 0, choose = 0;
	while (true) {
		system("cls");
		cout << "FIRST MATRIX:" << endl;
		cout << first_obj;
		cout << "SECOND MATRIX:" << endl;
		cout << second_obj;
		cout << endl;
		cout << "Press [Q] to perform the addition" << endl;
		cout << "Press [W] to perform the subtraction" << endl;
		cout << "Press [E] to perform the multiplication (1-st matrix * 2-d matrix)" << endl;
		cout << "Press [R] to perform the multiplication (matrix * scalar)" << endl;
		cout << "Press [A] to perform the division (matrix / scalar)" << endl;
		cout << "Press [S] to calculate the trace of the matrix" << endl;
		cout << "Press [D] to get a cell by index" << endl;
		cout << "Press [F] to change a cell by index" << endl;
		cout << "Press [Z] to calculate inverted matrix" << endl;
		cout << "Press [Esc] to go back" << endl;
		int key = get_key();
		switch (key) {
		case 113: //q
			system("cls");
			cout << "RESULT OF ADDITION:" << endl;
			try {
				cout << result_of_operation(first_obj, second_obj, "add");
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 119: //w
			system("cls");
			cout << "RESULT OF SUBSTRACTION:" << endl;
			try {
				cout << result_of_operation(first_obj, second_obj, "sub");
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 101: //e
			system("cls");
			cout << "RESULT OF MULTIPLICATION (matrix * matrix):" << endl;
			try {
				cout << result_of_operation(first_obj, second_obj, "mul");
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 114: //r
			system("cls");
			cout << "Result of MULTIPLICATION (matrix * scalar):" << endl << result_of_operation(first_obj, second_obj, "mul_scalar");
			break;
		case 97: //a
			try {
				system("cls");
				cout << "Result of DIVISION (matrix * scalar):" << endl << result_of_operation(first_obj, second_obj, "div_scalar");
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 115: //s
			system("cls");
			do {
				cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
				cin >> choose;
			} while (choose < 1 || choose > 2);
			if (choose == 1) cout << "Result of CALCULATE THE TRACE:" << first_obj.calculating_the_trace() << endl;
			if (choose == 2) cout << "Result of CALCULATE THE TRACE:" << second_obj.calculating_the_trace() << endl;
			break;
		case 100: //d
			try {
				system("cls");
				do {
					cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
					cin >> choose;
				} while (choose < 1 || choose > 2);
				cout << "Input X:";
				cin >> x_size_input;
				cout << "Input Y:";
				cin >> y_size_input;
				if (choose == 1) cout << "Value in cell [" << x_size_input + 1 << "][" << y_size_input + 1 << "] = " << first_obj(x_size_input - 1, y_size_input - 1) << endl;
				if (choose == 2) cout << "Value in cell [" << x_size_input + 1 << "][" << y_size_input + 1 << "] = " << second_obj(x_size_input - 1, y_size_input - 1) << endl;
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 102: //f
			try {
				system("cls");
				do {
					cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
					cin >> choose;
				} while (choose < 1 || choose > 2);
				cout << "Input X:";
				cin >> x_size_input;
				cout << "Input Y:";
				cin >> y_size_input;
				cout << "Input new value in cell: ";
				input_value = check_input<T>();
				if (choose == 1) cout << endl << "Value in cell [" << x_size_input << "][" << y_size_input << "] was switch on " << input_value << endl << first_obj(x_size_input - 1, y_size_input - 1, input_value) << endl;
				if (choose == 2) cout << endl << "Value in cell [" << x_size_input << "][" << y_size_input << "] was switch on " << input_value << endl << second_obj(x_size_input - 1, y_size_input - 1, input_value) << endl;
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 122: //z
			try {
				system("cls");
				cout << endl << result_of_operation(first_obj, second_obj, "inverted");
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 27: //esc
			return;
		}
		system("pause");

	}
}

template <class T>
int second_menu() {
	int x_size_input, y_size_input, choose;
	T input_value = 0;
	system("cls");
	cout << "INPUT INFO ABOUT 1-ST MATRIX:" << endl;
	cout << "Number of colums: ";
	y_size_input = check_and_input();
	cout << "Number of lines: ";
	x_size_input = check_and_input();

	cout << endl << "INPUT VALUE, WHICH FILL 1-ST MATRIX" << endl;
	cin >> input_value;

	Matrix<T> first_obj(x_size_input, y_size_input, input_value);

	cout << endl << "INPUT INFO ABOUT 2-D MATRIX:" << endl;
	do {
		cout << "Number of colums: ";
		cin >> y_size_input;
	} while (y_size_input <= 0);
	do {
		cout << "Number of lines: ";
		cin >> x_size_input;
	} while (y_size_input <= 0);

	cout << endl << "INPUT VALUE, WHICH FILL 2-D MATRIX" << endl;
	cin >> input_value;

	Matrix<T> second_obj(x_size_input, y_size_input, input_value);
	menu_interaction(first_obj, second_obj);
	return 0;
}

int main() {
	do {
		system("cls");
		cout << "Press [Q] to work with int" << endl;
		cout << "Press [W] to work with float" << endl;
		cout << "Press [E] to work with double" << endl;
		cout << "Press [A] to work with complex float" << endl;
		cout << "Press [S] to work with complex double" << endl;
		cout << "Press [Esc] to exit the program" << endl;
		int key = get_key();
		switch (key) {
		case 113:
			second_menu<int>();
			break;
		case 119:
			second_menu<float>();
			break;
		case 101:
			second_menu<double>();
			break;
		case 97:
			second_menu<std::complex<float>>();
			break;
		case 115:
			second_menu<std::complex<double>>();
			break;
		case 27:
			return 0;
			break;
		}
	} while (true);
}