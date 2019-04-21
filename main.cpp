
#include "main.h"


int main(int argc, char** argv) {

    clock_t t_ini1, t_ini2, t_fin;
    double secs;

    if(argc==1){
       numThreads = 1;
    }else if(argc >2){
        printf("Demasiados argumentos\n");
        return 1;
    }else{
        if(std::stoi(argv[1])<=0){
            printf("Numero invalido de hilos\n");
            return 1;  
        }else{
            numThreads = std::stoi(argv[1]);
        }
    }

    printf("Presione 1 si desea Ingresar usted mismo los datos, o cualquier otra tecla para Ejecutar un ejemplo de convolucion (aleatorio)\n");

    char a = getchar();
    t_ini1 = clock();

    printf("Convolucion 2D\n");

    if(a == '1'){

        Matrix Filtro = crear_matrix();
        Matrix Imagen = crear_matrix();
        t_ini2 = clock();
        Matrix Resultado = convolucion(Imagen, Filtro, numThreads);
        printf("\nImagen Convolucionada:\n");
        Resultado.print();

    }else{

        int n = 10, m = 16;
        Matrix Filtro = Matrix(n, n);
        printf("\nFiltro:\n");
        Filtro.full_in_matrix_rand();
        Filtro.print();

        Matrix Imagen = Matrix(m, m);
        printf("\nImagen:\n");
        Imagen.full_in_matrix();
        Imagen.print();

        t_ini2 = clock();
        Matrix Resultado = convolucion(Imagen, Filtro, numThreads);
        printf("\nImagen Convolucionada:\n");
        Resultado.print();
    }

    t_fin = clock();
    printf("\nEjecucion con %i hilos", numThreads);
    secs = (double)(t_fin - t_ini1) / CLOCKS_PER_SEC;
    printf("\nTotal Time Programm = %.16g milisegundos\n", secs * 1000.0);
    secs = (double)(t_fin - t_ini2) / CLOCKS_PER_SEC;
    printf("Total Time Convolution= %.16g milisegundos\n", secs * 1000.0);
    return 0;
}


Matrix convolucion (Matrix imagen, Matrix filtro, int numThreads)
{   
    int mitad, i,j,m,n,mm,nn,ii,jj, acumulador;

    int kernel[filtro.rows][filtro.cols];
    for (int i = 0; i < filtro.cols; i++){
        for (int j = 0; j < filtro.rows; j++){
            kernel[j][i] = filtro.get_value(j, i);
        }
    }

     int image[imagen.rows][imagen.cols];
     for (int i = 0; i < filtro.cols; i++){
        for (int j = 0; j < filtro.rows; j++){
            image[j][i] = imagen.get_value(j, i);
        }
    }                    
    
    Matrix result_matrix = Matrix(imagen.cols, imagen.rows);

    mitad = length(kernel) / 2;


    pthread_t threads[numThreads];
    pthread_attr_t attr[numThreads];
    Param_Threads data[numThreads];


    for(int i=0; i<numThreads; i++){
        data[i].imagen = imagen;
        data[i].filtro = filtro;
        data[i].resultado = result_matrix;
        data[i].threads = numThreads;
        data[i].offset = i;
        data[i].mitad = mitad;
        pthread_attr_init(&attr[i]);
        pthread_create(&threads[i], &attr[i], Paralell_Proces, &data[i]);
    }

    for(int i=0; i<numThreads; i++){
        pthread_join(threads[i], NULL);
        result_matrix = data[i].resultado.sum_to(result_matrix);
    }

    return result_matrix;
}

void* Paralell_Proces(void *param){

    int mitad, i,j,m,n,mm,nn,ii,jj, acumulador;
    Matrix imagen = ((Param_Threads*)param)->imagen;
    Matrix filtro =  ((Param_Threads*)param)->filtro;
    Matrix resultado = ((Param_Threads*)param)->resultado;
    int threads =  ((Param_Threads*)param)->threads;
    int hilo = ((Param_Threads*)param)->offset;
    int offset = imagen.rows/threads*hilo;
    mitad = ((Param_Threads*)param)->mitad;

    for (i = offset; i < imagen.rows/threads + offset ; ++i) // Filas
    {
        for (j = offset; j < imagen.cols/threads + offset; ++j) // Columnas
        {
            acumulador = 0; // Variable acumuladora
            
            for (m = 0; m < filtro.rows; ++m) // Filas del Kernel
            {
                mm = filtro.rows - 1 - m; // Indice de la fila del kernel alrevez

                for (n = 0; n < filtro.cols; ++n) // Columnas del kernel
                {
                    nn = filtro.cols - 1 - n; // Indice de la columna del kernel alrevez
                    
                    ii = i + (m - mitad);
                    jj = j + (n - mitad);

                    if (ii >= offset && ii <  imagen.rows/threads + offset && jj >= offset && jj <  imagen.cols/threads + offset) // validar limites de la imagen 00000
                    {
                        acumulador += imagen.get_value(ii, jj)* filtro.get_value(mm, nn);
                    }                        
                }
            }
            resultado.set_value(i, j, acumulador);
        }
    }

printf("\nResultado [%i]\n", hilo);
resultado.print();


}

Matrix crear_matrix(){
    std::cout << "Ingrese el numero de filas" << std::endl;
    int rows;
    std::cin >> rows;
    std::cout << rows << std::endl;
    std::cout << "Ingrese el numero de columnas" << std::endl;
    int cols;
    std::cin >> cols;
    std::cout << cols << std::endl;
    Matrix a = Matrix(rows, cols);

    int n;
    for (int j = 0; j < rows; j++)
            {
                for (int i = 0; i < cols; i++)
                {
                    std::cout << "Ingrese el valor de la posicion [" << j << "] [" << i << "]" << std::endl;
                    std::cin >> n;
                    std::cout << n << std::endl;
                    std::cout << j << std::endl;
                    std::cout << i << std::endl;
                    a.set_value(i, j, n);
                }
            }

    return a;
}
