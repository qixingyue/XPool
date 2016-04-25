#include "php_xpool.h"
#include "little_items.h"

ZEND_DECLARE_MODULE_GLOBALS(xpool)

static int le_xpool;

const zend_function_entry xpool_functions[] = {
	XPOOL_FUNCS
	PHP_FE_END
};

zend_module_entry xpool_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"xpool",
	xpool_functions,
	PHP_MINIT(xpool),
	PHP_MSHUTDOWN(xpool),
	PHP_RINIT(xpool),	
	PHP_RSHUTDOWN(xpool),	
	PHP_MINFO(xpool),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_XPOOL_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_XPOOL
ZEND_GET_MODULE(xpool)
#endif

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xpool.xpool_var_name", "x_run_pool", PHP_INI_ALL, OnUpdateString, xpool_var_name, zend_xpool_globals, xpool_globals)
PHP_INI_END()

PHP_MINIT_FUNCTION(xpool)
{
	REGISTER_INI_ENTRIES();
	XPOOL_STARTUP(X_Pool);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(xpool)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_RINIT_FUNCTION(xpool)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(xpool)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(xpool)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xpool support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

