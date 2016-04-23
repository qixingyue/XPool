#ifndef _XPOOL_MAIN_H
#define _XPOOL_MAIN_H

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define STATE_FREE 0
#define STATE_BUSY 1 

typedef enum { x_false , x_true } x_bool ;  


//一个子进程对应的基本单位
typedef struct {
	int pipe[2];
	int back_pipe[2];
	int state;
	int free_tick;
} x_task_list;

struct x_task_data;
typedef struct x_task_data x_task_data;

typedef void (*x_task_handler)(x_task_data*);

int xpool_init(int,int,x_task_handler,size_t);
void xpool_add_task(x_task_data*,int);
static void xpool_work_loop(int child_no);
static x_bool x_should_exit();

static x_task_handler __task_handler;
static int x_worker_num;
//子进程超过这么多周期没有数据以后，退出
static int x_max_free_tick;
static size_t x_task_data_size;
static x_task_list *x_list;

#endif
