#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

template <class T>
class Matrix {
private:
	int size_x, size_y;
	T** matrix;
	T calculate_determinant(int size_x, int size_y, T** matrix);
	T calculate_minor(int index_row, int index_col);

public:
	
	Matrix(int size_x, int size_y, T value_to_fill);
	
	void set_size_x(int size_x);
	void set_size_y(int size_y);
	int get_size_x() const;
	int get_size_y() const;

	T calculating_the_trace();

	T& operator () (int index_x, int index_y);
	Matrix& operator () (int index_x, int index_y, T new_value);
	Matrix& operator = (const Matrix& object);
	Matrix& operator + (const Matrix& Object);
	Matrix& operator - (const Matrix& Object);
	Matrix& operator * (const Matrix& Object);
	Matrix& operator * (const T scalar);
	friend Matrix& operator * (const T scalar, const Matrix& Object);
	Matrix& operator / (const T scalar);

	Matrix search_invers_matrix();

	friend ostream& operator << (ostream& os, const Matrix& object)
	{
		Matrix mat = object;
		for (int i = 0; i < object.get_size_x(); i++) {
			for (int j = 0; j < object.get_size_y(); j++) {
				os << "\t" << mat(i, j);
			}
			cout << endl;
		}
		return os;
	}
};