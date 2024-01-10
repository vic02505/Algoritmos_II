#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include<stdbool.h>


lista_t* lista_crear(){

    lista_t* lista = calloc(1, sizeof(lista_t));

    if(!lista){
        return NULL;
    }

    return lista;
}


lista_t* lista_insertar(lista_t* lista, void* elemento){

    if(!lista){
        return NULL;
    }

    nodo_t* nodo_auxiliar;

    if(lista_vacia(lista)){

        nodo_auxiliar = calloc(1, sizeof(nodo_t));

        if(!nodo_auxiliar){
            return NULL;
        }

        nodo_auxiliar->elemento = elemento;
        lista->nodo_inicio = nodo_auxiliar;
        lista->nodo_fin = nodo_auxiliar;
        lista->cantidad++;
    }
    else{

        nodo_auxiliar = calloc(1, sizeof(nodo_t));

        if(!nodo_auxiliar){
            return NULL;
        }

        nodo_auxiliar->elemento = elemento;

        lista->nodo_fin->siguiente = nodo_auxiliar;
        lista->nodo_fin = nodo_auxiliar;
        lista->cantidad++;
    }

    return lista;
}


lista_t* lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

    if(!lista){
        return NULL;
    }

    if(lista_vacia(lista)){
        return lista_insertar(lista, elemento);
    }

    nodo_t* nodo_a_insertar = calloc(1, sizeof(nodo_t));
    nodo_t* nodo_auxiliar;
    
    if(!nodo_a_insertar){
        return NULL;
    }
    
    nodo_a_insertar->elemento = elemento;

    if(posicion == 0){

        nodo_auxiliar = lista->nodo_inicio;
        nodo_a_insertar->siguiente = nodo_auxiliar;
        lista->nodo_inicio = nodo_a_insertar;
        lista->cantidad++;
    }
    else if(posicion >= lista->cantidad){
        free(nodo_a_insertar);
        return lista_insertar(lista, elemento);
    }
    else{

        nodo_auxiliar = lista->nodo_inicio;
        size_t i = 0;

        while(i < posicion-1){

            nodo_auxiliar = nodo_auxiliar->siguiente;
            i++;
        }

        nodo_a_insertar->siguiente = nodo_auxiliar->siguiente;
        nodo_auxiliar->siguiente = nodo_a_insertar;
        lista->cantidad++;
    }

    return lista;
}


void* lista_quitar(lista_t* lista){

    if(lista == NULL || lista_vacia(lista)){
        return NULL;
    }

    nodo_t* nodo_siguiente = lista->nodo_inicio;
    size_t i = 0;

    while(i < lista->cantidad-2 && lista->cantidad > 1){

        nodo_siguiente = nodo_siguiente->siguiente;

        i++;
    }

    void* elemento_a_eliminar = NULL;

    if(lista->cantidad != 1){
        elemento_a_eliminar = lista->nodo_fin->elemento;
        free(lista->nodo_fin);
        nodo_siguiente->siguiente = NULL;
        lista->nodo_fin = nodo_siguiente;
        lista->cantidad--;
    }
    else if(lista->cantidad == 1){
        elemento_a_eliminar = nodo_siguiente->elemento;
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        free(nodo_siguiente);
        lista->cantidad--;
    }

    return elemento_a_eliminar;
}


void* lista_quitar_de_posicion(lista_t* lista, size_t posicion){
    
    if(!lista || lista_vacia(lista)){
        return NULL;
    }

    void* elemento_eliminado = NULL;
    
    if(lista->cantidad == 1 || posicion >= lista->cantidad){
        elemento_eliminado = lista_quitar(lista);
    }
    else{

        nodo_t* nodo_a_eliminar = NULL;
        nodo_t* nodo_anterior_al_eliminar = NULL;
        nodo_t* nodo_aux = lista->nodo_inicio;
        size_t i = 0;

        if(posicion != 0){

            while(i < posicion-1){
            
                nodo_aux = nodo_aux->siguiente;
                i++;
            }

            nodo_anterior_al_eliminar = nodo_aux;
            nodo_a_eliminar = nodo_anterior_al_eliminar->siguiente;
            nodo_anterior_al_eliminar->siguiente = nodo_a_eliminar->siguiente;
            lista->cantidad--;
            elemento_eliminado = nodo_a_eliminar->elemento;
            free(nodo_a_eliminar);
        }
        else{

            nodo_a_eliminar = lista->nodo_inicio;
            elemento_eliminado = nodo_a_eliminar->elemento;
            lista->nodo_inicio = nodo_a_eliminar->siguiente;
            lista->cantidad--;
            free(nodo_a_eliminar);
        }
    }

    return elemento_eliminado;
}


void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

    if(!lista){
        return NULL;
    }

    if(posicion >= lista->cantidad){
        return NULL;
    }
    void* elemento_buscado = NULL;

    if(posicion == 0){
        elemento_buscado = lista->nodo_inicio->elemento;
    }
    else if(posicion == lista->cantidad-1){
        elemento_buscado = lista->nodo_fin->elemento;
    }
    else{

        size_t i = 0;
        nodo_t* nodo_auxiliar = lista->nodo_inicio;

        while(i < posicion){
            nodo_auxiliar = nodo_auxiliar->siguiente;
            i++;
        }

        elemento_buscado = nodo_auxiliar->elemento;
    }

    return elemento_buscado;
}


void* lista_primero(lista_t* lista){

    if(!lista || lista->cantidad == 0){
        return NULL;
    }

    return lista->nodo_inicio->elemento;
}

void* lista_ultimo(lista_t* lista){
    
    if(!lista || lista->cantidad == 0){
        return NULL;
    }
    
    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){

    if(!lista){
        return true;
    }

    return (lista->cantidad == 0);
}

size_t lista_tamanio(lista_t* lista){

    if(!lista){
        return 0;
    }
     
    return lista->cantidad;
}

void lista_destruir(lista_t* lista){

    if(lista == NULL){
        return;
    }

    if(lista_vacia(lista)){
        free(lista);
        return;
    }

    nodo_t* nodo_actual = lista->nodo_inicio;
    nodo_t* nodo_siguiente = lista->nodo_inicio->siguiente;

    while(nodo_siguiente != NULL){

        free(nodo_actual);

        nodo_actual = nodo_siguiente;
        nodo_siguiente = nodo_actual->siguiente;
    }
    free(nodo_actual);
    free(lista);
}


lista_iterador_t* lista_iterador_crear(lista_t* lista){

    if(!lista){
        return NULL;
    }

    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));

    if(!iterador){
        free(iterador);
        return NULL;
    }

    iterador->corriente = lista->nodo_inicio;
    iterador->lista = lista;

    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

    if(!iterador){
        return false;
    }
    
    if(!iterador->corriente){
        return false;
    }

    return true;
}


bool lista_iterador_avanzar(lista_iterador_t* iterador){

    if(!iterador){
        return false;
    }

    if(!iterador->corriente){
        return false;
    }

    if(!iterador->corriente->siguiente){
        iterador->corriente = iterador->corriente->siguiente;
        return false;
    }

    iterador->corriente = iterador->corriente->siguiente;

    return true;
}


void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    
    if(!iterador){
        return NULL;
    }

    if(!iterador->corriente){
        return NULL;
    }

    return iterador->corriente->elemento;
}


void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}


size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

    if(!lista || !funcion || !contexto){
        return 0;
    }

    bool se_sigue_recorriendo = true;
    size_t i = 0;
    size_t cantidad_de_elementos_recorridos = 0;
    nodo_t* nodo_auxiliar = lista->nodo_inicio;


    while(i < lista->cantidad && se_sigue_recorriendo){

        if(!funcion(nodo_auxiliar->elemento, contexto)){
            se_sigue_recorriendo = false;
        }

        cantidad_de_elementos_recorridos++;
        nodo_auxiliar = nodo_auxiliar->siguiente;
        i++;
    }

    return cantidad_de_elementos_recorridos;
}
