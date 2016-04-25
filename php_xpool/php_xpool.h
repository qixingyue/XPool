#ifndef PHP_XPOOL_H
#define PHP_XPOOL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_interfaces.h"

extern zend_module_entry xpool_module_entry;
#define phpext_xpool_ptr &xpool_module_entry

#define PHP_XPOOL_VERSION "0.1.0" 

#ifdef PHP_WIN32
#	define PHP_XPOOL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_XPOOL_API __attribute__ ((visibility("default")))
#else
#	define PHP_XPOOL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(xpool);
PHP_MSHUTDOWN_FUNCTION(xpool);
PHP_RINIT_FUNCTION(xpool);
PHP_RSHUTDOWN_FUNCTION(xpool);
PHP_MINFO_FUNCTION(xpool);

ZEND_BEGIN_MODULE_GLOBALS(xpool)
	char *xpool_var_name;
ZEND_END_MODULE_GLOBALS(xpool)

extern ZEND_DECLARE_MODULE_GLOBALS(xpool);

#ifdef ZTS
#define XPOOL_G(v) TSRMG(xpool_globals_id, zend_xpool_globals *, v)
#else
#define XPOOL_G(v) (xpool_globals.v)
#endif

#define XPOOL_STARTUP_FUNCTION(module)   	ZEND_MINIT_FUNCTION(xpool_##module)
#define XPOOL_STARTUP(module)	 		  	ZEND_MODULE_STARTUP_N(xpool_##module)(INIT_FUNC_ARGS_PASSTHRU)

#define DEBUG 0
#define S_PRINT if(DEBUG) php_printf

#define SEE_ZVAL(name,zp) php_printf("\nBEGIN SEE ZVAL %s \n",name); zend_print_zval_r(zp,0 TSRMLS_CC); php_printf("END SEE ZVAL %s \n",name);

#endif
