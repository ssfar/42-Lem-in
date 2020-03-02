#include "string.h"
#include "stdlib.h"
#include "stdio.h"

int main(void)
{
	char *str;

	str = malloc(sizeof(char) * 11);
	str = strcpy(str, "hello world");
	str++;
	printf("%s\n", str);
	free(str);
}