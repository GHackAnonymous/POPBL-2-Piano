#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/
#include <wiringPi.h>

#include "Funciones.h"

char getch() {
	char buf = 0;
	struct termios old = { 0 };
	fflush(stdout);
	if (tcgetattr(0, &old)<0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1)<0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old)<0)
		perror("tcsetattr ~ICANON");
	return buf;
}

int init_gpio()
{
	if (wiringPiSetup() == -1)
	{
		return 1;
	}

	pinMode(0, INPUT); //0 es el correspondiente del chip al pin 11
	pinMode(1, INPUT); //1 es el correspondiente del chip al pin 12
	pinMode(2, INPUT); //2 es el correspondiente del chip al pin 13
	pinMode(3, INPUT); //3 es el correspondiente del chip al pin 15
	pinMode(4, INPUT); //4 es el correspondiente del chip al pin 16
	pinMode(5, INPUT); //5 es el correspondiente del chip al pin 18
	pinMode(6, INPUT); //6 es el correspondiente del chip al pin 22
	pinMode(7, INPUT); //7 es el correspondiente del chip al pin 29
	pinMode(10, INPUT); //8 es el correspondiente del chip al pin 31
	pinMode(11, INPUT); //9 es el correspondiente del chip al pin 32
	pinMode(12, INPUT); //10 es el correspondiente del chip al pin 33
	pinMode(13, INPUT); //11 es el correspondiente del chip al pin 35
	pinMode(14, INPUT); // Cool rumner  p1 j1
	pinMode(22, INPUT); // cool runner p2 j1
	pinMode(29, OUTPUT); // cool runner p7 j1
	pinMode(27, OUTPUT); // cool runner p8 j1
	pinMode(26, INPUT); // cool runner p3 j1
	pinMode(25, INPUT); // cool runner p4 j1
	pinMode(21, INPUT); // Boton Salir
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
	int funcion;
	funcion = 1;

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
	int funcion;
	funcion = 2;
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
	printf("%d", cabesa);
	return cabesa;
}
int leer_cadena(PSONIDO aux)
{
	int tecla;
	tecla = 0;
	if (aux != NULL)
	{
		tecla = (aux)->tecla;
	}

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
	int boton;
	int i;

	boton = -1;
	i = 0;

	for (i = 0; i <= 13; i++)
	{
		int impulso = digitalRead(i);
		if (impulso == 1)
		{
			boton = i;
			break;
		}
		if (i == 7)
		{
			i = 9;
		}
	}

	return boton;
}
void lanzar_comando(char comando[])
{
	system(comando);
	sleep(0.5);
}
int escoger_nota_alta(int tecla)
{
	switch (tecla)
	{
	case LA:
		tecla = 48;
		return(tecla);
	case LAS:
		tecla = 49;
		return(tecla);
		break;
	case SI:
		tecla = 50;
		return(tecla);
		break;
	default:
		break;
	}
}
void reproducir_sonido(int tecla, int instrumento)
{
	char comando[] = "aplay ./00.wav";
	switch (instrumento)
	{
	case Piano:
		if (tecla >= LA)
		{
			comando[8] = 49;
			comando[9] = escoger_nota_alta(tecla);
			lanzar_comando(comando);
		}
		else if (tecla != 0)
		{
			comando[9] = ("%d", tecla);
			lanzar_comando(comando);
		}
		break;
	case Ukelele:
		comando[8] = 50;
		if (tecla >= LA)
		{
			comando[8] = 51;
			comando[9] = escoger_nota_alta(tecla);
			lanzar_comando(comando);
		}
		else if (tecla != 0)
		{
			comando[9] = ("%d", tecla);
			lanzar_comando(comando);
		}
		break;
	case Ocarina:
		comando[8] = 52;
		if (tecla >= LA)
		{
			comando[8] = 53;
			comando[9] = escoger_nota_alta(tecla);
			lanzar_comando(comando);
		}
		else if (tecla != 0)
		{
			comando[9] = ("%d", tecla);
			lanzar_comando(comando);
		}
		break;
	case Sintetizador:
		comando[8] = 54;
		if (tecla >= LA)
		{
			comando[8] = 55;
			comando[9] = escoger_nota_alta(tecla);
			lanzar_comando(comando);
		}
		else if (tecla != 0)
		{
			comando[9] = ("%d", tecla);
			lanzar_comando(comando);
		}
		break;
	}
}
int elegir_instrumento()
{
	int instrumento;
	int opcion1;
	int opcion2;

	instrumento = 0;
	opcion1 = digitalRead(14);
	opcion2 = digitalRead(22);

	if (opcion1 == 0 && opcion2 == 0)
	{
		instrumento = Piano;
	}
	else if (opcion1 == 1 && opcion2 == 0)
	{
		instrumento = Ukelele;
	}
	else if (opcion1 == 0 && opcion2 == 1)
	{
		instrumento = Ocarina;
	}
	else if (opcion1 == 1 && opcion2 == 1)
	{
		instrumento = Sintetizador;
	}

	return instrumento;
}
void reproducir(PSONIDO cabesa, int instrumento)
{
	PSONIDO aux;
	int control;

	aux = NULL;
	control = 1;

	cabesa = cargar_sonido(cabesa);

	aux = cabesa;

	do {

		while (leer_cadena(aux) != 0)
		{
			int tecla = leer_cadena(aux);
			reproducir_sonido(tecla, instrumento);
			aux = aux->pSig;
		}

		control = digitalRead(21);
	} while (control != 1);
	liberar(cabesa);
}
void tocar(int instrumento)
{
	int tecla;
	int control;

	tecla = 0;
	control = 1;

	do
	{
		tecla = detectar_gpio();
		int nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido(nuestra_tecla, instrumento);

		control = digitalRead(21);
	} while (control != 1);
}
PSONIDO grabar(PSONIDO cabesa, int instrumento)
{
	int nuestra_tecla;
	int tecla;
	int control;

	nuestra_tecla = 1;
	tecla = -2;
	control = 1;
	do {
		do
		{

			tecla = detectar_gpio();
			nuestra_tecla = comparar_tecla(tecla);
			reproducir_sonido(nuestra_tecla, instrumento);
			if (nuestra_tecla != 0)
			{
				cabesa = guardar_notas(cabesa, nuestra_tecla);
				guardar_archivo(cabesa);
			}

		} while (nuestra_tecla != 0);
		control = digitalRead(21);
	} while (control != 1);
	liberar(cabesa);
	return cabesa;
}
void liberar(PSONIDO cabesa)
{
	PSONIDO aux;
	while (cabesa->pSig != NULL)
	{
		aux = cabesa;
		cabesa = cabesa->pSig;
		free(aux);
	}
}
