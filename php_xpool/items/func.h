#ifndef PHP_FUNC_XPOOL_H
#define PHP_FUNC_XPOOL_H

#include "php.h"
#include "php_xpool.h"

PHP_FUNCTION(simpleTest);

#define XPOOL_FUNCS \
PHP_FE(simpleTest,  NULL) 

#endif
