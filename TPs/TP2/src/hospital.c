#include<stdio.h>
#include<string.h>
#include "hospital.h"
#include"abb.h"
#include"split.h"
#include"lista.h"
#include"structs_hospital.h"

#define SEPARADOR ';'


/*
Pre-condiciones: pokemon_a_destruir no debe ser NULL.

Post-condiciones: Libera la memoria ocupada por un pokemon. En caso de error, la funcion no hace nada.
*/
void destructor_de_pokemones(void* pokemon_a_destruir){

    if(!pokemon_a_destruir){
        return;
    }

    pokemon_t* pokemon_aux = (pokemon_t*)pokemon_a_destruir;

    free(pokemon_aux->nombre_pokemon);
    pokemon_aux->entrenador = NULL;
    free(pokemon_aux);
}


/*
Pre-condiciones: c1 y c2 deben ser elementos de tipo pokemon_t* casteados a void*. Ninguno de los dos debe ser NULL.
c1 y c2 -> elementos a comparar.

Post-condiciones: Hace una comparacion entre el nombre de pokemon contenido en c1 y el contenido en c2, devuelve el
resultado de esta comparacion (quien es mayor en el alfabeto). Devuelve el resultado de esta comparacion.
*/
int comparador(void* c1, void* c2){

    pokemon_t* pokemon = (pokemon_t*)c1;
    pokemon_t* pokemon_a_comparar = (pokemon_t*)c2;

    return strcmp(pokemon->nombre_pokemon, pokemon_a_comparar->nombre_pokemon);
}


/*
Pre-condiciones: paciente no debe ser NULL.

Post-condiciones: Crea un entrenador con la informacion contenida en pacientes (es decir, el entrenador y sus pokemones).
*/
entrenador_t* crear_entrenador(char** pacientes){

    if(!pacientes){
        return NULL;
    }

    entrenador_t* entrenador_a_crear = malloc(sizeof(entrenador_t));

    if(!entrenador_a_crear){
        return NULL;
    }

    size_t longitud_nombre = strlen(pacientes[1]);

    entrenador_a_crear->nombre_entrenador = malloc((longitud_nombre+1)*sizeof(char));

    if(!entrenador_a_crear->nombre_entrenador){
        free(entrenador_a_crear);
        return NULL;
    }

    entrenador_a_crear->id = (size_t)atoi(pacientes[0]);
    strcpy(entrenador_a_crear->nombre_entrenador, pacientes[1]);

    return entrenador_a_crear;
}

/*
Pre-condiciones:
-hospital no debe ser NULL.
-arbol_de_pokemones no debe ser NULL. EL contenido de arbol de pokemones deben ser los pokemones correspondientes a
entrenador.
-entrenador no debe ser NULL.

Post-condiciones: Carga a entrenador con su arbol de pokemones. Luego inserta al entrenador en la lista de entrenadores del
hospital. La fucniond devuelve la lista en caso de exito, en otro caso devuelve NULL.
*/
lista_t* agregar_entrenador_al_hospital(hospital_t* hospital,  abb_t* arbol_de_pokemones, entrenador_t* entrenador){

    if(!hospital || !arbol_de_pokemones || !entrenador){
        return NULL;
    }

    entrenador->arbol_de_pokemones = arbol_de_pokemones;
    lista_t* salida = lista_insertar(hospital->lista_de_entrenadores, (void*)entrenador);

    return salida;
}


/*
Pre-condiciones:
-arbol_de_pokemones no debe ser NULL.
-nombre_pokemon no debe ser NULL.
-nivel_pokemon no debe ser NULL.
-entrenador no debe ser NULL. entrenador debe ser el entrenador del pokemon que se quiera cargar al arbol.

Post-condiciones: Crea un pokemon con toda su infromacion (nivel, nombre, entrenador) y lo carga al arbol. La funcion
devuelve el arbol en caso de exito, en otro caso, devuelve NULL.
*/
abb_t* cargar_arbol_de_pokemones(abb_t* arbol_de_pokemones, char* nombre_pokemon, char* nivel_pokemon, entrenador_t* entrenador){

    if(!arbol_de_pokemones || !nombre_pokemon || !nivel_pokemon || !entrenador){
        return NULL;
    }

    pokemon_t* pokemon_a_agregar = malloc(sizeof(pokemon_t));
    
    if(!pokemon_a_agregar){
        return NULL;
    }

    pokemon_a_agregar->nombre_pokemon = malloc((strlen(nombre_pokemon)+1)*sizeof(char));

    if(!pokemon_a_agregar->nombre_pokemon){
        free(pokemon_a_agregar);
        return NULL;
    }


    strcpy(pokemon_a_agregar->nombre_pokemon, nombre_pokemon);
    pokemon_a_agregar->entrenador = entrenador;
    pokemon_a_agregar->nivel = (size_t)atoi(nivel_pokemon);

    abb_t* arbol_de_pokemones_aux = abb_insertar(arbol_de_pokemones, (void*)pokemon_a_agregar);

    if(!arbol_de_pokemones_aux){
        free(pokemon_a_agregar->nombre_pokemon);
        free(pokemon_a_agregar);
        return NULL;
    }

    return arbol_de_pokemones_aux;
}


/*
Pre-condiciones: 
-pokemones_totales no debe ser NULL.
-nombre_pokemon no debe ser NULL.
-nivel no debe ser NULL.
-entrenador no debe ser NULL. entrenador debe ser el entrenador del pokemon que se quiere agregar en pokemones_totales.

Post-condiciones: Crea un pokemon con toda su informacion (nivel, nombre, entrenador) y guarda en un arbol (pokemones totales).
La funcion devuelve el arbol en caso de exito, en otro caso devuelve NULL.

NOTA: Este arbol es un arbol que tiene la totalidad de los pokemones del hospital, no los pokemones de un entrenador.
*/
abb_t* cargar_arbol_de_pokemones_totales(abb_t* pokemones_totales, char* nombre_pokemon, char* nivel, entrenador_t* entrenador){

    if(!pokemones_totales || !nombre_pokemon || !entrenador || !nivel){
        return NULL;
    }

    pokemon_t* pokemon_a_guardar = malloc(sizeof(pokemon_t));

    if(!pokemon_a_guardar){
        return NULL;
    }

    pokemon_a_guardar->nombre_pokemon = malloc((strlen(nombre_pokemon)+1)*sizeof(char));

    if(!pokemon_a_guardar->nombre_pokemon){
        free(pokemon_a_guardar);
        return NULL;
    }


    strcpy(pokemon_a_guardar->nombre_pokemon, nombre_pokemon);
    pokemon_a_guardar->entrenador = entrenador;
    pokemon_a_guardar->nivel = (size_t)nivel;

    abb_t* arbol_de_pokemones_aux = abb_insertar(pokemones_totales, (void*)pokemon_a_guardar);

    if(!arbol_de_pokemones_aux){
        free(pokemon_a_guardar->nombre_pokemon);
        free(pokemon_a_guardar);
        return NULL;
    }

    return arbol_de_pokemones_aux;
}

/*
Pre-condiciones:
-hospital no debe ser NULL.
-pacientes no debe ser NULL.

Post-condiciones: Carga el hospital con la informacion contenida en pacientes. La funcion devuelve el hospital en caso
de exito, en otro caso, devuelve NULL. Si hay un error y se lograron cargar algunos pacientes, el hospital guarda la informacion
guardada antes del error,
*/
hospital_t* actualizacion_de_hospital(hospital_t* hospital, char** pacientes){

    if(!hospital || !pacientes){
        return NULL;
    }

    entrenador_t* entrenador_a_agregar = crear_entrenador(pacientes);

    if(!entrenador_a_agregar){
        return NULL;
    }

    size_t i = 2;

    abb_t* arbol_de_pokemones = abb_crear(comparador);

    if(!arbol_de_pokemones){
        free(entrenador_a_agregar->nombre_entrenador);
        free(entrenador_a_agregar);
        return NULL;
    }

    while(pacientes[i] != NULL){

        abb_t* arbol_de_pokemones_aux = cargar_arbol_de_pokemones(arbol_de_pokemones, pacientes[i], pacientes[i+1], entrenador_a_agregar);
        abb_t* pokemones_totales_aux = cargar_arbol_de_pokemones_totales(hospital->pokemones_totales, pacientes[i], pacientes[i+1], entrenador_a_agregar);

        if(!arbol_de_pokemones_aux || !pokemones_totales_aux){
            return NULL;
        }

       i += 2;
       hospital->cantidad_pokemon++;
    }

    lista_t* lista_de_entrenadores_aux = agregar_entrenador_al_hospital(hospital, arbol_de_pokemones, entrenador_a_agregar);

    if(!lista_de_entrenadores_aux){
        abb_destruir_todo(arbol_de_pokemones, destructor_de_pokemones);
        abb_destruir_todo(hospital->pokemones_totales, destructor_de_pokemones);
        free(entrenador_a_agregar->nombre_entrenador);
        free(entrenador_a_agregar);
        return NULL;
    }

    return hospital;
}


/*
-Pre-condiciones: archivo_a_leer debe ser un arhivo abierto en modo de lectura "r".

-Post-condiciones: Devuelve la linea de la posición actual del archivo como un string (la lee hasta un \n);

*Devuelve NULL si hubo algun error.

*/
char* proxima_linea_de_archivo(FILE* archivo_a_leer){

    char* linea_de_archivo = calloc(2, sizeof(char));
    char* linea_de_archivo_aux;
    size_t contador = 2; 

    if(linea_de_archivo == NULL){
        return NULL;
    }

    char caracter_leido;
    int i = 0;

    caracter_leido = (char)fgetc(archivo_a_leer);

    if(caracter_leido == EOF){
        free(linea_de_archivo);
        return NULL;
    }

    while(caracter_leido != '\n'){

        linea_de_archivo[i] = caracter_leido;
        contador++;
        linea_de_archivo_aux = realloc(linea_de_archivo, contador*sizeof(char));

        if(linea_de_archivo_aux == NULL){
            free(linea_de_archivo);
            return NULL;
        }
        
        linea_de_archivo = linea_de_archivo_aux;

        caracter_leido = (char)fgetc(archivo_a_leer);

        if(caracter_leido == EOF){
            free(linea_de_archivo);
            return NULL;
        }

        i++;
    }

    linea_de_archivo[i] = '\0';


    return linea_de_archivo;
}

//Funciones publicas:

hospital_t* hospital_crear(){

    hospital_t* hospital_pokemon = calloc(1, sizeof(hospital_t));

    if(hospital_pokemon == NULL){
        return NULL;
    }
    
    hospital_pokemon->lista_de_entrenadores = lista_crear();

    if(!hospital_pokemon->lista_de_entrenadores){
        free(hospital_pokemon);
        return NULL;
    }

    hospital_pokemon->pokemones_totales = abb_crear(comparador);

    if(!hospital_pokemon->pokemones_totales){
        lista_destruir(hospital_pokemon->lista_de_entrenadores);
        free(hospital_pokemon);
        return NULL;
    }

    return hospital_pokemon;
}


bool hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo){

    if(hospital == NULL){
        return false;
    }

    FILE* info_pacientes = fopen(nombre_archivo, "r");

    if(!info_pacientes){
        return false;
    }

    char* linea_de_archivo = NULL;
    char** split_linea_de_archivo = NULL;

    linea_de_archivo = proxima_linea_de_archivo(info_pacientes);

    while(!feof(info_pacientes)){

        if(linea_de_archivo == NULL){
            fclose(info_pacientes);
            return false;
        }

        split_linea_de_archivo = split(linea_de_archivo, SEPARADOR);

        if(split_linea_de_archivo == NULL){
            free(linea_de_archivo);
            fclose(info_pacientes);
            return false;
        }

        actualizacion_de_hospital(hospital, split_linea_de_archivo);  
        hospital->cantidad_entrenadores++;      

        free(linea_de_archivo);

        for(int i = 0;  split_linea_de_archivo[i] != NULL; i++){
            free(split_linea_de_archivo[i]);
        }

        free(split_linea_de_archivo);

        linea_de_archivo = proxima_linea_de_archivo(info_pacientes);
    }

    free(linea_de_archivo);
    fclose(info_pacientes);

    return true;
}


size_t hospital_cantidad_pokemon(hospital_t* hospital){

    if(hospital == NULL){
       return  0; 
    }
    else{
        return hospital->cantidad_pokemon;
    }
}


size_t hospital_cantidad_entrenadores(hospital_t* hospital){
    
    if(hospital == NULL){
        return 0;
    }
    else{
        return hospital->cantidad_entrenadores;
    }
}


size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){

    if(!hospital || !funcion){
        return 0;
    }

    void** vector_de_pokemones = malloc((hospital->cantidad_pokemon)*sizeof(void*));
    size_t  cantidad = 0;

    if(!vector_de_pokemones){
        return 0;
    }

    abb_recorrer(hospital->pokemones_totales, INORDEN, vector_de_pokemones, hospital->cantidad_pokemon);

    bool estado = true;
    size_t i = 0;

    while(estado && i < hospital->cantidad_pokemon){

        estado = funcion(vector_de_pokemones[i]);
        
        cantidad++;
        i++;
    } 
    
    free(vector_de_pokemones);
    return cantidad;
  
}


void hospital_destruir(hospital_t* hospital){

    if(!hospital){
        return;
    }
    
    while(lista_tamanio(hospital->lista_de_entrenadores) != 0){

        entrenador_t* entrenador = (entrenador_t*)lista_quitar_de_posicion(hospital->lista_de_entrenadores, 0);

        free(entrenador->nombre_entrenador);
        abb_destruir_todo(entrenador->arbol_de_pokemones, destructor_de_pokemones);
        free(entrenador);
    }

    abb_destruir_todo(hospital->pokemones_totales, destructor_de_pokemones);
    lista_destruir(hospital->lista_de_entrenadores);
    free(hospital);
}


size_t pokemon_nivel(pokemon_t* pokemon){
    
    if(pokemon == NULL){
        return 0;
    }

    return pokemon->nivel;
}


const char* pokemon_nombre(pokemon_t* pokemon){

    if(pokemon == NULL){
        return NULL;
    }

    return pokemon->nombre_pokemon;
}

entrenador_t* pokemon_entrenador(pokemon_t* pokemon){

    if(!pokemon){
        return NULL;
    }

    return pokemon->entrenador;
}
