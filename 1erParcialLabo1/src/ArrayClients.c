#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>

#include "ArrayClients.h"
#include "Loans.h"
#include "utn.h"




/*void harcodeClients(eClient clients[],int len, int howMany)
{


	eClient auxList[]=
	{
			{1,"Maria","Rodríguez",12561002458754,0},
			{2,"Marcos","Castro",16001001145489,0},
			{3,"Marcela","Vazquez",12771002154785,0},
			{4,"Marcia","Parodi",18001000458456,0},
			{5,"Maximo","Escalar",22501002125478,0},
			{6,"Pedro","Benitez",13301000458723,0},
			{7,"Lucas","Martinez",14791001458745,0},
			{8,"Lucia","Gimenez",21001002123489,0},
			{9,"Oscar","Lugares",16001001123548,0},
			{10,"Martin","Gutierrez",14001001456874,0}

	};

	if(howMany<len && howMany<11)
	{
		for(int i=0;i<=howMany;i++)
		{
			clients[i]=auxList[i];

		}
	}
}*/

//--------------------------------------------------------------------------------------------------------------------------

int initClients(eClient clients[],int len)
{
	int i;
	int ret=-1;

	if(clients!= NULL && len>0)
	{
		for(i =0; i<=len;i++)
		{
			clients[i].isEmpty=1;//INITIALIZE ALL CLIENTES IN EMPTY (1)

		}
	ret=0;
	}
	return ret;

}
//--------------------------------------------------------------------------------------------------------------------------

int addClient(eClient clients[],int len, int id,eLoan loans[],int lenLoan)
{
	int success=-1;
	int index;
	char name[50];
	char lastName[50];
	int cuil;


	if(clients!=NULL && len>0 && loans!= NULL && lenLoan>0)
		{
		printf("\n-------- ALTA CLIENTE ---------");
		index=searchFreeSpace(clients,len);


		if(index==-1)//IF THERE ARE NO FREE SPACES
		{

			printf("\n\n-------------------------------\n\n");
			printf("     *  NO HAY ESPACIOS LIBRES  * ");
			printf("\n\n-------------------------------\n\n");

		}
		else// IF AN EMPTY PLACE HAS BEEN FOUND, REQUESTS DATA
		{
			fflush(stdin);
			utn_getName(name,"\nIngrese Nombre : "," * Error. El nombre no es válido. *",0,237,30,10);
			fflush(stdin);
			utn_getName(lastName,"Ingrese Apellido : ","* Error. El apellido no es válido. *",0,237,30,10);
			fflush(stdin);
			printf("Ingrese cuil: ");
			scanf("%d",&cuil);

			clients[index]=newClient(id,name,lastName,cuil);
			printf("\n\n---------------------------------------");
			printf("\n * Se agregó nuevo Cliente* ");
			printf("\n---------------------------------------\n");
			success=1;

		}
	}

	return success;

}

//--------------------------------------------------------------------------------------------------------------------------

int searchFreeSpace(eClient clients[],int len)
{
	int index=-1;

	for(int i=0;i<len;i++)
	{
		if(clients[i].isEmpty==1)//IF IT FINDS FREE SPACE IT RETURNS THE INDEX OF THE POCISION
		{
			index=i;
			break;
		}
	}
	return index;
}

//--------------------------------------------------------------------------------------------------------------------------

eClient newClient(int id,char name[],char lastName[], char cuil)/////////////////////////////
{
	eClient newClient;
	newClient.id=id;
	strcpy(newClient.name,name);
	strcpy(newClient.lastName,lastName);
	newClient.cuil=cuil;
	newClient.isEmpty=0;
	return newClient;
}

//--------------------------------------------------------------------------------------------------------------------------

int removeClientMenu()
{
	int option;

	printf("------ Remove Client------\n");
	printf("-----------------------------\n\n");
	printf(" 1- Enter id ");
	printf("\n 2- Back to menu \n\n");
	printf("-----------------------------\n");
	utn_getNumber(&option,"\n-->   ", "\n * INVALID OPTION * \n",1, 2,100);
	return option;
}

//--------------------------------------------------------------------------------------------------------------------------

int removeClient(eClient clients[],int len,eLoan loans[],int lenLoan)
{
		int success=0;
		int clientId;
		int index;
		int confirm;
		int optionRemMenu;

		if(clients!=NULL && len>0 && loans!= NULL && lenLoan>0)
		 {
			if(pointOutIfThereAreClientsLoaded(clients,len)==0)//CHECK IF THE USER PREVIOUSLY LOADED CLIENTS
			{
				printf("\n *  No hay clientes cargados aún. debe haber almenos un cliente para poder operar *\n\n");
			}
			else
			{

				do{
					printClients(clients, loans,len,lenLoan);
					optionRemMenu=removeClientMenu();

					if(optionRemMenu==1)
					{
						printf("\n-------- Remove Client --------");
						utn_getNumber(&clientId,"\n\nEnter id :","* ID NO ENCONTRADO* ",0, 1100,2);
						index= searchClient(clientId,clients,len);//SERCH CLIENT

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

							printOneClientAndActiveLoans(clients[index],loans,len,lenLoan);


							printf("---------------------------------------------------------------------------------------\n");
							printf("---------------------------------------------------------------------------------------\n");

							confirm=confirmModificationMenu();

							if(confirm==1)
							{
								clients[index].isEmpty=1;
								printf("\n\n** ID REMOVED **\n");
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

//--------------------------------------------------------------------------------------------------------------------------

int modifyClient(eClient clients[],int len,eLoan loans[],int lenLoan)
{
	int success=-1;
	int index;
	int id;
	int option;
	char lastName[30];
	char name[30];
	int cuil;
	int confirm;


	if(clients!=NULL && len>0 && loans!= NULL && lenLoan>0)
		{
		if(pointOutIfThereAreClientsLoaded(clients,len)==0)//VERIFIES IF THE USER LOADED ANY CUSTOMER PREVIOUSLY
			{
			printf("\n *  No hay clientes cargados aún. debe haber almenos un cliente para poder operar  *");
			}
		else
		{

			printClients(clients,loans,len,lenLoan);
			utn_getNumber(&id,"Ingrese id :"," * NO SE ENCONTRÓ EL ID * ",100,150,10);


			index=searchClient(id,clients,len);
			if(index==-1)//IF ID NOT FOUNF
			{
				printf("\n-----------------------------------------------------------------");
				printf("\n\n               * No se encontró el id *\n");
				printf("\n-----------------------------------------------------------------");
			}
			else//IF ID FOUND,SHOWS CLIENT AND  REQUEST CONFIRMATION TO MODIFY
			{
				do{

					printf("\n---------------------------------------------------------------------------------------");
					printf("\n-------------------------------- MODIFICAR CLIENTE ------------------------------------\n\n");
					printf(" ID   NOMBRE    APELLIDO     CUIL      PRESTAMO    ESTADO PRESTAMO   ESTADO CLIENTE \n");
					printf("---------------------------------------------------------------------------------------\n");

					printOneClientAndActiveLoans(clients[index],loans,len,lenLoan);

					printf("---------------------------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------------------------\n");

					utn_getNumber(&option,"\n1-Modificer nombre \n2-Modificar Apellido  \n3-Modificar cuil\n4-Salir\n\n"
							"-----------------------------------------------------------------\n"
							"-----------------------------------------------------------------"
							"\n\n--> "," * OPCIÓN INVÁLIDA *",1,5,10);
					switch(option)//REQUEST INFORMATION TO MODIFY
					{
					case 1:
						fflush(stdin);
						utn_getName(name,"\nIngrese Nombre : "," * Error. El nombre no es válido. *",0,237,30,10);
						confirm=confirmModificationMenu();
						if(confirm==1)
						{
							strcpy(clients[index].name,name);
							printf("\n* NOMBRE DEL CLIENTE ACTUALIZADO *\n\n");
							success=1;
						}
						else
						{
							printf("\n\n * NO SE REALIZARON CAMBIOS * \n");
						}

						success=0;

						break;

					case 2:

						fflush(stdin);
						utn_getName(lastName,"Ingrese Apellido : ","* Error. El apellido no es válido. *",0,237,30,10);
						confirm=confirmModificationMenu();

						if(confirm==1)
						{
							strcpy(clients[index].lastName,lastName);
							printf("\n* APELLIDO DEL CLIENTE ACTUALIZADO *\n\n");
							success=1;
						}
						else
						{
							printf("\n\n * NO SE REALIZARON CAMBIOS * \n");
						}
						success=0;
						break;

					case 3:

						printf("Ingrese cuil: ");
						scanf("%d",&cuil);
						confirm=confirmModificationMenu();

						if(confirm==1)
						{
							clients[index].cuil=cuil;
							printf("\n* EMPLOYEE DATA UPDATED *\n\n");
							success=1;
						}
						else
						{
							printf("\n\n * NO SE REALIZARON CAMBIOS * \n");
						}
						success=0;

						break;

					}
				}while(option!=4);



			}
		}
	}
	return success;
}

//--------------------------------------------------------------------------------------------------------------------------

void printClients(eClient clients[], eLoan loans[],int len,int lenloans)
{
	int i;
	if(clients!=NULL && len>0 && loans!=NULL && lenloans>0)
	{
		printf("\n---------------------------------------------------------------------------------------");
		printf("\n-------------------------------- LISTA DE CLIENTES ------------------------------------\n\n");
		printf(" ID   NOMBRE    APELLIDO     CUIL    CANT PRESTAMOS     ESTADO  \n");
		printf("----------------------------------------------------------------------------------------\n");

		for(i=0;i<len;i++)
		{

			printOneClientAndActiveLoans(clients[i],loans,len,lenloans);



		}
		printf("---------------------------------------------------------------------------------------\n");
		printf("---------------------------------------------------------------------------------------\n");
		printf("\n\n");
	}
}

//--------------------------------------------------------------------------------------------------------------------------

void printOneClientAndActiveLoans(eClient client,eLoan loans[],int lenClient,int lenLoan)//PRINT CLIENT INFORMATION AND CUMBER OF ACTIVES LOANS
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


			if(client.isEmpty==0)
			{
			accLoans=serchActiveLoansbyBlientId(loans,client.id,lenLoan);



				printf(" %d   %.8s    %.8s          %d             %d  %s \n",
						client.id,
						client.name,
						client.lastName,
						client.cuil,
						accLoans,
						statusClient);

			}

}

//--------------------------------------------------------------------------------------------------------------------------
void SubMenuPrintClientAndActiveLoans()//PRINT DETAIL OF ONE CLIENT ACTIVE LOANS 7 SUB MENU///////////////////////////
{
  int option;
  do{

	  	  utn_getNumber(&option,"\n-------------------------------------------\n\n"
	  			  	  	  	  	"\n1- VER PRESTAMOS ACTIVOS DE ESTE CLIENTE "
		  	  	  	  			"\n2- SALIR "
		  	  	  	  			"\n\n-------------------------------------------\n\n"," * La opción ingresada no es válida * ",1,2,10);



  }while(option!=2);

}

//--------------------------------------------------------------------------------------------------------------------------

int searchClient(int id, eClient clients[],int len)
{
	int index=-1;

	for(int i=0;i<len;i++)
	{
		if(clients[i].isEmpty==0 && clients[i].id==id)
		{
			index=i;
			break;
		}
	}
	return index;
}


//--------------------------------------------------------------------------------------------------------------------------

int confirmModificationMenu()//////////////
{
	int confirm;
	printf("\n 1- CONFIRMAR");
	printf("\n 2- SALIR\n\n");

	utn_getNumber(&confirm,"--> ", "\n* NO ES UNA OPCIÓN VÁLIDA * \n 1- CONFIRMAR\n 2- VOLVER AL MENÚ DE MODIFICACIONES \n\n",1, 2,10);

	return confirm;
}

//--------------------------------------------------------------------------------------------------------------------------


int pointOutIfThereAreClientsLoaded(eClient clients[],int len)////////////
{
	int success=0;
	if(clients!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(clients[i].isEmpty==0)
			{

				success=1;
				break;
			}

		}
	}
		return success;
}

//--------------------------------------------------------------------------------------------------------------------------

int loadClientsDescription(eClient clients[], int idClient, int lenClient,char name[50],char lastName[50],int* cuil,char estado[20])/////////
{
	int success=0;
	int i;


	if(clients !=NULL && lenClient>0 && idClient>0)
	{

		for(i=0;i<lenClient;i++)
		{
			if(clients[i].id==idClient)
			{
				strcpy(name,clients[i].name);
				strcpy(lastName,clients[i].lastName);
				*cuil=clients[i].cuil;

				if(clients[i].isEmpty==0)
				{
					strcpy(estado,"ACTIVO");
				}
				else
				{
					strcpy(estado,"INACTIVO");
				}
			}
			success=1;
		}
	}

	return success;
}

