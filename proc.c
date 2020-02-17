// proc.c, 159
// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "spede.h"
#include "kernel.h"
#include "syscall.h"

void ToStr(int, char*);
int StrLen(char*);

/*prototype any subroutines of Clock() here
(or, prototype all functions of proc.c in proc.h, and include it on top)*/

void Clock(){
   int i;
   char str[] = "    ";  // str for 4-digits, plus NUL
   unsigned short *p;

   while(1){
      if (sys_tick % 100 == 0){
         ToStr((int)sys_tick/100, str);
         
         p = (unsigned short *) VIDEO_START;
         p += 75; //columns (to the right, on the same row)
         for(i=0; i<sizeof(str)-1; i++, p++){
            *p = str[i] + VIDEO_MASK;
         }
      }
      //sys_tick++;
   }
}

void Idle(){
    int secs;
    char *str = "    ";
    char ans[STR_SIZE];

    while(1){
        secs = get_time_call();
        ToStr(secs, str);
        write_call("The time is ");
        write_call(str);
        write_call(".\n");
        write_call("What do you say to a cup of coffee");
        read_call(ans);
        write_call("The answer is ");
        write_call(ans);
        write_call(".\n");
    }
}

void ToStr(int x, char *str){
  int i = StrLen(str) - 1;
  while(x){
    if(str[i] == '\0') break;
    str[i] = x%10 + '0';
    x = x/10;
    i--;
  }
}

int StrLen(char *str){
  int len = 0;
  while(str[len] != '\0'){
    len++;
  }
  return len;
}


