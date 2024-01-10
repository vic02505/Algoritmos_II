#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"hash.h"
#include"lista.h"

#define CAPACIDAD_MINIMA_ACEPTADA_PARA_EL_HASH 3
#define VALOR_DE_REHASH 0.75
#define INSERCION_FALLIDA -1
#define INSERCION_EXITOSA 0
#define REHASH_FALLIDO -1
#define REHASH_EXITOSO 0 
#define ELIMINACION_FALLIDA -1
#define ELIMINACION_EXITOSA 0


typedef struct elemento_del_hash{
    char* clave;  
    void* elemento;
}elemento_del_hash_t;

typedef struct tabla_de_hash{
    lista_t* lista;
}tabla_de_hash_t;

struct hash{
    tabla_de_hash_t* tabla_de_hash;
    size_t capacidad_de_la_tabla;
    size_t cantidad_de_elementos_en_el_hash;
    hash_destruir_dato_t destructor;
};


//FUNCIONES PRIVADAS:


/*
Pre-condiciones: 
-cantidad_total_de_elementos_en_el_hash debe estar en el rango [0-capacidad_del_la_tabla].
-capacidad_de_la_tabla debe ser mayor o igual que 3.

Post-condiciones: Devuelve un numero entre 0 y 1 que da a entender que tan lleno esta el hash.
*/
float factor_de_carga(size_t cantidad_de_elementos_en_el_hash, size_t capacidad_de_la_tabla){
    return ((float)cantidad_de_elementos_en_el_hash)/((float)capacidad_de_la_tabla);
}


/*
Pre-condiciones: 
-capacidad_de_la_tabla debe ser un numero mayor o igual que 3.
-clave debe ser un string no NULO.

Post-condiciones: Devuelve un numero positivo que correspode a la posicion en la tabla de hash que le corresponde a clave.
*/
size_t funcion_hash(const char* clave, size_t capacidad_de_la_tabla){

    size_t valor_de_hash = 0;

    for(size_t i = 0; clave[i] != '\0'; i++){
        valor_de_hash += (size_t)clave[i];
    }

    return valor_de_hash%(capacidad_de_la_tabla);
}


/*
Pre-condiciones: Debe recibir una lista no NULA, destructor puede ser NULL en caso de que el usuario opte por ello.

Post-condiciones: Destruye cada uno de los elementos insertados en una lista de la tabla de hash (registro del tipo elemento_del_hash_t), para esto 
libera el campo clave de cada registro insertado. En caso de que el usuario opte por usar destructor (en otro caso se debera recibir NULL) se le aplica el 
destructor al campo elemento de cada registro insertado.
*/
void destruir_elementos_de_lista(lista_t* lista, hash_destruir_dato_t destructor){

    if(!lista || lista_vacia(lista)){
        return;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista);
    elemento_del_hash_t* objeto_a_destruir;

    if(!iterador){
        return;
    }

    while(lista_iterador_tiene_siguiente(iterador)){

        objeto_a_destruir = (elemento_del_hash_t*)lista_iterador_elemento_actual(iterador);

        if(objeto_a_destruir != NULL){

            free(objeto_a_destruir->clave);

            if(destructor != NULL){
                destructor(objeto_a_destruir->elemento);
            }

            free(objeto_a_destruir);
        }

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
}


/*
Pre-condiciones: hash no debe ser NULL, clave no debe ser NULL.

Post-condiciones: Devuelve 0 si la insercion fue existosa, en caso contrario (insercion fallida o error) devuelve -1.
*/
int hash_insertar_aux(hash_t* hash, const char* clave, void* elemento){

    if(!hash || !clave){
        return INSERCION_FALLIDA;
    }

    size_t valor_de_hash = funcion_hash(clave, hash->capacidad_de_la_tabla);
    elemento_del_hash_t* objeto_a_insertar = malloc(sizeof(elemento_del_hash_t));

    if(!objeto_a_insertar){
        return INSERCION_FALLIDA;
    }

    objeto_a_insertar->clave = malloc((strlen(clave)+1)*sizeof(char));
    
    if(!objeto_a_insertar->clave){
        free(objeto_a_insertar);
        return INSERCION_FALLIDA;
    }

    strcpy(objeto_a_insertar->clave, clave);
    objeto_a_insertar->elemento = elemento;

    if(!hash->tabla_de_hash[valor_de_hash].lista){

        hash->tabla_de_hash[valor_de_hash].lista = lista_crear();

        if(!hash->tabla_de_hash[valor_de_hash].lista){
            return INSERCION_FALLIDA;
        }

    }

    lista_insertar(hash->tabla_de_hash[valor_de_hash].lista, (void*)objeto_a_insertar);
    hash->cantidad_de_elementos_en_el_hash++;

    return INSERCION_EXITOSA;
}


/*
Pre-condiciones:
-lista no debe ser NULL ni estar vacia.
-Clave no debe ser NULL.

Post-condiciones: Recorre la lista buscando el elemento en ella asociado a clave. Devuelve su posicion en caso de encontralo y -1 en
caso de que no se encuentre la lista o de un error.
*/
size_t posicion_de_elemento(lista_t* lista, const char* clave){

    if(!lista ||  !clave || lista_vacia(lista)){
        return -1;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista);
    elemento_del_hash_t* elemento;

    if(!iterador){
        return -1;
    }

    size_t i = 0;
    size_t posicion_a_buscar = -1;
    bool encontrado = false;
    while(lista_iterador_tiene_siguiente(iterador) && !encontrado){

        elemento = (elemento_del_hash_t*)lista_iterador_elemento_actual(iterador);

        if(elemento != NULL && strcmp(elemento->clave, clave) == 0){
            posicion_a_buscar = i;
            encontrado = true;
        }

        i++;
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
    return posicion_a_buscar;
}


/*
Pre-condiciones:
-lista_a_iterar no debe ser NULL ni estar vacia.
-clave no debe ser NULL.

Post-condiciones: Itera la lista buscando si se encuentra el elemento asociado a clave. Devuelve un registro del tipo elemento_del_hah_t en caso
de encontarlo (el registro tiene tanto a la clave como el elemento asociado en ella como campos). De no encontrarse o en caso de error se devolvera NULL.
*/
elemento_del_hash_t* iterar_hasta(lista_t* lista_a_iterar, const char* clave){

    if(!lista_a_iterar || lista_vacia(lista_a_iterar) || !clave){
        return NULL;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista_a_iterar);
    elemento_del_hash_t* elemento_a_buscar;
    bool encontrado = false;

    if(!iterador){
        return NULL;
    }

    while(lista_iterador_tiene_siguiente(iterador) && !encontrado){

        elemento_a_buscar = (elemento_del_hash_t*)lista_iterador_elemento_actual(iterador);

        if(strcmp(elemento_a_buscar->clave, clave) == 0){
            encontrado = true;
        }

        lista_iterador_avanzar(iterador);
    }

    if(!encontrado){
        lista_iterador_destruir(iterador);
        return NULL;
    }

    lista_iterador_destruir(iterador);
    return elemento_a_buscar;
}


/*
Pre-condiciones:
-tabla_de_hash no debe ser NULL
-capacidad debe ser mayor o igual que 3 y debe corresponderse a la capacidad de tabla_de_hash.

Post-Condiciones: En caso de tener memoria reservada, libera toda la memoria usada por tabla_de_hash.
*/
void liberar_tabla_de_hash(tabla_de_hash_t* tabla_de_hash, size_t capacidad){

    if(!tabla_de_hash){
        return;
    }

    for(size_t i = 0; i < capacidad; i++){

        if(tabla_de_hash[i].lista != NULL && !lista_vacia(tabla_de_hash[i].lista)){
            destruir_elementos_de_lista(tabla_de_hash[i].lista, NULL);
            lista_destruir(tabla_de_hash[i].lista);
        }
    }

    free(tabla_de_hash);
}


/*
Pre-condiciones:
-lista no deber NULL.
-hash no deber ser NULL.

Post-condiciones: Inserta todos los elmentos contenidos en una lista en hash_a_insertar.
*/
void reinsertar_elementos_de_hash(lista_t* lista, hash_t* hash_a_insertar){

    if(!lista || lista_vacia(lista) || !hash_a_insertar){
        return;
    }

    elemento_del_hash_t* objeto_a_reinsertar;
    lista_iterador_t* iterador = lista_iterador_crear(lista);

    if(!iterador){
        return;
    }

    while(lista_iterador_tiene_siguiente(iterador)){

        objeto_a_reinsertar = (elemento_del_hash_t*)lista_iterador_elemento_actual(iterador);

        if(objeto_a_reinsertar != NULL){
            hash_insertar_aux(hash_a_insertar, objeto_a_reinsertar->clave, objeto_a_reinsertar->elemento);
        }

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
    return;
}


/*
Pre-condiciones: hash no debe ser NULL.

Post-condiciones: rehashea el hash y todo su contenido haciendo uso de un hash auxiliar.
*/
int rehash(hash_t* hash){

    hash_t* hash_auxiliar = hash_crear(hash->destructor, 2*(hash->capacidad_de_la_tabla));
    
    if(!hash_auxiliar){
        return REHASH_FALLIDO;
    }

    for(size_t i = 0; i < hash->capacidad_de_la_tabla; i++){

        if(hash->tabla_de_hash[i].lista != NULL && !lista_vacia(hash->tabla_de_hash[i].lista)){ //ACA HABIA UN ERROR 
            reinsertar_elementos_de_hash(hash->tabla_de_hash[i].lista, hash_auxiliar);
        }
    }

    liberar_tabla_de_hash(hash->tabla_de_hash, hash->capacidad_de_la_tabla);
    hash->tabla_de_hash = hash_auxiliar->tabla_de_hash;
    hash->capacidad_de_la_tabla = hash_auxiliar->capacidad_de_la_tabla;
    free(hash_auxiliar);

    return REHASH_EXITOSO;
}


//FUNCIONES PUBLICAS:


hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){

    hash_t* hash = calloc(1, sizeof(hash_t));

    if(!hash){
        return NULL;
    }

    if(capacidad_inicial <= CAPACIDAD_MINIMA_ACEPTADA_PARA_EL_HASH){

        hash->capacidad_de_la_tabla = CAPACIDAD_MINIMA_ACEPTADA_PARA_EL_HASH;
        hash->destructor = destruir_elemento;
        hash->tabla_de_hash = calloc(CAPACIDAD_MINIMA_ACEPTADA_PARA_EL_HASH, sizeof(tabla_de_hash_t));

        if(!hash->tabla_de_hash){
            free(hash);
            return NULL;
        }

    }
    else{

        hash->capacidad_de_la_tabla = capacidad_inicial;
        hash->destructor = destruir_elemento;
        hash->tabla_de_hash = calloc(capacidad_inicial, sizeof(tabla_de_hash_t));

        if(!hash->tabla_de_hash){
            free(hash);
            return NULL;
        }
    }

    return hash;
}


int hash_insertar(hash_t* hash, const char* clave, void* elemento){

    if(!hash || !clave){
        return INSERCION_FALLIDA;
    }

    if(hash_contiene(hash, clave)){

        size_t valor_de_hash = funcion_hash(clave, hash->capacidad_de_la_tabla);
        elemento_del_hash_t* objeto_a_actualizar = iterar_hasta(hash->tabla_de_hash[valor_de_hash].lista, clave);

        if(hash->destructor != NULL){
            hash->destructor(objeto_a_actualizar->elemento);
        }

        objeto_a_actualizar->elemento = elemento;
        return INSERCION_EXITOSA;
    }

    int estado_de_insercion = hash_insertar_aux(hash, clave, elemento);

    if(factor_de_carga(hash->cantidad_de_elementos_en_el_hash, hash->capacidad_de_la_tabla) >= VALOR_DE_REHASH){
        estado_de_insercion = rehash(hash);
    }

    return estado_de_insercion;
}


int hash_quitar(hash_t* hash, const char* clave){

    if(!hash || !clave){
        return ELIMINACION_FALLIDA;
    }

    size_t valor_de_hash = funcion_hash(clave, hash->capacidad_de_la_tabla);
    elemento_del_hash_t* objeto_a_eliminar;

    if(!hash->tabla_de_hash[valor_de_hash].lista){
        return ELIMINACION_FALLIDA;
    }
    
    size_t posicion_a_eliminar = posicion_de_elemento(hash->tabla_de_hash[valor_de_hash].lista, clave);

    if(posicion_a_eliminar == -1){
        return ELIMINACION_FALLIDA;
    }

    objeto_a_eliminar = (elemento_del_hash_t*)lista_quitar_de_posicion(hash->tabla_de_hash[valor_de_hash].lista, posicion_a_eliminar);

    if(!objeto_a_eliminar){
        return ELIMINACION_FALLIDA;
    }

    free(objeto_a_eliminar->clave);

    if(hash->destructor != NULL){
        hash->destructor(objeto_a_eliminar->elemento);
    }

    free(objeto_a_eliminar);
    hash->cantidad_de_elementos_en_el_hash--;
    return ELIMINACION_EXITOSA;
}


void* hash_obtener(hash_t* hash, const char* clave){

    if(!hash || !clave){
        return NULL;
    }

    size_t valor_de_hash = funcion_hash(clave, hash->capacidad_de_la_tabla);

    if(!hash->tabla_de_hash[valor_de_hash].lista){
        return NULL;
    }
    
    elemento_del_hash_t* elemento_buscado = iterar_hasta(hash->tabla_de_hash[valor_de_hash].lista, clave);

    if(!elemento_buscado){
        return NULL;
    }

    return elemento_buscado->elemento;
}


bool hash_contiene(hash_t* hash, const char* clave){

    if(!hash || !clave){
        return false;
    }

    size_t valor_de_hash = funcion_hash(clave, hash->capacidad_de_la_tabla);

    if(!hash->tabla_de_hash[valor_de_hash].lista){
        return false;
    }

    return posicion_de_elemento(hash->tabla_de_hash[valor_de_hash].lista, clave) != -1;
}


size_t hash_cantidad(hash_t* hash){

    if(!hash){
        return 0;
    }

    return hash->cantidad_de_elementos_en_el_hash;
}


void hash_destruir(hash_t* hash){

    if(!hash){
        return;
    }

    for(size_t i = 0; i < hash->capacidad_de_la_tabla; i++){
        destruir_elementos_de_lista(hash->tabla_de_hash[i].lista, hash->destructor);
        lista_destruir(hash->tabla_de_hash[i].lista);
    }

    free(hash->tabla_de_hash);
    free(hash);
}


size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){

    if(!hash || !funcion){
        return 0;
    }

    size_t cantidad_iteraciones = 0;
    elemento_del_hash_t* elemento_del_hash = NULL;

    for(int i = 0; i < hash->capacidad_de_la_tabla; i++){

        if(hash->tabla_de_hash[i].lista != NULL || !lista_vacia(hash->tabla_de_hash[i].lista)){

            lista_iterador_t* iterador = lista_iterador_crear(hash->tabla_de_hash[i].lista);

            if(!iterador){
                return cantidad_iteraciones;
            }

            while(lista_iterador_tiene_siguiente(iterador)){
                cantidad_iteraciones++;
                elemento_del_hash = (elemento_del_hash_t*)lista_iterador_elemento_actual(iterador);
            
                if(funcion(hash, elemento_del_hash->clave, aux) == true){
                    lista_iterador_destruir(iterador);
                    return cantidad_iteraciones;
                }
            
                lista_iterador_avanzar(iterador);
            }

            lista_iterador_destruir(iterador);
        }
    }

    return cantidad_iteraciones;
}