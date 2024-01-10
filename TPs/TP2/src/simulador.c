#include<stdbool.h>
#include<string.h>
#include"simulador.h"
#include"hospital.h"
#include"structs_simulador.h"
#include"structs_hospital.h"
#include"heap.h"
#include"lista.h"
#include"abb.h"

#define PUNTAJE_BASE_FACIL 100
#define PUNTAJE_BASE_NORMAL 500
#define PUNTAJE_BASE_DIFICIL 100

#define SUPER_CALIENTE "MUY CALIENTE, ESTAS CERCA."
#define CALIENTE "CALIENTE."
#define ACERTASTE "ACERTASTE."
#define SUPER_TIBIO "MUY TIBIO."
#define TIBIO "TIBIO."
#define FRIO "FRIO."
#define SUPER_FRIO "MUY FRIO." 

//Funciones de dificultad:

/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve un puntaje correspondiente a la cantidad de intentos realizados. Toma como base para calcular el puntaje
PUNTAJE_BASE_FACIL, el puntaje total depende de la cantidad de intentos realizados, por cada intento se restan dos puntos a la base.

Retorno: Un numero entre 0 y 100.

*/
unsigned calcular_puntaje_facil(unsigned cantidad_intentos){

    if(PUNTAJE_BASE_FACIL - (int)2*cantidad_intentos <= 0){
        return 0;
    }

    return PUNTAJE_BASE_FACIL - 2*cantidad_intentos;
}


/*
Pre-condiciones: No tiene

Post-condiciones: Devuelve un punatje correspondiente a la cantidad de intentos realizados. Toma como base para calcular el puntaje
PUNTAJE_BASE_NORMAL, el puntaje total depende de la cantidad de intentos realizados, por cada intento se restan dos puntos a la base.

Retorno: UN numero entre 0 y 500.
*/
unsigned calcular_puntaje_normal(unsigned cantidad_intentos){

    if(PUNTAJE_BASE_NORMAL - (int)50*cantidad_intentos <= 0){
        return 0;
    }

    return PUNTAJE_BASE_NORMAL - 50*cantidad_intentos;
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve un punatje correspondiente a la cantidad de intentos realizados. Toma como base para calcular el puntaje
PUNTAJE_BASE_NORMAL, el puntaje total depende de la cantidad de intentos realizados, por cada intento se restan dos puntos a la base.

Retorno: Un numero entre 0 y 100.
*/
unsigned calcular_puntaje_dificil(unsigned cantidad_intentos){

    if(PUNTAJE_BASE_DIFICIL - (int)500*cantidad_intentos <= 0){
        return 0;
    }

    return PUNTAJE_BASE_DIFICIL - 500*cantidad_intentos;
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve la diferencia entre nivel_adivinado y nivel_pokemon.
*/
int verificar_nivel(unsigned nivel_adivinado, unsigned nivel_pokemon){
    return (int)nivel_adivinado - (int)nivel_pokemon;
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve un string que da una informacion sobre el nivel adivinado.
*/
const char* verificacion_a_string_facil(int resultado_verificacion){

    int diferencia = resultado_verificacion;

    if(diferencia < 0){
        diferencia *= -1;
    }

    if(diferencia > 0 &&  diferencia <= 10){
        return SUPER_CALIENTE;
    }
    else if(diferencia > 10 && diferencia <= 20){
        return CALIENTE;
    }
    else if(diferencia > 20 && diferencia <= 30){
        return SUPER_TIBIO;
    }
    else if(diferencia > 30 && diferencia <= 40){
        return TIBIO;
    }
    else if(diferencia > 40 && diferencia <= 50){
        return FRIO;
    }
    else if(diferencia > 50){
        return SUPER_FRIO;
    }
    else{
        return ACERTASTE;
    }
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve un string que da una informacion sobre el nivel adivinado.
*/
const char* verificacion_a_string_normal(int resultado_verificacion){

    if(resultado_verificacion < 0){
        return "EL NIVEL QUE INTENTAS ADIVINAR ES MAYOR.";
    }
    else{
        return "EL NIVEL QUE INTENTAS ADIVINAR ES MENOR";
    }
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve un string que da una informacion sobre el nivel adivinado.
*/
const char* verificacion_a_string_dificil(int resultado_verificacion){

    if(resultado_verificacion != 0){
        return "MAL, NO ACERTASTE EL NIVEL.";
    }
    else{
        return "CORRECTO, NIVEL ACERTADO";
    }


}


//Funciones privadas:

/*
Pre-condiciones: lista_de_dificultades no debe ser NULL.

Post-condiciones: Destruye cada una de las dificultades guardadas en lista_de_dificultades. En caso de error no 
hace nada.
*/
void destruir_dificultades(lista_t* lista_de_dificultades){

    if(!lista_de_dificultades){
        return;
    }

    lista_iterador_t* iterador_de_dificultades = lista_iterador_crear(lista_de_dificultades);

    if(!iterador_de_dificultades){
        return;
    }

    DatosDificultad* dificultad_a_destruir = NULL;

    while(lista_iterador_tiene_siguiente(iterador_de_dificultades)){

        dificultad_a_destruir = (DatosDificultad*)lista_iterador_elemento_actual(iterador_de_dificultades);

        if(dificultad_a_destruir != NULL){
            free((char*)dificultad_a_destruir->nombre);
            free(dificultad_a_destruir);
        }

        lista_iterador_avanzar(iterador_de_dificultades);
    }

    lista_iterador_destruir(iterador_de_dificultades);
}


/*
Pre-condiciones: 
-lista_dificultades no debe ser NULL.
-nombre_dificultad no debe ser NULL y solo puede ser: "FACIL", "NORMAL" o "DIFICIL".

Post-condiciones: Dado un nombre de una dificutlad, carga la dificultad con toda su informacion correspondiente en
lista_de_dificutlades. La funcion devuelve la lista_de_dificultades en caso de que exito, en caso contrario, devuelve NULL.
*/
lista_t* cargar_dificultades(lista_t* lista_de_dificultades, char* nombre_dificultad){

    if(!lista_de_dificultades || !nombre_dificultad){
        return NULL;
    }

    DatosDificultad* dificultad_a_agregar = malloc(sizeof(DatosDificultad));

    if(!dificultad_a_agregar){
        return NULL;
    }

    dificultad_a_agregar->nombre = malloc((strlen(nombre_dificultad)+1)*sizeof(char));

    if(!dificultad_a_agregar->nombre){
        free(dificultad_a_agregar);
        return NULL;
    }

    if(strcmp(nombre_dificultad, "FACIL") == 0){
        strcpy((char*)dificultad_a_agregar->nombre, "FACIL");
        dificultad_a_agregar->calcular_puntaje = calcular_puntaje_facil;
        dificultad_a_agregar->verificacion_a_string = verificacion_a_string_facil;

    }
    else if(strcmp(nombre_dificultad, "NORMAL") == 0){
         strcpy((char*)dificultad_a_agregar->nombre, "NORMAL");
        dificultad_a_agregar->calcular_puntaje = calcular_puntaje_normal;
        dificultad_a_agregar->verificacion_a_string = verificacion_a_string_normal;
    }
    else{
         strcpy((char*)dificultad_a_agregar->nombre, "DIFICIL");
        dificultad_a_agregar->calcular_puntaje = calcular_puntaje_dificil;
        dificultad_a_agregar->verificacion_a_string = verificacion_a_string_dificil;
    }

    dificultad_a_agregar->verificar_nivel = verificar_nivel;

    lista_t* lista_aux = lista_de_dificultades;
    lista_aux = lista_insertar(lista_de_dificultades, (void*)dificultad_a_agregar);

    if(!lista_aux){
        free((char*)dificultad_a_agregar->nombre);
        free(dificultad_a_agregar);
        return NULL;
    }

    return lista_de_dificultades;
}   


/*
Pre-condiciones:
-lista_de_dificultades no debe ser NULL.
-dificultad no debe ser NULL.

Post-condiciones: Recorre lista_de_dificultades verificando si dificultad se encuentra en ella. Devuelve true si esto 
ocurre, y false en caso contario o de error. 
*/
bool es_dificultad_repetida(lista_t* lista_de_dificultades, DatosDificultad* dificultad){

    if(!lista_de_dificultades || !dificultad){
        return false;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista_de_dificultades);

    if(!lista_de_dificultades){
        return false;
    }

    bool encontrado = false;
    DatosDificultad* dificultad_auxiliar = NULL;

    while(lista_iterador_tiene_siguiente(iterador) && !encontrado){

        dificultad_auxiliar = (DatosDificultad*)lista_iterador_elemento_actual(iterador);

        if(strcmp(dificultad_auxiliar->nombre, dificultad->nombre ) == 0){
            encontrado = true;
        }

        lista_iterador_avanzar(iterador);
    }

    free(iterador);
    return encontrado;
}


/*
Pre-condiciones: Ambos parametro deben ser registros de tipo pokemon_t* casteados a void*.

Post-condicones: Devuelve la diferencia de los niveles de los pokemones mandados como parametro.
*/
int comparador_de_heap(void* elemento_1, void* elemento_2){

    pokemon_t* poke_1 = (pokemon_t*)elemento_1;
    pokemon_t* poke_2 = (pokemon_t*)elemento_2;

    return ((int)poke_1->nivel - (int)poke_2->nivel);
}


/*
Pre-condiciones: estadisticas no debe ser NULL. simulador no debe ser NULL.

Se espera que la funcion solo sea usada por simulador_simular_evento.

Post-condiciones: Actualiza las estadisticas con la informacion contenida en simulador.
*/
bool actualizar_estadisticas(EstadisticasSimulacion* estadisticas, simulador_t* simulador){

    if(!estadisticas || !simulador){
        return false;
    }

    estadisticas->entrenadores_atendidos = simulador->sala_de_espera.entrenadores_atendidos;
    estadisticas->entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(simulador->hospital_de_pokemones);
    estadisticas->pokemon_atendidos = simulador->sala_de_espera.pokemones_atendidos;
    estadisticas->pokemon_en_espera = simulador->sala_de_espera.pokemones_en_espera;
    estadisticas->pokemon_totales = (unsigned)hospital_cantidad_pokemon(simulador->hospital_de_pokemones);
    estadisticas->puntos = simulador->puntos_simulador;
    estadisticas->cantidad_eventos_simulados = simulador->eventos_simulados;

    return true;
}


/*
Pre-condiciones: simulador no debe ser NULL.

Post-condiciones: Se encarga de actualizar el simulador, agregando pokemones a pokemones_en_tratamiento y actualizando
la informacion del campo sala_de_espera del simulador. Devuelve true en caso de exito, en otro caso, deveulve false.
*/
bool atender_proximo_entrenador(simulador_t* simulador){

    if(!simulador || !lista_iterador_tiene_siguiente(simulador->iterador_de_entrenadores)){
        return false;
    }

    entrenador_t* entrenador = (entrenador_t*)lista_iterador_elemento_actual(simulador->iterador_de_entrenadores);

    pokemon_t** vector_de_pokemones = malloc(abb_tamanio(entrenador->arbol_de_pokemones)*sizeof(pokemon_t));

    if(!vector_de_pokemones){
        return false;
    }
    
    abb_recorrer(entrenador->arbol_de_pokemones, INORDEN, (void**)vector_de_pokemones, abb_tamanio(entrenador->arbol_de_pokemones));

    for(size_t i = 0; i < abb_tamanio(entrenador->arbol_de_pokemones); i++){
        heap_insertar(simulador->pokemones_a_atender, vector_de_pokemones[i]);
    }

    if(heap_tamanio(simulador->pokemones_a_atender) >= 1 && !simulador->existe_pokemon_en_tratamiento){
        simulador->pokemon_en_tratamiento = (pokemon_t*)heap_extraer_raiz(simulador->pokemones_a_atender);
        simulador->existe_pokemon_en_tratamiento = true;
        simulador->sala_de_espera.pokemones_en_espera = (unsigned)heap_tamanio(simulador->pokemones_a_atender);
    }
    else{
        simulador->sala_de_espera.pokemones_en_espera = (unsigned)heap_tamanio(simulador->pokemones_a_atender);
    }

    simulador->sala_de_espera.entrenadores_atendidos++;
    simulador->sala_de_espera.pokemones_en_espera = (unsigned)heap_tamanio(simulador->pokemones_a_atender);
    free(vector_de_pokemones);
    lista_iterador_avanzar(simulador->iterador_de_entrenadores);
    return true;
}


/*
Pre-condiciones:
-info_pokemon no debe ser NULL.
-simulador no deb ser NULL.

Post-condicones: Llena los campos de info_pokemon con la informacion de pokemon en tratamiento (su nombre y el de su entrenador).
En caso de no haber pokemon en tratamiento, llena los campos de info_pokemon con NULL. Devuelve true en caso de exito
(existe pokemon en tratamiento) y false en caso contrario.
*/
bool obtener_info_pokemon_en_tratamiento(InformacionPokemon* info_pokemon, simulador_t* simulador){

    if(!info_pokemon || !simulador){
        return false;
    }

    if(!simulador->existe_pokemon_en_tratamiento){
        info_pokemon->nombre_pokemon = NULL;
        info_pokemon->nombre_entrenador = NULL;
        return false;
    }

    info_pokemon->nombre_pokemon = simulador->pokemon_en_tratamiento->nombre_pokemon;
    info_pokemon->nombre_entrenador = simulador->pokemon_en_tratamiento->entrenador->nombre_entrenador;

    return true;
}

/*
Pre-condiciones: 
-intento_de_adivinacion no debe ser NULL. intento_de_adiviancion debe venir con el campo nivel_adivinado iniciliazado 
(con el nivel que se intento adivinar).
-simulador no debe ser NULL.

Post-condiciones: Actualiza los campos de intento_de_adivinacion (verifica si se logro adivinar el nivel o no) usando 
el campo dificutlad_activa de simulador. Devuelve true en caso de exito y false en caso contrario.
*/
bool analizar_nivel_adivinado(Intento* intento_de_adivinacion, simulador_t* simulador){

    if(!intento_de_adivinacion || !simulador->pokemones_a_atender || !simulador->dificultad_activa || !simulador->pokemon_en_tratamiento){
        return false;
    }

    int resultado_verificacion = simulador->dificultad_activa->verificar_nivel(intento_de_adivinacion->nivel_adivinado, (unsigned)simulador->pokemon_en_tratamiento->nivel);

    if(resultado_verificacion != 0){
        intento_de_adivinacion->resultado_string = simulador->dificultad_activa->verificacion_a_string(resultado_verificacion);
        intento_de_adivinacion->es_correcto = false;
        simulador->intentos_de_adivinacion_de_nivel++;
        return true;
    }

    intento_de_adivinacion->resultado_string = simulador->dificultad_activa->verificacion_a_string(resultado_verificacion);
    intento_de_adivinacion->es_correcto = true;
    simulador->puntos_simulador += simulador->dificultad_activa->calcular_puntaje(simulador->intentos_de_adivinacion_de_nivel);

    simulador->sala_de_espera.pokemones_atendidos++;
    
    simulador->pokemon_en_tratamiento = (pokemon_t*)heap_extraer_raiz(simulador->pokemones_a_atender);

    simulador->sala_de_espera.pokemones_en_espera = (unsigned)heap_tamanio(simulador->pokemones_a_atender);

    simulador->intentos_de_adivinacion_de_nivel = 0;

    if(!simulador->pokemon_en_tratamiento){
        simulador->existe_pokemon_en_tratamiento = false;
    }

    return true;
}


/*
Pre-condiciones:
-dificultad_a_agregar no debe ser NULL. Sus campos no deben ser NULL.
-simulador no debe ser NULL.

Post-condiciones: Agrega dificultad_a_agregar a la lista de difcultades del simulador. Devuelve true en caso de exito, en caso
contrario, devuelve false.
*/
bool agregar_dificultad_al_simulador(DatosDificultad* dificultad_a_agregar , simulador_t* simulador){

    if(!dificultad_a_agregar || !simulador){
        return false;
    }

    if(es_dificultad_repetida(simulador->lista_de_dificultades, dificultad_a_agregar)){
        return false;
    }

    DatosDificultad* copia_de_dificultad_a_agregar = malloc(sizeof(DatosDificultad));

    if(!copia_de_dificultad_a_agregar){
        return false;
    }

    copia_de_dificultad_a_agregar->nombre = malloc((strlen(dificultad_a_agregar->nombre)+1)*sizeof(char));

    if(!copia_de_dificultad_a_agregar->nombre){
        free(copia_de_dificultad_a_agregar);
        return false;
    }   

    strcpy((char*)copia_de_dificultad_a_agregar->nombre, dificultad_a_agregar->nombre);
    copia_de_dificultad_a_agregar->calcular_puntaje = dificultad_a_agregar->calcular_puntaje;
    copia_de_dificultad_a_agregar->verificar_nivel = dificultad_a_agregar->verificar_nivel;
    copia_de_dificultad_a_agregar->verificacion_a_string = dificultad_a_agregar->verificacion_a_string;

    lista_insertar(simulador->lista_de_dificultades, (void*)copia_de_dificultad_a_agregar);

    return true;
}


/*
Pre-condiciones:
-id no debe ser NULL.
-simulador no debe ser NULL.

Post-condiciones: Actualiza el campo dificutlad activa con la dificultad de la lista de dificutlades correspondiente a id.
Devuelve true en caso de exito, en caso contario, devuelve false.
*/
bool seleccionar_dificultad(int* id, simulador_t* simulador){

    if(!id || !simulador){
        return false;
    }

    DatosDificultad* dificultad_a_seleccionar = (DatosDificultad*)lista_elemento_en_posicion(simulador->lista_de_dificultades, (size_t)(*id));

    if(!dificultad_a_seleccionar){
        return false;
    }

   simulador->dificultad_activa = dificultad_a_seleccionar;

    return true;
}

/*
Pre-condiciones:
-info_dificultad no debe ser NULL. Debe venir con su campo id inicializado con el id de la dificultad deseada.
-simulador no debe ser NULL.

Post-condiciones: Busca en la lista de dificultades la dificultad deseada (id correspondiente) e iniciliaza info_dificultad
con la informaicion de esta. Devuelve true en caso de exito, en otro caso, devuelve false.
*/
bool obtener_informacion_dificultad(InformacionDificultad* info_dificultad, simulador_t* simulador){

    if(!info_dificultad || !simulador){
        return false;
    }

    DatosDificultad* dificultad_buscada = (DatosDificultad*)lista_elemento_en_posicion(simulador->lista_de_dificultades, (size_t)info_dificultad->id);

    if(!dificultad_buscada){
        info_dificultad->nombre_dificultad = NULL;
        info_dificultad->en_uso = false;
        info_dificultad->id = -1;
        return false;
    }

    info_dificultad->nombre_dificultad = dificultad_buscada->nombre;

    if(!simulador->dificultad_activa || strcmp(info_dificultad->nombre_dificultad, simulador->dificultad_activa->nombre) != 0){   
        info_dificultad->en_uso = false;
    }else{
        info_dificultad->en_uso = true;
    }
    
    return true;
}


//Funciones publicas:

simulador_t* simulador_crear(hospital_t* hospital){

    if(!hospital){
        return NULL;
    }

    simulador_t* simulador = calloc(1, sizeof(simulador_t));

    if(!simulador){
        return NULL;
    }

    heap_t* heap_pokemones_a_atender = heap_crear(comparador_de_heap, 1);

    if(!heap_pokemones_a_atender){
        free(simulador);
        return NULL;    
    }

    lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_de_entrenadores);

    if(!iterador){
        free(heap_pokemones_a_atender);
        free(simulador);
        return NULL;
    }

    lista_t* lista_de_dificultades = lista_crear();

    if(!lista_de_dificultades){
        free(iterador);
        free(heap_pokemones_a_atender);
        free(simulador);
        return NULL;
    }

    simulador->pokemones_a_atender = heap_pokemones_a_atender;
    simulador->hospital_de_pokemones = hospital;
    simulador->iterador_de_entrenadores = iterador;
    simulador->lista_de_dificultades = lista_de_dificultades;

    cargar_dificultades(simulador->lista_de_dificultades, "FACIL");
    cargar_dificultades(simulador->lista_de_dificultades, "NORMAL");
    cargar_dificultades(simulador->lista_de_dificultades, "DIFICIL");

    simulador->sala_de_espera.entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital);
    simulador->sala_de_espera.entrenadores_atendidos = 0;
    simulador->sala_de_espera.pokemones_atendidos = 0;
    simulador->sala_de_espera.pokemones_en_espera = 0;
    simulador->sala_de_espera.pokemones_totales = (unsigned)hospital_cantidad_pokemon(hospital);

    simulador->dificultad_activa = lista_elemento_en_posicion(simulador->lista_de_dificultades, 1);

    return simulador;
}


ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos){

    bool estado_simulacion = true;

    if(!simulador || simulador->simulador_ha_finalizado){
        return ErrorSimulacion;
    }

    simulador->eventos_simulados++;
    
    switch(evento){

        case ObtenerEstadisticas:
            estado_simulacion = actualizar_estadisticas(datos, simulador);
            break;
        
        case AtenderProximoEntrenador:
            estado_simulacion = atender_proximo_entrenador(simulador);
            break;

        case ObtenerInformacionPokemonEnTratamiento:
            estado_simulacion = obtener_info_pokemon_en_tratamiento(datos, simulador); 
            break;

        case AdivinarNivelPokemon:
            estado_simulacion = analizar_nivel_adivinado(datos, simulador);
            break;

        case AgregarDificultad:
            estado_simulacion = agregar_dificultad_al_simulador(datos, simulador);
            break;

        case SeleccionarDificultad:
            estado_simulacion = seleccionar_dificultad(datos, simulador);
            break;

        case ObtenerInformacionDificultad:
            estado_simulacion = obtener_informacion_dificultad(datos, simulador);
            break;

        case FinalizarSimulacion:
            simulador->simulador_ha_finalizado = true;
            break;

        default:
            return ErrorSimulacion;
    }

    if(!estado_simulacion){
        return ErrorSimulacion;
    }
    
    return ExitoSimulacion;
}


void simulador_destruir(simulador_t* simulador){

    if(!simulador){
        return;
    }

    heap_destruir(simulador->pokemones_a_atender);
    hospital_destruir(simulador->hospital_de_pokemones);
    lista_iterador_destruir(simulador->iterador_de_entrenadores);
    destruir_dificultades(simulador->lista_de_dificultades);
    lista_destruir(simulador->lista_de_dificultades);
    free(simulador);
}