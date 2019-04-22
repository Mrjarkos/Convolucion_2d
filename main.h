#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <curses.h>
#include <math.h>
#include "Matrix.h"

#define length(x) (sizeof(x)/sizeof(x[0]))

using namespace std;

typedef struct bmpFileHeader
{
  uint32_t size;
  uint16_t resv1;
  uint16_t resv2;
  uint32_t offset;
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  uint32_t headersize;      /* DIB header size */
  uint32_t width;
  uint32_t height;
  uint16_t planes;         /* color planes */
  uint16_t bpp;            /* bits per pixel */
  uint32_t compress;
  uint32_t imgsize;     
  uint32_t bpmx;        /* X bits per meter */
  uint32_t bpmy;        /* Y bits per meter */
  uint32_t colors;      /* colors used */
  uint32_t imxtcolors;      /* important colors */
} bmpInfoHeader;

void SaveBMP(char *filename, bmpInfoHeader *info, unsigned char *imgdata);
unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader);
bmpInfoHeader *createInfoHeader(unsigned w, unsigned h, unsigned ppp);

Matrix convolucion (Matrix imagen, Matrix filtro, int hilos);

void* Paralell_Proces(void *param);

typedef struct {
	Matrix imagen;
	Matrix filtro;
	Matrix resultado;
	int threads;
	int offset;
	int mitad;
} Param_Threads;


int numThreads;
Matrix crear_matrix();

int main(int argc, char** argv);