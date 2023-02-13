#include <stdio.h>
#include <stdint.h>
#include "norm.h"
#include "common.h"
#define LINE_OFFSET 322


/* Функция инициализации объекта norm */
int norm_init(norm* p, char* file_name) {

	// Инициализация объекта типа norm
	p->title = NULL;
	if	(file_to_ram(p, file_name) == 0){
		p->line = (norm_line*)(LINE_OFFSET + (uintptr_t)p->title);
	}
	else {
		return -1;
	};
	return 0;
};

/* Функция закрытия объекта norm */
int norm_close(norm* p) {
	if(p->title != NULL) file_close (p);
	return 0;
};

