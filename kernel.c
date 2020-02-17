// kernel.c, 159, phase 1
//
// Team Name: sampsonj (Members: Joshua Sampson)

#include "spede.h"
#include "kernel.h"
#include "proc.h"
#include "misc.h"
#include "entry.h"
#include "syscall.h"

void TimerService( tf_t *p) {
  char ch;
  pcb[cur_pid].tf_p = p;
 
  if (cons_kbhit()){
    ch = cons_getchar();
    if (ch == 'g'){
      breakpoint();
    }
    if(!QisEmpty(&kb.wait_queue)){
    	KbService(ch);
    }
  }

  outportb(PIC_CONTROL_REG, TIMER_ACK);

  sys_tick++;
   
  pcb[cur_pid].run_tick++;
  pcb[cur_pid].total_tick++;

  if(pcb[cur_pid].run_tick == TIME_SIZE){
    EnQ(cur_pid, &ready_q);
    pcb[cur_pid].state = UNUSED;
    cur_pid = NA;
    //alter/downgrade its state
    //clear cur_pid to become NA
    Swapper();
  }
  
  Loader(pcb[cur_pid].tf_p);
}

void Swapper(){
  if (QisEmpty(&ready_q) == TRUE){
    cons_printf("Kernel: panic, no more process ready to run!\n");
    breakpoint();;
  }

  cur_pid = DeQ(&ready_q);
  pcb[cur_pid].run_tick = 0;
  pcb[cur_pid].state = RUN;
}

void GetTimeService(tf_t *tf_p){
	int sec = sys_tick/100;
	tf_p->eax = sec;
	Loader(tf_p);
}

void WriteService(tf_t *tf_p){
	char *p = (char*)tf_p->eax;
	while(*p) {
		WriteChar(*p);
		p++;
	}
	Loader(tf_p);
}

void KBService(char ch){
	int pid;
	WriteChar(ch);
	if(ch != CR){
		StrAdd(ch, kb.buf);
		return;
	}
	pid = DeQ(&kb.wait_queue);
	StrCpy(kb.buf, (char*) pcb[pid].tf_p->eax);
	pcb[pid].state = READY;
	EnQ(pid, &ready_q);
	Bzero(&kb.buf, sizeof(STR_SIZE));
}

void WriteChar(char ch){
	int i;
	int curpos;
	unsigned short *cursor = (unsigned short) VIDEO_START;
	if((int)(cursor - VIDEO_START) % 80 == 0 ){
		for(i=0; i<80; i++){
			*cursor = ' ' + VIDEO_MASK;
			cursor++;
		}
	}

	if(ch != CR && ch != LF) {
		*cursor = ch + VIDEO_MASK;
		cursor++;
	}else{
		curpos = (int)(cursor - VIDEO_START) % 80;
		cursor += 80-curpos;
	}

	if(cursor == (short)(80 * 25 + VIDEO_START)){
		cursor = (unsigned short) VIDEO_START;
	}
}

void ReadService(tf_t *tf_p){
	pcb[cur_pid].tf_p = tf_p;

	EnQ(cur_pid, &kb.wait_queue);
	pcb[cur_pid].state = WAIT;
	cur_pid = NA;

	Swapper();
	Loader(pcb[cur_pid].tf_p);
}