#ifndef HEAP_H_
#define HEAP_H_

#include <stdio.h>

typedef struct _heap_t heap_t;

heap_t* heap_crear(int (*comparador)(void*, void*), size_t tamanio_inicial);

int heap_insertar(heap_t* heap,void* elemento);

void* heap_extraer_raiz(heap_t* heap);

void* heap_raiz(heap_t* heap);

size_t heap_tamanio(heap_t* heap);

void heap_destruir(heap_t* heap);

#endif // HEAP_H_