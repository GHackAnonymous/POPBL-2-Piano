#ifndef Funciones
#define Funciones


#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/
#include <wiringPi.h>

#include "Funciones.h"


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


typedef struct Melodia
{
	int tecla;
	struct Melodia *pSig;
} SONIDO, *PSONIDO;

int elegir_instrumento();
char getch();
FILE* abrir_archivo(int funcion);
int comparar_tecla(int tecla);
PSONIDO crear_cadena(PSONIDO cabesa, int tecla);
int leer_cadena(PSONIDO aux);
void reproducir(PSONIDO cabesa, int instrumento);
void reproducir_sonido(int tecla, int instrumento);
PSONIDO saltar_cadena(PSONIDO aux);
PSONIDO cargar_sonido(PSONIDO cabesa);
void guardar_archivo(PSONIDO cabesa);
void escribir_nota(FILE* fp, PSONIDO cabesa);
PSONIDO guardar_notas(PSONIDO cabesa, int nota);
void tocar();
PSONIDO grabar(PSONIDO cabesa, int instrumento);
int cargar_de_archivo(FILE* fp, int tecla);
void lanzar_comando(char comando[]);
void liberar(PSONIDO cabesa);
int detectar_gpio();
int init_gpio();

#endif
