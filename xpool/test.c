#include <stdio.h>
#include <sys/time.h> 
#include "xpool.h"

struct x_task_data{
	int value;
};

// void std(struct task_data *p){
// 	printf("RUN : %d\n",p->value);
// }

void real_do_task(x_task_data *d_p){
	printf("RUN TASK : %d\n",d_p->value);
	sleep(2);
}

#define RAND(i_p,max) { struct timeval tpstart;gettimeofday(&tpstart,NULL); srand(tpstart.tv_usec);*i_p = rand() % max ; }

int main(){
	int worker_count = 8;
	int max_free_tick = 256;
	int r = 0;
	int k = 0;
	x_task_data m;

	r = xpool_init(worker_count,max_free_tick,real_do_task,sizeof(struct x_task_data));
	//子进程的main函数，退出
	if(r == -1){
		return 0;	
	} else {
		while(1){
			RAND(&m.value,2000);
			xpool_add_task(&m,0);	
		}
		while(1);
		return 0;
	}
}
