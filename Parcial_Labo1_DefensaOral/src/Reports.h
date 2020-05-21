/*
 * Reports.h
 *
 *  Created on: 16 may. 2020
 *      Author: Usuario
 */




#ifndef REPORTS_H_
#define REPORTS_H_



#endif /* REPORTS_H_ */

void printClientsWithMoreLoansActive(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void printClientsWithMoreLoans(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void printClientsWithMoreClosedLoans(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void LoansMoreThen1000(int amount,eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void menuLoansMoreThen1000(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
int serchClosedLoansbyIdClient(eLoan loans[], int idClient,int lenLoan);
int serchAllLoans(eLoan loans[], int idClient, int lenLoan);
int principalMenu();
void LoansTwelve(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void menuAskfees(eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void reportsByFees(int fees,eClient clients[], eLoan loans[],int lenClient,int lenLoan);
void printaALLClientReports(eClient client,eLoan loans[],int lenClient,int lenLoan);
void printClientReports1(eClient client,eLoan loans[],int lenClient,int lenLoan);


