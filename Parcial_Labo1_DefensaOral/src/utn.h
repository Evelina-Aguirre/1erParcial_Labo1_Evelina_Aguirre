#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/**
* \ brief Request a number to the user, then to verify it returns the result
* \ param pResult Pointer to the memory space where the result of the function will be left
* \ param message Is the message to be displayed
* \ param error message is the error message to be displayed
* \ minimum param It is the maximum number to be accepted
* \ param maximo It is the minimum minimum to be accepted
* \ return Returns 0 if the number was obtained and -1 if not
* */

int utn_getNumber(int *pResultado,char mensaje[], char mensajeError[],int minimo, int maximo,int reintentos);
int getInt(int *pResultado);

/**
* \brief Verifica si la cadena ingresada es numerica
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
*/

int esNumerica(char string[]);

//-----------------------------------------------------------------------------------------------------------------
/*
* \ brief Read from stdin until it finds a '\ n' or until you have copied in a string
* a maximum of 'length - 1' characters.
* \ param pResult Pointer to the memory space where the obtained string will be copied
* \ param length Defines the string size
* \ return Returns 0 (SUCCESS) if a string is obtained and -1 (ERROR) if not
*
* */
int myGets(char* string,int len);

//-----------------------------------------------------------------------------------------------------------------
/* **
 * \ brief Function for entering numbers with decimals, positive or negative
 * requests a number from the user and returns this by pointer in case it has been verified
 * that it is not empty, does not have more than one '.' and the negative sign is only in the 1st position
 * Returns 1 on successful case
 * */
int utn_getNumeroConDecimales(float* numero, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

//--------------------------------------------------------------------------------------------------------------------
int esNumeroDecimal(char* string);
int getFloat(float* pResultado);
int utn_getString(  char *pResult, char *messaje, char *pMessajeError, int min,int max, int attempts);
int utn_isValidName (char* string);
int utn_getName( char *pResult,char pMessage[],char pMessageError[],int min,int max,int len,int attemps);



//int getCuil(char* pResultado, int longitud);
//int utn_getCuil(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
