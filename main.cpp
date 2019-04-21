
#include "main.h"


int main(int argc, char** argv) {

    int hilos;
    clock_t t_ini1, t_ini2, t_fin;
    double secs;

    if(argc==1){
       hilos = 1;
    }else if(argc >2){
        printf("Demasiados argumentos\n");
        return 1;
    }else{
        if(std::stoi(argv[1])<=0){
            printf("Numero invalido de hilos\n");
            return 1;  
        }else{
            hilos = std::stoi(argv[1]);
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
        Matrix Resultado = convolucion(Imagen, Filtro);
        printf("\nImagen Convolucionada:\n");
        Resultado.print();

    }else{

        int n = 10, m = 10;
        Matrix Filtro = Matrix(n, n);
        printf("\nFiltro:\n");
        Filtro.full_in_matrix_rand();
        Filtro.print();

        Matrix Imagen = Matrix(m, m);
        printf("\nImagen:\n");
        Imagen.full_in_matrix();
        Imagen.print();

        t_ini2 = clock();
        Matrix Resultado = convolucion(Imagen, Filtro);
        printf("\nImagen Convolucionada:\n");
        Resultado.print();
    }

    t_fin = clock();
    printf("\nEjecucion con %i hilos", hilos);
    secs = (double)(t_fin - t_ini1) / CLOCKS_PER_SEC;
    printf("\nTotal Time Programm = %.16g milisegundos\n", secs * 1000.0);
    secs = (double)(t_fin - t_ini2) / CLOCKS_PER_SEC;
    printf("Total Time Convolution= %.16g milisegundos\n", secs * 1000.0);
    return 0;
}


Matrix convolucion (Matrix imagen, Matrix filtro)
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

    int result[imagen.cols][imagen.rows];     

    Matrix result_matrix = Matrix(imagen.cols, imagen.rows);

    mitad = length(kernel) / 2;

    for (i = 0; i < imagen.rows; ++i) // Filas
    {
        for (j = 0; j < imagen.cols; ++j) // Columnas
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

                    if (ii >= 0 && ii <  imagen.rows && jj >= 0 && jj <  imagen.cols) // validar limites de la imagen 00000
                    {
                        acumulador += image[ii][jj] * kernel[mm][nn];
                    }                        
                }
            }
            result[i][j] = acumulador;
        }
    }

    for (int i = 0; i < result_matrix.cols; i++){ //Llenar Matrix para retornar
        for (int j = 0; j < result_matrix.rows; j++){
            result_matrix.set_value(i, j, result[i][j]); 
        }
    }            

    return result_matrix;
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
