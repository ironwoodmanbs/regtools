#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include "list.h"

list* list_add(list* ls) {
	list* new = malloc(sizeof(list));
	if(new == NULL) {
		perror("Memory is not allocated");
		exit(EXIT_FAILURE);
	};
	new->prev = NULL; new->next = NULL; new->data = NULL;
	if(ls != NULL) {
		list* tmp = ls->next;
		if(ls->next) ls->next->prev = new;
		ls->next = new;
		new->prev = ls;
		new->next = tmp;
	};
	return new;
};


list* list_del(list* ls) {
	list* tmp_prev = ls->prev;
	list* tmp_next = ls->next;
	free(ls);
	if(tmp_prev) tmp_prev->next = tmp_next;
	if(tmp_next) tmp_next->prev = tmp_prev;
	if(tmp_prev) return tmp_prev;
	else if(tmp_next) return tmp_next;
	else return NULL;
};


int list_up(list* ls) {
	list* tmp_prev = ls->prev;
	list* tmp_next = ls->next;
	if(tmp_prev) {
		ls->prev = tmp_prev->prev;
		ls->next = tmp_prev;
		tmp_prev->next = tmp_next;
		tmp_prev->prev = ls;
		if(tmp_next) tmp_next->prev = tmp_prev;
		return 0;
	}
	else return -1;
}


int list_down(list* ls) {
	list* tmp_prev = ls->prev;
	list* tmp_next = ls->next;
	if(tmp_next) {
		ls->next = tmp_next->next;
		ls->prev = tmp_next;
		tmp_next->prev = tmp_prev;
		tmp_next->next = ls;
		if(tmp_prev) tmp_prev->next = tmp_next;
		return 0;
	}
	else return -1;
}


int list_count(list* ls) {
	if(ls == NULL) return 0;
	while(ls->prev) ls = ls->prev;
	int i = 1;
	while(ls->next){
		i++;
		ls = ls->next;
	};
	return i;
}
