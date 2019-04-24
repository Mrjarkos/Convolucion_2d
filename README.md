# Speed Up de algoritmo de Convolucion de imágenes .bmp en 2d

Alberto Cabuya\
Javier Cárdenas\
Brayan Roncancio\

## Resumen
En el presente documento se realizó la compararción del`Speed Up` teórica vs experimental de un algoritmo de convolución de imágenes con formato `.bmp` desde 1 hasta 16 hilos, en un computador con procesador `Intel Core i5-8300HQ` de 2.3Ghz de velocidad, con `4 núcleos físicos` y `8 virtuales`. El experimento se realizó con una imagen de 3552x2000 pixeles y con un filtro de desenfoque de orden 20. Sin embargo el código cuenta con funciones para implementar cualquier filtro de orden n y con cualquier imagen .bmp con formato y dimensiones wxh. Tambien se puede ejecutar con N hilos. Dentro de los resultados más importantes se econtró que el speed up fue `lineal` hasta 4 hilos que es el número de núcleos físicos de la máquina, tal como se esperó. El speed Up aumentó sutilmente hasta 8 hilos que es el número de núcleos virtuales de la máquina. De este número hasta 16 hilos, no hubo mayor cambio.

## Introduccion
La convolución que involucra señales unidimensionales se conoce como convolución 1D o simplemente convolución. De lo contrario, si la convolución se realiza entre dos señales que se extienden a lo largo de dos dimensiones mutuamente perpendiculares (es decir, si las señales son de naturaleza bidimensional), se la denominará convolución 2D. Este concepto se puede ampliar para incluir señales multidimensionales, debido a las cuales podemos tener convolución multidimensional.\
En el dominio digital, la convolución se realiza multiplicando y acumulando los valores instantáneos de las muestras superpuestas correspondientes a dos señales de entrada, una de las cuales se invierte. Esta definición de convolución 1D es aplicable incluso para convolución 2D, excepto que, en este último caso, una de las entradas se invierte dos veces.\
Este tipo de operación se usa ampliamente en el campo del procesamiento de imágenes digitales en el que la matriz 2D que representa la imagen se convendrá con una matriz comparativamente más pequeña llamada kernel 2D.\
Un filtro de imagen es un procedimiento que se aplica a una imagen para resaltar o mejorar algunas características de la misma, para lograr esto se modifica la matriz que compone la imagen aplicándole un determinado procedimiento, en este tutorial estudiaremos el procedimiento llamado convolución de matrices.\

En este documento se desarrolla un programa que realiza una convolción entre una imagen y un filtro predefinido y se realiza la comparacion en tiempo de procesamiento de la implementacion paralelizada con N hilos.

## Objetivos

### Generales

* Realizar un programa en C++ o, que permita leer una imagen del sistema de archivos, y aplicarle un filtro cualquiera cd mínimo 5x5, a través de la implementación paralela de una convolución 2D.

* Calcular el Speed Up del programa para N hilos y compararlo con el Speed Up teórico.

### Especificos

* Leer una imagen tipo `.bmp` almacenada en una ruta del sistema de archivos.

* Aplicar un filtro por color RGB a la imagen mediante convolucion 2D.

* Almacenar la imagen procesada en el mismo formato en el que se lee.

* Paralelizar el programa mediante implementación de hilos con `POSIX`.

## Planteamiento del Problema


## Estructura del Programa


## Desarrollo


## Resultados


## Conclusiones

## Referencias

* https://www.allaboutcircuits.com/technical-articles/two-dimensional-convolution-in-image-processing/
