#include<stdio.h>
#include<string.h>
#include "hospital.h"
#include "split.h"

#define SEPARADOR ';'


struct _hospital_pkm_t{
    size_t cantidad_entrenadores;
    size_t cantidad_pokemon;
    pokemon_t* vector_pokemones;
};

struct _pkm_t{
    char* nombre;
    size_t nivel;
};


/*
-Pre-condiciones: cantidad_pokemon debe ser mayor o igual que 0.

-Post-condicones: Ordena alfabeticamente (por nombre de pokemon) los pokemones contenidos en el vector pokemones.
*/
void ordenar_pokemones_alfabeticamente(pokemon_t* pokemones, size_t cantidad_pokemon){

    if(pokemones == NULL || cantidad_pokemon <= 0){
        return;
    }

    pokemon_t pokemon_auxliar;

    for(size_t i = 0; i < cantidad_pokemon-1; i++){

        for(size_t j = 0; j < cantidad_pokemon-1-i; j++){

            if(strcmp(pokemones[j].nombre, pokemones[j+1].nombre) > 0){

                pokemon_auxliar = pokemones[j];
                pokemones[j] = pokemones[j+1];
                pokemones[j+1] = pokemon_auxliar;
            }
        }
    }
}


/*
-Pre-condicones: hospital debe haber sido creado previamente.

-Post-condicones: Actualiza la información de hospital con la información contenida en pacientes.

-En caso de haber algun error en uno de los parametros, se devuelve NULL;
*/
hospital_t* actualizacion_de_hospital(hospital_t* hospital, char** pacientes){

    if(hospital == NULL || pacientes == NULL){
        return NULL;
    }

    size_t i = 2;
    size_t j = hospital->cantidad_pokemon;
    size_t longitud_nombre;
    int nivel;
    pokemon_t* vector_pokemones_aux;

    while(pacientes[i] != NULL){

        hospital->cantidad_pokemon++;
        vector_pokemones_aux = realloc(hospital->vector_pokemones, hospital->cantidad_pokemon*sizeof(pokemon_t));

        if(vector_pokemones_aux == NULL){
            hospital->cantidad_pokemon--;
            return NULL;
        }

        hospital->vector_pokemones = vector_pokemones_aux;

        longitud_nombre = strlen(pacientes[i]);
        hospital->vector_pokemones[j].nombre = malloc((longitud_nombre+1)*sizeof(char));

        if(hospital->vector_pokemones[j].nombre == NULL){
            hospital->cantidad_pokemon--;
            free(&hospital->vector_pokemones[j]);
            return NULL;
        }


        strcpy(hospital->vector_pokemones[j].nombre, pacientes[i]);
        i++;

        nivel = atoi(pacientes[i]);
        hospital->vector_pokemones[j].nivel = (size_t) nivel;

        j++;
        i++;
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


hospital_t* hospital_crear(){

    hospital_t* hospital_pokemon = calloc(1, sizeof(hospital_t));

    if(hospital_pokemon == NULL){
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

    if(hospital == NULL || funcion == NULL || hospital->vector_pokemones == NULL){
        return 0;
    }

    size_t cantidad = 0;
    ordenar_pokemones_alfabeticamente(hospital->vector_pokemones, hospital->cantidad_pokemon);
    bool se_sigue_recorriendo = true;

    size_t i = 0;
    while(i < hospital->cantidad_pokemon && se_sigue_recorriendo){

        se_sigue_recorriendo = funcion(&hospital->vector_pokemones[i]);
        i++;
        cantidad++;
    }
        
    return cantidad;
}


void hospital_destruir(hospital_t* hospital){

    if(hospital == NULL){
        return;
    }

    for(int i = 0; i < hospital->cantidad_pokemon; i++){
        free((hospital->vector_pokemones[i]).nombre);
    }

    free(hospital->vector_pokemones);
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

    return pokemon->nombre;
}
