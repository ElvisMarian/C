#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

	static int write_stdout(const char *token, int length)
	{
		int rc;
		int bytes_written = 0;

		do {
			rc = write(1, token + bytes_written, length - bytes_written);
			if (rc < 0)
				return rc;

			bytes_written += rc;
		} while (bytes_written < length);

		return bytes_written;
	}

char *convert(unsigned int number, int base) 
{ 
	static char base_hexa[]= "0123456789abcdef"; //simbolurile din baza 16
	static char buffer[10]; //un buffer

	char *ptr = &buffer[9]; //pointer-ul
	*ptr = '\0'; 
	
	while (number) { //cat timp numarul e valid,pun in pointer valoarea de la indexul number mod baze
		*(--ptr) = base_hexa[number % base];  //apoi scad pointerul(pun simbolurile de la dreapta spre stanga)
		number /= base; //impart numarul
	}
	return ptr; 
}


int iocla_printf(const char *format, ...) {

	int numberOfCharacters = 0;
	char *s;
	char c;
	int d;

	va_list arg; 
	va_start(arg, format); 

	for (int j = 0; j < strlen(format); j++) { //parcurg input-ul caracter cu caracter
        if (format[j] == '%') { //daca am % ma uit in continuare(acel ++j)
        	if (format[++j] == '%' ){ //daca urmatorul e tot % afisez
				write_stdout(&(format[j]), 1);  //si trec la urmatoarea iteratie
				numberOfCharacters++;
				continue;
        	} else {    //daca nu verific cazurile de baza
 				switch (format[j]) { 
					case 'c': 					//pentru char
							c = va_arg(arg, int); 
							write_stdout(&c, 1); 
							numberOfCharacters++;
							break;

					case 'd':					//pentru signed int
							d = va_arg(arg, int);
							if (d < 0) { 
								d = -d;
								numberOfCharacters++;
								write_stdout("-", 1); 
							}
							write_stdout(convert(d, 10), strlen(convert(d, 10)));
							numberOfCharacters += strlen(convert(d, 10));
							break; 

					case 'u': 					//pentru unsigned int
							d = va_arg(arg, int); 
							write_stdout(convert(d, 10), strlen(convert(d, 10)));
							numberOfCharacters += strlen(convert(d, 10));
							break;
						
					case 's': 					//pentru string
							s = va_arg(arg, char*); 
							write_stdout(s, strlen(s));
							numberOfCharacters += strlen(s);
							break; 
									
					case 'x': 					//pentru hexa
							d = va_arg(arg, unsigned int); 
							write_stdout(convert(d, 16), strlen(convert(d, 16)));
							numberOfCharacters += strlen(convert(d, 16));
							break;
        		}
        	}
		} else { //daca nu am procent atunci afisez
			write_stdout(&(format[j]), 1);
			numberOfCharacters++;
		}
	}
	return numberOfCharacters; //numarul de caractere pe care le-am afisat
}