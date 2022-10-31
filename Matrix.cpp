#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Matrix.h"
#include "Errors.h"

using namespace std;

double Matrix::calculate_determinant(int size_x, int size_y, double** matrix) {
	if (size_x == 2) return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
	double** help_matrix;
	help_matrix = new double* [size_x];
	for (int i = 0; i < size_x; i++) {
		help_matrix[i] = new double[size_y * 2 - 1];
	}
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			help_matrix[i][j] = matrix[i][j];
		}
	}
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y - 1; j++) {
			help_matrix[i][j + size_y] = matrix[i][j];
		}
	}

 	double determinant = 0, vedro = 1;

	for (int j = 0; j < size_y; j++) {
		vedro = 1;
		for (int i = 0; i < size_x; i++) {
			vedro *= help_matrix[i][i + j];
		}
		determinant += vedro;
	}

	for (int j = 0; j < size_y; j++) {
		vedro = 1;
		int k = j;
		for (int i = size_x - 1; i != -1; i--) {
			vedro *= help_matrix[i][k];
			k++;
		}
		determinant -= vedro;
	}

	return determinant;
}

double Matrix::calculate_minor(int index_row, int index_col) {
	double** help_matrix;

	help_matrix = new double* [size_x];
	for (int i = 0; i < size_x; i++) {
		help_matrix[i] = new double[size_y];
	}
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			help_matrix[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < size_y; i++) {
		help_matrix[index_row][i] = INT_MAX;
	}

	for (int i = 0; i < size_x; i++) {
		help_matrix[i][index_col] = INT_MAX;
	}

	double** minor;
	minor = new double* [size_x - 1];
	for (int i = 0; i < size_x - 1; i++) {
		minor[i] = new double[size_y - 1];
	}

	int x = 0, y = 0;
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			if (help_matrix[i][j] != INT_MAX) {
				int puk = help_matrix[i][j];
				minor[x][y] = help_matrix[i][j];
				if (y != size_y - 2) y++;
				else {
					x++; y = 0;
				}
			}
		}
	}
	return calculate_determinant(get_size_x() - 1, get_size_y() - 1, minor);
}

Matrix::Matrix(int size_x, int size_y, double value_to_fill) {
	set_size_x(size_x);
	set_size_y(size_y);
	matrix = new double* [size_x];
	for (int i = 0; i < size_x; i++) {
		matrix[i] = new double[size_y];
	}
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			matrix[i][j] = value_to_fill;
		}
	}
}

void Matrix::set_size_x(int size_x) {
	this->size_x = size_x;
}
void Matrix::set_size_y(int size_y) {
	this->size_y = size_y;
}
int Matrix::get_size_x() const {
	return size_x;
}
int Matrix::get_size_y() const {
	return size_y;
}

int Matrix::calculating_the_trace() {
	int trace = 0;
	if (size_x != size_y) throw E_Not_Square_Matrix();
	for (int i = 0; i < size_x; i++) {
		trace += matrix[i][i];
	}
	return trace;
}

double Matrix::operator () (int index_x, int index_y) {
	if (index_x >= this->get_size_x() || index_y >= this->get_size_y()) throw E_Invalid_Index(index_x, index_y);
	return this->matrix[index_x][index_y];
}
Matrix& Matrix::operator () (int index_x, int index_y, int new_value) {
	if (index_x >= this->get_size_x() || index_y >= this->get_size_y()) throw E_Invalid_Index(index_x, index_y);
	this->matrix[index_x][index_y] = new_value;
	return *this;
}
Matrix& Matrix::operator = (const Matrix& object) {
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
Matrix& Matrix::operator + (const Matrix& Object) {
	if (this->size_x != Object.size_x || this->size_y != Object.size_y) throw E_Different_Size();
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			this->matrix[i][j] += Object.matrix[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator - (const Matrix& Object) {
	if (this->size_x != Object.size_x || this->size_y != Object.size_y) throw E_Different_Size();
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			this->matrix[i][j] -= Object.matrix[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator * (const Matrix& Object) {
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
Matrix& Matrix::operator * (const int scalar) {
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_x; j++) {
			this->matrix[i][j] *= scalar;
		}
	}
	return *this;
}
Matrix& operator * (const int scalar, const Matrix& Object) {
	Matrix help_obj = Object;
	return help_obj * scalar;
}
Matrix& Matrix::operator / (const int scalar) {
	if (scalar == 0) throw E_Divizion_By_Zero();
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_y; j++) {
			this->matrix[i][j] /= scalar;
		}
	}
	return *this;
}

Matrix Matrix::search_invers_matrix() {
	double inverted_determinant = calculate_determinant(get_size_x(), get_size_y(), matrix);
	if (inverted_determinant == 0) throw E_Determinant_Is_Zero();
	inverted_determinant = 1 / inverted_determinant;
	Matrix new_obj(3, 3, 0);
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_x; j++) {
			new_obj.matrix[j][i] = calculate_minor(i, j) * inverted_determinant;
		}
	} 
	return new_obj;
}

ostream& operator << (ostream& os, const Matrix& object) {
	Matrix mat = object;
	for (int i = 0; i < object.get_size_x(); i++) {
		for (int j = 0; j < object.get_size_y(); j++) {
			os << "\t" << mat(i, j);
		}
		cout << endl;
	}
	return os;
}