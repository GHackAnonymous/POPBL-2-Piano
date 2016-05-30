#include "Funciones.h"
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>


PSONIDO crear_cadena(PSONIDO cabesa, int tecla)
{
	PSONIDO nuevo;
	PSONIDO aux;

	aux = cabesa;

	nuevo = malloc(sizeof(SONIDO));//crear_cadena
	nuevo->tecla = tecla;
	if (cabesa == NULL)
	{
		cabesa = nuevo;
		cabesa->pSig = NULL;
	}

	else
	{
		aux = saltar_cadena(aux);
		nuevo->pSig = NULL;
		aux->pSig = nuevo;
	}

	return cabesa;
}


PSONIDO saltar_cadena(PSONIDO aux)
{
	while (aux->pSig != NULL)
	{
		aux = aux->pSig;
	}
	return aux;
}


FILE* abrir_archivo(char funcion)
{
	FILE* fp;
	fp = fopen("grabacion.dat", "%c", funcion);
	return fp;
}


PSONIDO cargar_sonido()
{
	PSONIDO cabesa;
	FILE* fp;
	int tecla;

	cabesa = NULL;
	tecla = 0;
	fp = abrir_archivo("rb");
	while (cargar_archivo(fp, tecla) != 0)
	{
		cabesa = crear_cadena(cabesa, tecla);
		tecla = 0;
	}
	return cabesa;
}

void guardar_archivo(PSONIDO cabesa)
{
	FILE *fp;

	fp = abrir_archivo("wb");
	while (cabesa != NULL)
	{
		escribir_nota(fp, cabesa);
		cabesa = cabesa->pSig;
	}
	fclose(fp);
}

void escribir_nota(FILE* fp, PSONIDO cabesa)
{
	fwrite(&cabesa->tecla, sizeof(SONIDO), 1, fp);
}

PSONIDO guardar_notas(PSONIDO cabesa, int nota)
{
	cabesa = crear_cadena(cabesa, nota);
	return cabesa;
}
int leer_cadena(PSONIDO* aux)//aux* está apuntando a cabesa desde el main
{
	int tecla;

	tecla = (*aux)->tecla;
	(*aux) = (*aux)->pSig;

	return tecla;
}
int escanear_Tecla()
{
	int tecla = getch();
	return tecla;
}
int comparar_tecla(int tecla) 
{
	switch (tecla) 
	{
	case 97:
		return 1;
	break;
	case 98:
		return 2;
	break;
	case 99:
		return 3;
	break;
	}
}
void reproducir_sonido(int tecla)
{

	char comando[] = "start wmplayer \"C:\\Users\\GHackAnonymous\\Desktop\\ProyectoPiano\\Sonidos\\";
	char extension[] = ".wav\"";

	strcat(comando, tecla);
	strcat(comando, extension);
	printf(comando);
	system(comando);
}