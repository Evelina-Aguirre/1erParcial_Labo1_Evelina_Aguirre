#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"

#include "ArrayClients.h"
#include "Loans.h"
//--------------------------------------------------------------------------------------------------------------------

int utn_getNumber(int *pResultado,char mensaje[], char mensajeError[],int minimo, int maximo,int reintentos)
{
	int retorno;
	int numero;

	while(reintentos>0)
	{
		reintentos--;
		printf("%s",mensaje);
		fflush(stdin);
		if(getInt(&numero)==0)
		{
			if(numero<=maximo && numero>=minimo)
			{break;}
		}


		printf("%s",mensajeError);

	}
		if(reintentos==0)
		{
			retorno=-1;
		}
		else
		{
			retorno=0;
			*pResultado=numero;
		}
		return retorno;

}
//--------------------------------------------------------------------------------------------------------------------------


int getInt(int *pResultado)
{
	int retorno=-1;
	char buffer[64];

	if(pResultado != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer))
		{
			*pResultado=atoi(buffer);
				retorno=0;
		}
	}


	return retorno;
}
//--------------------------------------------------------------------------------------------------------------------------

int esNumerica(char cadena[])
 {
	int i=0;
	int retorno=1;

		while(cadena[i]!='\0')
		{
			if((cadena[i]<'0' || cadena[i] >'9')&&( cadena[i]!='+' && cadena[i]!='-'))
			{
				retorno =0;
				break;
			}
			i++;
		}

	return retorno;
 }

//--------------------------------------------------------------------------------------------------------------------------

int myGets(char* cadena,int longitud)
{
	int retorno=-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1]=='\n')
		{
			cadena[strlen(cadena)-1]='\0';
		}
		retorno=0;
	}
	return retorno;
}

//--------------------------------------------------------------------------------------------------------------------------



int utn_getNumeroConDecimales(float* numero, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{

		int ret=0;
		float ingreso;
		if (numero!= NULL && mensaje != NULL && mensajeError != NULL && maximo >= minimo && reintentos >=0 )
		{
			do
			{
				printf(mensaje);
				if(getFloat(&ingreso))
				{
					if(ingreso<minimo || ingreso>maximo)
					{
						fflush(stdin);
						printf(mensajeError, reintentos);
						reintentos--;
					}
				}
				else
				{
					printf(mensajeError,reintentos);
					reintentos--;
				}


			}while (reintentos>=0 && (ingreso<minimo || ingreso>maximo));

			if (reintentos>=0)
			{
				ret=1;
				*numero=ingreso;
			}

		}
		else
		{
			printf(mensajeError, reintentos);
		}

		return ret;
}

//--------------------------------------------------------------------------------------------------------------------------

int getFloat(float* pResultado)
{
	int ret=0;
	char ingreso[64];
	fgets(ingreso,sizeof(ingreso),stdin);
	ingreso[strlen(ingreso)-1]='\0';
	if(esNumeroDecimal(ingreso))
	{
		*pResultado = atof(ingreso);


		ret=1;
	}
	return ret;
}

//--------------------------------------------------------------------------------------------------------------------------
int esNumeroDecimal(char* cadena)
{
	int ret=0;
	int i=0;
	int controlP=0;
	if(cadena!=NULL && cadena[0]!='.' && cadena[strlen(cadena)-1]!='.')
	{
		while(cadena[i]!='\0')
		{

			if((cadena[i]<'0' || cadena[i]>'9') && ((cadena[i]!='.') && (cadena[i]!='-')))
			{
				break;
			}
			else if (cadena[i]=='-' && i!=0)
			{break;}

			else if(cadena[i]=='.')
			{
				controlP++;
			}

			i++;
		}
		if(cadena[i]=='\0' && cadena[0]!='\0' && controlP<=1)
		{ret=1;}
	}

return ret;
}

//--------------------------------------------------------------------------------------------------------------------------

int utn_getString(  char *pResult, char *messaje, char *pMessajeError, int min,int max, int attempts)
{
    int ret=-1;
    char bufferStr[4096];
    while(attempts>0)
    {
        printf(messaje);
        fgets(bufferStr,sizeof(bufferStr),stdin);
        bufferStr[strlen(bufferStr)-1] = '\0';
        if( pResult != NULL && strlen(bufferStr) >= min && strlen(bufferStr) <= max)
        {
            strncpy(pResult,bufferStr,max);
            ret=0;
            break;
        }
        else
        {
            printf(pMessajeError);
        }
        attempts--;
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------

int utn_getName(char *pResult,char pMessage[],char pMessageError[],int min,int max,int len,int attemps)
{
    int retorno = -1;
    char bufferStr[4096];
    while(attemps>0)
    {
        if(pResult != NULL)
        {
            if(!(utn_getString(bufferStr,pMessage,pMessageError,min,max,1)) && (utn_isValidName(bufferStr)&&strlen(bufferStr)<=len))
            {
                strncpy(pResult,bufferStr,len);
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}

int utn_isValidName (char* string)
{
    int ret=1;
    int i;
    for(i=0;string[i] != '\0';i++)
    {
        if(!isalpha(string[i]))
        {
            ret=0;
            break;
        }
    }
    return ret;
}
//-------------------------------------------------------------------------------------------------------------------------
/*int esCUIL(char string[])
{
   int i=0;
   int contGuion=0;

   while(string[i] != '\0')
   {
       if((string[i] < '0' || string[i] > '9') &&( string[i] != '-'))
           return 0;
       if(string[i] == '-')
            contGuion++;
       i++;
   }
   if(contGuion==2)
        return 1;

    return 0;
}

int getCUIL(char messege[], char input[]){

	char aux[20];
	getString(messege, aux);
	if(esCUIL(aux)){
		strcpy(input, aux);
		return 1;
	}
	return 0;
}*/



/*int getString(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}
*/
