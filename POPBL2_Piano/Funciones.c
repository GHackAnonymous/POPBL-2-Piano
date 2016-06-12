#define _CRT_SECURE_NO_WARNINGS

#include "Funciones.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>


PSONIDO crear_cadena(PSONIDO cabesa, int tecla)
{
	PSONIDO nuevo;
	PSONIDO aux;

	aux = cabesa;

	nuevo = malloc(sizeof(SONIDO));
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


FILE* abrir_archivo(int funcion)
{
	FILE* fp;
	if (funcion == 1)
	{
		fp = fopen("grabacion.dat", "rb");
	}
	else if (funcion == 2)
	{
		fp = fopen("grabacion.dat", "wb");
	}

	return fp;
}

int cargar_de_archivo(FILE* fp, int tecla)
{
	fread(&tecla, sizeof(SONIDO), 1, fp);
	return tecla;
}

PSONIDO cargar_sonido(PSONIDO cabesa)
{
	FILE* fp;
	int tecla;
	int funcion = 1;

	cabesa = NULL;
	tecla = 0;
	fp = abrir_archivo(funcion);
	
	while ((tecla = cargar_de_archivo(fp, tecla)) != 0)
	{
		cabesa = crear_cadena(cabesa, tecla);
		tecla = 0;
	}
	return cabesa;
}

void guardar_archivo(PSONIDO cabesa)
{
	FILE *fp;
	int funcion = 2;
	fp = abrir_archivo(funcion);
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
int leer_cadena(PSONIDO aux)
{
	int tecla = 0; 
	if (aux != NULL)
	{
		tecla = (aux)->tecla; 
	}

	return tecla;
}
int escanear_tecla()
{
	int tecla = _getch();
	return tecla;
}
int comparar_tecla(int nuestra_tecla)

{

			switch (nuestra_tecla) {

			case tecla_a:
				return DO;
				break;
			case tecla_w:
				return DOS;
				break;
			case tecla_s:
				return RE;
				break;
			case tecla_e:
				return RES;
				break;
			case tecla_d:
				return MI;
				break;
			case tecla_f:
				return FA;
				break;
			case tecla_t:
				return FAS;
				break;
			case tecla_g:
				return SOL;
				break;
			case tecla_y:
				return SOLS;
				break;
			case tecla_h:
				return LA;
				break;
			case tecla_u:
				return LAS;
				break;
			case tecla_j:
				return SI;
				break;
			default:
				return 0;
			
			}

			}

void lanzar_comando(char comando[])
{
	printf(comando);
	system(comando);
	Sleep(2000);
}
/*void reproducir_sonido(int tecla)
{
	
	char comando[] = "start wmplayer \"%cd%\\00.wav\"";
	if (tecla >= LA)
	{
		comando[21] = 49;
		switch (tecla)
		{
		case LA:
			comando[22] = 48;
			lanzar_comando(comando); 
			break;
		case LAS:
			comando[22] = 49;
			lanzar_comando(comando);
			break;
		case SI:
			comando[22] = 50;
			lanzar_comando(comando);
			break;
		default:
			break;
		}
	}
	else if(tecla != 0)
	{
		comando[22] = ("%d", tecla);
		lanzar_comando(comando);
	}
}
*/
void reproducir_sonido_mix(int nuestra_tecla,int instrumento)
{
	
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Chunk*Do = Mix_LoadWAV("01.wav");
	Mix_Chunk*Dos = Mix_LoadWAV("02.wav");
	Mix_Chunk*Re = Mix_LoadWAV("03.wav");
	Mix_Chunk*Res = Mix_LoadWAV("04.wav");
	Mix_Chunk*Mi = Mix_LoadWAV("05.wav");
	Mix_Chunk*Fa = Mix_LoadWAV("06.wav");
	Mix_Chunk*Fas = Mix_LoadWAV("07.wav");
	Mix_Chunk*Sol = Mix_LoadWAV("08.wav");
	Mix_Chunk*Sols = Mix_LoadWAV("09.wav");
	Mix_Chunk*La = Mix_LoadWAV("10.wav");
	Mix_Chunk*Las = Mix_LoadWAV("11.wav");
	Mix_Chunk*Si = Mix_LoadWAV("12.wav");
	Mix_Chunk*Uk_1 = Mix_LoadWAV("21.wav");
	Mix_Chunk*Uk_2 = Mix_LoadWAV("22.wav");
	Mix_Chunk*Uk_3 = Mix_LoadWAV("23.wav");
	Mix_Chunk*Uk_4 = Mix_LoadWAV("24.wav");
	Mix_Chunk*Uk_5 = Mix_LoadWAV("25.wav");
	Mix_Chunk*Uk_6 = Mix_LoadWAV("26.wav");
	Mix_Chunk*Uk_7 = Mix_LoadWAV("27.wav");
	Mix_Chunk*Uk_8 = Mix_LoadWAV("28.wav");
	Mix_Chunk*Uk_9 = Mix_LoadWAV("29.wav");
	Mix_Chunk*Uk_10 = Mix_LoadWAV("30.wav");
	Mix_Chunk*Uk_11 = Mix_LoadWAV("31.wav");
	Mix_Chunk*Uk_12 = Mix_LoadWAV("32.wav");
	Mix_Chunk*Oc_1 = Mix_LoadWAV("41.wav");
	Mix_Chunk*Oc_2 = Mix_LoadWAV("42.wav");
	Mix_Chunk*Oc_3 = Mix_LoadWAV("43.wav");
	Mix_Chunk*Oc_4 = Mix_LoadWAV("44.wav");
	Mix_Chunk*Oc_5 = Mix_LoadWAV("45.wav");
	Mix_Chunk*Oc_6 = Mix_LoadWAV("46.wav");
	Mix_Chunk*Oc_7 = Mix_LoadWAV("47.wav");
	Mix_Chunk*Oc_8 = Mix_LoadWAV("48.wav");
	Mix_Chunk*Oc_9 = Mix_LoadWAV("49.wav");
	Mix_Chunk*Oc_10 = Mix_LoadWAV("50.wav");
	Mix_Chunk*Oc_11 = Mix_LoadWAV("51.wav");
	Mix_Chunk*Oc_12 = Mix_LoadWAV("52.wav");
	Mix_Chunk*Sint_1 = Mix_LoadWAV("61.wav");
	Mix_Chunk*Sint_2 = Mix_LoadWAV("62.wav");
	Mix_Chunk*Sint_3 = Mix_LoadWAV("63.wav");
	Mix_Chunk*Sint_4 = Mix_LoadWAV("64.wav");
	Mix_Chunk*Sint_5 = Mix_LoadWAV("65.wav");
	Mix_Chunk*Sint_6 = Mix_LoadWAV("66.wav");
	Mix_Chunk*Sint_7 = Mix_LoadWAV("67.wav");
	Mix_Chunk*Sint_8 = Mix_LoadWAV("68.wav");
	Mix_Chunk*Sint_9 = Mix_LoadWAV("69.wav");
	Mix_Chunk*Sint_10 = Mix_LoadWAV("70.wav");
	Mix_Chunk*Sint_11 = Mix_LoadWAV("71.wav");
	Mix_Chunk*Sint_12 = Mix_LoadWAV("72.wav");


	//Estas son todas las notas que disponemos

	switch(instrumento){

	case Piano:
		switch (nuestra_tecla)
		{
		case DO:
			Mix_PlayChannel(1, Do, 0);
			break;
		case DOS:
			Mix_PlayChannel(2, Dos, 0);
			break;
		case RE:
			Mix_PlayChannel(3, Re, 0);
			break;
		case RES:
			Mix_PlayChannel(4, Res, 0);
			break;
		case MI:
			Mix_PlayChannel(5, Mi, 0);
			break;
		case FA:
			Mix_PlayChannel(6, Fa, 0);
			break;
		case FAS:
			Mix_PlayChannel(7, Fas, 0);
			break;
		case SOL:
			Mix_PlayChannel(7, Sol, 0);
			break;
		case SOLS:
			Mix_PlayChannel(7, Sols, 0);
			break;
		case LA:
			Mix_PlayChannel(7, La, 0);
			break;
		case LAS:
			Mix_PlayChannel(7, Las, 0);
			break;
		case SI:
			Mix_PlayChannel(7, Si, 0);
			break;
		default:
			break;
		}
		break;
		
	case Ukelele:
		switch (nuestra_tecla)
		{
		case DO:
			Mix_PlayChannel(1, Uk_1, 0);
			break;
		case DOS:
			Mix_PlayChannel(2, Uk_2, 0);
			break;
		case RE:
			Mix_PlayChannel(3, Uk_3, 0);
			break;
		case RES:
			Mix_PlayChannel(4, Uk_4, 0);
			break;
		case MI:
			Mix_PlayChannel(5, Uk_5, 0);
			break;
		case FA:
			Mix_PlayChannel(6, Uk_6, 0);
			break;
		case FAS:
			Mix_PlayChannel(7, Uk_7, 0);
			break;
		case SOL:
			Mix_PlayChannel(7, Uk_8, 0);
			break;
		case SOLS:
			Mix_PlayChannel(7, Uk_9, 0);
			break;
		case LA:
			Mix_PlayChannel(7, Uk_10, 0);
			break;
		case LAS:
			Mix_PlayChannel(7, Uk_11, 0);
			break;
		case SI:
			Mix_PlayChannel(7, Uk_12, 0);
			break;
		default:
			break;
		}
		break;

	case Ocarina:
		switch (nuestra_tecla)
		{
		case DO:
			Mix_PlayChannel(1, Oc_1, 0);
			break;
		case DOS:
			Mix_PlayChannel(2, Oc_2, 0);
			break;
		case RE:
			Mix_PlayChannel(3, Oc_3, 0);
			break;
		case RES:
			Mix_PlayChannel(4, Oc_4, 0);
			break;
		case MI:
			Mix_PlayChannel(5, Oc_5, 0);
			break;
		case FA:
			Mix_PlayChannel(6, Oc_6, 0);
			break;
		case FAS:
			Mix_PlayChannel(7, Oc_7, 0);
			break;
		case SOL:
			Mix_PlayChannel(7, Oc_8, 0);
			break;
		case SOLS:
			Mix_PlayChannel(7, Oc_9, 0);
			break;
		case LA:
			Mix_PlayChannel(7, Oc_10, 0);
			break;
		case LAS:
			Mix_PlayChannel(7, Oc_11, 0);
			break;
		case SI:
			Mix_PlayChannel(7, Oc_12, 0);
			break;
		default:
			break;

		}
		break;
	case Sintetizador:
		switch (nuestra_tecla)
		{
		case DO:
			Mix_PlayChannel(1, Sint_1, 0);
			break;
		case DOS:
			Mix_PlayChannel(2, Sint_2, 0);
			break;
		case RE:
			Mix_PlayChannel(3, Sint_3, 0);
			break;
		case RES:
			Mix_PlayChannel(4, Sint_4, 0);
			break;
		case MI:
			Mix_PlayChannel(5, Sint_5, 0);
			break;
		case FA:
			Mix_PlayChannel(6, Sint_6, 0);
			break;
		case FAS:
			Mix_PlayChannel(7, Sint_7, 0);
			break;
		case SOL:
			Mix_PlayChannel(7, Sint_8, 0);
			break;
		case SOLS:
			Mix_PlayChannel(7, Sint_9, 0);
			break;
		case LA:
			Mix_PlayChannel(7, Sint_10, 0);
			break;
		case LAS:
			Mix_PlayChannel(7, Sint_11, 0);
			break;
		case SI:
			Mix_PlayChannel(7, Sint_12, 0);
			break;
		default:
			break;
		}
	default:
		break;
		
}

}
void reproducir(PSONIDO cabesa,int instrumento)
{
	PSONIDO aux = NULL;

	cabesa = cargar_sonido(cabesa);

	aux = cabesa; 

	while (leer_cadena(aux) != 0)  
	{
		int tecla = leer_cadena(aux);
		reproducir_sonido_mix(tecla,instrumento);
		aux = aux->pSig;
	}
}
void tocar(int instrumento)
{
	int tecla = 0;
	do
	{
		tecla = escanear_tecla();
		int nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido_mix(nuestra_tecla,instrumento);
	} while (tecla != 27);
}
PSONIDO grabar(PSONIDO cabesa,int instrumento)
{
	int nuestra_tecla = 1;
	int tecla = 0;
	while (nuestra_tecla != 0)
	{
		tecla = escanear_tecla();
		nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido_mix(nuestra_tecla,instrumento);
		cabesa = guardar_notas(cabesa, nuestra_tecla);
		guardar_archivo(cabesa);

	}
	return cabesa;
}