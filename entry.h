// entry.h
//
// Team Name: sampsonj (Members: Joshua Sampson)

#ifndef __ENTRY__
#define __ENTRY__

#ifndef ASSEMBLER

#include <limits.h>
__BEGIN_DECLS

#include "kernel.h"
void Loader(tf_t *);
void TimerEntry(void);
void GetTimeEntry();
void WriteEntry();
void ReadEntry();



__END_DECLS

#endif

#endif