
#include "main.h"

#define origen "./Imagen.bmp"
#define destino "./ImagenConvolucionada.bmp"

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
    printf("\nConvolucion 2D\n");

    printf("\nAbriendo Imagen...\n");
    img=LoadBMP(origen, &info);

    printf("\nCreando Matrices RGB...\n");
    Matrix R = Matrix(info.height, info.width);
    Matrix G = Matrix(info.height, info.width);
    Matrix B = Matrix(info.height, info.width);

    printf("Copiando valores a RGB...\n");
     for (int i=0; i<info.height; i++)
       {
          for (int j=0; j<info.width; j++)
            {
            R.set_value(i, j, (int)img[3*(j+i*info.width)+2]);
            G.set_value(i, j, (int)img[3*(j+i*info.width)+1]);
            B.set_value(i, j, (int)img[3*(j+i*info.width)]);
        }
    }
    printf("Listo...\n");

    printf("\nFiltro:\n");
    int n = 10;
    Matrix Filtro = Matrix(n, n);
    Filtro.full_in_matrix(1);
    
   // int filter[5][5] = {{-1,1,1,1,1},{-1,0,0,0,1},{-1,0,0,0,1},{-1,0,0,0,1},{-1,1,1,1,1}};

/*
    for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                Filtro.set_value(j,i, filter[i][j]);
            }
        }
        */
    Filtro.print();

    t_ini2 = clock();
    printf("\nCalculando Convolucion RGB\n");
    R = convolucion(R, Filtro, numThreads);
    G = convolucion(G, Filtro, numThreads);
    B = convolucion(B, Filtro, numThreads);

    t_fin = clock();
    printf("\nEjecucion con %i hilos", numThreads);
    secs = (double)(t_fin - t_ini1) / CLOCKS_PER_SEC;
    printf("\nTotal Time Programm = %.16g milisegundos\n", secs * 1000.0/3);
    secs = (double)(t_fin - t_ini2) / CLOCKS_PER_SEC;
    printf("Total Time Convolution= %.16g milisegundos\n", secs * 1000.0/3);

    printf("Almacenando matriz Convolucionada\n");
     for (int i=0; i<info.height; i++)
       {
          for (int j=0; j<info.width; j++)
            {
            img[3*(j+i*info.width)+2] = (unsigned char)R.get_value(i, j);
            img[3*(j+i*info.width)+1] = (unsigned char)G.get_value(i, j);
            img[3*(j+i*info.width)] = (unsigned char)B.get_value(i, j);
        }
    }
    SaveBMP(destino, &info, img);
    delete(img);
    return 0;
}

Matrix convolucion (Matrix imagen, Matrix filtro, int numThreads)
{   
    pthread_t threads[numThreads];
    pthread_attr_t attr[numThreads];
    Param_Threads data[numThreads];

    for(int i=0; i<numThreads; i++){
        data[i].imagen = imagen;
        data[i].filtro = filtro;
        data[i].resultado = Matrix(imagen.rows, imagen.cols);
        data[i].threads = numThreads;
        data[i].id = i;
        pthread_attr_init(&attr[i]);
        pthread_create(&threads[i], &attr[i], Paralell_Proces, &data[i]);
    }

    Matrix resultado = Matrix(imagen.rows, imagen.cols);
    for(int i=0; i<numThreads; i++){
        pthread_join(threads[i], NULL);
        resultado = data[i].resultado.sum_to(resultado);
    }
   return resultado;
}

void* Paralell_Proces(void *param){

    int mitad, i,j,m,n,mm,nn,ii,jj, acumulador;
    Matrix imagen = ((Param_Threads*)param)->imagen;
    Matrix filtro =  ((Param_Threads*)param)->filtro;
    Matrix resultado = ((Param_Threads*)param)->resultado;
    mitad = filtro.rows / 2;
    int threads =  ((Param_Threads*)param)->threads;
    int id = ((Param_Threads*)param)->id;
    int sum = filtro.sum_elements();
    sum=sum==0?1:sum;

    printf("Jajaja\n");

    for (i = imagen.rows*(id/threads); i < imagen.rows*((id+1)/threads); ++i) // Filas
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
                                        if (ii >= imagen.rows*(id/threads) && ii <  imagen.rows*((id+1)/threads) && jj >= 0 && jj <  imagen.cols) // validar limites de la imagen 00000
                                        {
                                            acumulador += imagen.get_value(ii, jj)* filtro.get_value(mm, nn);
                                        }                        
                                }
                        }
                        resultado.set_value(i, j, acumulador/sum);
                    }
        }
    pthread_exit(0);
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

unsigned char calculaColorMedio(unsigned char *pixel)
{
  unsigned media = (*pixel + *(pixel+1) + *(pixel+2)) / 3;

  return (unsigned char) media;
}

unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader)
{

  FILE *f;
  bmpFileHeader header;
  unsigned char *imgdata;
  uint16_t type;
  f=fopen (filename, "r");
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
  printf("leido: %d\n", (int)fread(imgdata, bInfoHeader->imgsize,1, f));
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
  header.offset=sizeof(bmpFileHeader)+sizeof(bmpInfoHeader)+2;
  type=0x4D42;
  fwrite(&type, sizeof(type),1,f);
  fwrite(&header, sizeof(bmpFileHeader),1,f);
  fwrite(info, sizeof(bmpInfoHeader),1,f);
  fwrite(imgdata, info->imgsize, 1, f);
  fclose(f);
}