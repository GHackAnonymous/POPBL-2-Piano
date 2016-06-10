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
#include <wiringPi.h>

//#define DO 49
//#define DOS 50
//#define RE 51
//#define RES 52
//#define MI 53
//#define FA 54
//#define MIS 55
//#define SOL 56
//#define SOLS 57
//#define LA 58
//#define LAS 59
//#define SI 60
//#define a 97
//#define s 115
//#define e 101
//#define d 100
//#define w 119
//#define f 102
//#define t 116
//#define g 103
//#define y 121
//#define h 104
//#define u 117
//#define j 106

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
#define a 0
#define s 2
#define e 3
#define d 4
#define w 1
#define f 5
#define t 6
#define g 7
#define y 10
#define h 11
#define u 12
#define j 13
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

int elegir_instrumento();
char getch(); //ok
FILE* abrir_archivo(int funcion); // ok
int comparar_tecla(int tecla); //ok
PSONIDO crear_cadena(PSONIDO cabesa, int tecla); // OK
/*int escanear_tecla();*/ //ok
int leer_cadena(PSONIDO aux); //ok
void reproducir(PSONIDO cabesa, int instrumento); // ok
void reproducir_sonido(int tecla, int instrumento); //ok
PSONIDO saltar_cadena(PSONIDO aux); // ok
PSONIDO cargar_sonido(PSONIDO cabesa); // ok
void guardar_archivo(PSONIDO cabesa); //ok
void escribir_nota(FILE* fp, PSONIDO cabesa); //ok
PSONIDO guardar_notas(PSONIDO cabesa, int nota); //ok
void tocar();
PSONIDO grabar(PSONIDO cabesa, int instrumento);
int cargar_de_archivo(FILE* fp, int tecla);
void lanzar_comando(char comando[]);
void liberar(PSONIDO cabesa);
int detectar_gpio();

#endif
