/*
Algoritmo de ordenamiento: Merge sort.
Autor: Victor Zacarias.
Ultima actualizacion: 22-11-2021.
*/
#include<stdio.h>

void merge(int* subvector_1, size_t tope_1, int* subvector_2, size_t tope_2){

    int vector_3[tope_1+tope_2];
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    while(i < tope_1 && j < tope_2){

        if(subvector_1[i] <= subvector_2[j]){
            vector_3[k] = subvector_1[i];
            i++;
        }else{
            vector_3[k] = subvector_2[j];
            j++;
        }

        k++;
    }

    while(i < tope_1){
        vector_3[k] = subvector_1[i];
        i++;
        k++;
    }

    while(j < tope_2){
        vector_3[k] = subvector_2[j];
        j++;
        k++;
    }

    for(size_t i = 0; i < tope_1+tope_2; i++){
        subvector_1[i] = vector_3[i];
    }

}


void merge_sort(int* vector_a_ordenar, size_t tope){

    if(tope <= 1){
        return;
    }

    size_t mitad = tope/2;

    merge_sort(vector_a_ordenar, mitad);
    merge_sort(vector_a_ordenar+mitad, tope-mitad);
    merge(vector_a_ordenar, mitad, vector_a_ordenar+mitad, tope-mitad);
}


int main(){

    int vector_a_ordenar[8] = {90, 50, 95, 40, 20, 30, 35, 25};

    printf("------------------------------------------------\n");
    printf("Vector antes de aplicar el merge sort:\n");
    
    printf("-");
    for(int i = 0; i < 8; i++){
        printf("%i-", vector_a_ordenar[i]);
    }
    printf("\n");

    printf("------------------------------------------------\n\n");


    merge_sort(vector_a_ordenar, 8);


    printf("------------------------------------------------\n");
    printf("Vector despues de aplicar el merge sort:\n");
    
    printf("-");
    for(int i = 0; i < 8; i++){
        printf("%i-", vector_a_ordenar[i]);
    }
    printf("\n");

    printf("------------------------------------------------\n\n");
}
