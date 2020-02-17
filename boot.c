// boot.c, 159, phase 1
//
// Team Name: sampsonj (Members: Joshua Sampson)

#include "spede.h" 
#include "kernel.h"
#include "entry.h"
#include "misc.h"
#include "proc.h"

// kernel data are all declared here (prototyped in kernel.h):
int cur_pid;
q_t unused_q;
q_t ready_q;
pcb_t pcb[PROC_SIZE];
kb_t kb;
char stack[PROC_SIZE][STACK_SIZE];

unsigned sys_tick=0;
struct i386_gate *intr_table;

void boot();
void zeroQueues();
void CreateProc(func_p_t);


void main(void) {                   // kernel boots

    zeroQueues();
    boot();
}

void CreateProc(func_p_t type){
  cur_pid = DeQ(&unused_q);
  EnQ(cur_pid, &ready_q);

  //clear both the PCB and stack for the new PID
  Bzero(&stack[cur_pid][0], STACK_SIZE);
  Bzero((char*)&pcb[cur_pid], sizeof(q_t));

  pcb[cur_pid].state = READY;
  pcb[cur_pid].tf_p = (tf_t *) &stack[cur_pid][STACK_SIZE - sizeof(tf_t)];
  pcb[cur_pid].tf_p -> efl = EFL;
  pcb[cur_pid].tf_p -> cs = CS;
  pcb[cur_pid].tf_p -> eip = (int)type;

}



void boot(){
	int i;
	sys_tick = 0;
	intr_table = (struct i386_gate *)INTR_TABLE;

	i = 0;
	while(!QisFull(&unused_q)){
		EnQ(i, &unused_q);
		i++;
	}

	fill_gate(&intr_table[TIMER], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);
	fill_gate(&intr_table[GET_TIME], (int)GetTimeEntry, get_cs(), ACC_INTR_GATE, 0);
	fill_gate(&intr_table[WRITE], (int)WriteEntry, get_cs(), ACC_INTR_GATE, 0);
	fill_gate(&intr_table[READ], (int)ReadEntry, get_cs(), ACC_INTR_GATE, 0);
	outportb(PIC_MASK_REG, PIC_MASK);
	asm("sti");

	CreateProc((func_p_t)Clock);
	CreateProc((func_p_t)Idle);

	cur_pid = DeQ(&ready_q);
	Loader(pcb[cur_pid].tf_p);
}

void zeroQueues(){
	Bzero((char *)&unused_q, sizeof(q_t));
	Bzero((char *)&ready_q, sizeof(q_t));
	Bzero((char *)&kb.wait_queue, sizeof(q_t));

	unused_q.head = 0;
	unused_q.tail = 0;
	ready_q.head = 0;
	ready_q.tail = 0;
	kb.wait_queue.head = 0;
	kb.wait_queue.tail = 0;
}



