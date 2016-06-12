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
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>



#define DO 49
#define DOS 50
#define RE 51
#define RES 52
#define MI 53
#define FA 54
#define FAS 55
#define SOL 56
#define SOLS 57
#define LA 58
#define LAS 59
#define SI 60
#define tecla_a 97
#define tecla_w 119
#define tecla_s 115
#define tecla_e 101
#define tecla_d 100
#define tecla_f 102
#define tecla_t 116
#define tecla_g 103
#define tecla_y 121
#define tecla_h 104
#define tecla_u 117
#define tecla_j 106
#define Piano 1
#define Ukelele 2
#define Ocarina 3
#define Sintetizador 4



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

FILE* abrir_archivo(int funcion); // ok
int comparar_tecla(int tecla); //ok
PSONIDO crear_cadena(PSONIDO cabesa, int tecla); // OK
int escanear_tecla(); //ok
int leer_cadena(PSONIDO aux); //ok
void reproducir(PSONIDO cabesa, int instrumento); // ok
void reproducir_sonido(int tecla); //ok
PSONIDO saltar_cadena(PSONIDO aux); // ok
PSONIDO cargar_sonido(PSONIDO cabesa); // ok
void guardar_archivo(PSONIDO cabesa); //ok
void escribir_nota(FILE* fp, PSONIDO cabesa); //ok
PSONIDO guardar_notas(PSONIDO cabesa, int nota); //ok
void tocar(int instrumento);
PSONIDO grabar(PSONIDO cabesa,int instrumento);
int cargar_de_archivo(FILE* fp, int tecla);
void lanzar_comando(char comando[]);
void reproducir_sonido_mix(int nuestra_tecla,int instrumento);
#endif