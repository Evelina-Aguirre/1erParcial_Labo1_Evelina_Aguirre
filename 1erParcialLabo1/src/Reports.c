#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include "utn.h"



int principalMenu()
{
	int opcion;
	printf("\n\n--------------------------------");
	printf("\n----- PRINCIPAL MENU -----------\n");
	printf("\n  1-  Alta Cliente");
	printf("\n  2-  Modificar datos cliente");
	printf("\n  3-  Baja Cliente");
	printf("\n  4-  Prestamo");
	printf("\n  5-  Saldar préstamo");
	printf("\n  6-  Reanudar préstamo");
	printf("\n  7-  Imprimir clientes");
	printf("\n  8-  Imprimir préstamos");
	printf("\n  9-  Informar clientes");
	printf("\n  10- Informar préstamos");
	printf("\n  11- Exit");
	printf("\n--------------------------------");
	printf("\n--------------------------------\n");
	utn_getNumber(&opcion,"\n--> ", "\n * INVALID OPTION * \n",1, 5,100);
	return opcion;
}

