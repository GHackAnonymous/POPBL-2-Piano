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
#include <wiringPi.h>

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

int comparar_tecla(int tecla)
{
	printf("\n%d\n",tecla);
	switch (tecla)
	{
	case a:
		printf("%d\n", a);
		return DO;
		break;
	case w:
		printf("%d\n", w);
		return DOS;
		break;
	case s:
		printf("%d\n", s);
		return RE;
		break;
	case e:
		printf("%d\n", e);
		return RES;
		break;
	case d:
		printf("%d\n", d);
		return MI;
		break;
	case f:
		printf("%d\n", f);
		return FA;
		break;
	case t:
		printf("%d\n", t);
		return MIS;
		break;
	case g:
		printf("%d\n", g);
		return SOL;
		break;
	case y:
		printf("%d\n", y);
		return SOLS;
		break;
	case h:
		printf("%d\n", h);
		return LA;
		break;
	case u:
		printf("%d\n", u);
		return LAS;
		break;
	case j:
		printf("%d\n", j);
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
	for (i = 0; i <=13; i++)
	{
		int impulso = digitalRead(i);
		printf("\n%d\n",impulso);
		if(impulso == 1)
		{
			boton = i;
			printf("\n%d\n",boton);
			break;
		}
		if( i == 7)
		{
			i = 9;
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
      comando[9]= ("%d", tecla);
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
	int instrumento = 0;
	int opcion1 = digitalRead(14);
	int opcion2 = digitalRead(22);

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
	PSONIDO aux = NULL;
	int control = 1;
	cabesa = cargar_sonido(cabesa);

	aux = cabesa; 
	 do{

	while (leer_cadena(aux) != NULL)  
	{
		int tecla = leer_cadena(aux);
		reproducir_sonido(tecla, instrumento);
		aux = aux->pSig;
	}
        liberar(cabesa);
		control = digitalRead(21);
	} while (control != 1);
}
void tocar( int instrumento)
{
	int tecla = 0, control = 1;
	do
	{
		//tecla = escanear_tecla();
		tecla = detectar_gpio();
		int nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido(nuestra_tecla, instrumento);
		
		control = digitalRead(21);
	} while (control != 1);
}
PSONIDO grabar(PSONIDO cabesa, int instrumento)
{
	int nuestra_tecla = 1;
	int tecla = 0;
	int control = 1;
	do{
		while (nuestra_tecla != 0)
		{
			//tecla = escanear_tecla(); //ok
			tecla = detectar_gpio();
			nuestra_tecla = comparar_tecla(tecla); //ok
			reproducir_sonido(nuestra_tecla, instrumento); //ok
			cabesa = guardar_notas(cabesa, nuestra_tecla);
			guardar_archivo(cabesa);

		}
		control = digitalRead(21);
	}while(control != 1);
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
