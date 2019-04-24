//Compilacion: g++ -o N_hilos 2.crear_Nhilos.cpp -pthread

#include <iostream>
#include <sstream>
#include <pthread.h>
#include <cmath>

using namespace std;

typedef struct {
    int lw;
    int up;
    int id;
} arg_thread;

double sum = 0.0; //variable compartida por todos los hilos
double *sum_vector;
void *runner(void *data); //funcion a ser ejecutada por hilo
void hilos(int numThreads, int N);

//./N_hilos num_sumatoria num_hilos
int main(int argc, char *argv[]){
	int numThreads, N;
	stringstream ss((char*)argv[2]);
	ss >> numThreads;
	stringstream ss2((char*)argv[1]);
	ss2 >> N;
	sum_vector = new double[numThreads];

	hilos(numThreads, N);
}

void hilos(int numThreads, int N){
		pthread_t threads[numThreads];
	pthread_attr_t attr[numThreads];
	arg_thread data[numThreads];

	for(int i=0; i<numThreads; i++){
		data[i].lw = int(i*((double)N/numThreads))+1;
		data[i].up = int((i+1)*((double)N/numThreads));
		data[i].id = i;
		pthread_attr_init(&attr[i]);
		pthread_create(&threads[i], &attr[i], runner, &data[i]);
	}
	for(int i=0; i<numThreads; i++){
		pthread_join(threads[i], NULL);
		sum += sum_vector[i];
	}
	//Mostrar por consola el resultado de la operación del hilo
	cout << "sum = " << sum << "\n";

}
//funcion del hilo
void *runner(void *data){
	int lw, up, id;
	lw = ((arg_thread*)data)->lw;
	up = ((arg_thread*)data)->up;
	id = ((arg_thread*)data)->id;
	for(int i=lw; i<=up; i++){
		sum_vector[id] += sin((double)i);
		for(int j=0;j<10000; j++){
			printf(" ");
		}
	}
	pthread_exit(0);
}