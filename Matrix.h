#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class Matrix {
private:
	int size_x, size_y;
	vector<vector <T>> matrix;
	T calculate_determinant(int size_x, int size_y, vector <vector<T>> matrix);
	T calculate_minor(int index_row, int index_col);

public:
	
	auto begin() { return matrix.begin(); }
	auto end() { return matrix.end(); }
	auto cbegin() const { return matrix.cbegin(); }
	auto cend() const { return matrix.cend(); }

	Matrix() = default;
	Matrix(int size_x, int size_y, T value_to_fill);
	~Matrix() = default;

	void set_size_x(int size_x);
	void set_size_y(int size_y);
	int get_size_x() const;
	int get_size_y() const;

	T calculating_the_trace();

	T& operator () (int index_x, int index_y);
	Matrix& operator () (int index_x, int index_y, T new_value);
	Matrix& operator = (const Matrix& Object) = default;
	Matrix& operator + (const Matrix& Object);
	Matrix& operator - (const Matrix& Object);
	Matrix& operator * (const Matrix& Object);
	Matrix& operator * (const T scalar);
	friend Matrix& operator * (const T scalar, const Matrix& Object);
	Matrix& operator / (const T scalar);

	Matrix search_invers_matrix();

	friend ostream& operator << (ostream& os, const Matrix& object) {
		for (auto it = object.cbegin(); it != object.cend(); ++it) {
			for (auto iter : (*it)) {
				os << iter << "\t";
			}
			cout << endl;
		}
		return os;
	}
};