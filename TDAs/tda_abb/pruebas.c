#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"


/*
Pre-condiciones: Recibe dos punteros enteros casteados a void* (c1 y c2).

Post-condiciones: Devuelve el resultado de la diferencia entre el contenido apuntado por c1 y c2.
*/
int comparar_cosas(void* c1, void* c2){
  int* cosa1 = c1;
  int* cosa2 = c2;
  return (*cosa1)-(*cosa2);
}


/*
Pre-condiciones: numero debe ser un puntero a un entero casteado a void*, aux debe ser preriblemente NULL 

NOTA: este parametro, NULL, esta en la firma de esta funcion aunque no se use ya que esta funcion se pasa por parametro a algunas de las funciones del TDA
ABB, y en las firma de las mismas, la funcion pasada por parametro debe tener dos parametros.

Post-condiciones: Devuelve true si el contenido apuntado por numero es par, y false en caso contrario.
*/
bool es_par(void* numero, void* aux){

  if(!numero){
    return false;
  }

  return (*(int*)numero)%2 == 0;
 }


nodo_abb_t* anterior_predecesor_inorden_aux(nodo_abb_t* izquierdo_de_nodo_a_eliminar){

  if(!izquierdo_de_nodo_a_eliminar->derecha){
    return izquierdo_de_nodo_a_eliminar;
  }

  if(!izquierdo_de_nodo_a_eliminar->derecha->derecha){
    return izquierdo_de_nodo_a_eliminar;
  }

  return anterior_predecesor_inorden_aux(izquierdo_de_nodo_a_eliminar->derecha);
}



void DadoUnABB_CuandoSeLoCrea_EntonceSeCreaCorrectamente(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);
  pa2m_afirmar(abb_a_analizar->tamanio == 0, "Cuando se crea un ABB, este esta vacio, por lo que su tamanio es 0.");
  pa2m_afirmar(abb_a_analizar->nodo_raiz == NULL, "Cuando se crea un ABB, su nodo raiz es NULL.");
  pa2m_afirmar(abb_a_analizar->comparador == comparar_cosas, "El comparador del ABB es el esperado.");
  free(abb_a_analizar);

  abb_a_analizar = abb_crear(NULL);
  pa2m_afirmar(abb_a_analizar == NULL, "Si se intenta crear un ABB con un comparador NULL, este no se crea, y la funcion devuelve NULL.");
  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeLeInsertaUnElemento_EntoncesElElementoInsertadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 40;
  int inserto_2 = 35;
  int inserto_3 = 45;
  int inserto_4 = 50;
  int inserto_5 = 49;
  int inserto_6 = 55;
  int inserto_7 = 36;
  int inserto_8 = 30;
  int inserto_9 = 25;
  int inserto_10 = 34;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);
  abb_insertar(abb_a_analizar, (void*)&inserto_7);
  abb_insertar(abb_a_analizar, (void*)&inserto_8);
  abb_insertar(abb_a_analizar, (void*)&inserto_9);
  abb_insertar(abb_a_analizar, (void*)&inserto_10);
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->elemento == 40, "Se inserta un elemento en la raiz, luego, el elemento insertado es el esperado.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->izquierda->elemento == 35, "Se inserta un elemento en la izquierda de raiz, luego, el elemento insertado es el esperado.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->derecha->elemento == 45, "Se inserta un elemento en la derecha de raiz, luego, el elemento insertado es el esperado.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->derecha->derecha->izquierda->elemento == 49, "Se inserta el 49, esta en la posicion esperada.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->derecha->derecha->derecha->elemento == 55, "Se inserta el 55, esta en la posicion esperada.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->izquierda->izquierda->izquierda->elemento == 25, "Se inserta el 25, esta en la posicion esperada.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->izquierda->izquierda->derecha->elemento == 34, "Se inserta el 34, esta en la posicion esperada.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->izquierda->izquierda->elemento == 30, "Se inserta el 30, esta en la posicion esperada.");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->izquierda->derecha->elemento == 36, "Se inserta el 36, esta en la posicion esperada.");
  pa2m_afirmar(abb_a_analizar->tamanio == 10, "Al insertar 10 elementos, tamanio pasa a ser 10.");

  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeLeInsertanVariosElementosYSeLosBuscan_EntoncesSeLosEncuentra(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 40;
  int inserto_2 = 35;
  int inserto_3 = 45;
  int inserto_4 = 50;
  int inserto_5 = 49;
  int inserto_6 = 55;
  int inserto_7 = 36;
  int inserto_8 = 30;
  int inserto_9 = 25;
  int inserto_10 = 34;
  int elemento_falso_1 = 0;
  int elemento_falso_2 = 500;
  
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);
  abb_insertar(abb_a_analizar, (void*)&inserto_7);
  abb_insertar(abb_a_analizar, (void*)&inserto_8);
  abb_insertar(abb_a_analizar, (void*)&inserto_9);
  abb_insertar(abb_a_analizar, (void*)&inserto_10);

  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_1) == 40 , "Se encuentra al elemento '40' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_2) == 35 , "Se encuentra al elemento '35' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_3) == 45 , "Se encuentra al elemento '45' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_4) == 50 , "Se encuentra al elemento '50' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_6) == 55 , "Se encuentra al elemento '55' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_7) == 36 , "Se encuentra al elemento '36' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_8) == 30 , "Se encuentra al elemento '30' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_9) == 25 , "Se encuentra al elemento '25' en el ABB.");
  pa2m_afirmar(*(int*)abb_buscar(abb_a_analizar, &inserto_10) == 34 , "Se encuentra al elemento '34' en el ABB.");
  pa2m_afirmar(abb_buscar(NULL, NULL) == NULL, "No se puede buscar en un arbol NULL.");
  pa2m_afirmar(abb_buscar(abb_a_analizar, &elemento_falso_1) == NULL, "EL 0 no esta, y se lo busca, pero no se puede encontrar un elemento inexistente.");
  pa2m_afirmar(abb_buscar(abb_a_analizar, &elemento_falso_2) == NULL , "El 500 no esta, y se lo busca, pero no se puede encontrar un elemento inexistente.");


  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeVerificaSiEstaVacio_EntoncesElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  pa2m_afirmar(abb_vacio(abb_a_analizar) == true, "Cuando se crea un ABB este esta vacio");

  int inserto_1 = 20;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);

  pa2m_afirmar(abb_vacio(abb_a_analizar) == false, "Un ABB de 1 elemento no esta vacio.");

  int inserto_2 = 40;
  int inserto_3 = 35;
  int inserto_4 = 45;
  int inserto_5 = 50;
  int inserto_6 = 49;
  int inserto_7 = 55;
  int inserto_8 = 36;
  int inserto_9 = 30;
  int inserto_10 = 25;
  int inserto_11 = 34;
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);
  abb_insertar(abb_a_analizar, (void*)&inserto_7);
  abb_insertar(abb_a_analizar, (void*)&inserto_8);
  abb_insertar(abb_a_analizar, (void*)&inserto_9);
  abb_insertar(abb_a_analizar, (void*)&inserto_10);
  abb_insertar(abb_a_analizar, (void*)&inserto_11);
  pa2m_afirmar(abb_vacio(abb_a_analizar) == false, "Un ABB de 11 elementos no esta vacio.");


  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeAnalizaSuTamanio_EntoncesElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = NULL; 
  pa2m_afirmar(abb_tamanio(abb_a_analizar) == 0, "Un ABB inexistente tiene tamanio 0");

  abb_a_analizar = abb_crear(comparar_cosas);
  pa2m_afirmar(abb_tamanio(abb_a_analizar) == 0, "Un ABB recien creado tiene tamanio 0");

  int inserto_1 = 40;
  int inserto_2 = 35;
  int inserto_3 = 45;
  int inserto_4 = 50;
  int inserto_5 = 49;
  int inserto_6 = 55;
  int inserto_7 = 36;
  int inserto_8 = 30;
  int inserto_9 = 25;
  int inserto_10 = 34;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);
  abb_insertar(abb_a_analizar, (void*)&inserto_7);
  abb_insertar(abb_a_analizar, (void*)&inserto_8);
  abb_insertar(abb_a_analizar, (void*)&inserto_9);
  abb_insertar(abb_a_analizar, (void*)&inserto_10);
  pa2m_afirmar(abb_tamanio(abb_a_analizar) == 10, "Al insertarle 10 elementos al ABB, su tamanio pasa a ser 10");

  abb_destruir(abb_a_analizar);
}


void DadaUnaFuncionDeRecorrerUnAbbYGuardarSusElementosEnUnArray_CuandoSeLaUsaConTodoElAbb_ElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int** array = calloc(9, sizeof(int*));
 
  int inserto_1 = 40;
  int inserto_2 = 50;
  int inserto_3 = 60;
  int inserto_4 = 59;
  int inserto_5 = 61;
  int inserto_6 = 30;
  int inserto_7 = 20;
  int inserto_8 = 15;
  int inserto_9 = 21;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);
  abb_insertar(abb_a_analizar, (void*)&inserto_7);
  abb_insertar(abb_a_analizar, (void*)&inserto_8);
  abb_insertar(abb_a_analizar, (void*)&inserto_9);

  size_t elementos_insertados = abb_recorrer(abb_a_analizar, POSTORDEN, (void**)array, 9);

  printf("\nPRUEBAS SOBRE GUARDAR TODO UN ARBOL EN UN ARRAY\n");
  pa2m_afirmar(elementos_insertados == 9, "Cuando se recorre un ABB de tamanio 9 y se guardan sus elementos en un array, la cantidad de elementos del array es 9");
  pa2m_afirmar(*(int*)array[0] == 15, "El primer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 21, "El segundo elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 20, "El tercer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[3] == 30, "El cuarto elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[4] == 59, "El quinto elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[5] == 61, "El sexto elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[6] == 60, "El septimo elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[7] == 50, "El octavo elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[8] == 40, "El noveno elemento del ARRAY es el esperado.");
  free(array);
  abb_destruir(abb_a_analizar);
}

void DadaUnaFuncionDeRecorrerUnAbbYGuardarSusElementosEnUnArray_CuandoSeLaUsaConUnTamanioMayorAlDelAbb_ElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int** array = calloc(9, sizeof(int*));
 
  int inserto_1 = 40;
  int inserto_2 = 30;
  int inserto_3 = 60;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  
  size_t elementos_insertados = abb_recorrer(abb_a_analizar, POSTORDEN, (void**)array, 800);

  printf("\nPRUEBAS SOBRE GUARDAR LOS ELEMENTOS EN UN ARRAY CON UN TAMANIO MAYOR AL DEL ARBOL.\n");
  pa2m_afirmar(elementos_insertados == 3, "Cuando se recorre un ABB de tamanio 3 y se intentan guardar 800 elementos en un array, la cantidad de elementos del array es 3.");
  pa2m_afirmar(*(int*)array[0] == 30, "El primer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 60, "El segundo elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 40, "El tercer elemento del ARRAY es el esperado.");

  free(array);
  abb_destruir(abb_a_analizar);

}


void DadaUnaFuncionDeRecorrerUnAbbYGuardarSusElementosEnUnArray_CuandoSeLaUsaConUnTamanioMenorAlDelAbb_ElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int** array = calloc(9, sizeof(int*));
 
  int inserto_1 = 40;
  int inserto_2 = 30;
  int inserto_3 = 20;
  int inserto_4 = 50;
  int inserto_5 = 60;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);

  size_t elementos_insertados = abb_recorrer(abb_a_analizar, POSTORDEN, (void**)array, 2);

  printf("\nPRUEBAS SOBRE GUARDAR LOS ELEMENTOS EN UN ARRAY CON UN TAMANIO MENOR  AL DEL ARBOL.\n");
  pa2m_afirmar(elementos_insertados == 2, "Cuando se recorre un ABB de tamanio 5 y se intentan guardar 2 de sus elementos en un array, la cantidad de elementos del array es 2");
  pa2m_afirmar(*(int*)array[0] == 20, "El primer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 30, "El segundo elemento del ARRAY es el esperado.");

  free(array);
  abb_destruir(abb_a_analizar);
}

void DadaUnaFuncionDeRecorrerUnAbbInordenYGuardarSusElementosEnUnArray_CuandoSeLeUsa_ELResultadoEsEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int** array = calloc(5, sizeof(int*));
 
  int inserto_1 = 40;
  int inserto_2 = 30;
  int inserto_3 = 20;
  int inserto_4 = 50;
  int inserto_5 = 60;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);

  size_t elementos_insertados = abb_recorrer(abb_a_analizar, INORDEN, (void**)array, 5);

  pa2m_afirmar(elementos_insertados == 5, "Cuando se recorre un arbol de 5 elementos INORDEN y se los guarda en un vector, el tamanio del vector es 5");
  pa2m_afirmar(*(int*)array[0] == 20, "El primer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 30, "El segundo elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 40, "El tercer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[3] == 50, "El cuarto elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[4] == 60, "El quinto elemento del ARRAY es el esperado.");

  free(array);
  abb_destruir(abb_a_analizar);
}


void DadaUnaFuncionDeRecorrerUnAbbPeordenYGuardarSusElementosEnUnArray_CuandoSeLeUsa_ELResultadoEsEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int** array = calloc(5, sizeof(int*));
 
  int inserto_1 = 40;
  int inserto_2 = 30;
  int inserto_3 = 20;
  int inserto_4 = 50;
  int inserto_5 = 60;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);

  size_t elementos_insertados = abb_recorrer(abb_a_analizar, PREORDEN, (void**)array, 5);

  pa2m_afirmar(elementos_insertados == 5, "Cuando se recorre un arbol de 5 elementos PREORDEN y se los guarda en un vector, el tamanio del vector es 5");
  pa2m_afirmar(*(int*)array[0] == 40, "El primer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 30, "El segundo elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 20, "El tercer elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[3] == 50, "El cuarto elemento del ARRAY es el esperado.");
  pa2m_afirmar(*(int*)array[4] == 60, "El quinto elemento del ARRAY es el esperado.");

  free(array);
  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeLeAplicaUnaFuncionACadaElementoDelMismoPREORDEN_EntoncesElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 40;
  int inserto_2 = 31;
  int inserto_3 = 20;
  int inserto_4 = 50;
  int inserto_5 = 60;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);

  size_t cantidad = abb_con_cada_elemento(abb_a_analizar, PREORDEN, es_par, NULL);

  pa2m_afirmar(cantidad == 2, "Si se recorre un ABB PREORDEN buscando cuantas veces se le pudo aplicar la funcion es_par, el resultado es el esperado.");

  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeLeAplicaUnaFuncionACadaElementoDelMismoINORDEN_EntoncesElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 40;
  int inserto_2 = 31;
  int inserto_3 = 20;
  int inserto_4 = 50;
  int inserto_5 = 60;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);

  size_t cantidad = abb_con_cada_elemento(abb_a_analizar, INORDEN, es_par, NULL);

  pa2m_afirmar(cantidad == 2, "Si se recorre un ABB INORDEN buscando cuantas veces se le pudo aplicar la funcion es_par, el resultado es el esperado.");

  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeLeAplicaUnaFuncionACadaElementoDelMismoPOSTORDEN_EntoncesElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 40;
  int inserto_2 = 31;
  int inserto_3 = 20;
  int inserto_4 = 50;
  int inserto_5 = 60;

  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);

  size_t cantidad = abb_con_cada_elemento(abb_a_analizar, POSTORDEN, es_par, NULL);

  pa2m_afirmar(cantidad == 2, "Si se recorre un ABB POSTORDEN buscando cuantas veces se le pudo aplicar la funcion es_par, el resultado es el esperado.");

  abb_destruir(abb_a_analizar);
}


void DadoUnAbb_CuandoSeLeIntentaEliminarUnElementoConCeroOUnHijo_ElresultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 50;
  int inserto_2 = 40;
  int inserto_3 = 20;
  int inserto_4 = 25;
  int inserto_5 = 60;
  int inserto_6 = 70;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);

  void* elemento_eliminado = abb_quitar(abb_a_analizar, (void*)&inserto_6);

  printf("\nSe crea un arbol auxiliar de 6 elementos para las pruebas:\n");
  pa2m_afirmar(*(int*)elemento_eliminado == 70, "Se intenta eliminar un nodo sin hijos (hoja), el elemento eliminado es el esperado.");
  pa2m_afirmar(abb_a_analizar->tamanio == 5, "Al eliminar un elemento, el tamanio del abb pasa a ser 5");

  elemento_eliminado = abb_quitar(abb_a_analizar, (void*)&inserto_3);

  pa2m_afirmar(*(int*)elemento_eliminado == 20, "Se intenta eliminar un nodo con un hijo, el elemento eliminado es el esperado.");
  pa2m_afirmar(abb_a_analizar->tamanio == 4, "Al eliminar otro elemento, el tamanio del abb pasa a ser 4");
  pa2m_afirmar(*(int*)abb_a_analizar->nodo_raiz->izquierda->izquierda->elemento == 25, "Se elimino un nodo con hijo y todo esta OK");

  abb_destruir(abb_a_analizar);  
}


void DadaUnaFuncionQueBuscaElAnteriorDelPredecesorInordenDeUnNodoEnUnABB_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado(){

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 50;
  int inserto_2 = 60;
  int inserto_3 = 65;
  int inserto_4 = 55;
  int inserto_5 = 56;
  int inserto_6 = 57;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);

  nodo_abb_t* ok = anterior_predecesor_inorden_aux(abb_a_analizar->nodo_raiz->derecha->izquierda);

  pa2m_afirmar(*(int*)ok->elemento == 56, "El anterior del predecesor inorden de un nodo es el esperado.");

  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeIntentaEliminarUnNodoConDosHijos_ElResultadoEsElEsperadoParteI(){

  printf("\nPRUEBAS DE ELIMINAR CON DOS HIJOS PARTE I: El PREDECESOR INORDEN NO TIENE HIJOS.\n");

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  void** array = calloc(5, sizeof(void*));

  int inserto_1 = 50;
  int inserto_2 = 60;
  int inserto_3 = 65;
  int inserto_4 = 55;
  int inserto_5 = 56;
  int inserto_6 = 57;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);
  
  void* elemento_eliminado = abb_quitar(abb_a_analizar,(void*)&inserto_2);
  pa2m_afirmar(abb_a_analizar->tamanio == 5, "Al elminar de un ABB con 6 nodos, un nodo con dos hijos, el tamanio del ABB pasa a ser 5.");
  pa2m_afirmar(*(int*)elemento_eliminado == 60, "El elemento eliminado es el esperado");
  pa2m_afirmar(abb_buscar(abb_a_analizar, (void*)&inserto_2) == false, "Si se busca el elemento eliminado en el ABB, este ya no se encuentra en el.");

  abb_recorrer(abb_a_analizar, POSTORDEN, array, 5);

  printf("\nSe recorre el arbol con el nodo eliminado y se guardan sus elementos en un vector.\n");
  pa2m_afirmar(*(int*)array[0] == 56, "El 1er elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 55, "El 2do elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 65, "El 3er elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[3] == 57, "El 4to elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[4] == 50, "El 5to elemento del vector es esl esperado.");

  free(array);
  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeIntentaEliminarUnNodoConDosHijos_ElResultadoEsElEsperadoParteII(){

  printf("\nPRUEBAS DE ELIMINAR CON DOS HIJOS PARTE II: EL PREDECESOR INORDEN ES EL IZQUIERDO DEL NODO A ELIMINAR.\n");

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  void** array = calloc(4, sizeof(void*));

  int inserto_1 = 10;
  int inserto_2 = 20;
  int inserto_3 = 30;
  int inserto_4 = 25;
  int inserto_5 = 35;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  
  void* elemento_eliminado = abb_quitar(abb_a_analizar,(void*)&inserto_3);
  pa2m_afirmar(abb_a_analizar->tamanio == 4, "Al elminar de un ABB con 5 nodos, un nodo con dos hijos, el tamanio del ABB pasa a ser 4.");
  pa2m_afirmar(*(int*)elemento_eliminado == 30, "El elemento eliminado es el esperado");
  pa2m_afirmar(abb_buscar(abb_a_analizar, (void*)&inserto_3) == false, "Si se busca el elemento eliminado en el ABB, este ya no se encuentra en el.");

  abb_recorrer(abb_a_analizar, POSTORDEN, array, 4);

  printf("\nSe recorre el arbol con el nodo eliminado y se guardan sus elementos en un vector\n");
  pa2m_afirmar(*(int*)array[0] == 35, "EL 1er elemento del vector  es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 25, "El 2do elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 20, "El 3er elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[3] == 10, "El 4to elemento del vector es el esperado.");
  
  free(array);
  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeIntentaEliminarUnNodoConDosHijos_ElResultadoEsElEsperadoParteIII(){

  printf("\nPRUEBAS DE ELIMINAR CON DOS HIJOS PARTE III: EL PREDECESOR INORDEN TIENE HIJO IZQUIERDO.\n");

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  void** array = calloc(5, sizeof(void*));

  int inserto_1 = 10;
  int inserto_2 = 20;
  int inserto_3 = 30;
  int inserto_4 = 15;
  int inserto_5 = 18;
  int inserto_6 = 17;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);

  void* elemento_eliminado = abb_quitar(abb_a_analizar,(void*)&inserto_2);
  pa2m_afirmar(abb_a_analizar->tamanio == 5, "Al elminar de un ABB con 6 nodos, un nodo con dos hijos, el tamanio del ABB pasa a ser 5.");
  pa2m_afirmar(*(int*)elemento_eliminado == 20, "El elemento eliminado es el esperado");
  pa2m_afirmar(abb_buscar(abb_a_analizar, (void*)&inserto_2) == false, "Si se busca el elemento eliminado en el ABB, este ya no se encuentra en el.");

  abb_recorrer(abb_a_analizar, POSTORDEN, array, 5);

  printf("\nSe recorre el arbol con el nodo eliminado, y se cargan sus elementos en un vector.\n");
  pa2m_afirmar(*(int*)array[0] == 17, "EL 1er elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[1] == 15, "El 2do elemento del vector es el esperado.");
  pa2m_afirmar(*(int*)array[2] == 30, "EL 3er elemento del vector es el esperado");
  pa2m_afirmar(*(int*)array[3] == 18, "EL 4to elemento del vector es el esperado");
  pa2m_afirmar(*(int*)array[4] == 10, "EL 5to elemento del vector es el esperado.");
  
  free(array);
  abb_destruir(abb_a_analizar);
}


void DadoUnABB_CuandoSeIntentaEliminarElNodoRaizYEsteTieneDosHijos_ElResultadoEsElEsperado(){

  printf("\nPREUBAS SOBRE ELIMINAR LA RAIZ DE UN ARBOL:\n");

  abb_t* abb_a_analizar = abb_crear(comparar_cosas);

  int inserto_1 = 50;
  int inserto_2 = 40;
  int inserto_3 = 42;
  int inserto_4 = 44;
  int inserto_5 = 25;
  int inserto_6 = 60;
  abb_insertar(abb_a_analizar, (void*)&inserto_1);
  abb_insertar(abb_a_analizar, (void*)&inserto_2);
  abb_insertar(abb_a_analizar, (void*)&inserto_3);
  abb_insertar(abb_a_analizar, (void*)&inserto_4);
  abb_insertar(abb_a_analizar, (void*)&inserto_5);
  abb_insertar(abb_a_analizar, (void*)&inserto_6);

  nodo_abb_t* nodo_ant_p_inorden = anterior_predecesor_inorden_aux(abb_a_analizar->nodo_raiz->izquierda);
  
  void* elemento = abb_quitar(abb_a_analizar,(void*)&inserto_1);
  int nuevo_nodo_raiz = *(int*)abb_a_analizar->nodo_raiz->elemento;

  printf("\n");
  pa2m_afirmar(*(int*)nodo_ant_p_inorden->elemento == 42, "El anterior al predecesor inorden es el esperado.");
  pa2m_afirmar(*(int*)elemento == 50, "El elemento eliminado es el esperado.");
  pa2m_afirmar(nuevo_nodo_raiz == 44, "El nuevo nodo raiz es el correcto.");
  pa2m_afirmar(abb_buscar(abb_a_analizar, (void*)&inserto_1) == NULL, "Cuando se busca el elemento eliminado en el arbol, no se lo consigue.");

  abb_destruir(abb_a_analizar);
}



int main(){
  pa2m_nuevo_grupo("PRUEBAS DE ABB");

  pa2m_nuevo_grupo("-Pruebas de creacion de ABB:");
  DadoUnABB_CuandoSeLoCrea_EntonceSeCreaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de insersion de elementos en un ABB:");
  DadoUnABB_CuandoSeLeInsertaUnElemento_EntoncesElElementoInsertadoEsElEsperado();

  pa2m_nuevo_grupo("-Pruebas de busqueda de elementos en un ABB:");
  DadoUnABB_CuandoSeLeInsertanVariosElementosYSeLosBuscan_EntoncesSeLosEncuentra();

  pa2m_nuevo_grupo("-Pruebas sobre si un ABB esta vacio");
  DadoUnABB_CuandoSeVerificaSiEstaVacio_EntoncesElResultadoEsElEsperado();

  pa2m_nuevo_grupo("-Pruebas sobre el tamanio de un ABB:");
  DadoUnABB_CuandoSeAnalizaSuTamanio_EntoncesElResultadoEsElEsperado();

  pa2m_nuevo_grupo("-Pruebas sobre recorrer un ABB y guardar sus elementos en un array:");
  printf("\nPRUEBAS POSTORDEN\n");
  DadaUnaFuncionDeRecorrerUnAbbYGuardarSusElementosEnUnArray_CuandoSeLaUsaConTodoElAbb_ElResultadoEsElEsperado();
  DadaUnaFuncionDeRecorrerUnAbbYGuardarSusElementosEnUnArray_CuandoSeLaUsaConUnTamanioMayorAlDelAbb_ElResultadoEsElEsperado();
  DadaUnaFuncionDeRecorrerUnAbbYGuardarSusElementosEnUnArray_CuandoSeLaUsaConUnTamanioMenorAlDelAbb_ElResultadoEsElEsperado();
  printf("\nPRUEBAS INORDEN\n");
  DadaUnaFuncionDeRecorrerUnAbbInordenYGuardarSusElementosEnUnArray_CuandoSeLeUsa_ELResultadoEsEsperado();
  printf("\nPRUEBAS PREORDER\n");
  DadaUnaFuncionDeRecorrerUnAbbPeordenYGuardarSusElementosEnUnArray_CuandoSeLeUsa_ELResultadoEsEsperado();

  pa2m_nuevo_grupo("Preubas de abb_con_cada_elemento:");
  DadoUnABB_CuandoSeLeAplicaUnaFuncionACadaElementoDelMismoPREORDEN_EntoncesElResultadoEsElEsperado();
  DadoUnABB_CuandoSeLeAplicaUnaFuncionACadaElementoDelMismoINORDEN_EntoncesElResultadoEsElEsperado();
  DadoUnABB_CuandoSeLeAplicaUnaFuncionACadaElementoDelMismoPOSTORDEN_EntoncesElResultadoEsElEsperado();

  pa2m_nuevo_grupo("-Pruebas de eliminar nodos con 0 o 1 hijo:");
  DadoUnAbb_CuandoSeLeIntentaEliminarUnElementoConCeroOUnHijo_ElresultadoEsElEsperado();

  pa2m_nuevo_grupo("Pruebas sobre predecesor inorden:");
  DadaUnaFuncionQueBuscaElAnteriorDelPredecesorInordenDeUnNodoEnUnABB_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado();

  pa2m_nuevo_grupo("-Pruebas de eliminar con dos hijos:");
  DadoUnABB_CuandoSeIntentaEliminarUnNodoConDosHijos_ElResultadoEsElEsperadoParteI();
  printf("\n");
  DadoUnABB_CuandoSeIntentaEliminarUnNodoConDosHijos_ElResultadoEsElEsperadoParteII();
  printf("\n");
  DadoUnABB_CuandoSeIntentaEliminarUnNodoConDosHijos_ElResultadoEsElEsperadoParteIII();
  DadoUnABB_CuandoSeIntentaEliminarElNodoRaizYEsteTieneDosHijos_ElResultadoEsElEsperado();

  return pa2m_mostrar_reporte();
}
