// misc.h, 159

#ifndef __MISC__
#define __MIsC__

#include "kernel.h" // need definition of 'q_t' below

int QisEmpty(q_t *);
int QisFull(q_t *);
int DeQ(q_t *);
void EnQ(int , q_t *);
void StrAdd(char, char*);
void StrCpy(char*, char*);
void Bzero(char* , int );

#endif

