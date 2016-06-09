#define _CRT_SECURE_NO_WARNINGS

#include "Funciones.h"
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include <string.h>

int main()
{
	char str[128];
	PSONIDO cabesa = NULL;

	int opcion = 0, instrumento = 0;

do
  {
    printf("In: 1-Piano 2-Ukelele 3-Ocarina 4-Electronico:\n");
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
    else
    {
      instrumento = 0;
      system("cls");
    }
  } while (instrumento == 0);
	printf("In: 1-Repoducir 2-Tocar 3-grabar:\n");
	printf("->");
	fgets(str, 128, stdin);
	sscanf(str, "%d", &opcion);

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

	return 0;
}