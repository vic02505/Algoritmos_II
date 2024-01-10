#include"simulador.h"
#include"heap.h"
#include"lista.h"
#include"hospital.h"
                                                
typedef struct sala_de_espera{                  
    unsigned entrenadores_totales;               
    unsigned entrenadores_atendidos;              
    unsigned pokemones_atendidos;               
    unsigned pokemones_en_espera;              
    unsigned pokemones_totales;                
}sala_de_espera_t;                                                       
                                                  
struct _simulador_t{                              
    hospital_t* hospital_de_pokemones;            
    lista_iterador_t* iterador_de_entrenadores; 
    sala_de_espera_t sala_de_espera;
    DatosDificultad* dificultad_activa;
    lista_t* lista_de_dificultades;            
    heap_t* pokemones_a_atender;            
    pokemon_t* pokemon_en_tratamiento;
    bool existe_pokemon_en_tratamiento;
    bool simulador_ha_finalizado;
    unsigned puntos_simulador;
    unsigned eventos_simulados;
    unsigned intentos_de_adivinacion_de_nivel;
};