#define _CRT_SECURE_NO_WARNINGS

#include "Funciones.h"
//#include<windows.h>
//#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
//#include<dos.h>
#include <string.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/

int main()
{       
	char str[128];
	PSONIDO cabesa = NULL;

	int opcion = 0;

	printf("In: 1-Repoducir 2-Tocar 3-grabar:\n");
	printf("->");
	fgets(str, 128, stdin);
	sscanf(str, "%d", &opcion);

	switch (opcion)
	{
	case 1:
		reproducir(cabesa);
		break;
	case 2:
		tocar();
		break;
	case 3:
		grabar(cabesa);
		break;
	}


	return 0;
}