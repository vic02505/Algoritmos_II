#include "pa2mm.h"
#include "src/hash.h"
#include"src/lista.h"
#include<string.h>
#include<stdbool.h>

#define STRING_DE_PRUEBA_1 "AKJ-98G"
#define STRING_DE_PRUEBA_2 "BHY-05K"
#define STRING_DE_PRUEBA_3 "OAK_26J"
#define STRING_DE_PRUEBA_4 "PEM-47H"
#define STRING_DE_PRUEBA_5 "DWR-01S"
#define STRING_DE_PRUEBA_6 "SRS-00Z"
#define STRING_DE_PRUEBA_7 "GDB-54D"
#define STRING_DE_PRUEBA_8 "MAY-25Q"

typedef struct elemento_del_hash{
    const char* clave;  
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

//Verifica si la longitud de una clave es 7.
bool funcion(hash_t* hash, const char* clave, void* aux){
    return (strlen(clave) == 7);
}


void CrearConCapacidadMenorALaAceptada(){

    hash_t* hash_a_analizar = hash_crear(NULL, 1);

    pa2m_afirmar(hash_a_analizar->capacidad_de_la_tabla == 3, "Cuando se crea un hash con una capacidad menor a la minima aceptada, la capacidad de este es 3.");
    pa2m_afirmar(hash_a_analizar->tabla_de_hash != NULL, "Se creo una tabla de hash valida");
    pa2m_afirmar(hash_a_analizar->cantidad_de_elementos_en_el_hash == 0, "Al crear un hash la cantidad de elementos que este tiene es cero (0).");

    hash_destruir(hash_a_analizar);
}

void CrearConUnaCapacidadMayorALaAceptada(){

    hash_t* hash_a_analizar = hash_crear(NULL, 1000);

    pa2m_afirmar(hash_a_analizar->capacidad_de_la_tabla == 1000, "Se logra crear un hash con una capacidad de 1000 casilleros en la tabla.");
    pa2m_afirmar(hash_a_analizar->tabla_de_hash != NULL, "Se creo una tabla de hash valida");
    pa2m_afirmar(hash_a_analizar->cantidad_de_elementos_en_el_hash == 0, "Al crear un hash la cantidad de elementos que este tiene es cero (0).");

    hash_destruir(hash_a_analizar);
}


void  DadaUnaFuncionQueInsertaElementosDentroDeUnHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado(){

    hash_t* hash_a_analizar = hash_crear(NULL, 20);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;
    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_5, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_6, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_7, (void*)(&inserto_7));    
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_8, (void*)(&inserto_8));

    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_1), "El elemento asociado a STRING_DE_PRUEBA_1 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_2), "El elemento asociado a STRING_DE_PRUEBA_2 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_3), "El elemento asociado a STRING_DE_PRUEBA_3 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_4), "El elemento asociado a STRING_DE_PRUEBA_4 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_5), "El elemento asociado a STRING_DE_PRUEBA_5 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_6), "El elemento asociado a STRING_DE_PRUEBA_6 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_7), "El elemento asociado a STRING_DE_PRUEBA_7 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_8), "El elemento asociado a STRING_DE_PRUEBA_8 se encuentra en el hash");
    pa2m_afirmar(hash_contiene(hash_a_analizar, "STRING_INEXISTENTE") == false, "Una clave inexistente no puede tener algun elemento dentro del hash.");

    hash_destruir(hash_a_analizar);
}


void DadaUnaFuncionSobreEliminarElementosDentroDelHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado(){

    hash_t* hash_a_analizar = hash_crear(NULL, 20);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;
    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_5, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_6, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_7, (void*)(&inserto_7));    
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_8, (void*)(&inserto_8));

    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_1);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_2);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_3);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_4);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_5);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_6);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_7);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_8);

    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_1) == false, "El elemento asociado a STRING_DE_PRUEBA_1 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_2) == false, "El elemento asociado a STRING_DE_PRUEBA_2 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_3) == false, "El elemento asociado a STRING_DE_PRUEBA_3 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_4) == false, "El elemento asociado a STRING_DE_PRUEBA_4 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_5) == false, "El elemento asociado a STRING_DE_PRUEBA_5 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_6) == false, "El elemento asociado a STRING_DE_PRUEBA_6 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_7) == false, "El elemento asociado a STRING_DE_PRUEBA_7 no encuentra en el hash.");
    pa2m_afirmar(hash_contiene(hash_a_analizar, STRING_DE_PRUEBA_8) == false, "El elemento asociado a STRING_DE_PRUEBA_8 no encuentra en el hash.");

    hash_destruir(hash_a_analizar);
}


void DadaUnaFunCionSobreCrearUnHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado(){

    printf("-PRUEBAS SOBRE LA CREACION DE UN HASH CON UNA CAPACIDAD INICIAL MENOR A LA MINIMA ACEPTADA:\n");
    CrearConCapacidadMenorALaAceptada();

    printf("\n-PRUEBAS SOBRE LA CREACION DE UN HASH CON UNA CAPACIDAD INICIAL MAYOR A LA MINIMA ACEPTADA:\n");
    CrearConUnaCapacidadMayorALaAceptada();
}


void DadaUnaFuncionDeObtenerElementosEnUnHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado(){

    hash_t* hash_a_analizar = hash_crear(NULL, 20);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;
    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_5, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_6, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_7, (void*)(&inserto_7));    
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_8, (void*)(&inserto_8));

    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_1) == inserto_1, "Se consigue el 10 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_2) == inserto_2, "Se consigue el 20 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_3) == inserto_3, "Se consigue el 30 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_4) == inserto_4, "Se consigue el 40 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_5) == inserto_5, "Se consigue el 50 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_6) == inserto_6, "Se consigue el 60 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_7) == inserto_7, "Se consigue el 70 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_8) == inserto_8, "Se consigue el 80 dentro del hash.");
    pa2m_afirmar(hash_obtener(hash_a_analizar, "S") == NULL, "Un elemento inexistente no puede estar dentro del hash.");

    hash_destruir(hash_a_analizar);
}



void DadaUnaFuncionSobreLaCantidadDeElementosDentroDelHash_CuandoSeLaUsa_EntoncesElResultadoElEsperado(){

    hash_t* hash_a_analizar = hash_crear(NULL, 20);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;
    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    pa2m_afirmar(hash_cantidad(hash_a_analizar) == 0, "Al crear un hash, este tiene 0 elementos.")

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_5, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_6, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_7, (void*)(&inserto_7));    
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_8, (void*)(&inserto_8));

    pa2m_afirmar(hash_cantidad(hash_a_analizar) == 8, "Al insertar 8 elementos, la cantidad de elementos dentro del hash pasa a ser 8.");
    
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_1);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_2);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_3);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_4);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_5);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_6);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_7);
    hash_quitar(hash_a_analizar, STRING_DE_PRUEBA_8);

    pa2m_afirmar(hash_cantidad(hash_a_analizar) == 0, "Al eliminar los 8 elementos insertsfod, la cantidad de elementos dentor del hash pasa a ser 0.");
    
    hash_destruir(hash_a_analizar);
}


void DadaUnaFuncionDeInsertarElementos_CuandoSeInsertanElementosConClavesRepetidas_EntoncesElResultadoEsElEsperado(){

    hash_t* hash_a_analizar = hash_crear(NULL, 20);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));

    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_7));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_8));

    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_1) == inserto_5, "Se actualizo el 10 al 50.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_2) == inserto_6, "Se actualizo el 20 al 60.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_3) == inserto_7, "Se actualizo el 30 al 70.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_4) == inserto_8, "Se actualizo el 40 al 80.");


    hash_destruir(hash_a_analizar);
}


void DadoUnTdaHash_CuandoSeRehashea_ElResultadoEsElEsperado(){

    hash_t* hash_a_analizar = hash_crear(NULL, 4);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;
    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_5, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_6, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_7, (void*)(&inserto_7));    
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_8, (void*)(&inserto_8));

    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_1) == inserto_1, "Se consigue el 10 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_2) == inserto_2, "Se consigue el 20 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_3) == inserto_3, "Se consigue el 30 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_4) == inserto_4, "Se consigue el 40 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_5) == inserto_5, "Se consigue el 50 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_6) == inserto_6, "Se consigue el 60 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_7) == inserto_7, "Se consigue el 70 dentro del hash.");
    pa2m_afirmar(*(int*)hash_obtener(hash_a_analizar, STRING_DE_PRUEBA_8) == inserto_8, "Se consigue el 80 dentro del hash.");
    pa2m_afirmar(hash_obtener(hash_a_analizar, "S") == NULL, "Un elemento inexistente no puede estar dentro del hash.");

    hash_destruir(hash_a_analizar);
}



void PreubasSobreHashConCadaClave(){

    hash_t* hash_a_analizar = hash_crear(NULL, 100);

    int inserto_1 = 10;
    int inserto_2 = 20;
    int inserto_3 = 30;
    int inserto_4 = 40;
    int inserto_5 = 50;
    int inserto_6 = 60;
    int inserto_7 = 70;
    int inserto_8 = 80;

    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_1, (void*)(&inserto_1));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_2, (void*)(&inserto_2));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_3, (void*)(&inserto_3));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_4, (void*)(&inserto_4));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_5, (void*)(&inserto_5));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_6, (void*)(&inserto_6));
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_7, (void*)(&inserto_7));    
    hash_insertar(hash_a_analizar, STRING_DE_PRUEBA_8, (void*)(&inserto_8));

    hash_con_cada_clave(hash_a_analizar, funcion, NULL); 
    pa2m_afirmar(hash_con_cada_clave(hash_a_analizar, funcion, NULL) == 1, "La longitud de una clave es 1");
    
    hash_destruir(hash_a_analizar);
}


int main(){

    pa2m_nuevo_grupo("PRUEBAS SOBRE LA CREACION DE UN HASH:");
    DadaUnaFunCionSobreCrearUnHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("PRUEBAS SOBRE LA INSERCION Y CONTENCION DE ELEMENTOS EN UN HASH:");
    DadaUnaFuncionQueInsertaElementosDentroDeUnHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("PRUEBAS SOBRE LA ELIMINACION DE ELEMENTOS DENTRO DEL HASH:");
    DadaUnaFuncionSobreEliminarElementosDentroDelHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("PRUEBAS SOBRE LA OBTENCION DE ELEMENTOS EN UN HASH:");
    DadaUnaFuncionDeObtenerElementosEnUnHash_CuandoSeLaUsa_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("PRUEBAS SOBRE LA CANTIDAD DE ELEMENTOS DENTRO DE UN HASH:");
    DadaUnaFuncionSobreLaCantidadDeElementosDentroDelHash_CuandoSeLaUsa_EntoncesElResultadoElEsperado();

    pa2m_nuevo_grupo("PRUEBAS SOBRE INSERTAR CLAVES REPETIDAS");
    DadaUnaFuncionDeInsertarElementos_CuandoSeInsertanElementosConClavesRepetidas_EntoncesElResultadoEsElEsperado();

    pa2m_nuevo_grupo("PRUEBAS SOBRE REHASH");
    DadoUnTdaHash_CuandoSeRehashea_ElResultadoEsElEsperado();

    pa2m_nuevo_grupo("PREUBAS SOBRE HASH CON CADA ELEMENTO:");
    PreubasSobreHashConCadaClave();


    return pa2m_mostrar_reporte();
}