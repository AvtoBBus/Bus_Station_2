#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

class Matrix {
private:
	int size_x, size_y;
	double** matrix;
	int calculate_determinant();

public:
	
	Matrix(int size_x, int size_y, double** matrix); //заполнять 1-м значемнием всю матрицу

	void set_size_x(int size_x);
	void set_size_y(int size_y);
	int get_size_x() const;
	int get_size_y() const;
	int get_value_in_cell(int index_x, int index_y) const;
	void set_matrix(double** matrix);


	void set_value_index(double value, int index_x, int index_y);
	void print_matrix();

	int calculating_the_trace();

	double operator () (int index_x, int index_y);
	Matrix& operator () (int index_x, int index_y, int new_value);
	Matrix& operator = (const Matrix& object);
	Matrix& operator + (const Matrix& Object);
	Matrix& operator - (const Matrix& Object);
	Matrix& operator * (const Matrix& Object);
	Matrix& operator * (const int scalar);
	friend Matrix& operator * (const int scalar, Matrix& Object); //доработать
	Matrix& operator / (const int scalar);

	Matrix search_invers_matrix();

	friend ostream& operator << (ostream& os, const Matrix& object);
};