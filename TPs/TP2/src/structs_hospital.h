#include"hospital.h"
#include"abb.h"
#include"lista.h"

struct _entrenador_t{
    size_t id;
    char* nombre_entrenador;
    abb_t* arbol_de_pokemones;
};

struct _hospital_pkm_t{
    size_t cantidad_entrenadores;
    size_t cantidad_pokemon;
    lista_t* lista_de_entrenadores;
    abb_t* pokemones_totales;
};

struct _pkm_t{
    entrenador_t* entrenador;
    char* nombre_pokemon;
    size_t nivel;
};