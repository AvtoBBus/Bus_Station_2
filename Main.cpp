#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include "Errors.h"

using namespace std;

class Matrix {
private:
	int size_x, size_y;
	double** matrix;
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
	int get_size_x() {
		return size_x;
	}
	int get_size_y() {
		return size_y;
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
};

int main() {
	int x_size_input = 0, y_size_input = 0;
	cout << "INPUT INFO ABOUT 1-ST MATRIX:" << endl;
	cout << "Number of colums: ";
	cin >> y_size_input;
	cout << "Number of lines: ";
	cin >> x_size_input;

	double** matrix_input = new double* [x_size_input];
	for (int i = 0; i < x_size_input; i++) {
		matrix_input[i] = new double[y_size_input];
	}

	cout << endl << "INPUT VALUES IN CELL:" << endl;
	for (int i = 0; i < x_size_input; i++) {
		for (int j = 0; j < y_size_input; j++) {
			cout << "Cell [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> matrix_input[i][j];
		}
		cout << endl;
	}

	Matrix first_obj(x_size_input, y_size_input, matrix_input);
	first_obj.print_matrix();

	for (int i = 0; i < x_size_input; i++) {
		delete[] matrix_input[i];
	}
	delete[] matrix_input;

	cout << "INPUT INFO ABOUT 2-ST MATRIX::" << endl;
	cout << "Number of colums: ";
	cin >> y_size_input;
	cout << "Number of lines:  ";
	cin >> x_size_input;

	matrix_input = new double* [x_size_input];
	for (int i = 0; i < x_size_input; i++) {
		matrix_input[i] = new double[y_size_input];
	}

	cout << endl << "INPUT VALUES IN CELL:" << endl;
	for (int i = 0; i < x_size_input; i++) {
		for (int j = 0; j < y_size_input; j++) {
			cout << "Cell [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> matrix_input[i][j];
		}
		cout << endl;
	}

	Matrix second_obj(x_size_input, y_size_input, matrix_input);
	second_obj.print_matrix();
	Matrix new_obj(0, 0, matrix_input);
	new_obj = first_obj;

	int scalar = 0;
	cout << endl << "INPUT SCALAR:" << endl;
	cin >> scalar;

	system("pause");
	system("cls");

	cout << "RESULT OF ADDITION:" << endl;
	try {
		new_obj + second_obj;
		new_obj.print_matrix();
	}
	catch (Error& er) { er.print_message(); }

	cout << endl << "RESULT OF SUBSTRACTION:" << endl;
	try {
		new_obj = first_obj;
		new_obj - second_obj;
		new_obj.print_matrix();
	}
	catch (Error& er) { er.print_message(); }

	cout << endl << "RESULT OF MULTIPLICATION MATRIX:" << endl;
	try {
		new_obj = first_obj;
		new_obj * second_obj;
		new_obj.print_matrix();
	}
	catch (Error& er) { er.print_message(); }

	system("pause");
	system("cls");

	cout << endl << "RESULT OF MULTIPLICATION 1-ST MATRIX ON SCALAR:" << endl;
	new_obj = first_obj;
	new_obj * scalar;
	new_obj.print_matrix();

	cout << endl << "RESULT OF MULTIPLICATION 2-ST MATRIX ON SCALAR:" << endl;
	new_obj = second_obj;
	scalar * new_obj;
	new_obj.print_matrix();

	system("pause");
	system("cls");

	cout << endl << "RESULT OF DIVISION 1-ST MATRIX ON SCALAR:" << endl;
	new_obj = first_obj;
	new_obj / scalar;
	new_obj.print_matrix();

	cout << endl << "RESULT OF DIVISION 2-ST MATRIX ON SCALAR:" << endl;
	new_obj = second_obj;
	new_obj / scalar;
	new_obj.print_matrix();

	system("pause");
	system("cls");

	cout << "RESULT OF CALCULATING TRACE OF 1-ST MATRIX:" << endl;
	try {
		cout << first_obj.calculating_the_trace() << endl;
	}
	catch (Error& er) { er.print_message(); }

	cout << "RESULT OF CALCULATING TRACE OF 2-ST MATRIX:" << endl;
	try {
		cout << second_obj.calculating_the_trace() << endl;
	}
	catch (Error& er) { er.print_message(); }

	return 0;
}