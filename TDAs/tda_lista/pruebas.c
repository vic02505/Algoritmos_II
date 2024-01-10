#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"
#include<string.h>

/*
Pre-condicicones: lista no debe ser NULL ni estar vacia.

Post-condiciones: Dado una lista y un elemento_a_buscar, se recorre la lista buscando elemento_a_buscar y se devuelve en que posicion se encuentra.
*/
size_t posicion_de_elemento_en_lista(lista_t* lista, void* elemento_a_buscar){
  
  size_t i = 0;
  size_t posicion = 0;
  bool encontrado = false;

  nodo_t* nodo_auxiliar = lista->nodo_inicio;

  while(i < lista->cantidad && !encontrado){

    if(strcmp(nodo_auxiliar->elemento, elemento_a_buscar) == 0){
      encontrado = true;
      posicion = i;
    }

    nodo_auxiliar = nodo_auxiliar->siguiente;
    i++;
  }

  return posicion;
}


/*
Pre-condiciones: lista no debe ser NULL, cantidad_elementos a insertar debe ser mayor que cero.

Post-condiciones: Insertar en una lista el elemento "PRUEBA" la cantidad de veces que se haya indicado en el respectivo parametro. En caso de error la funcion
aborta su ejecucion.
*/
void insertar_varios_elementos_en_una_lista(lista_t* lista, size_t cantidad_de_elementos_a_insertar){

  if(!lista){
    return;
  }

  lista_t* lista_auxiliar = lista;

  for(size_t i = 0; i < cantidad_de_elementos_a_insertar; i++){

    lista_auxiliar = lista_insertar(lista, "PRUEBA");

    if(!lista_auxiliar){
      return;
    }

  }

}


void DadaUnaFuncionDeCrearUnaLista_CuandoSeUsa_EntoncesEstaSeCreaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();

  pa2m_afirmar(lista_a_analizar != NULL, "Dada una funcion de crear una lista al usarla esta se crea correctamente.");
  pa2m_afirmar(lista_a_analizar->nodo_inicio == NULL,"Dada una lista nueva, tiene a su campo nodo_inicio apuntando a NULL.");
  pa2m_afirmar(lista_a_analizar->nodo_fin == NULL, "Dada una lista nueva, tiene a su campo nodo_fin apuntando a NULL.");
  pa2m_afirmar(lista_a_analizar->cantidad == 0, "Dada una lista nueva, tiene su campo cantidad inicializado en cero (0).")

  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionDeAgregarElementosAlFinalDeUnaLista_CuandoSeUsaSobreUnaListaVacia_EntoncesEstaFuncionaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  lista_t* lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA");

  pa2m_afirmar(lista_auxiliar != NULL, "Cuando se le inserta un elemento a una lista vacia, el elemento, antes de insertarse, se crea correctamente.");
  pa2m_afirmar(lista_a_analizar->cantidad == 1, "Si se inserta un elemento al final de una lista vacia, entonces la nueva cantidad de elementos es 1.");
  pa2m_afirmar(lista_a_analizar->nodo_inicio == lista_a_analizar->nodo_fin, "Si se inserta un elemento en una lista vacia, entonces inicio y fin son iguales.");
  pa2m_afirmar(strcmp(lista_a_analizar->nodo_inicio->elemento, "PRUEBA") == 0, "Cuando se inserta una elemento en una lista vacia, el elemento insertado es el esperado.");

  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionDeAgregarElementosAlFinalDeUnaLista_CuandoSeUsaSobreUnaListaConMasDeUnELemento_EntoncesEstaFuncionaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  lista_t* lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA");

  lista_auxiliar = lista_insertar(lista_a_analizar, "12345");
  pa2m_afirmar(lista_auxiliar != NULL, "Cuando se intenta agregar un elemento al final de una lista, la funcion se ejecuta hasta el final.")
  pa2m_afirmar(lista_a_analizar->cantidad == 2, "Una lista con 1 elemento tiene cantidad 1, cuando se le agrega otro al final, ahora cantidad es 2.");
  pa2m_afirmar(lista_a_analizar->nodo_inicio != lista_a_analizar->nodo_fin, "Cuando se agrega un elemento al final de una lista con un elemento, el nodo inicio es distinto al nodo fin.");
  pa2m_afirmar(lista_a_analizar->nodo_fin->siguiente == NULL, "Cuando se agrega un elemento al final de una lista con un elemento, el ultimo elemento tiene como siguiente a NULL.");
  pa2m_afirmar(strcmp("12345", lista_a_analizar->nodo_fin->elemento) == 0, "Cuando se le agrega un elemento al finla de una lista con un elemento, el elemento agregado es el esperado.");

  insertar_varios_elementos_en_una_lista(lista_a_analizar, 148);

  pa2m_afirmar(lista_a_analizar->cantidad == 150, "Cuando se intenta agregar 148 elementos al final de una lista que tiene 2 elementos, ahora la lista tiene 150 elementos");
  pa2m_afirmar(lista_a_analizar->nodo_fin->siguiente == NULL, "El ultimo de elemento de la lista de 150 elementos tiene como siguiente elemento a NULL.");

  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionDeAgregarUnElmentoEnCualquierParteDeUnaLista_CuandoSeUsaSobreCualquierPosicion_EntoncesLaFuncionFuncionaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  lista_t* lista_auxiliar;

  insertar_varios_elementos_en_una_lista(lista_a_analizar, 150);

  lista_auxiliar = lista_insertar_en_posicion(lista_a_analizar, "12345", 8);

  pa2m_afirmar(lista_auxiliar != NULL, "Cuando se agregan elementos a la lista, no hay errores en la carga.")
  pa2m_afirmar(lista_a_analizar->cantidad == 151, "Cuando se le aniade un elemento a un lista de 150 elementos, esta pasa a tener 151 elementos.");
  pa2m_afirmar(posicion_de_elemento_en_lista(lista_a_analizar, "12345") == 8, "Cuando se intenta aniadir un elemento en la posicion 8, el elemento ingresado es el esperado.");
  pa2m_afirmar(lista_a_analizar->nodo_fin->siguiente == NULL, "El ultimo elemento de la lista con 151 elementos apunta a NULL.");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();
  lista_auxiliar = lista_insertar_en_posicion(lista_a_analizar, "PRUEBA", 200);

  printf("\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 1, "Cuando se le inserta un elemento en una posicion cualquiera a una lista vacia, esta pasa a tener 1 elemento.");
  pa2m_afirmar(strcmp(lista_a_analizar->nodo_inicio->elemento, "PRUEBA") == 0, "El elemento se incerto al principio, y es el esperado.")
  pa2m_afirmar(lista_a_analizar->nodo_fin->siguiente == NULL, "El ultimo elmento de la lista vacia a la que se le inserto un elemento, tiene como siguiente a NULL.");
  lista_destruir(lista_a_analizar); 

  lista_a_analizar = lista_crear();

  insertar_varios_elementos_en_una_lista(lista_a_analizar, 300);

  lista_auxiliar = lista_insertar_en_posicion(lista_a_analizar, "12345", 0);

  printf("\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 301, "Si le inserta un elemento al principio de una lista con 300 elementos, esta pasa a tener 301 elementos.");
  pa2m_afirmar(strcmp(lista_a_analizar->nodo_inicio->elemento, "12345") == 0, "El elemento insertado es el esperado y esta en la posicion 0.");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();

  insertar_varios_elementos_en_una_lista(lista_a_analizar, 600);

  lista_auxiliar = lista_insertar_en_posicion(lista_a_analizar, "12345", 1200);

  printf("\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 601, "Cuando se intenta insertar un elemento en una lista de 600 elementos, en una posicion inexistente, este se inserta y la lista pasa a tener 601 elementos.");
  pa2m_afirmar(strcmp(lista_a_analizar->nodo_fin->elemento, "12345") == 0, "Cuando se intenta insertar un elemento en una posicion inexistente de una lista, este se inserta al final, y el elemento insertado es el esperado.");
  pa2m_afirmar(lista_a_analizar->nodo_fin->siguiente == NULL, "El elemento agregado al final de lista tiene como siguiente a NULL.");
  //free(lista_a_analizar->nodo_fin);
  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionDeELiminarUnElementoAlFinalDeUnaLista_CuandoSeLeLlama_EntoncesEstaFuncionaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear(); 
  lista_t* lista_auxiliar;

  insertar_varios_elementos_en_una_lista(lista_a_analizar, 599);

  lista_auxiliar = lista_insertar(lista_a_analizar, "12345");
  void* elemento_eliminado = lista_quitar(lista_a_analizar);

  pa2m_afirmar(lista_auxiliar != NULL, "No hubo errores durante la prueba (vease, carga de varios elementos en una lista)");
  pa2m_afirmar(lista_a_analizar->cantidad == 599, "Lista tenia 600 elementos, al eliminarse uno del final ahora tengo 599.");
  pa2m_afirmar(lista_a_analizar->nodo_fin->siguiente == NULL, "Despues de eliminar un elemento del final, el  'nuevo' ultimo elemento tiene comos siguiente a NULL.");
  pa2m_afirmar(strcmp(elemento_eliminado, "12345") == 0, "El elemento eliminado es el esperado.");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();

  insertar_varios_elementos_en_una_lista(lista_a_analizar, 1000);

  printf("\n");

  pa2m_afirmar(lista_a_analizar->cantidad == 1000, "Se crea una lista con 1000 elementos.");

  for(int i = 0; i < 1000; i++){
    elemento_eliminado = lista_quitar(lista_a_analizar);
  }

  pa2m_afirmar(lista_a_analizar->cantidad == 0, "Dada una lista con 1000 elementos, cuando se los elimina a todos, la cantidad de elementos en lista es cero.");
  pa2m_afirmar(lista_a_analizar->nodo_inicio == NULL, "Cuando se eliminan todos los elementos de una lista, ahora inicio apunta a NULL");
  pa2m_afirmar(lista_a_analizar->nodo_fin == NULL, "Cuando se elimian todos los elementos de una lista, ahora fin apunta a NULL");
  lista_destruir(lista_a_analizar);  
}


void DadaUnaFuncionDeEliminarUnElementoEnCualquierPosicionDeUnaLista_CuandoSeLeUsa_EntoncesFuncionaCorrectamente(){

  lista_t* lista_a_analizar = NULL;
  lista_t* lista_auxiliar = NULL;
  void* elemento_eliminado = NULL;

  lista_a_analizar = lista_crear();
  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA");
  elemento_eliminado = lista_quitar_de_posicion(lista_a_analizar, 0);

  printf("Eliminacion de un elemento de una lista de tamanio 1:\n");
  pa2m_afirmar(lista_auxiliar != NULL, "No hubo errores en creacion y carga de elementos en una lista para las pruebas.");
  pa2m_afirmar(lista_a_analizar->cantidad == 0, "Dada una lista con un elemento, si se lo elimina, ahora la cantidad de elementos es 0.");
  pa2m_afirmar(strcmp(elemento_eliminado, "PRUEBA") == 0, "El elemento eliminado es el esperado.");
  pa2m_afirmar(lista_a_analizar->nodo_inicio == NULL, "El campo nodo_inicio de una lista vacia apunta a NULL.");
  pa2m_afirmar(lista_a_analizar->nodo_fin == NULL, "El campo nodo_fin de una lista vacia apunta a NULL.");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();
  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA");
  elemento_eliminado = lista_quitar_de_posicion(lista_a_analizar, 1000);

  printf("\nEliminacion de un elemento de una lista de tamanio 1 con una posicion inexistente:\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 0, "Si se intenta eliminar una posicion inexistente de una lista de elemento, se intenta eliminar el elemento, y la cantidad de elementos de la lista pasa a ser 0.");
  pa2m_afirmar(strcmp(elemento_eliminado, "PRUEBA") == 0, "El elemento elimnado es el esperado.");
  pa2m_afirmar(lista_a_analizar->nodo_inicio == NULL, "El campo nodo_inicio de una lista vacia apunta a NULL.");
  pa2m_afirmar(lista_a_analizar->nodo_fin == NULL, "El campo nodo_fin de una lista vacia apunta a NULL");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();
  insertar_varios_elementos_en_una_lista(lista_a_analizar, 999);
  lista_insertar(lista_a_analizar, "12345");
  elemento_eliminado = lista_quitar_de_posicion(lista_a_analizar, 10000);

  printf("\nEliminacion de un elemento de una lista de tamanio mayor a 1 con una poisicion inexistente:\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 999, "Si se intenta eliminar una posicion inexistente de una lista con 1000 elementos, se intentara eliminar el ultimo elemento y la cantidad de elementos de la lista pasa a ser 999.");
  pa2m_afirmar(strcmp(elemento_eliminado, "12345") == 0, "El elemento eliminado es el esperado.");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();
  lista_insertar(lista_a_analizar, "12345");
  lista_insertar(lista_a_analizar, "PRUEBA");
  nodo_t* nodo_auxiliar = lista_a_analizar->nodo_inicio->siguiente;
  insertar_varios_elementos_en_una_lista(lista_a_analizar, 998);
  elemento_eliminado = lista_quitar_de_posicion(lista_a_analizar, 0);

  printf("\nELiminacion del primer elemento de una lista de tamanio mayor a 1:\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 999, "Cuando se intenta eliminar la primera posicion de una lista de 1000 elementos, esta pasa a tener 999.");
  pa2m_afirmar(strcmp(elemento_eliminado, "12345") == 0, "El elemento eliminado es el esperado.");
  pa2m_afirmar(nodo_auxiliar == lista_a_analizar->nodo_inicio, "Al eliminar el primer elemento de la lista, el nuevo nodo_inicio es el correcto.");
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();
  insertar_varios_elementos_en_una_lista(lista_a_analizar, 499);
  lista_insertar(lista_a_analizar, "12345");
  insertar_varios_elementos_en_una_lista(lista_a_analizar, 500);
  elemento_eliminado = lista_quitar_de_posicion(lista_a_analizar, 499);

  printf("\nEliminacion de un elmentos en posiciones internas de la lista (Todas menos la primera y la ultima):\n");
  pa2m_afirmar(lista_a_analizar->cantidad == 999, "Cuando se intenta eliminar la posicion 499 de una lista de 1000 elementos, cantidad pasa a ser 999.");
  pa2m_afirmar(strcmp(elemento_eliminado, "12345") == 0, "El elemento eliminado es el esperado.");
  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionDeBuscarUnElementoEnUnaPosicionCualquieraDeUnaLista_CuandSeLeUsa_EntoncesElResultadoEsElEsperado(){

  lista_t* lista_a_analizar = lista_crear();
  lista_t* lista_auxiliar;

  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA1");
  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA2");
  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA3");
  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA4");
  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA5");

  pa2m_afirmar(lista_auxiliar != NULL, "No hubo errores en la creacion de una lista para realizar estas pruebas.");
  pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista_a_analizar, 0), "PRUEBA1") == 0, "El elemento de la posicion 0 es el esperado.");
  pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista_a_analizar, 1), "PRUEBA2") == 0, "El elemento de la posicion 1 es el esperado.");
  pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista_a_analizar, 2), "PRUEBA3") == 0, "El elemento de la posicion 2 es el esperado.");
  pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista_a_analizar, 3), "PRUEBA4") == 0, "El elemento de la posicion 3 es el esperado.");
  pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista_a_analizar, 4), "PRUEBA5") == 0, "El elemento de la posicion 4 es el esperado.");
  pa2m_afirmar(lista_elemento_en_posicion(lista_a_analizar, 1000) == NULL, "Cuando se intenta buscar que hay en una posicion inexistente de la lista, etonces la funcion devuelve NULL.");
  pa2m_afirmar(strcmp(lista_primero(lista_a_analizar), "PRUEBA1") == 0 , "El primer elemento de la lista es el esperado (funcion lista_primero).");
  pa2m_afirmar(strcmp(lista_ultimo(lista_a_analizar), "PRUEBA5") == 0, "El ultimo elemento de la lista es el esperado (funcion lista_ultimo).");

  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionQueVerificaSiUnaListaEstaVacia_CuandoSeLeUsa_EntoncesFuncionaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  lista_t* lista_auxiliar;

  pa2m_afirmar(lista_vacia(lista_a_analizar), "La funcion lista_vacia devuelve true cuando la lista esta vacia.");

  lista_auxiliar = lista_insertar(lista_a_analizar, "PRUEBA");

  pa2m_afirmar(lista_auxiliar != NULL, "Al crear una lista para hacer estas pruebas e insertarle un elemento no hubo ningun error.");
  pa2m_afirmar(!lista_vacia(lista_a_analizar), "La funcion lista_vacia devuelve false cuando la lista no esta vacia.");

  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionQueDevuelveElTamanioDeUnaLista_CuandoSeLeUsa_EntoncesFuncionaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  
  pa2m_afirmar(lista_tamanio(lista_a_analizar) == 0, "Una lista vacia tiene tamanio 0.");
  insertar_varios_elementos_en_una_lista(lista_a_analizar, 10);
  pa2m_afirmar(lista_tamanio(lista_a_analizar) == 10, "Una lista de 10 elementos tiene como tamanio 10.");
  insertar_varios_elementos_en_una_lista(lista_a_analizar, 90);
  pa2m_afirmar(lista_tamanio(lista_a_analizar) == 100, "Una lista de 100 elementos tiene como tamanio 100.");

  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionQueCreaUnIterador_CuandoSeLeUsa_EntoncesElIteradorSeCreaCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  lista_iterador_t* iterador = lista_iterador_crear(lista_a_analizar);

  pa2m_afirmar(iterador != NULL, "El iterador se crea correctamente.");
  pa2m_afirmar(iterador->corriente == NULL, "El corriente de un iterador a una lista vacia es NULL.");
  pa2m_afirmar(iterador->lista != NULL, "El campo lista de un iterador no es NULL.");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_a_analizar);

  lista_a_analizar = lista_crear();
  lista_insertar(lista_a_analizar, "PRUEBA1");
  lista_insertar(lista_a_analizar, "PRUEBA2");
  lista_insertar(lista_a_analizar, "PRUEBA3");
  iterador = lista_iterador_crear(lista_a_analizar);

  pa2m_afirmar(iterador->corriente != NULL, "EL elemento corriente de un iterador a una lista que no esta vacia no es NULL.");
  pa2m_afirmar(strcmp(iterador->corriente->elemento, "PRUEBA1") == 0, "EL elemento corriente de un iterador a una lista no vacia es el esperado.");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_a_analizar);
}


void DadaUnGrupoDeFuncionesQuePermitenVerElElementoActualDeUnIteradorYAvazanzarEnEl_CuandoSeLesUsa_EntoncesFuncionanCorrectamente(){

  lista_t* lista_a_analizar = lista_crear();
  lista_insertar(lista_a_analizar, "PRUEBA1");
  lista_insertar(lista_a_analizar, "PRUEBA2");
  lista_insertar(lista_a_analizar, "PRUEBA3");
  lista_insertar(lista_a_analizar, "PRUEBA4");
  
  lista_iterador_t* iterador = lista_iterador_crear(lista_a_analizar);
  pa2m_afirmar(strcmp(iterador->corriente->elemento, "PRUEBA1") == 0 , "Al crear un iterador de una lista de 4 elementos , el elemento corriente es el esperado.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(strcmp(iterador->corriente->elemento, "PRUEBA2") == 0 , "Al crear un iterador de  una lista de 4 elemtnos, si se itera al siguiente (1), el elemento corriente es el esperado.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(strcmp(iterador->corriente->elemento, "PRUEBA3") == 0 , "Al crear un iterador de  una lista de 4 elemtnos, si se itera al siguiente (2), el elemento corriente es el esperado.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(strcmp(iterador->corriente->elemento, "PRUEBA4") == 0 , "Al crear un iterador de  una lista de 4 elemtnos,si se itera al siguiente (3), el elemento corriente es el esperado.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(iterador->corriente == NULL, "Si se itera a la ultima posicion de una lista, el elemento corriente del iterador es NULL.");

  lista_iterador_destruir(iterador);
  lista_destruir(lista_a_analizar);
}


void DadaUnaFuncionQueVerificaSiUnIteradorTieneSiguiente_CuandoSeLeUsa_EntoncesFuncionaCorrectamente(){

   lista_t* lista_a_analizar = lista_crear();
  lista_insertar(lista_a_analizar, "PRUEBA1");
  lista_insertar(lista_a_analizar, "PRUEBA2");
  lista_insertar(lista_a_analizar, "PRUEBA3");
  lista_insertar(lista_a_analizar, "PRUEBA4");
  
  lista_iterador_t* iterador = lista_iterador_crear(lista_a_analizar);

  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "Un iterador (con corriente en el inicio) a una lista con 4 elementos tiene un siguente elemento valido.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "Al avanzar a la posicion 1, el siguiente elemento de un iterador a una lista con 4 elementos es valido.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "Al avanzar a la posicion 2, el siguiente elemento de un iterador a una lista con 4 elementos es valido.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "Al avanzar a la posicion 3, el siguiente elemento de un iterador a una lista con 4 elementos es valido.");
  lista_iterador_avanzar(iterador);
  pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "Al llegar al final de iterador, no hay siguientes.");

  lista_iterador_destruir(iterador);
  lista_destruir(lista_a_analizar);
}


void DadoUnTDAPila_CuandoSeLoUsa_EntoncesSuComportamientoEsElEsperado(){

  pila_t* pila_a_analizar = pila_crear();

  pa2m_afirmar(pila_vacia(pila_a_analizar), "Cuando se crea una pila, esta esta vacia.");
  pa2m_afirmar(pila_tamanio(pila_a_analizar) == 0 , "El tamanio de una pila vacia es 0.");

  pila_apilar(pila_a_analizar, "PRUEBA1");
  pila_apilar(pila_a_analizar, "PRUEBA2");
  pila_apilar(pila_a_analizar, "PRUEBA3");
  pila_apilar(pila_a_analizar, "PRUEBA4");

  pa2m_afirmar(pila_vacia(pila_a_analizar) == false, "Al insertarle varios elementos a la pila, esta deja de estar vacia.");
  pa2m_afirmar(pila_tamanio(pila_a_analizar) == 4, "Al insertarle 4 elementos a la pila su tamanio pasa a ser 4");
  pa2m_afirmar(strcmp(pila_tope(pila_a_analizar), "PRUEBA4") == 0, "El tope (su contenido) de la pila es el esperado.");
  pa2m_afirmar(strcmp(pila_desapilar(pila_a_analizar), "PRUEBA4") == 0, "Al desapilar el tope actual, se despila el elemento correcto.");
  pa2m_afirmar(strcmp(pila_desapilar(pila_a_analizar), "PRUEBA3") == 0, "Al desapilar el nuevo tope actual, se despila el elemento correcto.");
  pa2m_afirmar(strcmp(pila_desapilar(pila_a_analizar), "PRUEBA2") == 0, "Al desapilar el nuevo tope actual, se despila el elemento correcto.");
  pa2m_afirmar(strcmp(pila_desapilar(pila_a_analizar), "PRUEBA1") == 0, "Al desapilar el nuevo tope actual, se despila el elemento correcto.");
  pa2m_afirmar(pila_tamanio(pila_a_analizar) == 0, "Al desapiliar todos los elementos la lista pasa a tener cero elementos.");
  pa2m_afirmar(pila_vacia(pila_a_analizar), "Una lista a la que se le dapilaron todos sus elementos esta vacia.");

  pila_destruir(pila_a_analizar);
}


void DadoUnTDACola_CuandoSeLoUsa_EntoncesSuComportamientoEsElEsperado(){

  cola_t* cola_a_analizar = cola_crear();

  pa2m_afirmar(cola_vacia(cola_a_analizar), "Cuando se crea unacola, esta esta vacia.");
  pa2m_afirmar(cola_tamanio(cola_a_analizar) == 0 , "El tamanio de unacola vacia es 0.");

 cola_encolar(cola_a_analizar, "PRUEBA1");
 cola_encolar(cola_a_analizar, "PRUEBA2");
 cola_encolar(cola_a_analizar, "PRUEBA3");
 cola_encolar(cola_a_analizar, "PRUEBA4");

  pa2m_afirmar(cola_vacia(cola_a_analizar) == false, "Al insertarle varios elementos a la cola, esta deja de estar vacia.");
  pa2m_afirmar(cola_tamanio(cola_a_analizar) == 4, "Al insertarle 4 elementos a la cola su tamanio pasa a ser 4");
  pa2m_afirmar(strcmp(cola_frente(cola_a_analizar), "PRUEBA1") == 0, "El frente (su contenido) de la cola es el esperado.");
  pa2m_afirmar(strcmp(cola_desencolar(cola_a_analizar), "PRUEBA1") == 0, "Al desencolar el frente, se despila el elemento correcto.");
  pa2m_afirmar(strcmp(cola_desencolar(cola_a_analizar), "PRUEBA2") == 0, "Al desencolar el nuevo frente, se despila el elemento correcto.");
  pa2m_afirmar(strcmp(cola_desencolar(cola_a_analizar), "PRUEBA3") == 0, "Al desencolar el nuevo frente, se despila el elemento correcto.");
  pa2m_afirmar(strcmp(cola_desencolar(cola_a_analizar), "PRUEBA4") == 0, "Al desencolar el nuevo frente, se despila el elemento correcto.");
  pa2m_afirmar(cola_tamanio(cola_a_analizar) == 0, "Al desencolar todos los elementos la lista pasa a tener cero elementos.");
  pa2m_afirmar(cola_vacia(cola_a_analizar), "Una lista a la que se le dapilaron todos sus elementos esta vacia.");

  cola_destruir(cola_a_analizar);
}


int main() {
  
  pa2m_nuevo_grupo("PRUEBAS DEL TDA LISTA");

  pa2m_nuevo_grupo("-Pruebas de creacion de una lista:");
  DadaUnaFuncionDeCrearUnaLista_CuandoSeUsa_EntoncesEstaSeCreaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de insercion de elementos al final de una lista vacia:");
  DadaUnaFuncionDeAgregarElementosAlFinalDeUnaLista_CuandoSeUsaSobreUnaListaVacia_EntoncesEstaFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de insercion de elementos al final de una lista con un elemento o mas:");
  DadaUnaFuncionDeAgregarElementosAlFinalDeUnaLista_CuandoSeUsaSobreUnaListaConMasDeUnELemento_EntoncesEstaFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de insercion de elementos en una posicion cualquiera de una lista con un elemento o mas:");
  DadaUnaFuncionDeAgregarUnElmentoEnCualquierParteDeUnaLista_CuandoSeUsaSobreCualquierPosicion_EntoncesLaFuncionFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de eliminacion de elementos al final de una lista:");
  DadaUnaFuncionDeELiminarUnElementoAlFinalDeUnaLista_CuandoSeLeLlama_EntoncesEstaFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de eliminacion de elementos en cualquier posicion de una lista:");
  DadaUnaFuncionDeEliminarUnElementoEnCualquierPosicionDeUnaLista_CuandoSeLeUsa_EntoncesFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas de busqueda de un elemento en una posicion cualquiera de una lista:");
  DadaUnaFuncionDeBuscarUnElementoEnUnaPosicionCualquieraDeUnaLista_CuandSeLeUsa_EntoncesElResultadoEsElEsperado();

  pa2m_nuevo_grupo("-Pruebas sobre verificar si una lista esta vacia:");
  DadaUnaFuncionQueVerificaSiUnaListaEstaVacia_CuandoSeLeUsa_EntoncesFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas sobre verificar la cantidad de elementos en una lista:");
  DadaUnaFuncionQueDevuelveElTamanioDeUnaLista_CuandoSeLeUsa_EntoncesFuncionaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas sobre la creacion de un iterador:");
  DadaUnaFuncionQueCreaUnIterador_CuandoSeLeUsa_EntoncesElIteradorSeCreaCorrectamente();

  pa2m_nuevo_grupo("-Pruebas sobre ver elementos en un iteraodr y avanza en el:");
  DadaUnGrupoDeFuncionesQuePermitenVerElElementoActualDeUnIteradorYAvazanzarEnEl_CuandoSeLesUsa_EntoncesFuncionanCorrectamente();

  pa2m_nuevo_grupo("-Pruebas sobre el elemento siguiente de un iterador:");
  DadaUnaFuncionQueVerificaSiUnIteradorTieneSiguiente_CuandoSeLeUsa_EntoncesFuncionaCorrectamente();

  pa2m_nuevo_grupo("PRUEBAS DEL TDA PILA");
  DadoUnTDAPila_CuandoSeLoUsa_EntoncesSuComportamientoEsElEsperado();

  pa2m_nuevo_grupo("PRUEBAS DEL TDA COLA");
  DadoUnTDACola_CuandoSeLoUsa_EntoncesSuComportamientoEsElEsperado();

  return pa2m_mostrar_reporte();
}
