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
	PSONIDO cabesa = NULL;

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


	// tenemos que traer la senal de la raspberry pi

	int control = 0, instrumento = 0;
	
	do {
		//sleep(8);
		
		int opcion1 = digitalRead(26);
		int opcion2 = digitalRead(25);

		if (opcion1 == 0 && opcion2 == 0)
		{
			digitalWrite(29, 0);
			digitalWrite(27, 0);
			instrumento = elegir_instrumento();
			reproducir(cabesa, instrumento);
		}
		else if(opcion1 == 0 && opcion2 == 1)
		{
			digitalWrite(29, 0);
            digitalWrite(27, 1);
			instrumento = elegir_instrumento();
			tocar(instrumento);
		}
		else if (opcion1 == 1 && opcion2 == 0)
		{
			digitalWrite(29, 1);
            digitalWrite(27, 0);
			instrumento = elegir_instrumento();
			grabar(cabesa, instrumento);
		}
		else if (opcion1 == 1 && opcion2 == 1)
		{
			digitalWrite(29, 1);
            digitalWrite(27, 1);
			// no hace nada pero tenemos que enviar la senal
			//a la cool runner
		}
		
		control = digitalRead(0);
		printf("%d",control);

	} while (control != 1);

	return 0;
}
