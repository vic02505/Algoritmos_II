#include "pa2mm.h"
#include "src/hospital.h"
#include"src/simulador.h"
#include"src/structs_simulador.h"
#include"src/structs_hospital.h"
#include"src/heap.h"
#include "string.h"
#include <stdbool.h>

#define RUTA_ARCHIVO_ENTRENADORES "ejemplos/varios_entrenadores.hospital"

bool ignorar_pokemon(pokemon_t* p){
    p = p;
    return true;
}

/* No intenten esto en sus casas */
/* Ya vamos a ver como evitar esto en el TDA Lista */
struct{
    pokemon_t* pokemon[500];
    size_t cantidad;
} acumulados;

void resetear_acumulados(){
    acumulados.cantidad = 0;
}

bool acumular_pokemon(pokemon_t* p){
    acumulados.pokemon[acumulados.cantidad] = p;
    acumulados.cantidad++;
    return true;
}

bool acumular_pokemon_hasta_miltank(pokemon_t* p){
    acumulados.pokemon[acumulados.cantidad] = p;
    acumulados.cantidad++;
    return strcmp(pokemon_nombre(p), "miltank");
}

bool acumulados_en_orden_correcto(){
    if(acumulados.cantidad < 2)
        return true;
    pokemon_t* anterior = acumulados.pokemon[0];
    for(int i=1;i<acumulados.cantidad;i++){
        pokemon_t* actual =  acumulados.pokemon[i];
        if(strcmp(pokemon_nombre(anterior), pokemon_nombre(actual)) > 0)
            return false;
    }
    return true;
}

/* Pruebas */

void puedoCrearYDestruirUnHospital(){
    hospital_t* h=NULL;

    pa2m_afirmar((h=hospital_crear()), "Crear un hospital devuelve un hospital");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==0, "Un hospital se crea con cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==0, "Un hospital se crea con cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon)==0, "Recorrer los pokemon resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnHospitalNULL_lasPuedoAplicarLasOperacionesDelHospitalSinProblema(){
    hospital_t* h=NULL;

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==0, "Un hospital NULL tiene cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==0, "Un hospital NULL tiene cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon)==0, "Recorrer los pokemon de un hospital NULL resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnArchivoVacio_NoSeAgreganPokemonAlHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/archivo_vacio.hospital"), "Puedo leer un archivo vacío");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==0, "Un hospital vacío tiene cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==0, "Un hospital vacío tiene tiene cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon)==0, "Recorrer los pokemon resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnArchivoConUnEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/un_entrenador.hospital"), "Puedo leer un archivo con un entrenador");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==1, "El hospital tiene 1 entrenador");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==3, "El hospital tiene 3 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon)==3, "Recorrer los pokemon resulta en 3 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

void dadoUnArchivoConVariosEntrenadores_SeAgreganLosEntrenadoresYSusPokemonAlHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==5, "El hospital tiene 5 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==24, "El hospital tiene 24 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon)==24, "Recorrer los pokemon resulta en 24 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}


void dadosVariosArchivos_puedoAgregarlosTodosAlMismoHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer otro archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un tercer archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==15, "El hospital tiene 15 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==72, "El hospital tiene 72 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon)==72, "Recorrer los pokemon resulta en 72 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}


//PRUEBAS HECHAS POR MI:


void DadoUnSimulador_CuandoSeLoCrea_EntoncesElResultadoEsElEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    pa2m_afirmar(simulador_a_analizar->sala_de_espera.entrenadores_totales == hospital_cantidad_entrenadores(simulador_a_analizar->hospital_de_pokemones), "Cuando se crea el simulador, la cantidad total de entrenadores es la esperada.");
    pa2m_afirmar(simulador_a_analizar->sala_de_espera.entrenadores_atendidos == 0, "Cuando se crea el simulador, la cantidad de pokemones atentidos es 0.");
    pa2m_afirmar(simulador_a_analizar->sala_de_espera.pokemones_atendidos == 0, "Cuando se crea el simulador, la cantidad de pokemones atendidos es 0.");
    pa2m_afirmar(simulador_a_analizar->sala_de_espera.pokemones_en_espera == 0, "Cuando se crea el simulador, la cantidad de pokemones en espera es 0.");
    pa2m_afirmar(simulador_a_analizar->sala_de_espera.pokemones_totales == hospital_cantidad_pokemon(simulador_a_analizar->hospital_de_pokemones), "Cuando se crea el simulador, la cantidad de total es pokemones es la esperada.");
    pa2m_afirmar(simulador_a_analizar->puntos_simulador == 0, "Cuando se crea el simulador, la cantidad de puntos obtenidos en el es 0.");
    pa2m_afirmar(simulador_a_analizar->eventos_simulados == 0, "Cuando se crea el simulador, la cantidad de eventos simulados es 0.");


    simulador_destruir(simulador_a_analizar);
}


void DadoUnSimulador_CuandoSeLoCrea_EntoncesAlObtenerSusEstadisticasElResultadoEsElEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);
    EstadisticasSimulacion* estadisticas = malloc(sizeof(EstadisticasSimulacion));

    simulador_simular_evento(simulador_a_analizar, ObtenerEstadisticas, estadisticas);

    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0, "En las estadisticas de un simulador recien creado, no hay entrenadores atendidos.");
    pa2m_afirmar(estadisticas->entrenadores_totales == simulador_a_analizar->sala_de_espera.entrenadores_totales, "En las estadisticas de un simulador recien creados, la cantidad de entrenadores totales es la esperada.");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 0, "En las estadisticas de un simulador recien creado, la cantidad de pokemones atendidos es 0.");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 0, "En las estadisticas de un simulador recien creado, no hay pokemones en espera de ser atendidos.");
    pa2m_afirmar(estadisticas->pokemon_totales == simulador_a_analizar->sala_de_espera.pokemones_totales, "En las estadisticas de un simulador recien creado, la cantidad de pokemones en el hospital es la esperada.");
    pa2m_afirmar(estadisticas->puntos == 0, "En las estadisticas de un simulador recien creado los puntos obtenidos son 0.");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 1, "En las estadisticas de un simulador reciente creado, cuando se piden las estadisticas la cantidad de eventos simulados es 1.");

    simulador_simular_evento(simulador_a_analizar, ObtenerEstadisticas, estadisticas);
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 2, "Si se vuelven a pedir las estadisticas, la cantidad de eventos simulados es 2.");


    free(estadisticas);
    simulador_destruir(simulador_a_analizar);
}

void DadoUnSimulador_CuandoSeAtiendeAUnProximoEntrenador_EntoncesElResultadoEsElEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    simulador_simular_evento(simulador_a_analizar, AtenderProximoEntrenador, NULL);

    pa2m_afirmar(simulador_a_analizar->puntos_simulador == 0, "Cuando se atiende a un proximo entrenador, los puntos obtenidos en el simulador siguen siendo 0.");
    pa2m_afirmar(simulador_a_analizar->eventos_simulados == 1, "Cuando se atiende a un proximo entrenador, los eventos simulados pasan a ser 1");
    pa2m_afirmar(simulador_a_analizar->sala_de_espera.entrenadores_atendidos == 1, "Cuando se atiende a un proximo entrenador, la cantidad de entrenadores atendidos pasa a ser 1.");
    pa2m_afirmar(simulador_a_analizar->sala_de_espera.pokemones_en_espera == heap_tamanio(simulador_a_analizar->pokemones_a_atender), "Cuando se atiende a un proximo entrenador, la cantidad de pokmones a atender es la correcta.");
    
    simulador_simular_evento(simulador_a_analizar, AtenderProximoEntrenador, NULL);

    pa2m_afirmar(simulador_a_analizar->sala_de_espera.pokemones_en_espera == heap_tamanio(simulador_a_analizar->pokemones_a_atender), "Cuando se vuelve a atender a otro entrenador, la cantidad de pokemones a atender es la correcta.");

    simulador_destruir(simulador_a_analizar);
}


void DadoUnSimulador_CuandoSeSeleccionaUnaDificultad_Entonces_ElResultadoEsEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    int id = 0;

    pa2m_afirmar(strcmp(simulador_a_analizar->dificultad_activa->nombre, "NORMAL") == 0, "La dificultad seleccionada por defecto es normal.");

    simulador_simular_evento(simulador_a_analizar, SeleccionarDificultad, &id);

    pa2m_afirmar(strcmp(simulador_a_analizar->dificultad_activa->nombre, "FACIL") == 0, "Se logra seleccionar facil como dificultad.");

    id = 1;

    simulador_simular_evento(simulador_a_analizar, SeleccionarDificultad, &id);

    pa2m_afirmar(strcmp(simulador_a_analizar->dificultad_activa->nombre, "NORMAL") == 0, "Se logra seleccionar normal como dificultad.");

    id = 2;

    simulador_simular_evento(simulador_a_analizar, SeleccionarDificultad, &id);

    pa2m_afirmar(strcmp(simulador_a_analizar->dificultad_activa->nombre, "DIFICIL") == 0, "Se logra seleccionar dificil como dificultad.");

    simulador_destruir(simulador_a_analizar);
}


void DadoUnSimulador_CuandoSeIntentaObtenerInfrormacionSobreUnaDificultad_EntoncesElResultadoEsElEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    InformacionDificultad* info_dificultad = malloc(sizeof(InformacionDificultad));
    info_dificultad->id = 0;

    simulador_simular_evento(simulador_a_analizar, ObtenerInformacionDificultad, info_dificultad);

    pa2m_afirmar(strcmp(info_dificultad->nombre_dificultad, "FACIL") == 0, "El nombre de la info de dificultad con id 0 es la esperada.");

    info_dificultad->id = 1;

    simulador_simular_evento(simulador_a_analizar, ObtenerInformacionDificultad, info_dificultad);

    pa2m_afirmar(strcmp(info_dificultad->nombre_dificultad, "NORMAL") == 0, "El nombre de la info de dificultad con id 1 es la esperada.");
  
    info_dificultad->id = 2;

    simulador_simular_evento(simulador_a_analizar, ObtenerInformacionDificultad, info_dificultad);

    pa2m_afirmar(strcmp(info_dificultad->nombre_dificultad, "DIFICIL") == 0, "El nombre de la info de dificultad con id 2 es la esperada.");

    free(info_dificultad);
    simulador_destruir(simulador_a_analizar);
}


void DadoUnSimulador_CuandoSeIntentaAdivinarElNivelDeUnPokemon_EntoncesElResultadoEsElEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    //int id = 0;

    //simulador_simular_evento(simulador_a_analizar, SeleccionarDificultad, &id);
    simulador_simular_evento(simulador_a_analizar, AtenderProximoEntrenador, NULL);

    Intento* intento = malloc(sizeof(Intento));

    intento->nivel_adivinado = 10;

    simulador_simular_evento(simulador_a_analizar, AdivinarNivelPokemon, intento);

    pa2m_afirmar(intento->es_correcto, "Cuando se adivina el nivel de un pokemon con el nivel correcto, el resultado es el esperado.");
    
    simulador_a_analizar->pokemon_en_tratamiento = NULL;

    pa2m_afirmar(simulador_simular_evento(simulador_a_analizar, AdivinarNivelPokemon, intento) == ErrorSimulacion, "Intentar adivinar el nivel de un pokemon inexistente devuelve ErrorSimulacion.");

    free(intento);
    simulador_destruir(simulador_a_analizar);
}


void DadoUnSimulador_CuandoSeUsanVariasDeSusFuncionalidades_EntoncesElResultadoEsElEsperado(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    Intento* intento = malloc(sizeof(Intento));

    EstadisticasSimulacion* estadisticas = malloc(sizeof(EstadisticasSimulacion));

    intento->nivel_adivinado = 10;

    simulador_simular_evento(simulador_a_analizar, AtenderProximoEntrenador, NULL);

    simulador_simular_evento(simulador_a_analizar, AdivinarNivelPokemon, intento);

    simulador_simular_evento(simulador_a_analizar, ObtenerEstadisticas, estadisticas);

    pa2m_afirmar(estadisticas->entrenadores_atendidos == 1, "Cuando se atiende un entrenador la cantidad de entrenadores atendidos es 1");
    pa2m_afirmar(estadisticas->entrenadores_totales == lista_tamanio(simulador_a_analizar->hospital_de_pokemones->lista_de_entrenadores), "La cantidad total de entrenadores es la esperada.");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 1, "Al adivinar el nivel de un pokemon, la cantidad de pokemones atendidos es 1.");
    pa2m_afirmar(estadisticas->pokemon_en_espera == heap_tamanio(simulador_a_analizar->pokemones_a_atender), "Al advinar el nivel de un pokemon, la cantidad de pokemones en espera es la correcta.");
    pa2m_afirmar(estadisticas->pokemon_totales == abb_tamanio(simulador_a_analizar->hospital_de_pokemones->pokemones_totales), "La cantidad total de pokemones es la esperada.");
    pa2m_afirmar(estadisticas->puntos == 500, "Los puntos obtenidos hasta el momento son los esperados.");

    free(intento);
    free(estadisticas);
    simulador_destruir(simulador_a_analizar);
}

void xxss(){

    hospital_t* hospital_de_pokemones = hospital_crear();
    hospital_leer_archivo(hospital_de_pokemones, RUTA_ARCHIVO_ENTRENADORES);
    simulador_t* simulador_a_analizar = simulador_crear(hospital_de_pokemones);

    simulador_simular_evento(simulador_a_analizar, ObtenerInformacionPokemonEnTratamiento, NULL);

    simulador_destruir(simulador_a_analizar);
}



int main(){

    pa2m_nuevo_grupo("PRUEBAS DEL HOSPITAL");

    pa2m_nuevo_grupo("Pruebas de  creación y destrucción");
    puedoCrearYDestruirUnHospital();

    pa2m_nuevo_grupo("Pruebas con NULL");
    dadoUnHospitalNULL_lasPuedoAplicarLasOperacionesDelHospitalSinProblema();

    pa2m_nuevo_grupo("Pruebas con un archivo vacío");
    dadoUnArchivoVacio_NoSeAgreganPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con un archivo de un entrenador");
    dadoUnArchivoConUnEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con un archivo de varios entrenadores");
    dadoUnArchivoConVariosEntrenadores_SeAgreganLosEntrenadoresYSusPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con mas de un archivo");
    dadosVariosArchivos_puedoAgregarlosTodosAlMismoHospital();

    pa2m_nuevo_grupo("PRUEBAS DEL SIMULADOR");

    pa2m_nuevo_grupo("Pruebas sobre creacion de simulador:");
    DadoUnSimulador_CuandoSeLoCrea_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("Pruebas sobre obtener estadisticas una vez creado el simulador:");
    DadoUnSimulador_CuandoSeLoCrea_EntoncesAlObtenerSusEstadisticasElResultadoEsElEsperado();

    pa2m_nuevo_grupo("Pruebas sobre atender proximo entrenador:");
    DadoUnSimulador_CuandoSeAtiendeAUnProximoEntrenador_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("Pruebas sobre adivinar pokemon:");
    DadoUnSimulador_CuandoSeIntentaAdivinarElNivelDeUnPokemon_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("Pruebas sobre seleccion de dificultad:");
    DadoUnSimulador_CuandoSeSeleccionaUnaDificultad_Entonces_ElResultadoEsEsperado();

    pa2m_nuevo_grupo("Pruebas sobre obtencion de info de dificultad:");
    DadoUnSimulador_CuandoSeIntentaObtenerInfrormacionSobreUnaDificultad_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("Pruebas Varias:");
    DadoUnSimulador_CuandoSeUsanVariasDeSusFuncionalidades_EntoncesElResultadoEsElEsperado();

    return pa2m_mostrar_reporte();
}
