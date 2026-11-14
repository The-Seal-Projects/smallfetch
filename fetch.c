//how to make good fetch in C
//part 4

#include <stdio.h>
#include <string.h>

char cpu_name[128] = "Unknown";

void os() {
	FILE *fptr;
	fptr = fopen("/etc/os-release", "r");
	char preos [128];
	fgets(preos, sizeof(preos), fptr);

	printf("OS: ");

	for (int os = 13; os < 31; os++) {
		printf("%c", preos[os]);
	}
	printf("\n");

	fclose(fptr);

}

void cpu() {
	FILE *fptr;
	fptr = fopen("/proc/cpuinfo", "r");
	char precpu[128];

	while (fgets(precpu, sizeof(precpu), fptr)) {
		if (strncmp(precpu, "model name", 10) == 0) {
			//strchr
			char *colon = strchr(precpu, ':');
			if (colon != NULL) {
				strcpy(cpu_name, colon + 2);
			}
			break;
		}
	}

	printf("CPU: %s", cpu_name);
	fclose(fptr);
}

int main () {
	os();
	cpu();
	return 0;
}
