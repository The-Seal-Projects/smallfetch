//how to make good fetch in C

#include <stdio.h>

int main () {
	FILE *fptr;
	fptr = fopen("/etc/os-release", "r");
	char os [128];
	fgets(os, 128, fptr);
	printf("%s", os);

	fclose(fptr);
}
