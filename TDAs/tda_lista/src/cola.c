#include "cola.h"
#include "lista.h"


struct _cola_t{
    lista_t* lista;
};


cola_t* cola_crear(){

    cola_t* cola = calloc(1, sizeof(cola_t));

    if(!cola){
        return NULL;
    }

    cola->lista = lista_crear();

    if(!cola->lista){
        free(cola);
        return NULL;
    }

    return cola;
}


cola_t* cola_encolar(cola_t* cola, void* elemento){

    if(!cola){
        return NULL;
    }

    cola_t* cola_a_encolar = cola;
    lista_t* lista_auxiliar = lista_insertar(cola_a_encolar->lista, elemento);

    if(!lista_auxiliar){
        return NULL;
    }

    cola_a_encolar->lista = lista_auxiliar;

    return cola_a_encolar;
}


void* cola_desencolar(cola_t* cola){

    if(!cola){
        return NULL;
    }

    void* elemento_desencolado = lista_quitar_de_posicion(cola->lista, 0);

    return elemento_desencolado;
}


void* cola_frente(cola_t* cola){

    if(!cola){
        return NULL;
    }

    return lista_primero(cola->lista);
}


size_t cola_tamanio(cola_t* cola){
    
    if(!cola){
        return 0;
    }
    
    return cola->lista->cantidad;
}


bool cola_vacia(cola_t* cola){
    
    if(!cola || !cola->lista){
        return true;
    }
    
    return lista_vacia(cola->lista);
}


void cola_destruir(cola_t* cola){

    if(!cola){
        return;
    }

    lista_destruir(cola->lista);
    free(cola);
}