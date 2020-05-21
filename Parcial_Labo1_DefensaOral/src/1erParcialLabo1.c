/*
 ============================================================================
 Name        : TP2.c
 Author      : Evelina Aguirre
 Version     : v1.0
 Copyright   : Your copyright notice
 Description : Payroll management application
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>

#include "ArrayClients.h"
#include "Loans.h"
#include "Reports.h"
#include "utn.h"

#define QTY_CL 10
#define QTY_LO 10


int main(void) {

	setbuf(stdout,NULL);

		eClient arrayClients[QTY_CL];
		eLoan arrayLoans[QTY_LO];
		int idClient=100;
		int idLoans=1;
		int opcionMenu;

		initLoans(arrayLoans,QTY_LO);
		initClients(arrayClients,QTY_CL);
		//harcodeClients(arrayClients,QTY_CL,10);
		//harcodeLoans(arrayLoans,QTY_LO, 10);


	do{

		opcionMenu=principalMenu();
		switch(opcionMenu)
		{
		case 1://ADD CLIENT
			if(addClient(arrayClients,QTY_CL,idClient,arrayLoans,QTY_LO))
			  {
				idClient++;//Auto-increase ID
			  }
			break;

		case 2://MODIFY CLIENT
			modifyClient(arrayClients,QTY_CL,arrayLoans,QTY_LO);
			break;

		case 3://REMOVE CLIENT
			removeClient(arrayClients,QTY_CL,arrayLoans,QTY_LO);
			 break;

			case 4://ADD LOAN

				if(addLoan(arrayClients,QTY_CL,idLoans,arrayLoans,QTY_LO))
				{
				 idLoans++;
				}

			break;

			case 5:
				closeLoan(arrayClients,QTY_CL,arrayLoans,QTY_LO);
				break;

			case 6:
				resumeLoan(arrayClients,QTY_CL,arrayLoans,QTY_LO);
				break;

			case 7:
				printClients(arrayClients, arrayLoans,QTY_CL,QTY_LO);
				if(pointOutIfThereAreClientsLoaded(arrayClients,QTY_CL)==1)
					{
						SubMenuPrintClientAndActiveLoans(arrayClients,arrayLoans,QTY_CL,QTY_LO);
					}
				break;

			case 8:
				printLoansandClientCuil(arrayLoans,arrayClients,QTY_CL,QTY_LO);
				break;

			case 9:
				printClientsWithMoreLoansActive(arrayClients,arrayLoans,QTY_CL, QTY_LO);
				printClientsWithMoreClosedLoans(arrayClients,arrayLoans,QTY_CL, QTY_LO);
				printClientsWithMoreLoans(arrayClients,arrayLoans,QTY_CL, QTY_LO);

				break;
			case 10:
					menuLoansMoreThen1000(arrayClients, arrayLoans,QTY_CL,QTY_LO);
				 LoansTwelve(arrayClients, arrayLoans,QTY_CL,QTY_LO);
				 menuAskfees(arrayClients, arrayLoans,QTY_CL,QTY_LO);
				break;

				}

			}while(opcionMenu!=11);

	return EXIT_SUCCESS;
}








