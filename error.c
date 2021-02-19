#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

void error(const char *msg, ...)
{
	va_list args;
	
	printf("error: ");
	va_start(args, msg);
	vprintf(msg, args);
	va_end(args);
	printf("\n");
	exit(1);
}
