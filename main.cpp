
#include "main.h"

#define archivo "/home/mrjarkos/Pictures/Panda.bmp"

int main(int argc, char** argv) {

    bmpInfoHeader info;  
    unsigned char *img;
    unsigned char color[3];
    unsigned char media;
    
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

    t_ini1 = clock();

    printf("Convolucion 2D\n");

/*    Filtro.set_value(1,1,4);
    Filtro.set_value(1,2,4);
    Filtro.set_value(1,3,4);

    Filtro.set_value(2,1,4);
    Filtro.set_value(2,2,12);
    Filtro.set_value(2,3,4);

    Filtro.set_value(3,1,4);
    Filtro.set_value(3,2,4);
    Filtro.set_value(3,3,4);
*/

    printf("Abriendo Imagen...\n");
    img=LoadBMP(archivo, &info);

    printf("Creando Matrices RGB...\n");
    Matrix R = Matrix(info.height, info.width);
    Matrix G = Matrix(info.height, info.width);
    Matrix B = Matrix(info.height, info.width);
    //R.full_in_matrix(100);

    printf("Copiando valores a RGB...\n");
     for (int i=0; i<info.height; i++)
       {
          for (int j=0; j<info.width; j++)
            {
        //    Imagen.set_value(i, j, img[(j+i*info.width)]);
            R.set_value(i, j, (int)img[3*(j+i*info.width)+2]);
            G.set_value(i, j, (int)img[3*(j+i*info.width)+1]);
            B.set_value(i, j, (int)img[3*(j+i*info.width)]);
        }
    }
    
    printf("Listo...\n");
    //printf("\nImagen:\n");
   // Imagen.print();

    printf("\nFiltro:\n");
    int n = 3;
    Matrix Filtro = Matrix(n, n);
    Filtro.full_in_matrix(1);
    Filtro.print();


    t_ini2 = clock();
    printf("Calculando Convolucion RGB\n");
    R = convolucion(R, Filtro, numThreads);
    G = convolucion(G, Filtro, numThreads);
    B = convolucion(B, Filtro, numThreads);
    //Matrix Resultado = convolucion(Imagen, Filtro, numThreads);
    //printf("\nImagen Convolucionada:\n");
    //Resultado.print();
    //B = Matrix(info.height, info.width);
    //R = Matrix(info.height, info.width);
    //G = Matrix(info.height, info.width);

    printf("Almacenando matriz Convolucionadau\n");
     for (int i=0; i<info.height; i++)
       {
          for (int j=0; j<info.width; j++)
            {
            img[3*(j+i*info.width)+2] = (unsigned char)R.get_value(i, j);
            img[3*(j+i*info.width)+1] = (unsigned char)G.get_value(i, j);
            img[3*(j+i*info.width)] = (unsigned char)B.get_value(i, j);
      //      img[j+i*info.width] = Resultado.get_value(i, j);    
        }
    }
    SaveBMP("/home/mrjarkos/Pictures/J.bmp", &info, img);
    delete(img);


    printf("\nMatrix: \n");
    Matrix matrix = Matrix(3,5);
    matrix.full_in_matrix();
    matrix.print();

    printf("\nConvolucion \n");
    matrix = convolucion(matrix, Filtro, numThreads);
    matrix.print();

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

    Matrix result_matrix = Matrix(imagen.rows, imagen.cols);

    mitad = filtro.rows / 2;
    /*pthread_t threads[numThreads];
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
*/
int offset = 0;
int threads = 1;

 for (i = offset; i < imagen.rows/threads + offset; ++i) // Filas
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
            result_matrix.set_value(i, j, acumulador);
        }
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

unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader)
{

  FILE *f;
  bmpFileHeader header;
  unsigned char *imgdata;
  uint16_t type;
  f=fopen (filename, "r");
  /* handle open error */
  fread(&type, sizeof(uint16_t), 1, f);
  if (type !=0x4D42)
    {
      fclose(f);
      return NULL;
    }
  fread(&header, sizeof(bmpFileHeader), 1, f);

  printf ("size: %u\n", header.size);
  printf ("offs: %u\n", header.offset);
  fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);
  printf ("header size:      %d\n", bInfoHeader->headersize);
  printf ("image width:      %d\n", bInfoHeader->width);
  printf ("image height:     %d\n", bInfoHeader->height);
  printf ("colour planes:    %d\n", bInfoHeader->planes);
  printf ("bpp:              %d\n", bInfoHeader->bpp);
  printf ("compress:         %d\n", bInfoHeader->compress);
  printf ("imgage size:      %d\n", bInfoHeader->imgsize);
  printf ("bpmx:             %d\n", bInfoHeader->bpmx);
  printf ("bpmy:             %d\n", bInfoHeader->bpmy);
  printf ("colors:           %d\n", bInfoHeader->colors);
  printf ("important colors: %d\n", bInfoHeader->imxtcolors);
  imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);
  fseek(f, header.offset, SEEK_SET);
  printf("leido: %d\n", fread(imgdata, bInfoHeader->imgsize,1, f));
  fclose(f);

  return imgdata;
}

bmpInfoHeader *createInfoHeader(unsigned w, unsigned h, unsigned ppp)
{
  bmpInfoHeader *ih = new bmpInfoHeader;

  ih->headersize=sizeof(bmpInfoHeader);
  ih->width=w;
  ih->height=h;
  ih->planes=1;
  ih->bpp=24;
  ih->compress=0;
  ih->imgsize=w*h*3;        /* 3 bytes por pixel w*h pixels */
  ih->bpmx=(unsigned)round((double)ppp*100/2.54);
  ih->bpmy=ih->bpmx;        /* Misma resolución vertical y horiontal */
  ih->colors=0;
  ih->imxtcolors=0;

  return ih;
}

void SaveBMP(char *filename, bmpInfoHeader *info, unsigned char *imgdata)
{
  bmpFileHeader header;
  FILE *f;
  uint16_t type;
  
  f=fopen(filename, "w+");
  header.size=info->imgsize+sizeof(bmpFileHeader)+sizeof(bmpInfoHeader);
  /* header.resv1=0; */
  /* header.resv2=1; */
  /* El offset será el tamaño de las dos cabeceras + 2 (información de fichero)*/
  header.offset=sizeof(bmpFileHeader)+sizeof(bmpInfoHeader)+2;
  /* Escribimos la identificación del archivo */
  type=0x4D42;
  fwrite(&type, sizeof(type),1,f);
  /* Escribimos la cabecera de fichero */
  fwrite(&header, sizeof(bmpFileHeader),1,f);
  /* Escribimos la información básica de la imagen */
  fwrite(info, sizeof(bmpInfoHeader),1,f);
  /* Escribimos la imagen */
  fwrite(imgdata, info->imgsize, 1, f);
  fclose(f);
}