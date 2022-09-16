#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Errors.h"

using namespace std;

void E_Different_Size::print_message() const {
	cout << endl << "Error:\nUnreal operation. Matrix have unsuitable size" << endl;
}

E_Invalid_Index::E_Invalid_Index(int index_x, int index_y) {
	this->index_x = index_x;
	this->index_y = index_y;
};

void E_Invalid_Index::print_message() const {
	cout << endl << "Error:\nIndex: " << index_x << " and " << index_y << " is invalid" << endl;
}