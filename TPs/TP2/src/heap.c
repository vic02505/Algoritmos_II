#include"heap.h"
#include<stdlib.h>
#include<stdbool.h>

struct _heap_t{
    void** heap;
    size_t tamanio_heap;
    size_t tope_heap;
    int (*comparador_de_elementos_del_heap)(void*, void*); //-> < 0 si el primer elemento es menor al segundo, > 0 si pasa lo contrario.
};


/*
Pre-condiciones: vector_a_swapear no debe ser NULL.

Post-condiciones: Intercambia el contenido del vector de pos_a con el de pos_b,
y el de pos_b con el pos_a.
*/
void swap(void** vector_a_swapear, size_t pos_a, size_t pos_b){
    void* aux = vector_a_swapear[pos_a];
    vector_a_swapear[pos_a] = vector_a_swapear[pos_b];
    vector_a_swapear[pos_b] = aux; 
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve la posicion del nodo padre del nodo al que posicion
haga referencia.
*/
size_t posicion_nodo_padre(size_t posicion){
    return((posicion - 1)/2);
}


/*
Pre-condiciones: No tiene.

Post-condicione: Devuelve true si un heap esta vacio o no existe.
*/
bool heap_vacio(heap_t* heap){
    return((heap == NULL) || (heap->heap == NULL) || (heap_tamanio(heap) == 0));
}


/*
Pre-condiciones: 
-heap_a_usar no debe ser NULL ni estar vacio.
-posicion debe ser una posicion valida del heap.

Post-condiciones: Hace sift_up del elemento en "posicion" del heap.
*/
void sift_up(heap_t* heap_a_usar, size_t posicion){

    if(heap_vacio(heap_a_usar) || heap_a_usar->tamanio_heap  == 0 || posicion == 0){
        return;
    }

    size_t pos_nodo_padre = posicion_nodo_padre(posicion);

    if(heap_a_usar->comparador_de_elementos_del_heap(heap_a_usar->heap[posicion], heap_a_usar->heap[pos_nodo_padre]) < 0){
        swap(heap_a_usar->heap, posicion, pos_nodo_padre);
        sift_up(heap_a_usar, pos_nodo_padre);
    }

}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve la posicion del hijo izquierdo a la que posicion_nodo hace referencia.
*/
size_t posicion_hijo_izquierdo(size_t posicion_nodo){
    return((posicion_nodo*2) + 1);
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve la posicion del hijo derecho a la que posicion_nodo hace referencia.
*/
size_t posicion_hijo_derecho(size_t posicion_nodo){
    return ((posicion_nodo*2) + 2);
}


/*
Pre-condiciones: heap_a_usar no debe ser NULL ni estar vacio.

Post-condiciones: posicion debe hacer referencia a una posicion valida de un elemento dentro del heap.
*/
void sift_down(heap_t* heap_a_usar, size_t posicion){

    if(heap_vacio(heap_a_usar)){
        return;
    }

    size_t pos_hijo_izquierdo = posicion_hijo_izquierdo(posicion);

    if(pos_hijo_izquierdo >= heap_a_usar->tope_heap){
        return;
    }

    //pos_aux sirve para guardar al menor elemento de los hijos de un nodo.
    size_t pos_aux = pos_hijo_izquierdo;
    size_t pos_hijo_derecho = posicion_hijo_derecho(posicion);

    if(pos_hijo_derecho < heap_a_usar->tope_heap){

        if(heap_a_usar->comparador_de_elementos_del_heap(heap_a_usar->heap[pos_hijo_derecho], heap_a_usar->heap[pos_aux]) < 0);
        pos_aux = pos_hijo_derecho;
    }

    if(heap_a_usar->comparador_de_elementos_del_heap(heap_a_usar->heap[posicion], heap_a_usar->heap[pos_aux]) > 0){
        swap(heap_a_usar->heap, posicion, pos_aux);
        sift_down(heap_a_usar, pos_aux);
    }
}


//Implementaicon del heap:

heap_t* heap_crear(int (*comparador_de_elementos)(void*, void*), size_t tamanio_inicial){

    if(!comparador_de_elementos){
        return NULL;
    }

    heap_t* heap_a_crear = calloc(1, sizeof(heap_t));

    if(!heap_a_crear){
        return NULL;
    }

    heap_a_crear->heap = malloc(tamanio_inicial*sizeof(void*));

    if(!heap_a_crear->heap){
        free(heap_a_crear);
        return NULL;
    }

    heap_a_crear->tamanio_heap = tamanio_inicial;
    heap_a_crear->comparador_de_elementos_del_heap = comparador_de_elementos;

    return heap_a_crear;
}


size_t heap_tamanio(heap_t* heap_a_revisar){

    if(!heap_a_revisar){
        return 0;
    }

    return heap_a_revisar->tope_heap;
}


int heap_insertar(heap_t* heap_a_insertar, void* elemento_a_insertar){

    if(!heap_a_insertar){
        return -1;
    }

    if(heap_a_insertar->tamanio_heap == heap_a_insertar->tope_heap){

        void** heap_auxiliar = realloc(heap_a_insertar->heap, ((heap_a_insertar->tope_heap)+1)*sizeof(void*));

        if(!heap_auxiliar){
            return -1;
        }

        heap_a_insertar->heap = heap_auxiliar;
        heap_a_insertar->tamanio_heap++;
    }

    heap_a_insertar->heap[heap_a_insertar->tope_heap] = elemento_a_insertar;
    sift_up(heap_a_insertar, heap_a_insertar->tope_heap);
    heap_a_insertar->tope_heap++;

    return 0;
}


void* heap_extraer_raiz(heap_t* heap_a_extraer){

    if(heap_vacio(heap_a_extraer)){
        return NULL;
    }

    void* raiz = heap_a_extraer->heap[0];
    swap(heap_a_extraer->heap, 0 , heap_a_extraer->tope_heap-1);
    heap_a_extraer->heap = realloc(heap_a_extraer->heap, (heap_a_extraer->tamanio_heap - 1)*sizeof(void*));

    heap_a_extraer->tope_heap--;

    if(heap_a_extraer->tope_heap > 0){
        sift_down(heap_a_extraer, 0);
    }

    heap_a_extraer->tamanio_heap--;

    return raiz;
}


void* heap_raiz(heap_t* heap){

    if(!heap){
        return NULL;
    }

    return heap->heap[0];
}


void heap_destruir(heap_t* heap_a_destruir){
    
    if(!heap_a_destruir){
        return;
    }

    if(!heap_vacio(heap_a_destruir) || heap_tamanio(heap_a_destruir) == 0){
        free(heap_a_destruir->heap);
    }
        
    free(heap_a_destruir);
}