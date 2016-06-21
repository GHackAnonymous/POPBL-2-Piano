/** @file Funciones.c
* @brief Funciones del piano
*
* En esta libreria estan todas las funciones del funcionamiento
* de programa.
*
* @author Irene Delgado (irene.delgado@alumni.mondragon.edu)
* @author Lucas Sousa (lucas.sousa@alumni.mondragon.edu)
* @author Xabier Gandiaga (xabier.gandiaga@alumni.mondragon.edu)
* @author Eder Gomez de Segura (eder.gomezp@alumni.mondragon.edu)
* @author Nikolay Zabaleta (nikolay.zabaleta@alumni.mondragon.edu)
* @author Inigo Ayestaran (inigo.ayestaran@alumni.mondragon.edu)
*
* @date 2016-06-10
*
* @todo Inplementar una funcion para poder tcar dos teclas a mismo tiempo.
* @todo Inplementar una funcion para guardar los silencios a la hora de grabar.
* @todo Inplementar una funcion para para guardar mas de una grabacion.
*
* @bug A las tres pricipales funciones (Grabar, Tocar, Reproducir) les pasamos
*		el parametro cabesa el cual es NULL y esta de sobra pero no altera del
*		funcionamiento del programa.
*/
#define _CRT_SECURE_NO_WARNINGS


#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>

#include "Funciones.h"

/** @brief Se crea un nuevo PSONIDO que ira ultimo o
*         primero, en base a que haya uno o no lo haya.
*
* @param Cabesa, es la primera direccion de las estructuras concatenadas.
* @param tecla, la nota a guardar.
*
* @return cabesa, es la primera direccion de las estructuras concatenadas.
*/
PSONIDO crear_cadena(PSONIDO cabesa, int tecla)
{
	//Valores locales
	PSONIDO nuevo;
	PSONIDO aux;

	aux = cabesa;

	//nuevo recibe la direccion de la memoria dinamica. 
	nuevo = malloc(sizeof(SONIDO));

	//La variable tecla de la estructura nuevo recibe el valor de la variable local tecla.
	nuevo->tecla = tecla;

	/*	La algoritmia
	*
	*	Si cabesa es igual a NULL al ser el primer nodo se le asigna el primer valor,
	*/
	if (cabesa == NULL)
	{
		cabesa = nuevo;
		cabesa->pSig = NULL;
	}
	else
	{
		/*
		*	La funcion saltar_cadena nos lleva a la ultima estructura y manda su direccion
		*	a aux.
		*
		*	La estructura nuevo se coloca en la ultima posicion de la cadena.
		*/
		aux = saltar_cadena(aux);
		nuevo->pSig = NULL;
		aux->pSig = nuevo;
	}
	return cabesa;
}

/**
*	@brief Nos lleva al final de la cadena.
*
*	@param aux, contiene la direccion de cabesa.
*
*	@return aux, la ultima direccion de la cadena.
*/
PSONIDO saltar_cadena(PSONIDO aux)
{
	while (aux->pSig != NULL)
	{
		aux = aux->pSig;
	}
	return aux;
}

/**
*	@brief Se abre o guarda un archivo en base a funcion.
*
*	@param funcion, que designa si se leera o escribira en el archivo.
*
*	@return fp, el fichero que abrimos.
*/
FILE* abrir_archivo(int funcion)
{
	//Valores locales
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

/**
*	@brief Cargarmos el valor de tecla del fichero.
*
*	@param fp, el fichero que contiene la grabacion.
*	@param tecla, la nota del archivo.
*
*	@return tecla, nota de la grabacion.
*/
int cargar_de_archivo(FILE* fp, int tecla)
{
	fread(&tecla, sizeof(SONIDO), 1, fp);
	return tecla;
}

/**
*	@brief Se carga la cadena de estructuras desde el fichero.
*
*	@param cabesa, paramentro que no influye en la funcion.
*
*	@return cabesa, la primera direccion de la cadena.
*/
PSONIDO cargar_sonido(PSONIDO cabesa)
{
	//Variables locales
	FILE* fp;
	int tecla;
	int funcion;

	funcion = 1;
	cabesa = NULL;
	tecla = 0;
	fp = abrir_archivo(funcion);

	//La funcion cargar_de_archivo carga la nota y la gurada en tecla.
	while ((tecla = cargar_de_archivo(fp, tecla)) != NULL)
	{
		//Se crea la cadena
		cabesa = crear_cadena(cabesa, tecla);

		//Se otorga a tecla el valor de 0 para que no haya ningun problema
		tecla = 0;
	}
	return cabesa;
}

/**
*	@brief Se guarda la cadena de estructuras creadas en un fichero.
*
*	@param cabesa, la primira direccion de la cadena.
*
*	@return no retorna nada.
*/
void guardar_archivo(PSONIDO cabesa)
{
	//Variables locales
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

/**
*	@brief Guarda la tecla de la estructura en el fichero
*
*	@param cabesa, la primera direcion de la cadena.
*	@param fp, el fichero donde se guarda.
*
*	@return No retorna nada.
*/
void escribir_nota(FILE* fp, PSONIDO cabesa)
{
	fwrite(&cabesa->tecla, sizeof(SONIDO), 1, fp);
}

/**
*	@brief Guardar las notas en la cadena de estructuras.
*
*	@param cabesa, la primera dicecion de la cadena.
*	@param  nota, La nota perteneciente a la tecla que se nota.
*
*	@return cabesa, la primera direccion de la cadena.
*/
PSONIDO guardar_notas(PSONIDO cabesa, int nota)
{
	cabesa = crear_cadena(cabesa, nota);

	return cabesa;
}

/**
*	@brief Obtiene la tecla de la estructura.
*
*	@param aux, es una direccion de la cadena.
*
*	@return tecla, el valor obtenido del parametro tecla de la estructura.
*/
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

/**
*	@brief Escanea la tecla que ha sido pulsada
*
*	@return tecla, el valor de la tecla pulsada
*/
int escanear_tecla()
{
	int tecla = _getch();

	return tecla;
}

/**
*	@brief Esta funcion compara la tecla escaneada y la devuelve como la nota correspondiente
*
*  @param tecla, la tecla que ha sido escaneada
*
*  @return Las distintas notas (DO, DOS, RE...)
*/
int comparar_tecla(int tecla)
{
	//Las teclas correspondes a las del piano
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

/**
*	@brief Se lanza el comando del comando que se le pasa.
*
*	@param comando, el char que contiene el comando y direccion
*         de los archivos de sonido.
*
*	@return Void
*/
void lanzar_comando(char comando[])
{
	printf(comando);
	system(comando);
	Sleep(2000);
}

/**
*	@brief Se usa para escoger las notas de LA a SI.
*
*	@param tecla, que contiene la nota.
*
*	@return tecla, con el valor escogido para la nota.
*/
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

/**
*	@brief se reproduce el fichero de audio de la nota correspondiente
*
*	@param tecla, el cual tiene la nota
*	@param instrumento, sirve para escoger los ficheros de audio correspondientes.
*
*	@bug en vez de utilizar el sprintf utilizamos un char que lo altera el programa
*		 pero no es una forma correcta de ponerlo.
*
*	@return void
*/
void reproducir_sonido(int tecla, int instrumento)
{
	//Variable local
	char comando[] = "start wmplayer \"%cd%\\00.wav\"";

	//Se escoge el instrumento
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
			comando[22] = ("%d", tecla);
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

/**
*	@brief La funcion coge la anterior grabacion y la reproduce.
*
*	@param cabesa, en este caso es NULL.
*	@param instrumento, sirve para escoger los ficheros de audio correspondientes.
*
*	@return Void
*/
void reproducir(PSONIDO cabesa, int instrumento)
{
	//Variables locales
	PSONIDO aux;

	aux = NULL;

	//Carga la grabacion
	cabesa = cargar_sonido(cabesa);
	aux = cabesa;

	//Mientras que tecla no sea NULL 
	while (leer_cadena(aux) != NULL)
	{
		//Tecla obtiene el valor de aux
		int tecla = leer_cadena(aux);
		//Se reproduce
		reproducir_sonido(tecla, instrumento);
		//Salta a la sigiente estructura.
		aux = aux->pSig;
		//El bucle se completa cuando llega al final de la estructura.
	}

}

/**
*	@brief Reproduce sonido en base a la tecla tocada y el instrumento escogido.
*
*	@param instrumento, sirve para escoger los ficheros de audio correspondientes.
*
*	@return Void
*/
void tocar(int instrumento)
{
	//Variables locales
	int tecla;

	//Se inicializan los valores
	tecla = 0;

	do
	{
		//Se escanea la tecla
		tecla = escanear_tecla();
		//Se devuelve tecla como nota
		int nuestra_tecla = comparar_tecla(tecla);
		//Reproduce un sonido en base a nuestra_tecla e instrumento
		reproducir_sonido(nuestra_tecla, instrumento);
		//Hasta que la tecla no sea esc
	} while (tecla != 27);

}

/**
*	@brief Genera un fichero en base a las notas que
*         sean recibidas a la hora de presionar teclas
*
*	@param cabesa, en este caso es NULL
*	@param instrumento, sirve para escoger los ficheros de audio correspondientes.
*
*	@return Void
*/
void grabar(PSONIDO cabesa, int instrumento)
{
	//Variables locales
	int nuestra_tecla;
	int tecla;

	nuestra_tecla = 1;
	tecla = 0;



	while (nuestra_tecla != 0)
	{
		//Se escanea la tecla
		tecla = escanear_tecla();
		//Devuelve su valor como nota
		nuestra_tecla = comparar_tecla(tecla);
		//Reproduce el sonido en base a la nota y el instrumento
		reproducir_sonido(nuestra_tecla, instrumento);
		//Guarda las notas en PSONIDO cabesa
		cabesa = guardar_notas(cabesa, nuestra_tecla);
	}

	//Guarda cabesa en un fichero
	guardar_archivo(cabesa);
}