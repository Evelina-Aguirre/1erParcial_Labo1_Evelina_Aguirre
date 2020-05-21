/*
 * ArrayClients.h
 *
 *  Created on: 17 may. 2020
 *      Author: Usuario
 */



#ifndef ARRAYCLIENTS_H_
#define ARRAYCLIENTS_H_


typedef struct{
int id;
char name[51];
char lastName[51];
int cuil;
int isEmpty;
}eClient;

#endif /* ARRAYCLIENTS_H_ */

#include "Loans.h"

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/

void harcodeClients(eClient clients[],int len, int howMany);
//--------------------------------------------------------------------------------------------------
/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param  Employees* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initClients(eClient clients[],int len);

//--------------------------------------------------------------------------------------------------

/** \brief add in a existing list of employees the values received as parameters
* in the first empty position
* \param employee* Pointer to array of employees
* \param len int Array length
* \param id int AutoIvrease employee id
* \param sector* Pointer to array of sectors
* \param lenSector Sector array length
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
*free space] - (0) if Ok.
* */

int addClient(eClient clients[],int len, int id,eLoan loans[],int lenLoan);

//--------------------------------------------------------------------------------------------------
/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \param id int Employee id to remove
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee]
*
*/

int removeClient(eClient clients[],int len,eLoan loans[],int lenLoan);

//--------------------------------------------------------------------------------------------------

/** \brief Menu for removing employee
*
* \param void
* \return ( ) if the user confirm action, (2) cancel an back to previus menu.
*/
int removeClientMenu();

//--------------------------------------------------------------------------------------------------

/** \brief Modify an existing employee name, Last Name, salary or sector.
* \param employee* Pointer to array of employees
* \param len int Array length
* \param id int AutoIvrease employee id
* \param sector* Pointer to array of sectors
* \param lenSector Sector array length
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
*free space] - (0) if Ok.
* */
int modifyClient(eClient clients[],int len,eLoan loans[],int lenLoan);
//--------------------------------------------------------------------------------------------------

/** \brief find free spaces to load new employees en returns the index position in array.
*
* \param list Employee* Pointer to array of employees
* \param len intArray length
* \param id int employee id
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or free space not found]
*
*/
int searchFreeSpace(eClient clients[],int len);
//--------------------------------------------------------------------------------------------------

/** \brief find an Employee by Id an returns the index position in array.
*
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \param id int employee id
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/

int searchClient(int id, eClient clients[],int len);

//--------------------------------------------------------------------------------------------------
/** \brief uploads data of a new employee to the payroll
*
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \param id int Employee id to remove
* \return int Return new employee data loaded
*
*/

eClient newClient(int id,char name[],char lastName[], char cuil);

//--------------------------------------------------------------------------------------------------

/** \brief print the content of employees array
*
* \param Employee* Pointer to Array Employees
* \param len int Array length
* \return void
*/
void printClients(eClient clients[], eLoan loans[],int len,int lenLoan);
//--------------------------------------------------------------------------------------------------

/** \brief Menu for confirm or goback an action
*
* \param void
* \return ( ) if the user confirm action, (2) cancel an back to previus menu.
*/
int confirmModificationMenu();
//--------------------------------------------------------------------------------------------------
/** \brief find out if there are Employees loaded
*
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return Return employee index position or (0) if [Invalid length or NULL
pointer received or employee not found] (1) if success
*
*/
int pointOutIfThereAreClientsLoaded(eClient clients[],int len);
//--------------------------------------------------------------------------------------------------
/** \brief Loads the customer information in the variables provided (name, surname, cuil)
*
* \param clients* Pointer arry clients
* \param idClient
* \param lenClient Client lenght
* \param name
* \param lastName
* \param cuil
* \param estado
* \return Return employee index position or (0) if [Invalid length or NULL
pointer received or employee not found] (1) if success
*
*/
int loadClientsDescription(eClient clients[], int idClient, int lenClient,char name[50],char lastName[50],int* cuil,char estado[20]);
void SubMenuPrintClientAndActiveLoans(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void printOneClientAndActiveLoans(eClient client,eLoan loans[],int lenClient,int lenLoan);
void printOneClientAndClosedLoans(eClient client,eLoan loans[],int lenClient,int lenLoan);




