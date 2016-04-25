#!/bin/sh

module_name="$1"

u_module_name=$(echo $module_name | echo "$module_name" | sed 'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/')

j="#"

(

cat > items/${module_name}.h <<EOT

${j}ifndef SCRAW_${u_module_name}_H
${j}define SCRAW_${u_module_name}_H

${j}include "php_xpool.h"

extern zend_class_entry *${module_name}_class_ce;

SCRAW_STARTUP_FUNCTION(${module_name});

${j}endif

EOT


cat > items/${module_name}.c <<EOT

${j}include "${module_name}.h"

zend_class_entry *${module_name}_class_ce;

zend_function_entry ${module_name}_methods[] = {
	// PHP_ABSTRACT_ME(${module_name}, test, NULL) 
	// PHP_ME(${module_name}, real, NULL,ZEND_ACC_PUBLIC) 
	{NULL, NULL, NULL}
};

SCRAW_STARTUP_FUNCTION(${module_name}){
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "${module_name}", ${module_name}_methods);
	${module_name}_class_ce = zend_register_internal_class(&ce TSRMLS_CC);
	// ${module_name}_class_ce = zend_register_internal_interface(&ce TSRMLS_CC);
	// zend_declare_property_null(${module_name}_class_ce ,ZEND_STRL("testProperty"),ZEND_ACC_PUBLIC TSRMLS_DC);
}


EOT

)


(
cd items
for a in $(ls *.h)
do
	echo "#include \"items/$a\""
done
) > little_items.h

echo "COPY THIS LINE TO xpool.c "
echo "SCRAW_STARTUP(${module_name});"
