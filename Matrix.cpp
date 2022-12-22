#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <complex>
#include <vector>
#include "Matrix.h"
#include "Errors.h"

using namespace std;

template <class T>
T Matrix<T>::calculate_determinant(int size_x, int size_y, vector <vector<T>> matrix) {
	if (size_x == 1) return matrix[0][0];
	if (size_x == 2) return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
	T** help_matrix;
	help_matrix = (T**) new T* [size_x];
	for (int i = 0; i < size_x; i++) {
		help_matrix[i] = (T*) new T[size_y * 2 - 1];
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

	T determinant = 0, vedro = 1;

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

template <class T>
T Matrix<T>::calculate_minor(int index_row, int index_col) {
	vector <vector<T>> help_matrix;
	for (int i = 0; i < size_y; i++) {
		help_matrix[index_row][i] = INT_MAX;
	}

	for (int i = 0; i < size_x; i++) {
		help_matrix[i][index_col] = INT_MAX;
	}

	vector <vector<T>>  minor;

	int x = 0, y = 0;
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			if (help_matrix[i][j] != (T)INT_MAX) {
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

template <class T>
Matrix<T>::Matrix(int size_x, int size_y, T value_to_fill) {
	set_size_x(size_x);
	set_size_y(size_y);
	vector <vector <T>> new_matrix(size_x, vector<T> (size_y, value_to_fill));
	matrix = new_matrix;
}

template <class T>
void Matrix<T>::set_size_x(int size_x) {
	this->size_x = size_x;
}

template <class T>
void Matrix<T>::set_size_y(int size_y) {
	this->size_y = size_y;
}

template <class T>
int Matrix<T>::get_size_x() const {
	return size_x;
}

template <class T>
int Matrix<T>::get_size_y() const {
	return size_y;
}

template <class T>
T Matrix<T>::calculating_the_trace() {
	T trace = 0;
	if (size_x != size_y) throw E_Not_Square_Matrix();
	for (int i = 0; i < size_x; i++) {
		trace += matrix[i][i];
	}
	return trace;
}

template <class T>
T& Matrix<T>::operator () (int index_x, int index_y) {
	if (index_x >= this->get_size_x() || index_y >= this->get_size_y()) throw E_Invalid_Index(index_x, index_y);
	return this->matrix[index_x][index_y];
}

template <class T>
Matrix<T>& Matrix<T>::operator () (int index_x, int index_y, T new_value) {
	if (index_x >= this->get_size_x() || index_y >= this->get_size_y() || index_x < 0 || index_y < 0) throw E_Invalid_Index(index_x + 1, index_y + 1);
	this->matrix[index_x][index_y] = new_value; 
	return *this;
}

//template <class T>
//Matrix<T>& Matrix<T>::operator = (const Matrix& object) {
//	/*if (this == (&object)) {
//		return *this;
//	}
//	if (size_x < object.size_x)	{
//		if (matrix != NULL) {
//			for (int i = 0; i < this->size_x; i++) {
//				delete[] this->matrix[i];
//			}
//			delete[] this->matrix;
//		}
//		matrix = NULL;
//		matrix = new T* [object.size_x];
//		for (int i = 0; i < object.size_x; i++) {
//			matrix[i] = new T[object.size_y];
//		}
//	}
//	for (int i = 0; i < object.size_x; i++) {
//		for (int j = 0; j < object.size_y; j++) {
//			this->matrix[i][j] = object.matrix[i][j];
//		}
//	}
//	size_x = object.size_x;
//	size_y = object.size_y;*/
//	
//	size_x = object.size_x;
//	size_y = object.size_y;
//
//	auto object_iter_row = object.cbegin();
//	for (auto iter = begin(); iter != end(); ++iter) {
//		auto object_iter_col = object_iter_row->begin();
//		for (auto it = iter->begin(); it != iter->end(); ++it) {
//			(*it) = (*object_iter_col);
//		}
//		++object_iter_row;
//	}
//	return *this;
//}

template <class T>
Matrix<T>& Matrix<T>::operator + (const Matrix<T>& Object) {
	if (this->size_x != Object.size_x || this->size_y != Object.size_y) throw E_Different_Size();
	
	auto obj_iter = Object.cbegin();
	for (auto iter = begin(); iter != end(); iter++) {
		auto obj_it = obj_iter->begin();
		for (auto it = iter->begin(); it != iter->end(); it++) {
			(*it) += (*obj_it);
			obj_it++;
		}
		obj_iter++;
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator - (const Matrix<T>& Object) {
	if (this->size_x != Object.size_x || this->size_y != Object.size_y) throw E_Different_Size();
	auto obj_iter = Object.cbegin();
	for (auto iter = begin(); iter != end(); iter++) {
		auto obj_it = obj_iter->begin();
		for (auto it = iter->begin(); it != iter->end(); it++) {
			(*it) += (*obj_it);
			obj_it++;
		}
		obj_iter++;
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator * (const Matrix<T>& Object) {
	if (this->size_x != Object.size_y || this->size_y != Object.size_x) throw E_Different_Size();	
	
	Matrix<T> Result_Matrix(this->get_size_x(), Object.get_size_y(), (T)0);

	for (int i = 0; i < this->size_x; ++i) {
		for (int j = 0; j < this->size_y; ++j) {
			for (int k = 0; k < this->size_x; ++k) {
				Result_Matrix.matrix.at(i).at(j) += Result_Matrix.matrix.at(i).at(k) * Object.matrix.at(k).at(j);
			}
		}
	}

	return Result_Matrix;
}

template <class T>
Matrix<T>& Matrix<T>::operator * (const T scalar) {
	for (auto iter = begin(); iter != this->end(); ++iter) {
		for (auto it = iter->begin(); it != iter->end(); ++it) {
			(*it) = (*it) * scalar;
		}
	}
	return *this;
}

template <class T>
Matrix<T>& operator * (const T scalar, const Matrix<T>& Object) {
	Matrix<T> help_obj = Object;
	return help_obj * scalar;
}

template <class T>
Matrix<T>& Matrix<T>::operator / (const T scalar) {
	if (scalar == (T)0) throw E_Divizion_By_Zero();
	for (auto iter = begin(); iter != this->end(); ++iter) {
		for (auto it = iter->begin(); it != iter->end(); ++it) {
			(*it) = (*it) / scalar;
		}
	}
	return *this;
}


template <class T>
Matrix<T> Matrix<T>::search_invers_matrix() {
	T inverted_determinant = calculate_determinant(get_size_x(), get_size_y(), matrix);
	if (inverted_determinant == (T)0) throw E_Determinant_Is_Zero();
	inverted_determinant = (T)1 / inverted_determinant;
	Matrix<T> new_obj;
	for (int i = 0; i < this->size_x; ++i) {
		for (int j = 0; j < this->size_y; ++j) {
			new_obj.matrix.at(i).at(j) += calculate_minor(i, j) * inverted_determinant;
		}
	}

	return new_obj;
}


template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<complex<float>>;
template class Matrix<complex<double>>;