/*
Algoritmo de ordenamiento: Quick Sort.
Autor: Victor Zacarias.
Ultima Actualizacion: 22-11-2021.
*/
#include<stdio.h>

void imprimir_vector(int* vector, size_t tope){

    printf("\n");

    printf("-");
    for(size_t i = 0; i < tope; i++){   
        printf("%i-", vector[i]);
    }

    printf("\n");
}


void swap(int* vector, size_t posicion_a, size_t posicion_b){

    int aux = vector[posicion_a];
    vector[posicion_a] = vector[posicion_b];
    vector[posicion_b] = aux;
}


size_t pivotear(int* vector, size_t tope){

    size_t posicion_pivote = tope-1;    
    size_t posicion_final_del_pivote = 0;

    size_t posicion_actual = 0;
    while(posicion_actual < tope){

        if(vector[posicion_actual] < vector[posicion_pivote]){
            
            swap(vector, posicion_actual, posicion_final_del_pivote);
            posicion_final_del_pivote++;
        }

        posicion_actual++;
    }

    swap(vector, posicion_final_del_pivote, posicion_pivote);

    return posicion_final_del_pivote;
}


void quick_sort(int* vector, size_t tope){

    if(tope <= 1){
        return;
    }

   size_t posicion_pivote = pivotear(vector, tope);

    quick_sort(vector, posicion_pivote);
    quick_sort(vector+posicion_pivote+1, tope-(posicion_pivote+1));
}


int main(){

    int vector_a_ordenar[8] = {1, 4, 20, 9, 12, 3, 8, 6};

    printf("Vector antes de aplicarle quick_sort:\n");
    imprimir_vector(vector_a_ordenar, 8);

    quick_sort(vector_a_ordenar, 8);

    printf("\n");
    printf("Vector despues de aplicarle quick_sort:\n");
    imprimir_vector(vector_a_ordenar, 8);

    return 0;
}