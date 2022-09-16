#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Error {
public:
	virtual void print_message() const = 0;
};

class E_Different_Size : public Error {
public:
	void print_message() const;
};

class E_Invalid_Index : public Error {
private:
	int index_x, index_y;
public:
	E_Invalid_Index(int index_x, int index_y);
	void print_message() const;
}; 
