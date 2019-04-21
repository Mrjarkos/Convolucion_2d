#include "Matrix.h"



Matrix::Matrix(int _rows, int _cols){
	this->rows = _rows;
	this->cols = _cols;

	data = new int*[rows];
	for(int i=0; i<rows; i++){
    data[i] = new int[cols];
    for(int j=0; j<cols; j++){
        data[i][j] = 0;
    }
}
}

int** Matrix::get_data_pointer(){
	return data;
}

void Matrix::set_value(int _row, int _col, int value){
	data[_row][_col] = value;
}

int Matrix::get_value(int row, int col){
	return data[row][col];
}

void Matrix::print(){

	std::cout << "\nMATRIX:" << std::endl;

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			std::cout << data[j][i] << "\t"; 
		}

		std::cout << std::endl;
	}
}


void  Matrix::full_in_matrix_rand(){

	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->rows; j++)
		{
			this->data[j][i] = rand()%10;
		}
	}
}

void  Matrix::full_in_matrix(){

int cont =1;
	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->rows; j++)
		{
			this->data[j][i] = cont;
			cont++;
		}
	}
}

void  Matrix::full_in_matrix(int cont ){
	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->rows; j++)
		{
			this->data[j][i] = cont;
		}
	}
}