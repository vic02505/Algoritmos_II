# Descripción

TDAs (Tipos de datos abstractos). Esta parte del repositorio contiene la implementación de distintos tipos de TDAs. En ella se podrá encontrar:

-Lista (que a su vez contiene una implementación de una cola y una pila).
-ABB (árbol binario de búsqueda).
-Hash.

La implementación de cada TDA se encuentra contenido en la subcarpeta *src* de cada uno de ellos. 

    NOTA: Cada TDA hace uso de la memoria dinámica provista por el sistema operativo.

La nota de los TDAs es un valor numérico entre 0 y 2, siendo 0 el valor mínimo, y
2 el valor máximo.

# Ejecución 

Si se desea ejecutar alguno de los TDAs basta con ejecutar el comando "make" en la carpeta correspondiente a cada TDA (ejemplo: desde /TDAs/ABB, no desde /TDAs/ABB/src) . Vale añadir que lo que se hace al correr un TDA de este repositorio es ejecutar las pruebas unitarias del mismo (para poder ver una aplicación de los TDAs se puede revisar la carpeta TPs de Algoritmos_II).  

En cada TDA existe un archivo llamado "pruebas.c". El archivo de pruebas no es más que un programa que hace una inclusión de algún TDA y realiza pruebas unitarias sobre cada una de las funciones del mismo. Este archivo puede ser consultado si se desea ver un uso en particular de los TDAs, pero vale añadir que el código contenido en el estuvo diseñado para hacer pruebas, por lo que su organización y seguimiento de buenas practicas no son lo más adecuados. 

