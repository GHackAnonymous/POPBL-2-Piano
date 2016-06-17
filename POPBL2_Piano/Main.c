#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/
#include <wiringPi.h>

#include "Funciones.h"

int main(int argc, char *argv[])
{

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	PSONIDO cabesa = NULL;

	init_gpio();

	int control;
	int instrumento;

	control = 0;
	instrumento = 0;

	do {

		int opcion1;
		int opcion2;


		opcion1 = digitalRead(26);
		opcion2 = digitalRead(25);
		control = 0;


		if (opcion1 == 0 && opcion2 == 0)
		{
			digitalWrite(29, 1);
			digitalWrite(27, 1);
			instrumento = elegir_instrumento();
			reproducir(cabesa, instrumento);
		}
		else if (opcion1 == 0 && opcion2 == 1)
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
			digitalWrite(29, 0);
			digitalWrite(27, 0);
		}

		sleep(1);

		control = digitalRead(21);

	} while (control != 1);

	return 0;
}
