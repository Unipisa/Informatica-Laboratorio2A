#include <stdio.h>
#define TO_STRING(x) #x

int main(){
	printf("%s\n", TO_STRING(2*3));
	return 0;
}