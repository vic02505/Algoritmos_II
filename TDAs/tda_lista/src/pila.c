#include "pila.h"
#include "lista.h"

struct _pila_t{
    lista_t* lista;
};


pila_t* pila_crear(){
    
    pila_t* pila = calloc(1, sizeof(pila_t));

    if(!pila){
        return NULL;
    }

    pila->lista = lista_crear();

    if(!pila->lista){
        free(pila);
        return NULL;
    }

    return pila;
}


pila_t* pila_apilar(pila_t* pila, void* elemento){

    if(!pila){
        return NULL;
    }
    
    pila_t* pila_apilada = pila;
    lista_t* lista_auxiliar;
    lista_auxiliar = lista_insertar(pila->lista, elemento);

    if(!lista_auxiliar){
        return NULL;
    }

    pila_apilada->lista = lista_auxiliar;

    return pila_apilada;
}


void* pila_desapilar(pila_t* pila){

    if(!pila){
        return NULL;
    }

    return lista_quitar(pila->lista);
}


void* pila_tope(pila_t* pila){

    if(!pila || lista_vacia(pila->lista)){
        return NULL;
    }

    return lista_ultimo(pila->lista);
}


size_t pila_tamanio(pila_t* pila){
    
    if(!pila){
        return 0;
    }
    
    return pila->lista->cantidad;
}


bool pila_vacia(pila_t* pila){

    if(!pila || !pila->lista){
        return true;
    }   

    //return pila->lista->cantidad;
    return lista_vacia(pila->lista);
}


void pila_destruir(pila_t* pila){

    if(!pila){
        return;
    }

    lista_destruir(pila->lista);
    free(pila);
}