#ifndef XPOOL_X_POOL_H
#define XPOOL_X_POOL_H

#include "php_xpool.h"

#define X_MAX_SIZE 1024

#define XPOOL_STATUS_OK 0
#define XPOOL_STATUS_BUSY 1
#define XPOOL_STATUS_TOO_LARGE 2

#define XPOOL_INIT_FAILED -2
#define XPOOL_INIT_OK 0
#define XPOOL_INIT_CHILD -1

extern zend_class_entry *X_Pool_class_ce;

XPOOL_STARTUP_FUNCTION(X_Pool);

#endif

