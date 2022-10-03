#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Errors.h"

using namespace std;

class Matrix {
private:
	int size_x, size_y;
	double** matrix;
	int calculate_determinant() {
		int determinant = matrix[0][0] * matrix[1][1] * matrix[2][2];
		determinant += matrix[0][1] * matrix[1][2] * matrix[0][2];
		determinant += matrix[0][1] * matrix[1][2] * matrix[2][0];
		determinant -= matrix[2][0] * matrix[1][1] * matrix[0][2];
		determinant -= matrix[2][1] * matrix[1][2] * matrix[0][0];
		determinant -= matrix[2][2] * matrix[0][1] * matrix[1][0];
		return determinant;
	}
public:

	Matrix();
	Matrix(int size_x, int size_y, double** matrix) {
		set_size_x(size_x);
		set_size_y(size_y);
		set_matrix(matrix);
	}

	void set_size_x(int size_x) {
		this->size_x = size_x;
	}
	void set_size_y(int size_y) {
		this->size_y = size_y;
	}
	int get_size_x() const {
		return size_x;
	}
	int get_size_y() const {
		return size_y;
	}
	int get_value_in_cell(int index_x, int index_y) const {
		return matrix[index_x][index_y];
	}
	void set_matrix(double** matrix) {

		this->matrix = new double* [size_x];
		for (int i = 0; i < size_x; i++) {
			this->matrix[i] = new double[size_y];
		}

		for (int i = 0; i < this->size_x; i++) {
			for (int j = 0; j < this->size_y; j++) {
				this->matrix[i][j] = matrix[i][j];
			}
		}
	}


	void set_value_index(double value, int index_x, int index_y) {
		if (index_x > size_x || index_y > size_y) throw E_Invalid_Index(index_x, index_y);
	}
	void print_matrix() {
		cout << endl;
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				cout << "\t" << matrix[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}

	int calculating_the_trace() {
		int trace = 0;
		if (size_x != size_y) throw E_Not_Square_Matrix();
		for (int i = 0; i < size_x; i++) {
			trace += matrix[i][i];
		}
		return trace;
	}


	friend ostream& operator << (ostream& os, const Matrix& object) {
		for (int i = 0; i < object.get_size_x(); i++) {
			for (int j = 0; j < object.get_size_y(); j++) {
				os << "\t" << object.get_value_in_cell(i, j);
			}
			cout << endl;
		}
		return os;
	}
	double operator () (int index_x, int index_y) {
		return this->matrix[index_x][index_y];
	}
	Matrix& operator () (int index_x, int index_y, int new_value) {
		this->matrix[index_x][index_y] = new_value;
		return *this;
	}
	Matrix& operator = (const Matrix& object) {
		this->size_x = object.size_x;
		this->size_y = object.size_y;

		this->matrix = new double* [size_x];
		for (int i = 0; i < size_x; i++) {
			this->matrix[i] = new double[size_y];
		}

		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				this->matrix[i][j] = object.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix& operator + (const Matrix& Object) {
		if (this->size_x != Object.size_x || this->size_y != Object.size_y) throw E_Different_Size();
		for (int i = 0; i < this->size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				this->matrix[i][j] += Object.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix& operator - (const Matrix& Object) {
		if (this->size_x != Object.size_x || this->size_y != Object.size_y) throw E_Different_Size();
		for (int i = 0; i < this->size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				this->matrix[i][j] -= Object.matrix[i][j];
			}
		}
		return *this;
	}
	Matrix& operator * (const Matrix& Object) {
		if (this->size_x != Object.size_y || this->size_y != Object.size_x) throw E_Different_Size();
		double** First_Matrix{}, ** Second_Matrix{}, ** Result_Matrix{};
		int First_size_x = this->size_x, First_size_y = this->size_y,
			Second_size_x = Object.size_x, Second_size_y = Object.size_y;
		First_Matrix = new double* [size_x];
		for (int i = 0; i < size_x; i++) {
			First_Matrix[i] = new double[size_y];
		}
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				First_Matrix[i][j] = this->matrix[i][j];
			}
		}

		Second_Matrix = new double* [Object.size_x];
		for (int i = 0; i < Object.size_x; i++) {
			Second_Matrix[i] = new double[Object.size_y];
		}
		for (int i = 0; i < Object.size_x; i++) {
			for (int j = 0; j < Object.size_y; j++) {
				Second_Matrix[i][j] = Object.matrix[i][j];
			}
		}

		Result_Matrix = new double* [First_size_x];
		for (int i = 0; i < First_size_x; i++) {
			Result_Matrix[i] = new double[Second_size_y];
		}

		for (int row = 0; row < First_size_x; row++) {
			for (int col = 0; col < Second_size_y; col++) {
				Result_Matrix[row][col] = 0;
				for (int inner = 0; inner < First_size_y; inner++) {
					Result_Matrix[row][col] += First_Matrix[row][inner] * Second_Matrix[inner][col];
				}
			}
		}

		for (int i = 0; i < this->size_x; i++) {
			delete[] this->matrix[i];
		}
		delete[] this->matrix;

		this->matrix = new double* [First_size_x];
		for (int i = 0; i < First_size_x; i++) {
			this->matrix[i] = new double[Second_size_y];
		}

		this->size_x = First_size_x;
		this->size_y = Second_size_y;

		for (int i = 0; i < First_size_x; i++) {
			for (int j = 0; j < Second_size_y; j++) {
				this->matrix[i][j] = Result_Matrix[i][j];
			}
		}
		return *this;
	}
	Matrix& operator * (const int scalar) {
		for (int i = 0; i < this->size_x; i++) {
			for (int j = 0; j < this->size_x; j++) {
				this->matrix[i][j] *= scalar;
			}
		}
		return *this;
	}
	friend Matrix& operator * (const int scalar, Matrix& Object) {
		return Object * scalar;
	}
	Matrix& operator / (const int scalar) {
		for (int i = 0; i < this->size_x; i++) {
			for (int j = 0; j < this->size_x; j++) {
				this->matrix[i][j] /= scalar;
			}
		}
		return *this;
	}

	Matrix search_invers_matrix() {
		if (size_x != 3 || size_y != 3) throw E_No_Suitable_Size();
		Matrix new_obj = *this;

		return new_obj;
	}
};

int get_key() {
	int key = _getch();
	return key;
}

Matrix result_of_operation(Matrix first_obj, Matrix second_obj, const char* operation) {
	double** matrix = { 0 };
	Matrix help_obj(0, 0, matrix);
	help_obj = first_obj;
	if (strcmp("add", operation) == 0) {
		if (first_obj.get_size_x() == second_obj.get_size_x() && first_obj.get_size_y() == second_obj.get_size_y()) return help_obj + second_obj;
	}
	else if (strcmp("sub", operation) == 0) {
		if (first_obj.get_size_x() == second_obj.get_size_x() && first_obj.get_size_y() == second_obj.get_size_y()) return help_obj - second_obj;
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
	else throw E_Different_Size();
}

double** input_data(int x_size_input, int y_size_input, double** matrix_input) {
	cout << endl << "INPUT VALUES IN CELL:" << endl;
	for (int i = 0; i < x_size_input; i++) {
		for (int j = 0; j < y_size_input; j++) {
			cout << "Cell [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> matrix_input[i][j];
		}
		cout << endl;
	}
	return matrix_input;
}

int main() {
	int x_size_input = 0, y_size_input = 0, choose = 0;;
	
	cout << "INPUT INFO ABOUT 1-ST MATRIX:" << endl;
	cout << "Number of colums: ";
	cin >> y_size_input;
	cout << "Number of lines: ";
	cin >> x_size_input;
	double** matrix_input = new double* [x_size_input];
	for (int i = 0; i < x_size_input; i++) {
		matrix_input[i] = new double[y_size_input];
	}
	matrix_input = input_data(x_size_input, y_size_input, matrix_input);
	Matrix first_obj(x_size_input, y_size_input, matrix_input);

	for (int i = 0; i < x_size_input; i++) {
		delete[] matrix_input[i];
	}
	delete[] matrix_input;

	cout << "INPUT INFO ABOUT 2-ST MATRIX:" << endl;
	cout << "Number of colums: ";
	cin >> y_size_input;
	cout << "Number of lines: ";
	cin >> x_size_input;
	matrix_input = new double* [x_size_input];
	for (int i = 0; i < x_size_input; i++) {
		matrix_input[i] = new double[y_size_input];
	}
	matrix_input = input_data(x_size_input, y_size_input, matrix_input);
	Matrix second_obj(x_size_input, y_size_input, matrix_input);
	
	while (true) {
		system("cls");
		cout << "FIRST MATRIX:" << endl;
		cout << first_obj;
		cout << "SECOND MATRIX:" << endl;
		cout << second_obj;
		cout << endl;
		cout << "Press [Q] to perform the addition" << endl;
		cout << "Press [W] to perform the subtraction" << endl;
		cout << "Press [E] to perform the multiplication (matrix * matrix)" << endl;
		cout << "Press [R] to perform the multiplication (matrix * scalar)" << endl;
		cout << "Press [A] to perform the division (matrix / scalar)" << endl;
		cout << "Press [S] to calculate the trace of the matrix" << endl;
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
			system("cls");
			cout << "Result of DIVISION (matrix * scalar):" << endl << result_of_operation(first_obj, second_obj, "div_scalar");
			break;
		case 115: //s
			system("cls");
			cout << "Chose matrix (1 - FIRST, 2 - SECOND): ";
			cin >> choose;
			if (choose == 1) cout << "Result of CALCULATE THE TRACE:" << first_obj.calculating_the_trace() << endl;
			if (choose == 2) cout << "Result of CALCULATE THE TRACE:" << second_obj.calculating_the_trace() << endl;
			break;
		case 27: //esc
			return 0;
		}
		system("pause");
	
	}

	return 0;
}