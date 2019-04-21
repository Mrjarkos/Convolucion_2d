
#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Matrix
{
	int** data;
public:
	int rows;
	int cols;
	Matrix(int, int);
	int** get_data_pointer();
	Matrix sum_to(Matrix);
	void full_in_matrix();
	void  full_in_matrix(int cont);
	void  full_in_matrix_rand();
	void set_value(int, int, int);
	int get_value(int, int);
	void print();
};

#endif