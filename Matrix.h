
#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Matrix
{
private:
	int** data;
public:
	long int rows;
	long int cols;
	Matrix();
	Matrix(long int _rows, long int _cols);
	int** get_data_pointer();
	Matrix sum_to(Matrix);
	void full_in_matrix();
	void  full_in_matrix(int cont);
	void  full_in_matrix_rand();
	void set_value(long int, long int, int);
	int get_value(long int, long int);
	void print();
	int sum_elements();
	Matrix copy();
	Matrix copy(Matrix Copia);
};

#endif