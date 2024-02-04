# Descripción

Trabajos prácticos realizados con el fin de demostrar la aplicación de un concepto (para tener más
información detallada sobre los TPs se recomienda revisar el informe y enunciado de cada uno de ellos).

La nota de los TPs es un valor numérico entre 0 y 2, siendo 0 el valor mínimo, y
2 el valor máximo.

-TP0: Tiene un error en una de las pruebas. Al parecer es un caso borde, al ser opcional no me tome el tiempo
de revisarlo en detalle. Este TP buscaba dar una introducción al manejo de la memoria dinámica en C, en él se podrá encontrar el código de un split para una cadena de caracteres.

-TP1: La idea era la de actualizar el arcaico sistema de pacientes (una libreta y un lapiz) de un hospital de pokemones a uno más tecnológico. Para tal fin se disponía de una serie de archivos en formato .csv cargados con la información de los pacientes del hospital. El objetivo era el de crear un programa que leyese cada archivo, y recogiese la información pertinente de cada línea (un paciente) para cargarla al nuevo sistema.

NOTA: El TP1 tiene problemas con permisos al momento de correr el makefile.

La estructura básica del nuevo sistema fue provista por la cátedra. El objetivo del TP era el de crear la funciones necesarias para leer los archivos y moverse sobre las estructuras provistas de forma correcta. Todo esto haciendo un correcto uso de la memoria dinámica.

-TP2: Su objetivo era el de crear como programa de consola a un simulador de atención de pokemones para las enfermeras del hospital. El TP requería hacer uso del hospital creado en el primer TP de modo que sirviese como base de datos para el simulador. 

Este trabajo presento como reto la necesidad de modificar el sistema de pacientes creados en el TP1 de acuerdo a los nuevos requerimientos del problema. Esto implicó, tener que modificar los registros del primer TP, agregando o eliminando nuevos campos, e incluyendo algunos de los TDAs hechos durante la cursada para almacenar y acceder información de forma más efectiva.

La elección de los TDAs no debía ser abitraria, sino que debía estar justificada en base a la complejidad algorítmica, a la eficiencia, y legiblidad del código.


Buscan resolver un problema asociado al sistema de pacientes a un hospital de pokemones. El TP2 es una continuación del TP1. La idea de estos TPs era la de usar TDAs (en particular, en el TP2) para crear el sistema más adecuado para guardar a los pacientes y atenderlos (gestionar el sistema informático del hospital). La combinación de los TDAs escogida debía ser la mejor en términos de complejidad algorítmica y de simplicidad del código.


# Ejecución

-TP0: basta con escribir make desde dicha carpeta y correr las pruebas. 

-TP1: se ejecuta haciendo make desde la subcarpeta TP1/Implementacion (como resultado se correran las pruebas).

-TP2: Para ejecutarlo es necesario compilar antes los archivos fuente. Para ello se debe ejecutar la siguiente línea de comandos desde la carpeta TP2

    gcc main.c src/abb.c src/heap.c src/hospital.c src/lista.c src/simulador.c src/split.c -o simulador.exe

Luego basta con ejecutar el archivo simulador.exe

    ./simulador.exe

Respecto a las pruebas es necesario compilar los siguientes archivos fuente (desde la carpeta TP2):

    gcc pruebas.c src/abb.c src/heap.c src/hospital.c src/lista.c src/simulador.c src/split.c -o pruebas.exe

Luego para correrlas hay que ejecutar el archivo pruebas.exe

    ./pruebas.exe
    Las pruebas son de autoría propia.