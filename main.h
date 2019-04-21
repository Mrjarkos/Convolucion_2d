#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include <curses.h>

#define length(x) (sizeof(x)/sizeof(x[0]))

using namespace std;

Matrix convolucion (Matrix imagen, Matrix filtro);

Matrix crear_matrix();

int main(int argc, char** argv);