/* normpars.c */
#include <stdio.h>
#include <stdint.h>
#include "norm.h"
#include "common.h"

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Используй normpars normX.dat\n");
		return -1;
	}
	else {
		norm p;
		if (norm_init(&p, argv[1]) == 0) {
			printf("\n-------------------------------ЗАГОЛОВОК-----------------------------\n");
			printf("Параметр                                   Значение                  \n");
			printf("---------------------------------------------------------------------\n");
			printf("Номер регистратора: \t%i\n", p.title->RegNumb);
			printf("Дата, время: \t\t%s\n", str_local_time((DayTime*)&(p.title->Day)));
			printf("Количество линий: \t%i\n", p.title->LineCount);
			printf("Флаг (0-норма,1-авария,2-внеш.пуск): \t%i\n", p.title->Flag);
			prnMatrixBin((uint16_t*)&(p.title->Bin));
			printf("\n");
			for(int i = 0; i < 32; i++)	printf("Канал N %i\t%f\n", i, p.title->RMS[i]);
			for(int i = 0; i < p.title->LineCount; i++) {
				printf("\n------------------------------  ЛИНИЯ %i  ----------------------------\n", p.line[i].LineNumb);
				for(int j = 0; j < 6; j++) {
					printf("Канал %i\t K: %f\n", p.line[i].ratio[j].ChNumb, p.line[i].ratio[j].ChRatio);
				};
				printf("\n");
				printf("Ua:\t%f\n", p.line[i].calc.Ua);
				printf("Ub:\t%f\n", p.line[i].calc.Ub);
				printf("Uc:\t%f\n", p.line[i].calc.Uc);
				printf("Ia:\t%f\n", p.line[i].calc.Ia);
				printf("Ib:\t%f\n", p.line[i].calc.Ib);
				printf("Ic:\t%f\n", p.line[i].calc.Ic);
				printf("Pa:\t%f\n", p.line[i].calc.Pa);
				printf("Pb:\t%f\n", p.line[i].calc.Pb);
				printf("Pc:\t%f\n", p.line[i].calc.Pc);
				printf("Psum:\t%f\n", p.line[i].calc.Psum);
				printf("Qa:\t%f\n", p.line[i].calc.Qa);
				printf("Qb:\t%f\n", p.line[i].calc.Qb);
				printf("Qc:\t%f\n", p.line[i].calc.Qc);
				printf("Qsum:\t%f\n", p.line[i].calc.Qsum);
				printf("Sa:\t%f\n", p.line[i].calc.Sa);
				printf("Sb:\t%f\n", p.line[i].calc.Sb);
				printf("Sc:\t%f\n", p.line[i].calc.Sc);
				printf("Ssum:\t%f\n", p.line[i].calc.Ssum);
				printf("Angle_a:\t%f\n", p.line[i].calc.Angle_a);
				printf("Angle_b:\t%f\n", p.line[i].calc.Angle_b);
				printf("Angle_c:\t%f\n", p.line[i].calc.Angle_c);
				printf("Cos_phi:\t%f\n", p.line[i].calc.Cos_phi);
				printf("Status:\t%i\n", p.line[i].calc.Status);
			};		
			norm_close(&p);
			return 0;
		}
		else return -1;
	};
};
