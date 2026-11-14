//how to make good fetch in C
//part 2222222

#include <stdio.h>

int main () {
	FILE *fptr;
	fptr = fopen("/etc/os-release", "r");
	char preos [128];
	fgets(preos, sizeof(preos), fptr);

	for (int os = 13; os < 31; os++) {
		printf("%c", preos[os]);
	}
	printf("\n");

	fclose(fptr);
}
