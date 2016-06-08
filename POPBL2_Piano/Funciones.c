#define _CRT_SECURE_NO_WARNINGS

#include "Funciones.h"
//#include <windows.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
//#include <dos.h>
#include <string.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/

char getch(){
    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }

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
	
	while ((tecla = cargar_de_archivo(fp, tecla)) != NULL)
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
        int tecla = getch();
        return tecla;
}
int comparar_tecla(int tecla)
{
	switch (tecla)
	{
	case a:
		return DO;
		break;
	case w:
		return DOS;
		break;
	case s:
		return RE;
		break;
	case e:
		return RES;
		break;
	case d:
		return MI;
		break;
	case f:
		return FA;
		break;
	case t:
		return MIS;
		break;
	case g:
		return SOL;
		break;
	case y:
		return SOLS;
		break;
	case h:
		return LA;
		break;
	case u:
		return LAS;
		break;
	case j:
		return SI;
		break;
	default:
		return 0;

	}
}
int detectar_gpio()
{
	int boton = -1;
	int i = 0;
	for (i = 0; i <= 11; i++)
	{
		int impulso = digitalRead(i);
		if(impulso == 1)
		{
			boton = i;
			break;
		}
	}
	return boton;
}
void lanzar_comando(char comando[])
{
	printf(comando);
	system(comando);
	sleep(0.5);
}
void reproducir_sonido(int tecla)
{
	
	char comando[] = "aplay ./00.wav";
	if (tecla >= LA)
	{
		comando[8] = 49;
		switch (tecla)
		{
		case LA:
			comando[9] = 48;
			lanzar_comando(comando); 
			break;
		case LAS:
			comando[9] = 49;
			lanzar_comando(comando);
			break;
		case SI:
			comando[9] = 50;
			lanzar_comando(comando);
			break;
		default:
			break;
		}
	}
	else if(tecla != 0)
	{
		comando[9] = ("%d", tecla);
		lanzar_comando(comando);
	}
}

void reproducir(PSONIDO cabesa)
{
	PSONIDO aux = NULL;

	cabesa = cargar_sonido(cabesa);

	aux = cabesa; 

	while (leer_cadena(aux) != NULL)  
	{
		int tecla = leer_cadena(aux);
		reproducir_sonido(tecla);
		aux = aux->pSig;
	}
        liberar(cabesa);
}
void tocar()
{
	int tecla = 0;
	do
	{
		//tecla = escanear_tecla();
		tecla = detectar_gpio();
		int nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido(nuestra_tecla);
	} while (tecla != 27);
}
PSONIDO grabar(PSONIDO cabesa)
{
	int nuestra_tecla = 1;
	int tecla = 0;
	while (nuestra_tecla != 0)
	{
		//tecla = escanear_tecla(); //ok
		tecla = detectar_gpio();
		nuestra_tecla = comparar_tecla(tecla); //ok
		reproducir_sonido(nuestra_tecla); //ok
		cabesa = guardar_notas(cabesa, nuestra_tecla);
		guardar_archivo(cabesa);

	}
        liberar(cabesa);
	return cabesa;
}
void liberar(PSONIDO cabesa)
{
    PSONIDO aux;
    while(cabesa->pSig != NULL)
    {
        aux = cabesa;
        cabesa = cabesa->pSig;
        free(aux);
    }
}