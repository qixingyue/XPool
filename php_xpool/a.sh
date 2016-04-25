#!/bin/bash

PHP_BIN=/data0/php/bin/

make clean
${PHP_BIN}phpize
./configure --with-php-config=${PHP_BIN}php-config
make
sudo make install

${PHP_BIN}php xpool.php
