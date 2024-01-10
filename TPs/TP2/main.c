#include"src/lista.h"
#include"src/hospital.h"
#include"src/simulador.h"
#include"src/structs_simulador.h"
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define OBTENER_ESTADISTICAS 'e'
#define ATENDER_PROXIMO_ENTRENADOR 'p'
#define OBTENER_INFORMACION_POKEMON_EN_TRATAMIENTO 'i'
#define ADIVINAR_NIVEL_POKEMON 'a'
#define AGREGAR_DIFICULTAD 'n'
#define SELECCIONAR_DIFICULTAD 'd'
#define OBETENER_INFORMACION_DIFICULTAD 'o'
#define FINALIZAR_SIMULACION 'q'


typedef struct{
    simulador_t* simulador_de_hospital;
    lista_t* lista_de_dificultades;
    bool se_sigue_jugando;
}Juego;

//FUNCIONES SOBRE DIFICULTADES EXTRAS:

/*
Pre-condicoines: No tiene.

Post-condiciones: Verifica si nivel_adivinado es correcto. En caso de ser correcto devuelve -1, en toro caso
devuelve el resto de nivel_pokemon con 2, indicando si el nivel del pokemon es par o no.
*/
int verificar_nivel_acertijo(unsigned nivel_adivinado, unsigned nivel_pokemon){

    int resultado_adivinacion = (int)nivel_adivinado - (int)nivel_pokemon;

    if(resultado_adivinacion == 0){
        return -1;
    } 

    return nivel_pokemon%2;
}


/*
Pre-condiciones: no tiene.

Post-condicones: Dado intetos deveulve un puntaje, punataje es un numero entre 0 y 500, mientras
mas grande sea puntaje este numero es mas chico.
*/
unsigned calcular_puntaje_acertijo(unsigned intentos){

    if(intentos >= 500){
        return 0;
    }

    return 500 - intentos;
}


/*
Pre-condiciones: no tiene.

Post-condiciones: Devuelve un string en base a resultado_de_verificacion. Cada string es una pista sobre 
el nivel que se intento adivinar.
*/
const char* verificacion_a_string_acertijo(int resultado_verificiacion){
    
    if(resultado_verificiacion == -1){
        return "ACERTASTE!!!";
    }
    else if(resultado_verificiacion == 0){
        return "EL NIVEL QUE INTENTAS ADIVINAR ES PAR!!!";
    }
    else{
        return "EL NIVEL QUE INTENTAS ADIVINAR ES IMPAR!!!";
    }
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Dado intentos, devuelve un numero entre 0 y 3, este numero es mas chico si intentos es mas grande.
*/
unsigned calcular_puntaje_muy_facil(unsigned intentos){

    if(intentos >= 3){
        return 0;
    }

    return 1;
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Devuelve la diferencia entre nivel_adivinado y nivel_pokemon.
*/
int verificar_muy_facil(unsigned nivel_adivinado, unsigned nivel_pokemon){
    return((int)nivel_adivinado - (int)nivel_pokemon);
}


/*
Pre-condiciones: No tiene.

Post-condiciones: Dado resultado_verificacion, devuelve un string. Este string es una pista sobre el intento
de adivinacion.
*/
const char* verificacion_a_string_muy_facil(int resultado_verificiacion){

    if(resultado_verificiacion >= -10 && resultado_verificiacion <= 10){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 10 numeros";
    }
    else if(resultado_verificiacion >= -20 && resultado_verificiacion <= 20){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 20 numeros";
    }
    else if(resultado_verificiacion >= -30 && resultado_verificiacion <= 30){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 30 numeros";
    }
    else if(resultado_verificiacion >= -40 && resultado_verificiacion <= 40){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 40 numeros";
    }
    else if(resultado_verificiacion >= -40 && resultado_verificiacion <= 40){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 40 numeros";
    }
    else if(resultado_verificiacion >= -50 && resultado_verificiacion <= 50){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 50 numeros";
    }
    else if(resultado_verificiacion >= -60 && resultado_verificiacion <= 60){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 60 numeros";
    }
    else if(resultado_verificiacion >= -70 && resultado_verificiacion <= 70){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 70 numeros";
    }
    else if(resultado_verificiacion >= -80 && resultado_verificiacion <= 80){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 80 numeros";
    }
    else if(resultado_verificiacion >= -90 && resultado_verificiacion <= 90){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 90 numeros";
    }
    else if(resultado_verificiacion >= -100 && resultado_verificiacion <= 100){
        return "La diferencia entre el nivel seleccionado y el real puede ser como mucho de 100 numeros";
    }
    else if(resultado_verificiacion == 0){
        return "Acertaste el nivel!!.";
    }
    else{
        return "No es posible determinar alguna pista.....";
    }
}


//FUCNIONES AUXILIARES:

/*
Pre-condiciones: hospital no debe ser NULL ni estar vacio.

Post-condicoines: Crea la estrcutrua juego cargandola con toda su informaicion inicial. Devuelve el juego, en caso de error devuelve 
true.
*/
Juego* inicializar_juego(hospital_t* hospital){

    Juego* juego_a_crear = malloc(sizeof(Juego));

    if(!juego_a_crear){
        return NULL;
    }

    juego_a_crear->simulador_de_hospital = simulador_crear(hospital);

    if(!juego_a_crear->simulador_de_hospital){
        free(juego_a_crear);
        return NULL;
    }

    juego_a_crear->se_sigue_jugando = true;

    return juego_a_crear;
}


char leer_comando(){
    char linea[100];
    char* leido;
    leido = fgets(linea, 100, stdin);
    if(!leido)
        return 0;
    while(*leido == ' ')
        leido++;
    return (char)tolower(*leido);
}


int leer_numero(){
    char linea[100];
    char* leido;
    leido = fgets(linea, 100, stdin);
    if(!leido)
        return 0;
    while(*leido == ' ')
        leido++;
    return atoi(leido);
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Libera toda  la memoria liberada por juego. En caso de ocurrir un error no hace nada.
*/
void destruir_juego(Juego* juego){

    if(!juego){
        return;
    }

    simulador_destruir(juego->simulador_de_hospital);
    free(juego);
}


/*
Pre-condiciones: lista_dificultades no debe ser NULL.

Post-condiciones: Muestra por pantalla las dificultades contenidad en lista_de_dificultades.
*/
void mostrar_lista_de_dificultades(lista_t* lista_de_dificultades){

    lista_iterador_t* iterador = lista_iterador_crear(lista_de_dificultades);

    if(!iterador){
        return;
    }

    DatosDificultad* dificultad_a_mostrar = NULL;
    int id = 0;

    while(lista_iterador_tiene_siguiente(iterador)){

        dificultad_a_mostrar = lista_iterador_elemento_actual(iterador);

        
        if(dificultad_a_mostrar != NULL){
            printf("    |-Nombre dificultad: %s; ID de dificultad: %i-\n", dificultad_a_mostrar->nombre, id);
        }

        id++;
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
}


/*
Pre-conciones: No tiene.

Post-condiciones: Muestra por pantalla una interfaz para el simulador.
*/
void dar_bienvenida(){
    
    printf("    -------------------------------------------------------SIMULADOR DE HOSPITAL DE POKEMONES-------------------------------------------------------\n");
    printf("\n");
    printf("    PARA UTILIZAR EL SIMULADOR PUEDE UTILIZAR ALGUNA DE LAS SIGUIENTES OPCIONES:\n");
    printf("    -Obtener estadisticas (E)- -Atender proximo entrenador (P)- -Obtener informacion pokemon en tratamiento (I)-\n");
    printf("    -Adivinar nivel pokemon (A)- -Agregar dificultad (N)- -SeleccionarDificultad (D)- -ObtenerInformacionDificultad (O)- -Finalizar simulacion (Q)-\n");
    printf("    -------------------------------------------------------------------------------------------------------------------------------------------------\n");
}


/*
Pre-condiciiones: juego no debe ser NULL.

Post-condiciones: Muestra por pantalla estdisticas referentes al al informaicon del simulador_de_hospital.
*/
void obtener_estadisticas(Juego* juego){

    system("clear");
    dar_bienvenida();

    char letra_cualquiera;

    EstadisticasSimulacion estadisticas;

    simulador_simular_evento(juego->simulador_de_hospital, ObtenerEstadisticas, &estadisticas);
    printf("\n");

    printf("    |ESTADISICAS DEL SIMULADOR:\n");
    printf("    |Entrenadores atendidos: %i\n", estadisticas.entrenadores_atendidos);
    printf("    |Entrenadores totales: %i\n",estadisticas.entrenadores_totales);
    printf("    |Pokemon atendidos: %i\n", estadisticas.pokemon_atendidos);
    printf("    |Pokemon en espera: %i\n", estadisticas.pokemon_en_espera);
    printf("    |Pokemon totales: %i\n", estadisticas.pokemon_totales);
    printf("    |Puntos obtenidos: %i\n", estadisticas.puntos);
    printf("    |Cantidad de eventos simulados: %i\n",estadisticas.cantidad_eventos_simulados);

    printf("\n");
    printf("    Ingrese una tecla cualquiera para volver al menun principal: ");
    letra_cualquiera = leer_comando();

    if(letra_cualquiera){
        return;
    }
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Hace atender al proximo entrenador conteniod en simulador_de_hospital (campo del registro juego).
*/
void atender_siguiente_entrenador(Juego* juego){
    simulador_simular_evento(juego->simulador_de_hospital, AtenderProximoEntrenador, NULL);
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Muestra por pantalla la informaicion del pokemon que esta siendo atendido. Si no hay pokemon
en tratamiento muestra un mensaje de error.
*/
void obtener_info_poke_en_tratamiento(Juego* juego){

    system("clear");
    dar_bienvenida();

    char letra_cualquiera;    
    InformacionPokemon info_pokemon;
    ResultadoSimulacion estado_evento;

    estado_evento = simulador_simular_evento(juego->simulador_de_hospital, ObtenerInformacionPokemonEnTratamiento, &info_pokemon);

    printf("\n");

    if(estado_evento == ErrorSimulacion){
        printf("    HA OCURRIDO UN ERROR!! Asegurese de que haya un pokemon en tratamiento.\n\n");
        letra_cualquiera = leer_comando();

        if(letra_cualquiera){
            return;
        }
    }

    printf("    |INFORMACION POKEMON EN TRATAMIENTO\n");
    printf("    |Nombre del entrenador: %s.\n", info_pokemon.nombre_entrenador);
    printf("    |Nombre del pokemon: %s.\n", info_pokemon.nombre_pokemon);

    printf("\n");
    printf("    Ingrese una tecla cualquiera para volver al menun principal: ");
    letra_cualquiera = leer_comando();

    if(letra_cualquiera){
        return;
    }
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Muestra por pantalla info sobre el pokemon a adinvar (si este exite, en caso contrario devuelve NULL), permitiendo
al usuario advinar su nivel, finalmente muestra un mensaje que da informacion sobre si la adiviancion fue correcta o no.
*/
void adivinar_nivel_de_pokemon(Juego* juego){

    system("clear");
    dar_bienvenida();

    char letra_cualquiera;
    InformacionPokemon info_pokemon;
    Intento intento_de_adivinacion;
    ResultadoSimulacion estado_evento;

    estado_evento = simulador_simular_evento(juego->simulador_de_hospital, ObtenerInformacionPokemonEnTratamiento, &info_pokemon);

    printf("\n");

    if(estado_evento == ErrorSimulacion){
        printf("    HA OCURRIDO UN ERROR! No es posible adivinar el nivel de un pokemon si no hay ninguno en tratamiento.\n");
        printf("\n");
        printf("    Ingrese una tecla cualquiera para volver al menun principal: ");
        letra_cualquiera = leer_comando(); 

        if(letra_cualquiera){
            return;
        }
    }

    printf("    |INFORMACION POKEMON EN TRATAMIENTO\n");
    printf("    |Nombre del entrenador: %s.\n", info_pokemon.nombre_entrenador);
    printf("    |Nombre del pokemon: %s.\n", info_pokemon.nombre_pokemon);
    printf("\n");

    printf("    Ingrese el nivel del pokemon en tratamiento: ");
    intento_de_adivinacion.nivel_adivinado = (unsigned)leer_numero();

    estado_evento = simulador_simular_evento(juego->simulador_de_hospital, AdivinarNivelPokemon, &intento_de_adivinacion);

    system("clear");
    dar_bienvenida();

    printf("\n");
    printf("    |RESULTADO DEL INTENTO DE ADIVINACION DE NIVEL:\n");
    printf("    |Intentaste avidinar el nivel de %s, cuyo entrenador es %s.\n", info_pokemon.nombre_pokemon, info_pokemon.nombre_entrenador);
    printf("    |Resultado adivinacion: %s.\n", intento_de_adivinacion.resultado_string);

    printf("\n");
    printf("    Ingrese una tecla cualquiera para volver al menun principal: ");
    letra_cualquiera = leer_comando();

    if(letra_cualquiera){
        return;
    }
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: A traves de un mensaje por pantalla, permite agregar una nueva dificultad al simulador.
*/
void agregar_una_dificultad(Juego* juego){

    system("clear");
    dar_bienvenida();

    DatosDificultad dificultad_muy_facil;
    dificultad_muy_facil.nombre = "MUY FACIL";
    dificultad_muy_facil.calcular_puntaje = calcular_puntaje_muy_facil;
    dificultad_muy_facil.verificar_nivel = verificar_muy_facil;
    dificultad_muy_facil.verificacion_a_string = verificacion_a_string_muy_facil;

    DatosDificultad dificultad_acertijo;
    dificultad_acertijo.nombre = "ACERTIJO";
    dificultad_acertijo.calcular_puntaje = calcular_puntaje_acertijo;
    dificultad_acertijo.verificar_nivel = verificar_nivel_acertijo;
    dificultad_acertijo.verificacion_a_string = verificacion_a_string_acertijo;

    printf("\n\n");
    printf("    |Dificultades disponibles para agregar (ingrese una tecla):\n");
    printf("    |Acertijo (a), Muy facil (m).\n");

    printf("\n");
    printf("    Selecione la dificultad que desea agregar: ");

    char dificultad_a_escoger = '0';

    dificultad_a_escoger = leer_comando();

    while(dificultad_a_escoger != 'a' && dificultad_a_escoger != 'm'){

        system("clear");
        dar_bienvenida();

        printf("\n\n");
        printf("    |DIFICULTAD INGRESADA INVALIDA!!! ESCOGA UN CARACTER VALIDO\n");
        printf("    |Dificultades disponibles para agregar (ingrese una tecla):\n");
        printf("    |Acertijo (a), Muy facil (m)\n.");

        printf("\n");
        printf("    Selecione la dificultad que desea agregar: ");

        dificultad_a_escoger = leer_comando();
    }

    if(dificultad_a_escoger == 'a'){
        simulador_simular_evento(juego->simulador_de_hospital, AgregarDificultad, &dificultad_acertijo);
    }
    else{
        simulador_simular_evento(juego->simulador_de_hospital, AgregarDificultad, &dificultad_muy_facil);
    }

    printf("\nPresione una tecla cualquiera para voler al menu principal:");
    char letra_cualquiera = leer_comando();

    if(letra_cualquiera){
        return;
    }
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Permite cambiar la dificultad del simulador.
*/
void escoger_dificultad(Juego* juego){

    system("clear");
    dar_bienvenida();

    char letra_cualquiera;

    printf("\n\n");
    printf("    |LISTA DE DIFICULTADES (EL SIMULADOR POR DEFECTO INICIA CON SU DIFICULTAD EN NORMAL):\n");
    mostrar_lista_de_dificultades(juego->simulador_de_hospital->lista_de_dificultades);
    printf("\n\n");

    int id_dificultad;

    printf("    Ingrese el id de la dificultad que desea seleccionar:");
    id_dificultad = leer_numero();

    simulador_simular_evento(juego->simulador_de_hospital, SeleccionarDificultad, &id_dificultad);

    printf("    Ingrese una tecla cualquiera para volver al menun principal: ");

    letra_cualquiera = leer_comando();

    if(letra_cualquiera){
        return;
    }
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Permite obtener la informacion sobre una dificultad conociendo su id.
*/
void obtener_info_dificultad(Juego* juego){

    system("clear");
    dar_bienvenida();

    char letra_cualquiera;
    InformacionDificultad info_dificultad;
    ResultadoSimulacion estado_evento;

    printf("\n");

    printf("    Igrese el ID de la dificultad cuya informacion quiera conocer: ");
    info_dificultad.id = leer_numero();

    printf("\n");

    system("clear");
    dar_bienvenida();

    estado_evento = simulador_simular_evento(juego->simulador_de_hospital, ObtenerInformacionDificultad, &info_dificultad);

    if(estado_evento == ErrorSimulacion){

        printf("\n");

        printf("    HA OCURRIDO UN ERROR!! Asegurese de ingresar un id de un dificultad existente.\n\n");

        printf("    Ingrese una tecla cualquiera para volver al menun principal: ");

        letra_cualquiera = leer_comando();

        if(letra_cualquiera){
            return;
        }
    }

    printf("\n");

    printf("    |Datos de dificultad:\n");
    printf("    |ID de dificutlad: %i.\n", info_dificultad.id);
    printf("    |Nombre dificultad: %s.\n", info_dificultad.nombre_dificultad);
    printf("    |Esta en uso? : %d (0 no, cualquier otro numero si).", info_dificultad.en_uso);

    printf("\n\n");
    printf("    Ingrese una tecla cualquiera para volver al menun principal: ");

    letra_cualquiera = leer_comando();

    if(letra_cualquiera){
        return;
    }
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Da por finalizado el simulador.
*/
void finalizar_todo(Juego* juego){

    simulador_simular_evento(juego->simulador_de_hospital, FinalizarSimulacion, NULL);
    juego->se_sigue_jugando = false;
}


/*
Pre-condiciones: juego no debe ser NULL.

Post-condiciones: Realiza una determinada accion del simulador segun sea el comando mandado.
*/
void ejecutar_comando(Juego *juego, char comando){
    
    switch(comando) {
        
        case OBTENER_ESTADISTICAS:
            obtener_estadisticas(juego);
            break;
        
        case ATENDER_PROXIMO_ENTRENADOR:
            atender_siguiente_entrenador(juego);
            break;

        case OBTENER_INFORMACION_POKEMON_EN_TRATAMIENTO:
            obtener_info_poke_en_tratamiento(juego);
            break;
        
        case ADIVINAR_NIVEL_POKEMON:
            adivinar_nivel_de_pokemon(juego);
            break;

        case AGREGAR_DIFICULTAD:
            agregar_una_dificultad(juego);
            break;

        case SELECCIONAR_DIFICULTAD:
            escoger_dificultad(juego);
            break;

        case OBETENER_INFORMACION_DIFICULTAD:
            obtener_info_dificultad(juego);
            break;
        
        case FINALIZAR_SIMULACION:
            finalizar_todo(juego);
            break;
    }
}


int main(int argc, char *argv[]) {

    hospital_t* hospital = hospital_crear();

    if(!hospital){
        return 0;
    }

    bool se_pudo_cargar = hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital");

    if(!se_pudo_cargar){
        hospital_destruir(hospital);
        return 0;
    }

    Juego* juego = inicializar_juego(hospital);
    
    if(!juego){
        hospital_destruir(hospital);
        return 0;
    }

    do{
        system("clear");
        dar_bienvenida();
        printf("    Selecione un evento a realizar: ");
        char c = leer_comando();
        ejecutar_comando(juego, c);
    }while(juego->se_sigue_jugando);

    destruir_juego(juego);

    return 0;
}
