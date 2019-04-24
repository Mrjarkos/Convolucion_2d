#include "Matrix.h"

Matrix::Matrix(){
	Matrix(1,1);
}

Matrix::Matrix(long int _rows, long int _cols){
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

void Matrix::set_value(long int _row, long int _col, int value){
	data[_row][_col] = value;
}

int Matrix::get_value(long int row, long int col){
	return data[row][col];
}

void Matrix::print(){

	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->rows; j++)
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

void  Matrix::full_in_matrix(int cont){
	int col=0;
	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->rows; j++)
		{
			col++;
			if(col%2)
			this->data[j][i] = cont;
		}
	}
}


Matrix Matrix::sum_to(Matrix mat1){
		
	if(mat1.rows == this->rows && mat1.cols == this->cols){
	 	Matrix a = Matrix(this->rows, this->cols);
		for (int i = 0; i < cols; i++)
			{
				for (int j = 0; j < rows; j++)
				{
		 			a.set_value(j, i, mat1.get_value(j,i)+this->get_value(j,i));
				}
			}
		return a;
	}
	else{
		std::cout << "ERROR 404: Dimensiones no adecuadas" << std::endl;
		Matrix a = Matrix(0, 0);
	return a;
	}
}

int Matrix::sum_elements(){
	int suma = 0;

		for (int i = 0; i < this->cols; i++)
		{
			for (int j = 0; j < this->rows; j++)
			{
				suma+= this->data[j][i];
			}
		}
	return suma;
}

Matrix Matrix::copy(){

	Matrix Copia = Matrix(this->rows, this->cols);

	for (int i = 0; i < this->cols; i++)
		{
			for (int j = 0; j < this->rows; j++)
			{
				Copia.set_value(j,i, this->data[j][i]);
			}
		}

	return Copia;	
}

Matrix Matrix::copy(Matrix Copia){

	for (int i = 0; i < this->cols; i++)
		{
			for (int j = 0; j < this->rows; j++)
			{
				this->set_value(j,i, Copia.get_value(j,i));
			}
		}
	return Copia;
}