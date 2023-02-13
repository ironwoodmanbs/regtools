#include <stdio.h>
#include <stdint.h>
#include "rgset.h"

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Используй rgsetpars rgset.dat\n");
		return -1;
	}
	else {
		rgset* p = rgsetInit(argv[1]);
			if(p != NULL) {
			prnRgsetAll(p);
			rgsetClose(p);
			return 0;
		}
		else return -1;
	};
};
