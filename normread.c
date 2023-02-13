/* normread.c */
#include <stdio.h>
#include <stdint.h>
#include "norm.h"
#include "common.h"
#include "rgset.h"

int search_channel(rgset* p, int ch_numb); // Возвращает номер канала в файле rgset.dat соответствующий номеру канала регистратора

int main(int argc, char** argv) {
	if(argc != 3) {
		printf("Используй normread normX.dat rgset.dat\n");
		return -1;
	}
	else {
		norm pn;
		rgset* pr = rgsetInit(argv[2]);	
		if (norm_init(&pn, argv[1]) == 0 && pr != NULL) {
			for(int i = 0; i < pr->reg->CountChanels; i++)	{
				prnFix(str_local_time((DayTime*)&(pn.title->Day)), 19, 22);
				prnFix(pr->chanel[i].Name, 20, 21);
				printf("%f\t", pn.title->RMS[i]);
				prnFix(pr->chanel[i].SymbolPrimCircuit, 3, 4);
				printf("\n");
			};

			for(int i = 0; i < pn.title->LineCount; i++) {
				prnFix(str_local_time((DayTime*)&(pn.title->Day)), 19, 22);
				prnFix(pr->line[pn.line[i].LineNumb].Name, 20, 21);
				printf("Psum: %f", pn.line[i].calc.Psum);
				printf("\t Qsum: %f", pn.line[i].calc.Qsum);
				printf("\tSsum: %f\n", pn.line[i].calc.Ssum);
				/*
				printf("Ua:\t%f\n", pn.line[i].calc.Ua);

				printf("Ub:\t%f\n", pn.line[i].calc.Ub);
				printf("Uc:\t%f\n", pn.line[i].calc.Uc);
				printf("Ia:\t%f\n", pn.line[i].calc.Ia);
				printf("Ib:\t%f\n", pn.line[i].calc.Ib);
				printf("Ic:\t%f\n", pn.line[i].calc.Ic);
				printf("Pa:\t%f\n", pn.line[i].calc.Pa);
				printf("Pb:\t%f\n", pn.line[i].calc.Pb);
				printf("Pc:\t%f\n", pn.line[i].calc.Pc);
				printf("Qa:\t%f\n", pn.line[i].calc.Qa);
				printf("Qb:\t%f\n", pn.line[i].calc.Qb);
				printf("Qc:\t%f\n", pn.line[i].calc.Qc);
				printf("Sa:\t%f\n", pn.line[i].calc.Sa);
				printf("Sb:\t%f\n", pn.line[i].calc.Sb);
				printf("Sc:\t%f\n", pn.line[i].calc.Sc);
				printf("Angle_a:\t%f\n", pn.line[i].calc.Angle_a);
				printf("Angle_b:\t%f\n", pn.line[i].calc.Angle_b);
				printf("Angle_c:\t%f\n", pn.line[i].calc.Angle_c);
				printf("Cos_phi:\t%f\n", pn.line[i].calc.Cos_phi);
				printf("Status:\t%i\n", pn.line[i].calc.Status);
				*/
			};		
			norm_close(&pn);
			rgsetClose(pr);
			return 0;
		}
		else return -1;
	};
};


int search_channel(rgset* p, int ch_numb) // Возвращает номер канала в файле rgset.dat соответствующий номеру канала регистратора
{
	for (int i = 0; i <= p->title->CountChanel; i++) if (p->chanel[i].ChNumber == ch_numb) return i;
	return -1;
}


