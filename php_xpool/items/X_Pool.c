#include "X_Pool.h"
#include "xpool/xpool.h"

struct task_data {
	char buf[X_MAX_SIZE];
};

void do_real_task(struct task_data *data){
 	zval **self_pp, *retval , *arg;

	php_printf("%s\n",data->buf);

	MAKE_STD_ZVAL(arg);
	ZVAL_STRINGL(arg,data->buf,strlen(data->buf),0);

	if( 
			zend_hash_find( 
				EG(active_symbol_table),
			 	XPOOL_G(xpool_var_name),
			 	strlen(XPOOL_G(xpool_var_name)) + 1 , 
				(void**) &self_pp
			) == SUCCESS
		) {
		zend_call_method_with_1_params(self_pp,Z_OBJCE_PP(self_pp),NULL,"handle",&retval,arg);	
	} else {
			
	}
}

zend_class_entry *X_Pool_class_ce;

PHP_METHOD(X_Pool,addTask){
	struct task_data data;
	char *buf;
	int len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&buf,&len) == FAILURE) {
		return ;
	}

	if(len >= X_MAX_SIZE){
		RETURN_FALSE;	
	}

	memcpy(data.buf,buf,len);

	xpool_add_task(&data,0);
	RETURN_TRUE;
}

PHP_METHOD(X_Pool,init){
	long r,worker_count,max_free_tick;
	zval **self_pp;

	if( 
			zend_hash_find(
				EG(active_symbol_table),
			 	XPOOL_G(xpool_var_name),
				strlen(XPOOL_G(xpool_var_name)) + 1,
			 	(void**) &self_pp
			) == SUCCESS 
			&& Z_TYPE_PP(self_pp) == IS_OBJECT 
			&& instanceof_function(Z_OBJCE_PP(self_pp), X_Pool_class_ce TSRMLS_CC)
		){
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l",&worker_count,&max_free_tick) == FAILURE) {
			RETURN_LONG(-2);
		}
		r = xpool_init(worker_count,max_free_tick,do_real_task,sizeof(struct task_data) );
		RETURN_LONG(r);
	} else {
		zend_error(E_STRICT,"No %s Class object named %s found ! \n",X_Pool_class_ce->name,XPOOL_G(xpool_var_name));	
		RETURN_LONG(-2);
	}
}

PHP_METHOD(X_Pool,__construct){}


zend_function_entry X_Pool_methods[] = {
	PHP_ABSTRACT_ME(X_Pool, handle, NULL) 
	PHP_ME(X_Pool, __construct, NULL,ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) 
	PHP_ME(X_Pool, addTask, NULL,ZEND_ACC_PUBLIC) 
	PHP_ME(X_Pool, init, NULL,ZEND_ACC_PUBLIC) 
	{NULL, NULL, NULL}
};

XPOOL_STARTUP_FUNCTION(X_Pool){
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "X_Pool", X_Pool_methods);
	X_Pool_class_ce = zend_register_internal_class(&ce TSRMLS_CC);
	// X_Pool_class_ce = zend_register_internal_interface(&ce TSRMLS_CC);
	// zend_declare_property_null(X_Pool_class_ce ,ZEND_STRL("testProperty"),ZEND_ACC_PUBLIC TSRMLS_DC);
}


