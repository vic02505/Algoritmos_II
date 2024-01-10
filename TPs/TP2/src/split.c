#include "split.h"
#include <stdlib.h>

/*
Pre-condiciones:
Post-condiciones:
*/
void escribir_substring(const char* string, char* substring, char separador){

  size_t i = 0;
  size_t j = 0;
  while(string[i] != '\0' && string[i] != separador){
    
    substring[j] = string[i];
    
    i++;
    j++;
  }
  
  substring[j] = '\0';
}


/*
Pre-condiciones:
Post-condiciones:
*/
size_t longitud_substring(const char* string, char separador){
  
  size_t longitud = 0;
  
  size_t i = 0;
  while(*(string+i) != '\0' && *(string+i) != separador){
    longitud++;
    i++;
  }
  
  return longitud+1;
}


/*
Pre-condiciones: string NO debe ser NULL. 
Post-condiciones: Devuelve la cantidad de particiones que deben hacersele a string para hacerle un split.
*/
size_t particiones_de_string(const char* string, char separador){

    size_t cantidad_de_particiones = 0;

    int i = 0;
    while(string[i] != '\0'){

        if(string[i] == separador){
            cantidad_de_particiones++;
        }

        i++;
    }

    return cantidad_de_particiones+2;
}


char** split(const char* string, char separador){

    if(string == NULL){
        return NULL;
    }

    size_t longitud_string_con_split = particiones_de_string(string, separador);
    char** string_con_split = malloc(longitud_string_con_split*sizeof(char*));

    if(string_con_split == NULL){
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    size_t longitud;
    while(i < longitud_string_con_split-1){

        longitud = longitud_substring(string+j, separador);
        string_con_split[i] = malloc(longitud*sizeof(char));

        if(string_con_split[i] == NULL){
            return NULL;
        }

        escribir_substring(string+j, *(string_con_split+i), separador);

        j+= longitud;
        i++;
    }

    string_con_split[longitud_string_con_split-1] = NULL;

    return string_con_split;
}
