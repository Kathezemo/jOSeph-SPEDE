//
// Created by ChronoGuardian on 2/16/2020.
//

int get_time_call(void) {    // phase2
	int time;

	asm("int $48;
	movl %%eax, %0"
	: "=g" (time)
	:
	: "eax"
	);

	return time;
}

void write_call(char *str) {
	asm("movl %0, %%eax;
	int $49"
	:
	: "g" ((int)str)
	: "eax"
	);
}

void read_call(char *str){
    asm("movl %0, %%eax;
    int $50"
    :
    : "g" ((int)str)
    : "eax"
    );
}
