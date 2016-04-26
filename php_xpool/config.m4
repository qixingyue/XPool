PHP_ARG_ENABLE(xpool, whether to enable xpool support,
Make sure that the comment is aligned:
[  --enable-xpool           Enable xpool support])


if test -z "$PHP_DEBUG" ; then
	AC_ARG_ENABLE(debug,
		[--enable-debug compile with debugging system],
		[PHP_DEBUG=$enableval],[PHP_DEBUG=no]
	)
fi

if test "$PHP_SCRAW" != "no"; then
PHP_NEW_EXTENSION(xpool, xpool.c \
		items/func.c \
		items/X_Pool.c \
		xpool/xpool.c \
		, $ext_shared)
	PHP_ADD_BUILD_DIR([$ext_builddir/items])
fi
