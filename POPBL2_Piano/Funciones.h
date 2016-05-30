/** 
*  @file Funciones.h
*  @brief Function prototypes for the console driver.
*
*  This contains the prototypes for the console
*  driver and eventually any macros, constants,
*  or global variables you will need.
*
*  @author Eder Gómez de Segura (eder.gomezp@alumni.mondragon.edu)
*  @author
*  @author
*  @author
*  @author
*  @author
*/



#ifndef Funciones
#define Funciones

#include "Funciones.h"


/** @brief explicacion corta
*
*  Comentario de que hacer
*
*  @param ch 
*  @return 
*/

typedef struct Melodia
{
	int tecla;
	struct Melodia *pSig;
} SONIDO, *PSONIDO;

//FILE* abrir_archivo(char funcion); // ok
int abrir_archivo(char funcion); // ok
int comparar_tecla(int tecla);
PSONIDO crear_cadena(PSONIDO cabesa, int tecla); // OK
int escanear_Tecla();
//void grabar(FILE* fp, PSONIDO cabesa);
void grabar(int fp, PSONIDO cabesa);
void grabar_archivo(PSONIDO cabesa);
int leer_cabesa(PSONIDO aux); //ok
//void reproducir(FILE* fp, PSONIDO cabesa);
void reproducir(int  fp, PSONIDO cabesa);
void reproducir_sonido(int tecla);
void tecla();
//PSONIDO cargar_archivo(FILE* fp, int tecla);
PSONIDO cargar_archivo(int fp, int tecla);
PSONIDO saltar_cadena(PSONIDO aux); // ok
PSONIDO cargar_sonido(); // ok
void guardar_archivo(PSONIDO cabesa); //ok
//void escribir_nota(FILE* fp, PSONIDO cabesa); //ok
void escribir_nota(int fp, PSONIDO cabesa); //ok
PSONIDO guardar_notas(PSONIDO cabesa, int nota); //ok



#endif