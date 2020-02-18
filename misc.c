// misc.c, 159
//
// Team Name: sampsonj (Members: Joshua Sampson)

#include "spede.h"
#include "kernel.h"

int QisEmpty (q_t *p){
	if(p->size == 0)return TRUE;
	return FALSE;
}

int QisFull (q_t *p){
	if(p->size == Q_SIZE) return TRUE;
	return FALSE;
}

int DeQ (q_t *p){
	int pid;
	if (QisEmpty(p)) return NA;
	pid = p->q[p->head];
	p->head = (p->head + 1) % Q_SIZE;
	p->size--;
	return pid;
}

void EnQ (int n, q_t *p){
	if(QisFull(p) == TRUE){
		cons_printf("Panic: queue is full, cannot EnQ!\n");
		breakpoint();
	}
	p->q[p->tail] = n;
	p->tail = (p->tail+1) % Q_SIZE;
	p->size++;
}

void StrAdd(char ch, char *str){
	while(*str){
		str++;
	}
	*str = ch;
	str++;
	*str = '\0';
}

void StrCpy(char *src, char *dest){
	while(*src){
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

void Bzero(char* p, int n){
	int i;
	for(i=0; i<n; i++){
		p[i] = '\0';
	}
}

