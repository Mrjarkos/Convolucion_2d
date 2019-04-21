#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <curses.h>
#include "Matrix.h"

#define length(x) (sizeof(x)/sizeof(x[0]))

using namespace std;

Matrix convolucion (Matrix imagen, Matrix filtro, int hilos);

void* Paralell_Proces(void *param);

typedef struct 
{
	Matrix imagen;
	Matrix filtro;
	Matrix resultado;
	int threads;
	int offset;
	int mitad;
}Param_Threads;


int numThreads;
Matrix crear_matrix();

int main(int argc, char** argv);