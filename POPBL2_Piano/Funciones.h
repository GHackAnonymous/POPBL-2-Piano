/**
* @file Funciones.h
*
* @brief Aqui estan definidas las teclas, notas e intrumentos mediante defines.
*		 Estan incluido la estructura Melodia llamada SONIDO.
*
* @author Irene Delgado (irene.delgado@alumni.mondragon.edu)
* @author Lucas Sousa (lucas.sousa@alumni.mondragon.edu)
* @author Xabier Gandiaga (xabier.gandiaga@alumni.mondragon.edu)
* @author Eder Gomez de Segura (eder.gomezp@alumni.mondragon.edu)
* @author Nikolay Zabaleta (nikolay.zabaleta@alumni.mondragon.edu)
* @author Inigo Ayestaran (inigo.ayestaran@alumni.mondragon.edu)
*
* @date 2016-06-10
*/

#ifndef Funciones
#define Funciones

#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>

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
#define Piano 1
#define Ukelele 2
#define Ocarina 3
#define Sintetizador 4

typedef struct Melodia
{
	int tecla;
	struct Melodia *pSig;
} SONIDO, *PSONIDO;

FILE* abrir_archivo(int funcion);
int comparar_tecla(int tecla);
PSONIDO crear_cadena(PSONIDO cabesa, int tecla);
int escanear_tecla();
int leer_cadena(PSONIDO aux);
void reproducir(PSONIDO cabesa, int instrumento);
void reproducir_sonido(int tecla, int instrumento);
PSONIDO saltar_cadena(PSONIDO aux);
PSONIDO cargar_sonido(PSONIDO cabesa);
void guardar_archivo(PSONIDO cabesa);
void escribir_nota(FILE* fp, PSONIDO cabesa);
PSONIDO guardar_notas(PSONIDO cabesa, int nota);
void tocar(int instrumento);
void grabar(PSONIDO cabesa, int instrumento);
int cargar_de_archivo(FILE* fp, int tecla);
void lanzar_comando(char comando[]);

#endif