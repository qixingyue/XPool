#ifndef XPOOL_X_POOL_H
#define XPOOL_X_POOL_H

#include "php_xpool.h"

#define X_MAX_SIZE 1024

#define X_POOL_ITEM_HANDLER "itemHanlder"

extern zend_class_entry *X_Pool_class_ce;

XPOOL_STARTUP_FUNCTION(X_Pool);

#endif

