#include "xpool.h"

int xpool_init(int wn,int mft,x_task_handler handler,size_t tds){
	int i = 0;
	pid_t pid;
	x_list = (x_task_list *) malloc(sizeof(x_task_list) * wn);
	__task_handler = handler;
	x_task_data_size = tds;

	x_worker_num = wn;
	x_max_free_tick = mft;

	for(i=0;i<wn;i++){
		x_list[i].state = STATE_FREE;
		x_list[i].free_tick = 0;

		pipe(x_list[i].pipe);
		pipe(x_list[i].back_pipe);
		fcntl(x_list[i].pipe[0],F_SETFL,FNDELAY);
		fcntl(x_list[i].back_pipe[0],F_SETFL,FNDELAY);
	}

	for(i=0;i < wn; i++){
		pid = fork();
		if(pid == 0){
			xpool_work_loop(i);	
			return -1;
		}
	}
	return 0;
}

x_status xpool_add_task(x_task_data *data_p,int times){

	int i;
	int back_res;
	size_t read_size;

	if( 10 == times){
		return x_busy;	
	} else if( 0 == times) {
			
	} else {
		//太多的任务，没有空闲的进程
		usleep(200);
	}

	for ( i = 0 ; i < x_worker_num ; i++ ) {
		if(x_list[i].state == STATE_FREE)	{
			x_list[i].state = STATE_BUSY;
			write(x_list[i].pipe[1],data_p,x_task_data_size);
			return x_ok;
		}
	}	

	//查找空闲的子进程
	for ( i = 0 ; i < x_worker_num ; i++ ) {
		back_res = -1;
		read_size = 0;
		read_size = read(x_list[i].back_pipe[0],&back_res,sizeof(int));
		if( sizeof(int) == read_size && 1 == back_res){
			x_list[i].state = STATE_FREE;
		}
	}

	//重新插入任务
	return xpool_add_task(data_p,times + 1);
}

static void xpool_work_loop(int child_no){
	int res = 1;
	x_task_data *data = (x_task_data*) malloc(x_task_data_size);
	size_t read_size = 0;
	setsid();
	signal(SIGCHLD,SIG_IGN);
	while(1){

		read_size = 0;
		bzero(data,x_task_data_size);

		read_size = read(x_list[child_no].pipe[0],data,x_task_data_size);
		if(read_size != 0 && read_size != -1){
				x_list[child_no].free_tick = 0;
				__task_handler(data);
				res = 1;
				write(x_list[child_no].back_pipe[1],&res,sizeof(int));
		} else {
			if( x_true == x_should_exit(child_no) ){
				free(data);
				break;	
			}
		}

	}
}

static x_bool x_should_exit(int child_no){
	if( x_max_free_tick <= x_list[child_no].free_tick){
		return x_true;	
	} else {
		x_list[child_no].free_tick += 1;
		usleep(1000);
		return x_false;
	}
}
