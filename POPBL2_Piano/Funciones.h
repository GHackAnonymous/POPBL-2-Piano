/**
*  @file Funciones.h
*  @brief Function prototypes for the console driver.
*
*  This contains the prototypes for the console
*  driver and eventually any macros, constants,
*  or global variables you will need.
*
*  @author Eder G�mez de Segura (eder.gomezp@alumni.mondragon.edu)
*  @author
*  @author
*  @author
*  @author
*  @author
*/



#ifndef Funciones
#define Funciones

#include "Funciones.h"
//#include<windows.h>
//#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
//#include<dos.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/

#define DO 49
#define DOS 50
#define RE 51
#define RES 52
#define MI 53
#define FA 54
#define MIS 55
#define SOL 56
#define SOLS 57
#define LA 58
#define LAS 59
#define SI 60
#define a 97
#define s 115
#define e 101
#define d 100
#define w 119
#define f 102
#define t 116
#define g 103
#define y 121
#define h 104
#define u 117
#define j 106


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

char getch(); //ok
FILE* abrir_archivo(int funcion); // ok
int comparar_tecla(int tecla); //ok
PSONIDO crear_cadena(PSONIDO cabesa, int tecla); // OK
int escanear_tecla(); //ok
int leer_cadena(PSONIDO aux); //ok
void reproducir(PSONIDO cabesa); // ok
void reproducir_sonido(int tecla); //ok
PSONIDO saltar_cadena(PSONIDO aux); // ok
PSONIDO cargar_sonido(PSONIDO cabesa); // ok
void guardar_archivo(PSONIDO cabesa); //ok
void escribir_nota(FILE* fp, PSONIDO cabesa); //ok
PSONIDO guardar_notas(PSONIDO cabesa, int nota); //ok
void tocar();
PSONIDO grabar(PSONIDO cabesa);
int cargar_de_archivo(FILE* fp, int tecla);
void lanzar_comando(char comando[]);
void liberar(PSONIDO cabesa);


#endif