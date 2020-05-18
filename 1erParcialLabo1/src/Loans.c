/*
 * Sectors.c
 *
 *  Created on: 4 may. 2020
 *      Author: Usuario
 */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include "ArrayClients.h"
#include "Loans.h"
#include "utn.h"


int initLoans(eLoan loans[],int lenLoan)
{
	int i;
	int ret=-1;

	if(loans!= NULL && lenLoan>0)
	{
		for(i =0; i<=lenLoan;i++)
		{
			loans[i].isEmpty=1;//INITIALIZE ALL CLIENTES IN EMPTY (1)

		}
	ret=0;
	}
	return ret;

}

//------------------------------------------------------------------------------------------
int addLoan(eClient clients[],int lenClient, int loanId,eLoan loans[],int lenLoan)
{
	int success=-1;
	int index;
	int amount;
	int fees;
	int clientId;



	if(clients!=NULL && lenClient>0 && loans!= NULL && lenLoan>0)
		{
		printf("\n               -------- NUEVO PRESTAMO ---------");
		index=searchFreeSpaceLoans(loans,lenLoan);


		if(index==-1)//IF THERE ARE NO FREE SPACES
		{

			printf("\n\n-------------------------------\n\n");
			printf("     *  NO HAY ESPACIOS LIBRES  * ");
			printf("\n\n-------------------------------\n\n");

		}
		else// IF AN EMPTY PLACE HAS BEEN FOUND, REQUESTS DATA
		{
			printClients(clients, loans,lenClient,lenLoan);//SHOWS CLIENT LIST
			utn_getNumber(&clientId,"Ingrese el ID del Cliente : "," * El ID ingresado no es válido* ",100,150,10);//ASKS THE USER TO CHOOSE THE CLIENT ID

			amount=subMenuAdLoansAmount();//ASKS USER TO CHOOSE AN AMOUNT

			fees=subMenuAdLoansFees();//ASKS USER TO CHOOSE AMOUNT OF FEES

			loans[index]=newLoan(loanId,clientId,amount,fees);
			printf("\n\n----------------------------------------");
			printf("\n * Se agregó nuevo Prestamo al Cliente  * ");
			printf("\n-----------------------------------------\n");
			success=1;

		}
	}

	return success;

}

//--------------------------------------------------------------------------------------------------------------------------

int searchFreeSpaceLoans(eLoan loans[],int lenLoan)/////////
{
	int index=-1;

	for(int i=0;i<lenLoan;i++)
	{
		if(loans[i].isEmpty==1)//IF IT FINDS FREE SPACE IT RETURNS THE INDEX OF THE POCISION
		{
			index=i;
			break;
		}
	}
	return index;
}

//--------------------------------------------------------------------------------------------------------------------------

eLoan newLoan(int loanId, int clientId,int amount,int fees)/////////////////////////////
{
	eLoan newLoan;

	newLoan.id=loanId;
	newLoan.idClient=clientId;
	newLoan.amount=amount;
	newLoan.fees=fees;
	newLoan.isEmpty=0;

	return newLoan;
}

//--------------------------------------------------------------------------------------------------------------------------
int subMenuAdLoansAmount()//////////////////
{
	int option;
	int amount;
	utn_getNumber(&option,"Ingrese Importe : \n\n1- $500 \n2- $1000 \n3- $5000 \n4- $10000 \n\n--> "," * Error. la opción ingresada no es válida *",1,4,10);

	switch(option)
	{
	case 1:
		amount=500;
		break;
	case 2:
		amount=1000;
		break;
	case 3:
		amount=5000;
		break;
	case 5:
		amount=10000;
		break;
	}
	return amount;

}
//--------------------------------------------------------------------------------------------------------------------------
int subMenuAdLoansFees()//////////////////
{
	int option;
	int fees;
	utn_getNumber(&option,"Ingrese cantidad de cuotas : \n\n1- 6 cuotas \n2- 12 cuotas \n3- 18 cuotas \n4- 24 cuotas \n\n--> "," * Error. la opción ingresada no es válida *",1,4,10);

	switch(option)
	{
	case 1:
		fees=6;
		break;
	case 2:
		fees=12;
		break;
	case 3:
		fees=18;
		break;
	case 5:
		fees=24;
		break;
	}
	return fees;

}
//--------------------------------------------------------------------------------------------------------------------------

int closeLoan(eClient clients[],int lenClient,eLoan loans[],int lenLoan)
{
		int success=-1;
		int loanId;
		int index;
		int confirm;
		int optionRemMenu;

		if(clients!=NULL && lenClient>0 && loans!= NULL && lenLoan>0)
		 {

				do{
						printLoans(loans,clients,lenClient,lenLoan);
						optionRemMenu=closeLoanMenu();

						if(optionRemMenu==1)
						{
							printf("\n-------- SALDAR PRESTAMO --------");
							utn_getNumber(&loanId,"\n\nID del prestamo a saldar :","* ID NO ENCONTRADO* ",1, 50,2);
							index= searchActiveLoan(loanId,loans,lenLoan);//SERCHS LOAN

							index= searchClient(loanId,clients,lenLoan);//SERCH CLIENT


							if(index==-1)//IF ID NOT FOUNF
							{
								printf("\n\n* ID NO ENCONTRADO *\n");


							}
							else//IF ID FOUND,SHOWS EMPLOYEE AND  REQUEST CONFIRMATION TO REMOVE
							{

								printf("\n---------------------------------------------------------------------------------------");
								printf("\n-------------------------------- MODIFIECAR CLIENTE -----------------------------------\n\n");
								printf(" ID   NOMBRE    APELLIDO     CUIL      PRESTAMO    ESTADO PRESTAMO   ESTADO CLIENTE \n");
								printf("----------------------------------------------------------------------------------------\n");

								printOneClientAndActiveLoans(clients[index],loans,lenClient,lenLoan);


								printf("---------------------------------------------------------------------------------------\n");
								printf("---------------------------------------------------------------------------------------\n");

								confirm=confirmCloseMenu();

								if(confirm==1)
								{
									loans[index].isEmpty=1;
									printf("\n\n** PRESTAMO SALDADO **\n");
									success=1;

								}
								else
								{
								printf("\n\n ** NO SE REALIZARON CAMBIOS ** \n");
								}
							}
						}


				}while(optionRemMenu!=2);

		 }
		return success;

}

//----------------------------------------------------------------------------------------------------------------------------------
int closeLoanMenu()
{
	int option;

	printf("------ SALDAR PRESTAMO ------\n");
	printf("-----------------------------\n\n");
	printf("1- Ingresar id  ");
	printf("\n2- Salir \n\n");
	printf("-----------------------------\n");
	utn_getNumber(&option,"\n-->   ", "\n * LA OPCIÓN NO ES VÁLIDA * \n",1, 2,10);
	return option;
}
//-------------------------------------------------------------------------------------------------------------------------------------


int confirmCloseMenu()//////////////
{
	int confirm;
	printf("\n 1- Confirmar");
	printf("\n 2- Salir\n\n");

	utn_getNumber(&confirm,"--> ", "\n* NO ES UNA OPCIÓN VÁLIDA * \n 1- Confirmar\n 2- Salir \n\n",1, 2,10);

	return confirm;
}

//------------------------------------------------------------------------------------------------------------------------------------
int resumeLoan(eClient clients[],int lenClient,eLoan loans[],int lenLoan)
{
		int success=0;
		int loanId;
		int index;
		int confirm;
		int optionRemMenu;

		if(clients!=NULL && lenClient>0 && loans!= NULL && lenLoan>0)
		 {
			if(pointOutIfThereAreClientsLoaded(clients,lenClient)==0)//CHECKS IF THE USER PREVIOUSLY LOADED CLIENTS
			{
				printf("\n * No hay clientes cargados aún. Debe haber almenos un cliente para poder operar.  *\n\n");
			}
			else if(pointOutIfThereAreLoansLoaded(loans,lenLoan)==0)//CHECKS IF THE USER PREVIOUSLY LOADED LOANS
			{
				printf("\n * No hay prestamos cargados aún. Debe haber almenos un Prestamo cargado para poder ingresar a esta opción.  *\n\n");
			}
			else
			{

				do{
					printLoans(loans,clients,lenClient,lenLoan);
					optionRemMenu=closeLoanMenu();

					if(optionRemMenu==1)
					{
					printf("\n-------- SALDAR PRESTAMO --------");
					utn_getNumber(&loanId,"\n\nID del prestamo a reanudar :","* ID NO ENCONTRADO* ",0, 1100,2);
					index= searchCloseLoan(loanId,loans,lenLoan);//SERCHS LOAN

						index= searchClient(loanId,clients,lenLoan);//SERCH CLIENT

						if(index==-1)//IF ID NOT FOUNF
						{
							printf("\n\n* ID NO ENCONTRADO *\n");


						}
						else//IF ID FOUND,SHOWS EMPLOYEE AND  REQUEST CONFIRMATION TO REMOVE
						{

							printf("\n---------------------------------------------------------------------------------------");
							printf("\n-------------------------------- MODIFIECAR CLIENTE -----------------------------------\n\n");
						    printf(" ID   NOMBRE    APELLIDO     CUIL      PRESTAMO    ESTADO PRESTAMO   ESTADO CLIENTE \n");
							printf("----------------------------------------------------------------------------------------\n");

							printOneClientAndActiveLoans(clients[index],loans,lenClient,lenLoan);


							printf("---------------------------------------------------------------------------------------\n");
							printf("---------------------------------------------------------------------------------------\n");

							confirm=confirmCloseMenu();

							if(confirm==1)
							{
								loans[index].isEmpty=0;
								printf("\n\n** PRESTAMO REANUDADO **\n");
							success=1;
							}
							else
							{
								printf("\n\n ** NO SE REALIZARON CAMBIOS ** \n");
							}
						}
					}
					else
					{
						break;
					}

				}while(optionRemMenu!=2);
			}
		 }
		return success;

}

//----------------------------------------------------------------------------------------------------------------------------------



void printLoans(eLoan loans[], eClient clients[],int lenClient,int lenLoan)//////////////////////////////////////////
{
	int i;
	if(loans!=NULL && lenClient>0 && clients!=NULL && lenLoan>0)
	{
		printf("\n----------------------------------------------------------------------------------------------------");
		printf("\n-------------------------------------- PRESTAMOS  -----------------------------------------------\n\n");
		printf(" ID   IMPORTE    CUAOTAS    ID CLIENTE    NOMBRE APELLIDO    CUIL    ESTADO CLIENTE  ESTADO PRESTAMO \n");
		printf("----------------------------------------------------------------------------------------------------\n");

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].isEmpty==0)
			{
			printLoan(loans[i],clients,lenClient,lenLoan);

			}

		}


		printf("----------------------------------------------------------------------------------------------------\n");
		printf("----------------------------------------------------------------------------------------------------\n");
		printf("\n\n");
	}
}

//--------------------------------------------------------------------------------------------------------------------------

void printLoan(eLoan loan,eClient clients[],int lenClient,int lenLoan)//////////////////////
{

	char statusClient[10];
	char statusLoan[10];
	char name[50];
	char lastName[50];
	int cuil;
	int clientId;

	clientId=loan.idClient;


					if(loan.isEmpty ==0)
						{
							strcpy(statusLoan,"ACTIVO");
						}
						else
						{
							strcpy(statusLoan,"SALDADO");
						}


		if(loadClientsDescription(clients,clientId,lenClient,name,lastName,&cuil,statusClient))
		{
			printf(" %d    %d          %d            %d         %s   %s   %d      %s       %s\n",
					loan.id,
					loan.amount,
					loan.fees,
					loan.idClient,
					name,
					lastName,
					cuil,
					statusClient,
					statusLoan);
		}


}


//--------------------------------------------------------------------------------------------------------------------------

int loadLoansDescription(eLoan loans[], int idClient, int lenLoan, int* amount, int* fees, int* loanId, char  status[])
{
	int success=0;
	int i;


	if(loans!=NULL && idClient>0&& lenLoan>0)
	{

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].idClient==idClient)
			{
				*amount=loans[i].amount;
				*fees=loans[i].fees;
				*loanId=loans[i].id;

				if(loans[i].isEmpty ==0)
				{
					strcpy(status,"ACTIVO");
				}
				else
				{
					strcpy(status,"SALDADO");
				}

			}
		}
	}

	return success;
}

//---------------------------------------------------------------------------------------------------------------------
int serchActiveLoansbyBlientId(eLoan loans[], int idClient, int lenLoan)
{

	int accLoansById;
	int i;

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].idClient==idClient && loans[i].isEmpty==0)
			{
				accLoansById++;

			}
			else
			{
				accLoansById=0;
			}
		}


	return accLoansById;
}

//-------------------------------------------------------------------------------------------------------
void printLoansByClientId(eClient client,eLoan loans[],int lenClient,int lenLoan)//PRINT DETAIL OF ONE CLIENT ACTIVE LOANS/////////////////////////
{


		int loanId;
		int amount;
		int fees;
		char loanStatus[10];

				if(loadLoansDescription(loans,client.id, lenLoan, &amount, &fees, &loanId, loanStatus))
				{
					printf("\n\n-------------------------------------------------------------------\n");
					printf("                PRESTAMOS A NOMBRE DE : %.8s    \n\n",client.lastName);
					printf("\n\n-------------------------------------------------------------------\n");
					printf(" ID PRESTAMO   IMPORTE    CUOTAS   STATUS ");
					printf(" %d            %d         %d       %s\n",loanId,amount,fees,loanStatus);
					printf("\n\n-------------------------------------------------------------------\n");
					printf("\n\n-------------------------------------------------------------------\n");
				}

}

//--------------------------------------------------------------------------------------------------------------------------------

int pointOutIfThereAreLoansLoaded(eLoan loans[],int lenLoan)////////////
{
	int success=0;
	if(loans!=NULL && lenLoan>0)
	{
		for(int i=0;i<lenLoan;i++)
		{
			if(loans[i].isEmpty==0)
			{

				success=1;
				break;
			}
			else
			{
				success=0;
			}
		}
	}
		return success;
}

//-----------------------------------------------------------------------------------------------------------------------------------

int searchActiveLoan(int loanId, eLoan loans[],int lenLoan)//////////
{
	int index=-1;

	for(int i=0;i<lenLoan;i++)
	{
		if(loans[i].isEmpty==0 && loans[i].id==loanId)
		{
			index=i;
			break;
		}
	}
	return index;
}

//-----------------------------------------------------------------------------------------------------------------------------------
int searchCloseLoan(int loanId, eLoan loans[],int lenLoan)//////////
{
	int index=-1;

	for(int i=0;i<lenLoan;i++)
	{
		if(loans[i].isEmpty==1 && loans[i].id==loanId)
		{
			index=i;
			break;
		}
	}
	return index;
}
//------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------
