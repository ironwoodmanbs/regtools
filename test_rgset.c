/* test_rgset.c */
/* Це файл для автоматичного тестування функцій  rgset.c */
#include <stdio.h>
#include <stdint.h>
#include "common.h"
#include "rgset.h"

int main(int argc, char** argv) {
	
	//printf("%s" , argv[1]);	
	rgset* p = rgsetInit(argv[1]);
	if(p != NULL) 
			prnRgsetAll(p);
			
	 printf("\nПЕРЕВІРКА rgsetSplit()\t");
	printf("-----------------------------------------------------------------1234\n");

	 if(rgsetSplit(p) == -1) {
		 printf("ERROR\n");
		 	return -1;
	};
		prnRgsetAll(p);
	
	printf("OK\n");
	 
	printf("\nПЕРЕВІРКА rgsetNew()\t");
	rgset* rp = rgsetNew();
	if(rp == NULL) {
		printf("ERROR\n");
		return -1;
	};
	printf("OK\n");

	printf("\nПЕРЕВІРКА rgsetAddReg()\t");
	if(rgsetAddReg(rp, 0) == -1) {
		printf("ERROR\n");
		return -1;
	}; 
	printf("OK\n");

	
	printf("\nПЕРЕВІРКА rgsetAddChanel()\t");
	if(rgsetAddChanel(rp, 0) == -1) {
		printf("ERROR\n");
		return -1;
	}; 
		printf("OK\n");
	
	printf("\nПЕРЕВІРКА rgsetDelChanel()\t");
	if(rgsetDelChanel(rp, 0) == -1) {
		printf("ERROR\n");
		return -1;
	}; 
		printf("OK\n");

	printf("\nПЕРЕВІРКА rgsetDelReg()\t");
	if(rgsetDelReg(rp, 0) == -1) {
		printf("ERROR\n");
		return -1;
	};
		printf("OK\n");

	rgsetClose(rp);
	return 0;
}
