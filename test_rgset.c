/* test_rgset.c */
/* Це файл для автоматичного тестування функцій  rgset.c */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "common.h"
#include "rgset.h"

int main(int argc, char** argv) {
	
		
	rgset* rp = rgsetInit(argv[1]);
	if(rp != NULL) 		prnRgsetAll(rp);			
	
	
	printf("\nПЕРЕВІРКА rgsetSplit()\t");
	printf("-----------------------------------------------------------------1234\n");
	 if(rgsetSplit(rp) == -1) {
		 printf("ERROR\n");
		 return -1;
	};
	prnRgsetAll(rp);	
	printf("OK\n");
	
	
	printf("-----------------------------------------------------------------------------------------------\n");
	
	//printf("\nПЕРЕВІРКА rgsetAddChanel()\t");	
	//if(rgsetAddChanel(rp, rp->title->CountChanel) == -1) {
		//printf("ERROR\n");
		//return -1;
	//}
	//printf ("OK\n");
 	//strcpy(rp->chanel[rp->title->CountChanel - 1].Name, "Name of new channel");
 	//strcpy(rp->chanel[rp->title->CountChanel - 1].SymbolChanel, "NewChanel");
 	//strcpy(rp->chanel[rp->title->CountChanel - 1].SymbolPrimCircuit, "kPopugay");
 	//strcpy(rp->chanel[rp->title->CountChanel - 1].SymbolSecondCircuit, "Popugay");
	//rp->chanel[rp->title->CountChanel - 1].ChNumber = 123;
	//rp->chanel[rp->title->CountChanel - 1].LineNumber = 12;
	//rp->chanel[rp->title->CountChanel - 1].RegNumber = 1;
	//prnRgsetTitle (rp);
	//prnRgsetChanel(rp);	 

	//printf("\nПЕРЕВІРКА rgsetAddReg()\t");
	//if(rgsetAddReg(rp, 0) == -1) {
		//printf("ERROR\n");
		//return -1;
	//}; 
	//printf("OK\n");
	//prnRgsetTitle (rp);
	//prnRgsetReg(rp);
	
	//printf("\nПЕРЕВІРКА rgsetAddChanel()\t");
	//if(rgsetAddChanel(rp, 0) == -1) {
		//printf("ERROR\n");
		//return -1;
	//}; 
		//printf("OK\n");
	
	//printf("\nПЕРЕВІРКА rgsetDelChanel()\t");
	//if(rgsetDelChanel(rp, 0) == -1) {
		//printf("ERROR\n");
		//return -1;
	//}; 
		//printf("OK\n");

	//printf("\nПЕРЕВІРКА rgsetDelReg()\t");
	//if(rgsetDelReg(rp, 0) == -1) {
		//printf("ERROR\n");
		//return -1;
	//};
		//printf("OK\n");
		
		
	printf("\n Перевірка rgsetUnit()\t");
	if (rgsetUnit(rp) == -1) {
		printf("ERROR\n");
		return -1;
	};
	printf ("OK\n"); 
	
	printf("\nПеревірка RgsetSave()\t");
	if (rgsetSave(rp, "newrgset.dat") == -1){
		printf("ERROR\n");
		return -1;
	}
	printf ("OK\n"); 
		
	printf("\nПЕРЕВІРКА rgsetNew()\t");
	 rp = rgsetNew();
	if(rp == NULL) {
		printf("ERROR\n");
		return -1;
	};
	printf("OK\n");	
	
	printf ("%ld", sizeof(rgset));


	rgsetClose(rp);
	return 0;
}
