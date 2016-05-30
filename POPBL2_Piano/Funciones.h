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

int Abrir_Archivo(int tecla);
int Comparar_Tecla(int tecla);
PSONIDO Crear_Cadena(PSONIDO cabesa);
int Escanear_Tecla();
void Grabar(FILE * fp, PSONIDO cabesa);
void Grabar_Archivo(PSONIDO cabesa);
int Leer_Cabesa(PSONIDO cabesa);
void Reproducir(FILE * fp, PSONIDO cabesa);
void Reproducir_Tecla(int tecla);
void Tecla();
PSONIDO Cargar_Archivo(int tecla);
void Saltar_Cadena(PSONIDO aux);



#endif