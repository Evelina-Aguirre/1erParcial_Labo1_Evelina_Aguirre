/*
 * Loans.h
 *
 *  Created on: 17 may. 2020
 *      Author: Usuario
 */



#ifndef LOANS_H_
#define LOANS_H_

typedef struct{
	int id;
	int idClient;
	int amount;
	int fees;
	int isEmpty;
}eLoan;

#endif /* LOANS_H_ */

void harcodeLoans(eLoan loans[],int lenLoan, int howMany);
int initLoans(eLoan loans[],int lenLoan);
int addLoan(eClient clients[],int len, int loanId,eLoan loans[],int lenLoan);
int searchFreeSpaceLoans(eLoan loans[],int lenLoan);
eLoan newLoan(int loanId, int clientId,int amount,int fees);
int subMenuAdLoansAmount();
int subMenuAdLoansFees();
int closeLoan(eClient clients[],int lenClient,eLoan loans[],int lenLoan);
int closeLoanMenu();
int confirmCloseMenu();
int resumeLoan(eClient clients[],int lenClient,eLoan loans[],int lenLoan);
void printLoans(eLoan loans[], eClient clients[],int lenClient,int lenLoan);
void printLoan(eLoan loan,eClient clients[],int lenClient,int lenLoan);
int loadLoansDescription(eLoan loans[], int idClient, int lenLoan, int* amount, int* fees, int* loanId, char  status[]);
int serchActiveLoansbyBlientId(eLoan loans[], int idClient,int lenLoan);
void printLoansByClientId(eClient client,eLoan loans[],int lenClient,int lenLoan);
int pointOutIfThereAreLoansLoaded(eLoan loans[],int lenLoan);
int searchActiveLoan(int loanId, eLoan loans[],int lenLoan);
int searchCloseLoan(int loanId, eLoan loans[],int lenLoan);
void printCloseLoans(eLoan loans[], eClient clients[],int lenClient,int lenLoan);
int serchCloseLoansbyBlientId(eLoan loans[], int idClient, int lenLoan);
void printOneLoanAndClientCuil(eLoan loan,eClient clients[],int lenClient,int lenLoan);
void printLoansandClientCuil(eLoan loans[], eClient clients[],int lenClient,int lenLoan);

int loadLoansDescriptionbyClientAndLoanId(eLoan loans[], int idClient, int lenLoan, int* amount, int* fees, int loanId, char  status[]);
