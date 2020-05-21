#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include "utn.h"
#include "ArrayClients.h"
#include "Loans.h"



int principalMenu()
{
	int opcion;
	printf("\n\n--------------------------------");
	printf("\n------- PRINCIPAL MENU ---------\n");
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
	utn_getNumber(&opcion,"\n--> ", "\n * INVALID OPTION * \n",1, 11,100);
	return opcion;
}



void printClientsWithMoreLoansActive(eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{

	    int i,j;
	    int contMax;
	    int mayor;
	    eClient idMax;
	    int flag=0;



	    		for(i=0;i<lenClient;i++)
	    		{	contMax=0;
	    			if(clients[i].isEmpty==0)
	    			{
	    				for(j=0;j<lenLoan;j++)
	    					{
	    						if(loans[j].isEmpty==0 && loans[j].idClient==clients[i].id)
	    						{
	    							contMax++;

	    						}
	    						if(flag==0 || (contMax>mayor))
	    						{
	    						mayor = contMax;
	    						idMax = clients[i];
	    						flag=1;
	    						}

	    					}
	    			}

	    		}
	    		printf("\n---------------------------------------------------------------------------------------");
	    		printf("\n---------------------Cliente con más Prestamos Activos---- ----------------------------\n\n");
	    		printf(" ID   NOMBRE    APELLIDO     CUIL    CANT PRESTAMOS     ESTADO  \n");
	    		printf("----------------------------------------------------------------------------------------\n");

	    		printOneClientAndActiveLoans(idMax,loans,lenClient,lenLoan);
	    		printf("---------------------------------------------------------------------------------------\n");
	    		printf("---------------------------------------------------------------------------------------\n");
	    		printf("\n\n");
}


//-------------------------------------------------------------------------------------------------------
void printClientsWithMoreClosedLoans(eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{

	    int i,j;
	    int contMax;
	    int mayor;
	    eClient idMax;
	    int flag=0;



	    		for(i=0;i<lenClient;i++)
	    		{	contMax=0;
	    			if(clients[i].isEmpty==0)
	    			{
	    				for(j=0;j<lenLoan;j++)
	    					{
	    						if(loans[j].isEmpty==2 && loans[j].idClient==clients[i].id)
	    						{
	    							contMax++;

	    						}
	    						if(flag==0 || (contMax>mayor))
	    						{
	    						mayor = contMax;
	    						idMax = clients[i];
	    						flag=1;
	    						}

	    					}
	    			}

	    		}
	    		printf("\n---------------------------------------------------------------------------------------");
	    		printf("\n------------------ Cliente con más Prestamos Saldados --------------------------------\n\n");
	    		printf(" ID   NOMBRE    APELLIDO     CUIL    CANT PRESTAMOS     ESTADO  \n");
	    		printf("----------------------------------------------------------------------------------------\n");

	    		printClientReports1(idMax,loans,lenClient,lenLoan);
	    		printf("---------------------------------------------------------------------------------------\n");
	    		printf("---------------------------------------------------------------------------------------\n");
	    		printf("\n\n");
}

//--------------------------------------------------------------------------------------------------------------------------

void menuLoansMoreThen1000(eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{
	int option;
	int amount;


		utn_getNumber(&option,"Ingrese Importe : \n\n\n1- $5000 \n2- $10000 \n\n--> "," * Error. la opción ingresada no es válida *",1,2,10);

		switch(option)
		{
		case 1:
			amount=5000;
			break;
		case 2:
			amount=10000;
			break;

		}

		LoansMoreThen1000(amount,clients,loans,lenClient, lenLoan);

}
void LoansMoreThen1000(int amount,eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{
	int i;
	int accMil=0;

	for(i=0;i>lenLoan;i++)
	{
		if(loans[i].amount == amount)
		{
			accMil++;
		}

	}


	printf("\n\nPrestamos con Monto %d : %d ",amount,accMil);

}
//------------------------------------------------------------------------------------------------------------------------
void printClientsWithMoreLoans(eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{

	    int i,j;
	    int contMax;
	    int mayor;
	    eClient idMax;
	    int flag=0;



	    		for(i=0;i<lenClient;i++)
	    		{	contMax=0;
	    			if(clients[i].isEmpty==0)
	    			{
	    				for(j=0;j<lenLoan;j++)
	    					{
	    						if(loans[j].idClient==clients[i].id)
	    						{
	    							contMax++;

	    						}
	    						if(flag==0 || (contMax>mayor))
	    						{
	    						mayor = contMax;
	    						idMax = clients[i];
	    						flag=1;
	    						}

	    					}
	    			}

	    		}
	    		printf("\n---------------------------------------------------------------------------------------");
	    		printf("\n-------------------------------- Cliente con más Prestamos ----------------------------\n\n");
	    		printf(" ID   NOMBRE    APELLIDO     CUIL    CANT PRESTAMOS     ESTADO  \n");
	    		printf("----------------------------------------------------------------------------------------\n");

	    		printaALLClientReports(idMax,loans,lenClient,lenLoan);
	    		printf("---------------------------------------------------------------------------------------\n");
	    		printf("---------------------------------------------------------------------------------------\n");
	    		printf("\n\n");
}


//-------------------------------------------------------------------------------------------------------------------------------
void printClientReports1(eClient client,eLoan loans[],int lenClient,int lenLoan)//PRINT CLIENT INFORMATION AND CUMBER OF ACTIVES LOANS
{

	char statusClient[10];
	int accLoans;

			if(client.isEmpty==0)
				{
					strcpy(statusClient,"ACTIVO");
				}
				else
				{
					strcpy(statusClient,"INACTIVO");
				}



			accLoans=serchCloseLoansbyBlientId(loans,client.id,lenLoan);


				printf(" %d   %.8s    %.8s          %d          %d        %s \n",
						client.id,
						client.name,
						client.lastName,
						client.cuil,
						accLoans,
						statusClient);




}

//--------------------------------------------------------------------------------------------------


void printaALLClientReports(eClient client,eLoan loans[],int lenClient,int lenLoan)//PRINT CLIENT INFORMATION AND CUMBER OF ACTIVES LOANS
{

	char statusClient[10];
	int accLoans;

			if(client.isEmpty==0)
				{
					strcpy(statusClient,"ACTIVO");
				}
				else
				{
					strcpy(statusClient,"INACTIVO");
				}



			accLoans=serchAllLoans(loans,client.id,lenLoan);


				printf(" %d   %.8s    %.8s          %d          %d        %s \n",
						client.id,
						client.name,
						client.lastName,
						client.cuil,
						accLoans,
						statusClient);


}

//-------------------------------------------------------------------------------------------------------------
int serchAllLoans(eLoan loans[], int idClient, int lenLoan)
{

	int closedLoansById=0;
	int i;

		for(i=0;i<lenLoan;i++)
		{
			if(loans[i].idClient==idClient)
			{
				closedLoansById++;

			}

		}


	return closedLoansById;
}
//----------------------------------------------------------------------

void LoansTwelve(eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{
	int i;
	int accTwelve=0;

	for(i=0;i>lenLoan;i++)
	{
		if(loans[i].fees==12 && loans[i].isEmpty==2)
			{
			  accTwelve++;
			}

	}


	printf("\n\nPrestamos en 12 cuotas saldados : %d ",accTwelve);

}

//-----------------------------------------------------------------------
void menuAskfees(eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{
	int option;
	int fees;
	utn_getNumber(&option,"\nIngrese cantidad de Cuotas: \n1- 6 cuotas \n2- 12 cuotas \n3- 18 cuotas \n4-24 cuotas","\nError.\n",1,4,10);

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
	case 4:
		fees=24;
		break;
	}

	reportsByFees(fees,clients,loans,lenClient, lenLoan);

}

//-----------------------------------------------------------------------------------------------

void reportsByFees(int fees,eClient clients[], eLoan loans[],int lenClient,int lenLoan)
{
	int i;
	int accFees=0;

	for(i=0;i>lenLoan;i++)
	{
		if(loans[i].fees==fees&& loans[i].isEmpty==0)
			{

			accFees++;

			}

	}


	printf("\n\nCantidad de prestamos en %d cuotas : %d ",fees,accFees);

}

