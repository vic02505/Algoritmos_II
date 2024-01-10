//NOTA: Todas las convenciones tomadas al momento de hacer funciones auxiliares (vease: por que se usaron algunos parametros de un a determinada forma),
//se encuentran explicadas en el infrome de este TDA.

#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

//FUNCIONES PRIVADAS:

/*
Pre-condiciones: abb_nodo debe ser el nodo_raiz del abb cuando se llama a esta funcion por primera vez. destructor es una funcion que se aplica a cada 
elemento del abb, en caso de no querer de usarse, solo debe mandarse NULL en lugar de alguna funcion como parametro.

Post-condiciones: Recorre cada una de los nodos del abb y libera la memoria ocupada por estos. El destructor (si no es NULL) hace una determinada operacion 
sobre cada elemento del abb (el que y como de esta operacion es responsablidad del usuario).
*/
void abb_destruir_raices(nodo_abb_t* abb_nodo, void (*destructor)(void *)){

  if(!abb_nodo){
    return;
  }

  abb_destruir_raices(abb_nodo->izquierda, destructor);
  abb_destruir_raices(abb_nodo->derecha, destructor);

  if(destructor != NULL){
    destructor(abb_nodo->elemento);
  }

  free(abb_nodo);
}


/*
Pre-condiciones: 
-Nodo debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-comparador no debe ser NULL.

Post-condiciones: Recorre recursivamente el abb e inserta un elemento en la posicion correspondiente. Devuelve NULL en caso de error y el abb en caso
de poder hacer la insercion.
*/
nodo_abb_t* insertar_nodo(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){

  nodo_abb_t* nodo_auxiliar = NULL;

  if(!nodo){

    nodo_auxiliar = calloc(1, sizeof(nodo_abb_t));
    
    if(!nodo_auxiliar){
      return NULL;
    }

    nodo_auxiliar->elemento = elemento;
    
    return nodo_auxiliar;
  }

  int comparacion = comparador(elemento, nodo->elemento);

  if(comparacion <= 0){
    nodo->izquierda = insertar_nodo(nodo->izquierda, elemento, comparador);
  }
  else{
   nodo->derecha = insertar_nodo(nodo->derecha, elemento, comparador);
  }

  return nodo;
}


/*
Pre-condiciones: nodo debe ser el nodo_raiz al ser llamado por primera vez. comparador no debe ser NULL.

Post-condiciones: Devuelve elemento si se encuentra en el abb, devuelve NULL en caso contrario.
*/
void* abb_buscar_elemento_en_el_arbol(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){

  if(!comparador){
    return NULL;
  }

  if(!nodo){
    return NULL;
  }

  int comparacion = comparador(elemento, nodo->elemento);

  if(comparacion == 0){
    return nodo->elemento;
  }
  else if(comparacion > 0){
    return abb_buscar_elemento_en_el_arbol(nodo->derecha, elemento, comparador);
  }
  else{
    return abb_buscar_elemento_en_el_arbol(nodo->izquierda, elemento, comparador);
  }

}


/*
Pre-condiciones: 
-nodo_entrada no debe ser NULL y debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-array no debe ser NULL.
-tamanio debe ser mayor a 0.
-elementos_insertados debe ser 0 cuando la funcion es llamada por primera vez.
-posicion debe ser 0 cuando la funcion es llamada por primera vez.

Post-condiciones: Recorre el arbol en el orden especificado y guarda lo elementos indicados por tamanio en un vector.
-Si tamanio es igual al tamanio del arbol, se guarda todo el arbol en el vector.
-Si tamanio es mayor al tamanio del arbol, se guarda todo el arbol en el vecto, dejando posiciones vacias (no se pudo llenaro todo el vector).
-Si tamanio es menor al tamanio del arbol, se guardan la cantidad de elementos en el vector (el vector no se llena con todo el arbol, sino con una parte de el).

NOTA: El orden de los elementos del vector depende del tipo de recorrido con el que se recorra al arbol.
*/
void guardar_en_array_postorden(nodo_abb_t* nodo_de_entrada, void** array, size_t tamanio, size_t* elementos_insertados, size_t* posicion){

  if(!nodo_de_entrada || !array || (*posicion) >= tamanio){
    return;
  }
  
  guardar_en_array_postorden(nodo_de_entrada->izquierda, array, tamanio, elementos_insertados, posicion);
  guardar_en_array_postorden(nodo_de_entrada->derecha, array, tamanio, elementos_insertados, posicion);

  if((*posicion) >= tamanio){
    return;
  }

  array[*posicion] = nodo_de_entrada->elemento;
  (*elementos_insertados)++;
  (*posicion)++;

}


/*
Pre-condiciones: 
-nodo_entrada no debe ser NULL y debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-array no debe ser NULL.
-tamanio debe ser mayor a 0.
-elementos_insertados debe ser 0 cuando la funcion es llamada por primera vez.
-posicion debe ser 0 cuando la funcion es llamada por primera vez.

Post-condiciones: Recorre el arbol en el orden especificado y guarda lo elementos indicados por tamanio en un vector.
-Si tamanio es igual al tamanio del arbol, se guarda todo el arbol en el vector.
-Si tamanio es mayor al tamanio del arbol, se guarda todo el arbol en el vecto, dejando posiciones vacias (no se pudo llenaro todo el vector).
-Si tamanio es menor al tamanio del arbol, se guardan la cantidad de elementos en el vector (el vector no se llena con todo el arbol, sino con una parte de el).

NOTA: El orden de los elementos del vector depende del tipo de recorrido con el que se recorra al arbol.
*/
void guardar_en_array_inorden(nodo_abb_t* nodo_de_entrada, void** array, size_t tamanio, size_t* elementos_insertados, size_t* posicion){

  if(!nodo_de_entrada || !array || (*posicion) >= tamanio){
    return;
  }
  
  guardar_en_array_inorden(nodo_de_entrada->izquierda, array, tamanio, elementos_insertados, posicion);

  if((*posicion) >= tamanio){
    return;
  }

  array[*posicion] = nodo_de_entrada->elemento;
  (*elementos_insertados)++;
  (*posicion)++;


  guardar_en_array_inorden(nodo_de_entrada->derecha, array, tamanio, elementos_insertados, posicion);
}


/*
Pre-condiciones: 
-nodo_entrada no debe ser NULL y debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-array no debe ser NULL.
-tamanio debe ser mayor a 0.
-elementos_insertados debe ser 0 cuando la funcion es llamada por primera vez.
-posicion debe ser 0 cuando la funcion es llamada por primera vez.

Post-condiciones: Recorre el arbol en el orden especificado y guarda lo elementos indicados por tamanio en un vector.
-Si tamanio es igual al tamanio del arbol, se guarda todo el arbol en el vector.
-Si tamanio es mayor al tamanio del arbol, se guarda todo el arbol en el vecto, dejando posiciones vacias (no se pudo llenaro todo el vector).
-Si tamanio es menor al tamanio del arbol, se guardan la cantidad de elementos en el vector (el vector no se llena con todo el arbol, sino con una parte de el).

En caso de eror la funcion deja de ejecutarse.

NOTA: El orden de los elementos del vector depende del tipo de recorrido con el que se recorra al arbol.
*/
void guardar_en_array_preorden(nodo_abb_t* nodo_de_entrada, void** array, size_t tamanio, size_t* elementos_insertados, size_t* posicion){

  if(!nodo_de_entrada || !array || (*posicion) >= tamanio){
    return;
  }

  if((*posicion) >= tamanio){
    return;
  }

  array[*posicion] = nodo_de_entrada->elemento;
  (*elementos_insertados)++;
  (*posicion)++;
  
  guardar_en_array_preorden(nodo_de_entrada->izquierda, array, tamanio, elementos_insertados, posicion);

  guardar_en_array_preorden(nodo_de_entrada->derecha, array, tamanio, elementos_insertados, posicion);
}


/*
Pre-condiciones:
-nodo_inicio debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-funcion no debe ser NULL, y lo que haga depende exclusivamente del usario.
-cantidad deber ser cero cuando la funcion es llamada por primera vez.
-aux depende exlusivamente del usario, es una variable que se aplica como segundo parametro de funcion (en caso de no querer usarla se envia NULL).
-estadod debe ser true cuando la funciones llamada por primera vez.

Post-condiciones: La funcion recorre el arbol en el orden indicado por su nombre, y segun corresponda le aplica funcion a cada elemento del mismo hasta que
funcion "funcion" devuelva false, en ese caso, la funcion se deja de ejecutar y guarda en cantidad la cantidad de veces que la funcion "funcion" fue ejecutada.
*/
void abb_con_cada_elemento_preorder(nodo_abb_t* nodo_inicio, bool (*funcion)(void *, void *), size_t* cantidad, void* aux, bool* estado){

  if(!(*estado) || !nodo_inicio){
    return;
  }

  if(funcion(nodo_inicio->elemento, aux) == false){
    *estado = false;
    (*cantidad)++;
    return;
  }

  (*cantidad)++;
  abb_con_cada_elemento_preorder(nodo_inicio->izquierda, funcion, cantidad, aux, estado);
  abb_con_cada_elemento_preorder(nodo_inicio->derecha, funcion, cantidad, aux, estado);
}


/*
Pre-condiciones:
-nodo_inicio debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-funcion no debe ser NULL, y lo que haga depende exclusivamente del usario.
-cantidad deber ser cero cuando la funcion es llamada por primera vez.
-aux depende exlusivamente del usuario, es una variable que se aplica como segundo parametro de funcion (en caso de no querer usarla se envia NULL).
-estado debe ser true cuando la funciones llamada por primera vez.

Post-condiciones: La funcion recorre el arbol en el orden indicado por su nombre, y segun corresponda le aplica funcion a cada elemento del mismo hasta que
funcion "funcion" devuelva false, en ese caso, la funcion se deja de ejecutar y guarda en cantidad la cantidad de veces que la funcion "funcion" fue ejecutada.
*/
void abb_con_cada_elemento_inorder(nodo_abb_t* nodo_inicio, bool (*funcion)(void *, void *), size_t* cantidad, void* aux, bool* estado){

  if(!(*estado)  || !nodo_inicio || !funcion){
    return;
  }

  abb_con_cada_elemento_inorder(nodo_inicio->izquierda, funcion, cantidad, aux, estado);

  if(!(*estado)){
    return;
  }

  if(funcion(nodo_inicio->elemento, aux) == false){
    *estado = false;
    (*cantidad)++;
    return;
  }
  (*cantidad)++;

  abb_con_cada_elemento_inorder(nodo_inicio->derecha, funcion, cantidad, aux, estado);
}


/*
Pre-condiciones:
-nodo_inicio debe ser el nodo_raiz del abb cuando la funcion es llamada por primera vez.
-funcion no debe ser NULL, y lo que haga depende exclusivamente del usario.
-cantidad deber ser cero cuando la funcion es llamada por primera vez.
-aux depende exlusivamente del usario, es una variable que se aplica como segundo parametro de funcion (en caso de no querer usarla se envia NULL).
-estadod debe ser true cuando la funciones llamada por primera vez.

Post-condiciones: La funcion recorre el arbol en el orden indicado por su nombre, y segun corresponda le aplica funcion a cada elemento del mismo hasta que
funcion "funcion" devuelva false, en ese caso, la funcion se deja de ejecutar y guarda en cantidad la cantidad de veces que la funcion "funcion" fue ejecutada.
*/
void abb_con_cada_elemento_postorder(nodo_abb_t* nodo_inicio, bool (*funcion)(void *, void *), size_t* cantidad, void* aux, bool* estado){

  if(!(*estado) || !nodo_inicio){
    return;
  }

  abb_con_cada_elemento_postorder(nodo_inicio->izquierda, funcion, cantidad, aux, estado);

  abb_con_cada_elemento_postorder(nodo_inicio->derecha, funcion, cantidad, aux, estado);

  if(!(*estado)){
    return;
  }

  if(funcion(nodo_inicio->elemento, aux) == false){
    *estado = false;
    (*cantidad)++;
    return;
  }
  (*cantidad)++;

}


/*
Pre-condiciones: izquierdo_de_nodo_a_eliminar debe ser el izquierdo del nodo a eliminar cuando se usa esta funcion por primera vez. 
-Solo usar si se sabe que el izquierdo_nodo_a_eliminar no es NULL.

Post-condiciones: La funcion recorre el arbol buscando el nodo anterior al predecesor inorden del nodo que se desea eliminar del arbol.
-Se devuelve el nodo izquierdo (en este caso, este es el predecesor inorden) al nodo a eliminar si este no tiene hijos, en otro caso se devuelve al 
anterior al predecesor inorden.
*/
nodo_abb_t* anterior_predecesor_inorden(nodo_abb_t* izquierdo_de_nodo_a_eliminar){

  if(!izquierdo_de_nodo_a_eliminar->derecha){
    return izquierdo_de_nodo_a_eliminar;
  }

  if(!izquierdo_de_nodo_a_eliminar->derecha->derecha){
    return izquierdo_de_nodo_a_eliminar;
  }

  return anterior_predecesor_inorden(izquierdo_de_nodo_a_eliminar->derecha);
}


/*
Pre-condiciones:
-nodo_inicio debe ser el nodo raiz cuando la funcion es llamada por primera vez.
-comparador no debe ser NULL.
-estado debe ser false cuando la funcion es llamada por primera vez.

Post-condicones: La funcion recorre el arbol hasta encontrar el nodo que se desea eliminar (si no lo consigue deveulve NULL), devuelve un puntero
al nodo_raiz si todo salio bien (se elimnino el nodo deseado), en ese caso, la variable estado cambia de true a false.
*/
nodo_abb_t* abb_quitar_aux(nodo_abb_t* nodo_inicio, void* elemento, abb_comparador comparador, bool* estado){

  if(!nodo_inicio){
    return NULL;
  }

  nodo_abb_t* nodo_auxiliar = nodo_inicio;
  int comparacion = comparador(elemento, nodo_inicio->elemento);

  if(comparacion == 0){

    *estado = true;
  
    if(nodo_inicio->izquierda != NULL && nodo_inicio->derecha != NULL){
      
      nodo_abb_t* auxiliar = anterior_predecesor_inorden(nodo_inicio->izquierda);
      nodo_abb_t* predecesor_inorden;
      nodo_abb_t* hijo_izquierdo_predecesor_inorden;

      if(!auxiliar->derecha){
        predecesor_inorden = auxiliar;
        predecesor_inorden->derecha = nodo_inicio->derecha; 
      }
      else{
        hijo_izquierdo_predecesor_inorden = auxiliar->derecha->izquierda;
        predecesor_inorden = auxiliar->derecha;
        predecesor_inorden->izquierda = nodo_inicio->izquierda;
        predecesor_inorden->derecha = nodo_inicio->derecha;
        auxiliar->derecha = hijo_izquierdo_predecesor_inorden;
      }

      free(nodo_inicio);
      return predecesor_inorden;
      
    }
    else if(nodo_inicio->izquierda != NULL){
      nodo_auxiliar = nodo_inicio->izquierda;
      free(nodo_inicio);
      return nodo_auxiliar;
    }
    else if(nodo_inicio->derecha != NULL){
      nodo_auxiliar = nodo_inicio->derecha;
      free(nodo_inicio);
      return nodo_auxiliar;

    }
    else{
      free(nodo_inicio);
      nodo_inicio = NULL;
      return NULL;
    }

  }
  else if(comparacion < 0){
    nodo_inicio->izquierda = abb_quitar_aux(nodo_inicio->izquierda, elemento, comparador, estado);
  }
  else if(comparacion > 0){
    nodo_inicio->derecha = abb_quitar_aux(nodo_inicio->derecha, elemento, comparador, estado);
  }

  return nodo_auxiliar;
}

//FUNCIONES PUBLICAS:

abb_t* abb_crear(abb_comparador comparador){

  if(!comparador){
    return NULL;
  }

  abb_t* abb = calloc(1, sizeof(abb_t));

  if(!abb){
    return NULL;
  }

  abb->comparador = comparador;

  return abb;
}


abb_t* abb_insertar(abb_t* arbol, void* elemento){

  if(!arbol){
    return NULL;
  }

  abb_t* abb_auxiliar = arbol;
  abb_auxiliar->nodo_raiz = insertar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);

  if(!abb_auxiliar->nodo_raiz){
    return NULL;
  }

  (arbol->tamanio)++;

  return abb_auxiliar;
}


void* abb_quitar(abb_t* arbol, void *elemento){

  if(!arbol){
    return NULL;
  }

  bool estado = false;

  nodo_abb_t* nueva_raiz = abb_quitar_aux(arbol->nodo_raiz, elemento, arbol->comparador, &estado);

  if(!estado){
    return NULL;
  }

  arbol->nodo_raiz = nueva_raiz;

  arbol->tamanio--;
  return elemento;
}


void* abb_buscar(abb_t* arbol, void* elemento){

  if(!arbol){
    return NULL;
  }

  return abb_buscar_elemento_en_el_arbol(arbol->nodo_raiz, elemento, arbol->comparador);
}


bool abb_vacio(abb_t* arbol){

  if(!arbol){
    return true;
  }

  return arbol->tamanio == 0;
}


size_t abb_tamanio(abb_t *arbol){

  if(!arbol){
    return 0;
  }

  return arbol->tamanio;
}


void abb_destruir(abb_t *arbol){

  if(!arbol){
    return;
  }

  if(abb_vacio(arbol)){
    free(arbol);
    return;
  }

  abb_destruir_raices(arbol->nodo_raiz, NULL);
  free(arbol);
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){

  if(!arbol){
    return;
  }

  if(abb_vacio(arbol)){
    free(arbol);
    return;
  }

  abb_destruir_raices(arbol->nodo_raiz, destructor);
  free(arbol);
}


size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
  
  if(!arbol || !funcion){
    return 0;
  }

  size_t cantidad = 0;
  bool estado = true;

  if(recorrido == PREORDEN){
    abb_con_cada_elemento_preorder(arbol->nodo_raiz, funcion, &cantidad, aux, &estado);
  }
  else if(recorrido == INORDEN){
    abb_con_cada_elemento_inorder(arbol->nodo_raiz, funcion, &cantidad, aux, &estado);
  }
  else if(recorrido == POSTORDEN){
    abb_con_cada_elemento_postorder(arbol->nodo_raiz, funcion, &cantidad, aux, &estado);
  }

  return cantidad;
}


size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){

  if(!arbol || tamanio_array <= 0){
    return 0;
  }  

  size_t cantidad_elementos_almacenados = 0;
  size_t auxiliar = 0;

  if(recorrido == INORDEN){
    guardar_en_array_inorden(arbol->nodo_raiz, array, tamanio_array, &cantidad_elementos_almacenados, &auxiliar);
  }
  else if(recorrido == PREORDEN){
    guardar_en_array_preorden(arbol->nodo_raiz, array, tamanio_array, &cantidad_elementos_almacenados, &auxiliar);
  }
  else if(recorrido == POSTORDEN){
    guardar_en_array_postorden(arbol->nodo_raiz, array, tamanio_array, &cantidad_elementos_almacenados, &auxiliar);
  }
  
  return cantidad_elementos_almacenados;
}
