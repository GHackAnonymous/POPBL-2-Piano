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
#include <wiringPi.h>

int main()
{       
	//char str[128];
	PSONIDO cabesa = NULL;

	//int opcion = 0;

	//printf("In: 1-Repoducir 2-Tocar 3-grabar:\n");
	//printf("->");
	//fgets(str, 128, stdin);
	//sscanf(str, "%d", &opcion);

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
	pinMode(8, INPUT); //8 es el correspondiente del chip al pin 31
	pinMode(9, INPUT); //9 es el correspondiente del chip al pin 32
	pinMode(10, INPUT); //10 es el correspondiente del chip al pin 33
	pinMode(11, INPUT); //11 es el correspondiente del chip al pin 35




	// tenemos que traer la señal de la raspberry pi

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