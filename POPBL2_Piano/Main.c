/** @file Main.c
*  @brief Es el piano
*
* Se le pide un numero al usuario para que escoja un
* instrumento. Una vez haya sido elegido, se le vuelve
* a pedir que escoja una accion, y de ahí, sale o
* ejecuta las funciones.
*
* @author Irene Delgado (irene.delgado@alumni.mondragon.edu)
* @author Lucas Sousa (lucas.sousa@alumni.mondragon.edu)
* @author Xabier Gandiaga (xabier.gandiaga@alumni.mondragon.edu)
* @author Eder Gomez de Segura (eder.gomezp@alumni.mondragon.edu)
* @author Nikolay Zabaleta (nikolay.zabaleta@alumni.mondragon.edu)
* @author Inigo Ayestaran (inigo.ayestaran@alumni.mondragon.edu)
*
* @date 2016-06-10
* @image html diagrama_main.jpg
*
* @todo Volver de las acciones grabar, reproducir y tocar al menu.
*/

#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include <string.h>

#include "Funciones.h"

//Funcion principal
int main()
{
	//Variables
	char str[128];
	PSONIDO cabesa;
	int opcion;
	int instrumento;

	//Inicializacion
	cabesa = NULL;
	opcion = 0;
	instrumento = 0;

	//Procedemos a escoger un instrumento
	do
	{
		printf("In: 1-Piano 2-Ukelele 3-Ocarina 4-Sintetizador:\n");
		printf("->");
		fgets(str, 128, stdin);
		sscanf(str, "%d", &instrumento);
		if (instrumento == 1)
		{
			instrumento = Piano;
		}
		else if (instrumento == 2)
		{
			instrumento = Ukelele;
		}
		else if (instrumento == 3)
		{
			instrumento = Ocarina;
		}
		else if (instrumento == 4)
		{
			instrumento = Sintetizador;
		}
		//En el caso de que no se escoja ninguno, se limpia la pantalla
		else
		{
			instrumento = 0;
			system("cls");
		}
		//Se repite hasta que se escoja un instrumento
	} while (instrumento == 0);

	printf("In: 1-Repoducir 2-Tocar 3-Grabar Cualquier otro valor-Salir:\n");
	printf("->");
	fgets(str, 128, stdin);
	sscanf(str, "%d", &opcion);

	//Se escoge lo que se va a  hacer
	switch (opcion)
	{
	case 1:
		reproducir(cabesa, instrumento);
		break;
	case 2:
		tocar(instrumento);
		break;
	case 3:
		grabar(cabesa, instrumento);
		break;
	}

	//En el caso de que no se escoja nada, se sale
	return 0;
}