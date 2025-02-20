#include <stdio.h>

#define DEBUG
#define VERSION 2

int main()
{
#ifdef DEBUG
	printf("Debug mode\n");
#endif

#ifndef RELEASE
	printf("Not a Release\n");
#endif

#if VERSION == 1
	printf("Version 1\n");
#elif VERSION == 2
	printf("Version 2\n");
#else
	#error "Unsupported.\n"
#endif

#ifdef DEBUG
	printf("Performing additional debug checks...\n");
#endif

#line 100 "custom_file.c"

	printf("Code from %s at line %d.\n", __FILE__, __LINE__);
	return 0;
}
