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


void harcodeLoans(eLoan loans[],int lenLoan, int howMany)
{


	eLoan auxList[]={
			{1,100,500,6,0},
			{1,100,1000,12,0},
			{1,100,5000,24,0},
			{1,102,10000,6,0},
			{1,102,1000,6,0},
			{1,103,5000,12,0},
			{1,103,10000,24,0},
			{1,103,500,6,0},
			{1,104,1000,12,0},
			{1,105,5000,12,1}

	};

	if(howMany<lenLoan && howMany<11)
	{
		for(int i=0;i<=howMany;i++)
		{
			loans[i]=auxList[i];

		}
	}
}

//-----------------------------------------------------------------------------------------------------

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
				if(pointOutIfThereAreClientsLoaded(clients,lenClient)==0)//CHECK IF THE USER PREVIOUSLY LOADED CLIENTS
					{
						printf("\n *  No hay clientes cargados aún. debe haber almenos un cliente para poder operar *\n\n");
					}
					else
					{

						printf("\n         **     NUEVO PRESTAMO   **");
						index=searchFreeSpaceLoans(loans,lenLoan);


						if(index==-1)//IF THERE ARE NO FREE SPACES
						{

							printf("\n\n-----------------------------------\n");
							printf("     *  NO HAY ESPACIOS LIBRES   * ");
							printf("\n---------------------------------\n\n");

						}
						else// IF AN EMPTY PLACE HAS BEEN FOUND, REQUESTS DATA
						{
							printClients(clients, loans,lenClient,lenLoan);//SHOWS CLIENT LIST
							utn_getNumber(&clientId,"Ingrese el ID del Cliente : "," * El ID ingresado no es válido* ",100,150,10);//ASKS THE USER TO CHOOSE THE CLIENT ID

							amount=subMenuAdLoansAmount();//ASKS USER TO CHOOSE AN AMOUNT

							fees=subMenuAdLoansFees();//ASKS USER TO CHOOSE AMOUNT OF FEES

							loans[index]=newLoan(loanId,clientId,amount,fees);
							printf("\n\n-----------------------------------------");
							printf("\n * Se agregó nuevo Prestamo al Cliente  * ");
							printf("\n-----------------------------------------\n");
							success=1;
						}
		}
	}//EN FIRS IF

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
	case 4:
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
			if(pointOutIfThereAreClientsLoaded(clients,lenClient)==0 || pointOutIfThereAreLoansLoaded(loans,lenLoan)==0)//CHECK IF THE USER PREVIOUSLY LOADED CLIENTS
				{
					printf("\n *  Debe haber almenos un cliente para poder operar *\n\n");
				}
				else
				{
					do{
						printLoans(loans,clients,lenClient,lenLoan);
						optionRemMenu=closeLoanMenu();

						switch(optionRemMenu)
						{
						case 1:
							printf("\n-------- SALDAR PRESTAMO --------");

							utn_getNumber(&loanId,"\n\nID del prestamo a saldar :","* ID NO ENCONTRADO* ",1, 50,2);
							index= searchActiveLoan(loanId,loans,lenLoan);//SERCHS LOAN

							if(index==-1)//IF ID NOT FOUNF
							{
								printf("\n\n* ID NO ENCONTRADO *\n");

							}
							else//IF ID FOUND,SHOWS EMPLOYEE AND  REQUEST CONFIRMATION TO REMOVE
							{

								printf("\n----------------------------------------------------------------------------------------------------");
								printf("\n-------------------------------------- PRESTAMOS  --------------------------------------------------\n\n");
								printf(" ID   IMPORTE    CUAOTAS    ID CLIENTE    NOMBRE APELLIDO    CUIL    ESTADO CLIENTE  ESTADO PRESTAMO \n");
								printf("----------------------------------------------------------------------------------------------------\n");

								printLoan(loans[index],clients,lenClient,lenLoan);

								printf("----------------------------------------------------------------------------------------------------\n");
								printf("----------------------------------------------------------------------------------------------------\n");

								confirm=confirmCloseMenu();

								if(confirm==1)
								{
									loans[index].isEmpty=2;//is empty 0 cargado, 1 vacio, 2 saldado
									printf("\n\n** PRESTAMO SALDADO **\n");

									success=1;

								}
								else
								{
								printf("\n\n ** NO SE REALIZARON CAMBIOS ** \n");

								}
							}
							break;

						}


				}while(optionRemMenu!=2);
			}

		 }
		return success;


}

//----------------------------------------------------------------------------------------------------------------------------------
int closeLoanMenu()
{
	int option;

	printf("1- Ingresar id péstamo a saldar ");
	printf("\n2- Salir \n\n");
	scanf("%d",&option);

	//utn_getNumber(&option,"\n\n-->   ", "\n * LA OPCIÓN NO ES VÁLIDA * \n",1, 2,1);
	return option;
}
//-------------------------------------------------------------------------------------------------------------------------------------


int confirmCloseMenu()//////////////
{
	int confirm;
	printf("\n 1- Confirmar");
	printf("\n 2- Salir\n\n");

	utn_getNumber(&confirm,"--> ", "\n* NO ES UNA OPCIÓN VÁLIDA * \n\n",1, 2,10);

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
			if(pointOutIfThereAreClientsLoaded(clients,lenClient)==0 || pointOutIfThereAreLoansLoaded(loans,lenLoan)==0)//CHECK IF THE USER PREVIOUSLY LOADED CLIENTS OR LOANS
				{
					printf("\n *   Debe haber almenos un cliente y un préstamo para poder operar.   *\n\n");
				}
				else
				{
					do{
					printCloseLoans(loans,clients,lenClient,lenLoan);
					optionRemMenu=closeLoanMenu();

					if(optionRemMenu==1)
					{
					printf("\n-------- REANUDAR PRESTAMO --------");
					utn_getNumber(&loanId,"\n\nID del prestamo a reanudar :","* ID NO ENCONTRADO* ",0, 1100,2);
					index= searchCloseLoan(loanId,loans,lenLoan);//SERCHS LOAN


						if(index==-1)//IF ID NOT FOUNF
						{
							printf("\n\n* ID NO ENCONTRADO *\n");

						}
						else//IF ID FOUND,SHOWS EMPLOYEE AND  REQUEST CONFIRMATION TO REMOVE
						{

							printf("\n------------------------------------------------------------------------------------------");
							printf("\n-------------------------------- REANUDAR PRESTAMO ---------------------------------------\n\n");
						    printf(" ID   IMPORTE    CUOTAS   ID CLIENTE     NOMBRE  APELLIDO    ESTADO PRESTAMO   ESTADO CLIENTE \n");
							printf("------------------------------------------------------------------------------------------\n");

							if(loans[index].isEmpty==0)
							  {
								printLoan(loans[index],clients,lenClient,lenLoan);



							  }
							printf("-------------------------------------------------------------------------------------------\n");
							printf("-------------------------------------------------------------------------------------------\n");

							confirm=confirmCloseMenu();

							if(confirm==1)
							{
								loans[index].isEmpty=0;
								printf("\n\n ** PRESTAMO REANUDADO ** \n");
							success=1;
							break;
							}
							else
							{
								printf("\n\n ** NO SE REALIZARON CAMBIOS ** \n");
								break;
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
void printCloseLoans(eLoan loans[], eClient clients[],int lenClient,int lenLoan)//////////////////////////////////////////
{
	int i;
	if(loans!=NULL && lenClient>0 && clients!=NULL && lenLoan>0)
	{
		printf("\n----------------------------------------------------------------------------------------------------");
		printf("\n---------------------------------- PRESTAMOS SALDADOS ----------------------------------------------\n\n");
		printf(" ID   IMPORTE    CUAOTAS    ID CLIENTE    NOMBRE APELLIDO    CUIL    ESTADO CLIENTE  ESTADO PRESTAMO \n");
		printf("----------------------------------------------------------------------------------------------------\n");

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].isEmpty==2)
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


					if(loan.isEmpty ==2)
						{
							strcpy(statusLoan,"SALDADO");
						}
					else if(loan.isEmpty==0)
						{
							strcpy(statusLoan,"ACTIVO");
						}
					else
					{
						strcpy(statusLoan,"VACIO");
					}


		if(loadClientsDescription(clients,clientId,lenClient,name,lastName,&cuil,statusClient))
		{
			printf(" %d    %d          %d            %d         %s   %s   %d        %s         %s\n",
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
				else if(loans[i].isEmpty ==2)
				{
					strcpy(status,"SALDADO");
				}
				else
				{
					strcpy(status,"VACIO");
				}

			}
			success=1;
		}
	}

	return success;
}

//---------------------------------------------------------------------------------------------------------------------
int serchActiveLoansbyBlientId(eLoan loans[], int idClient,int lenLoan)
{

	int accLoansById=0;
	int i;

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].isEmpty==0 && loans[i].idClient==idClient)
			{
				accLoansById++;

			}
		}

	return accLoansById;
}




//-------------------------------------------------------------------------------------------------------
void printLoansByClientId(eClient client,eLoan loans[],int lenClient,int lenLoan)//PRINT DETAIL OF ONE CLIENT ACTIVE LOANS/////////////////////////
{
		int i;
		int loanId;
		int amount;
		int fees;
		char loanStatus[10];


					printf("\n\n-------------------------------------------------------------------\n");
					printf("                PRESTAMOS A NOMBRE DE : %.8s    ",client.lastName);
					printf("\n-------------------------------------------------------------------\n");
					printf(" ID PRESTAMO   IMPORTE    CUOTAS   STATUS \n");



						for(i=0;i<lenLoan;i++)
						{//printf("\ncliente id : %d // index %d // is empty %d // idPrestamo %d",loans[i].idClient,i,loans[i].isEmpty,loans[i].id);
							if(loans[i].idClient==client.id && loans[i].isEmpty==0)
							{
								loanId =loans[i].id;;

								if(loadLoansDescriptionbyClientAndLoanId(loans,client.id, lenLoan, &amount, &fees, loanId, loanStatus))
								{
									printf("    %d         %d         %d       %s\n",loanId,amount,fees,loanStatus);

								}
							}

						}


				printf("\n-------------------------------------------------------------------\n");
				printf("\n-------------------------------------------------------------------\n");


}

//--------------------------------------------------------------------------------------------------------------------------------

int loadLoansDescriptionbyClientAndLoanId(eLoan loans[], int idClient, int lenLoan, int* amount, int* fees, int loanId, char  status[])
{
	int success=0;
	int i;


	if(loans!=NULL && idClient>0&& lenLoan>0)
	{

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].idClient==idClient && loans[i].id==loanId)
			{
				*amount=loans[i].amount;
				*fees=loans[i].fees;

				if(loans[i].isEmpty ==0)
				{
					strcpy(status,"ACTIVO");
				}
				else
				{
					strcpy(status,"SALDADO");
				}

			}
			success=1;
		}
	}

	return success;
}
//------------------------------------------------------------------------------------------------------------------------------
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
		if(loans[i].isEmpty==2 && loans[i].id==loanId)
		{

			index=i;
			break;
		}
	}
	return index;
}
//------------------------------------------------------------------------------------------------------------------------------------

int serchCloseLoansbyBlientId(eLoan loans[], int idClient, int lenLoan)
{

	int closedLoansById=0;
	int i;

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].idClient==idClient && loans[i].isEmpty==2)
			{
				closedLoansById++;

			}

		}


	return closedLoansById;
}
//------------------------------------------------------------------------------------------------------------------------------------

void printLoansandClientCuil(eLoan loans[], eClient clients[],int lenClient,int lenLoan)//////////////////////////////////////////
{
	int i;
	if(loans!=NULL && lenClient>0 && clients!=NULL && lenLoan>0)
	{
		if(pointOutIfThereAreClientsLoaded(clients,lenClient)==0 || pointOutIfThereAreLoansLoaded(loans,lenLoan)==0)//CHECK IF THE USER PREVIOUSLY LOADED CLIENTS
			{
				printf("\n *  Debe haber almenos un cliente y un préstamo para poder operar.  *\n\n");
			}
			else
			{
				printf("\n---------------------------------------------------------------------");
				printf("\n--------------------------  PRESTAMOS  ------------------------------\n\n");
				printf(" ID   IMPORTE    CUOTAS     CUIL CLIENTE       ESTADO PRESTAMO \n");
				printf("-----------------------------------------------------------------------\n");

				for(i=0;i<lenLoan;i++)
				{
					if(loans[i].isEmpty==0)
					{
						printOneLoanAndClientCuil(loans[i],clients,lenClient,lenLoan);
					}

				}
				printf("-----------------------------------------------------------------------\n");
				printf("-----------------------------------------------------------------------\n");
				printf("\n\n");
			}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------
void printOneLoanAndClientCuil(eLoan loan,eClient clients[],int lenClient,int lenLoan)//////////////////////
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
			printf(" %d    %d          %d           %d             %s\n",
					loan.id,
					loan.amount,
					loan.fees,
					cuil,
					statusLoan);
		}


}

//--------------------------------------------------------------------------------------------------------------

