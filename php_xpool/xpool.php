<?php

if(!extension_loaded("xpool")){
	dl("xpool.so");
}


class M_Pool extends X_Pool {

	public function handle($data){
		$obj = unserialize($data);	
		echo $obj['id'] . "\n";
	}

}

//变量名必须为x_run_pool,否则，模块内部的任务回调不识别
$x_run_pool = new M_Pool();

//子进程数
$worker_count = 8;

//子进程最大的空闲周期
$max_free_tick = 256;

$res = $x_run_pool->init($worker_count,$max_free_tick);

//子进程返回，必要的时候，可以做部分清理工作
if($res == -1) {
	printf("This is child , bye ! \n");
	exit();
}

if($res == -2){
	printf("Xpool init failed . \n");
	exit();
}

//主进程部分,可以往进程池里添加数据了

while(true){
	$d = array(
		'place'=>'BJ'
		,'id'=>mt_rand(1,2000)
	);
	$x_run_pool->addTask(serialize($d));
}
