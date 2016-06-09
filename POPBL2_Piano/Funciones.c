#define _CRT_SECURE_NO_WARNINGS

#include "Funciones.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>


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
	//tecla = cargar_de_archivo(fp, tecla);
	//while (cargar_de_archivo(fp, tecla) != NULL)//necesita funcion;  //Fallo AQUI TECLA DESPUES OBTIONE 0
	while ((tecla = cargar_de_archivo(fp, tecla)) != NULL)//necesita funcion;  //Fallo AQUI TECLA DESPUES OBTIONE 0
	//while (tecla != NULL)//necesita funcion;  //Fallo AQUI TECLA DESPUES OBTIONE 0
	{
		//tecla = cargar_de_archivo(fp, tecla);
		//cabesa = crear_cadena(cabesa, tecla);
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
int leer_cadena(PSONIDO aux)//aux* está apuntando a cabesa desde el main (HAY QUE COMPROBAR, NO DIGO QUE NO SEA CIERTO)
{
	int tecla = 0; 
	if (aux != NULL)
		tecla = (aux)->tecla; // SIEMPRE SE QUEDA EN LA PRIMERO NOTA
	//(aux) = (aux)->pSig; // ESTO HAY QUE HACER EN EUNA FUNCION ANTES (UNA MAS ARRIBA EN LA ESCALERA DE FUNCIONES)

	return tecla;
}
int escanear_tecla()
{
	int tecla = _getch();
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
void lanzar_comando(char comando[])
{
	printf(comando);
	system(comando);
	Sleep(2000);
}
int escoger_nota_alta(int tecla)
{
		switch (tecla)
		{
		case LA:
			tecla = 48;
			return(tecla);
			break;
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
  char comando[] = "start wmplayer \"%cd%\\00.wav\"";
  switch (instrumento)
  {
  case Piano:
    if (tecla >= LA)
    {
      comando[21] = 49;
      comando[22] = escoger_nota_alta(tecla);
      lanzar_comando(comando);
    }
    else if (tecla != 0)
    {
      comando[22]= ("%d", tecla);
      lanzar_comando(comando);
    }
    break;
  case Ukelele:
    comando[21] = 50;
    if (tecla >= LA)
    {
      comando[21] = 51;
      comando[22] = escoger_nota_alta(tecla);
      lanzar_comando(comando);
    }
    else if (tecla != 0)
    {
      comando[22] = ("%d", tecla);
      lanzar_comando(comando);
    }
    break;
  case Ocarina:
    comando[21] = 52;
    if (tecla >= LA)
    {
      comando[21] = 53;
      comando[22] = escoger_nota_alta(tecla);
      lanzar_comando(comando);
    }
    else if (tecla != 0)
    {
      comando[22] = ("%d", tecla);
      lanzar_comando(comando);
    }
    break;
  case Sintetizador:
    comando[21] = 54;
    if (tecla >= LA)
    {
      comando[21] = 55;
      comando[22] = escoger_nota_alta(tecla);
      lanzar_comando(comando);
    }
    else if (tecla != 0)
    {
      comando[22] = ("%d", tecla);
      lanzar_comando(comando);
    }
    break;
  }
}

void reproducir(PSONIDO cabesa, int instrumento)
{
	//PSONIDO * aux = NULL;
	PSONIDO aux = NULL;

	cabesa = cargar_sonido(cabesa);

	//aux = &cabesa; // No se Copia
	aux = cabesa; // No se Copia

	while (leer_cadena(aux) != NULL)  // DEBUENVE DE NUEVO LA CADENA DESDE EL PRINCIPIO
	{
		int tecla = leer_cadena(aux);
		reproducir_sonido(tecla, instrumento);
		aux = aux->pSig;
	}
	/*while (leer_cadena(aux) != NULL)
	{
		int tecla = leer_cadena(aux);
		reproducir_sonido(tecla);
	}*/
	liberar(cabesa);

}
void tocar(int instrumento)
{
	int tecla = 0;
	do
	{
		tecla = escanear_tecla();
		int nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido(nuestra_tecla, instrumento);
	} while (tecla != 27);
}
PSONIDO grabar(PSONIDO cabesa, int instrumento)
{
	int nuestra_tecla = 1;
	int tecla = 0;
	while (nuestra_tecla != 0)
	{
		tecla = escanear_tecla();
		nuestra_tecla = comparar_tecla(tecla);
		reproducir_sonido(nuestra_tecla, instrumento);
		cabesa = guardar_notas(cabesa, nuestra_tecla);
		guardar_archivo(cabesa);

	}
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