#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Errors.h"
#include "Matrix.h"

using namespace std;

int get_key() {
	int key = _getch();
	return key;
}

Matrix result_of_operation(Matrix first_obj, Matrix second_obj, const char* operation) {
	Matrix help_obj(0, 0, 0);
	help_obj = first_obj;
	if (strcmp("add", operation) == 0) {
		if (first_obj.get_size_x() == second_obj.get_size_x() && first_obj.get_size_y() == second_obj.get_size_y()) return help_obj + second_obj;
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
		int scalar = 0, choose = 0;
		cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
		cin >> choose;
		cout << "Input scalar: ";
		cin >> scalar;
		if (choose == 2) help_obj = second_obj;
		return help_obj * scalar;
	}
	else if (strcmp("div_scalar", operation) == 0) {
		int scalar = 0, choose = 0;
		cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
		cin >> choose;
		cout << "Input scalar: ";
		cin >> scalar;
		if (choose == 2) help_obj = second_obj;
		return help_obj / double(scalar);
	}
	else if (strcmp("inverted", operation) == 0) {
		int choose = 0;
		do {
			cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
			cin >> choose;
		} while (choose < 1 || choose > 2);
		if (choose == 2) help_obj = second_obj;
		return help_obj.search_invers_matrix();
	}
}

int main() {
	int x_size_input = 0, y_size_input = 0, choose = 0;
	double input_value = 0;

	cout << "INPUT INFO ABOUT 1-ST MATRIX:" << endl;
	do {
		cout << "Number of colums: ";
		cin >> y_size_input;
	} while (y_size_input <= 0);
	do {
		cout << "Number of lines: ";
		cin >> x_size_input;
	} while (y_size_input <= 0);

	cout << endl << "INPUT VALUE, WHICH FILL 1-ST MATRIX" << endl;
	cin >> input_value;

	Matrix first_obj(x_size_input, y_size_input, input_value);

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

	Matrix second_obj(x_size_input, y_size_input, input_value);

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
		cout << "Press [Esc] to exit the program" << endl;
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
				cin >> input_value;
				if (choose == 1) cout << endl << "Value in cell [" << x_size_input << "][" << y_size_input << "] was switch on " << input_value << endl << first_obj(x_size_input - 1, y_size_input - 1, input_value) << endl;
				if (choose == 2) cout << endl << "Value in cell [" << x_size_input << "][" << y_size_input << "] was switch on " << input_value << endl << second_obj(x_size_input - 1, y_size_input - 1, input_value) << endl;
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 122:
			try {
				system("cls");
				cout << endl << result_of_operation(first_obj, second_obj, "inverted");
			}
			catch (Error& er) { er.print_message(); }
			break;
		case 27: //esc
			return 0;
		}
		system("pause");

	}

	return 0;
}