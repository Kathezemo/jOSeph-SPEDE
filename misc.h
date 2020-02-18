// misc.h, 159
//
// Team Name: sampsonj (Members: Joshua Sampson)

#ifndef __MISC__
#define __MIsC__

#include "kernel.h"

int QisEmpty(q_t *);
int QisFull(q_t *);
int DeQ(q_t *);
void EnQ(int , q_t *);
void StrAdd(char, char*);
void StrCpy(char*, char*);
void Bzero(char* , int );

#endif

