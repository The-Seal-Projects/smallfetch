//how to make good fetch in C
//part 6

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void gpu() {
	FILE *fptr;
	fptr = fopen("/sys/class/drm/card0/device/uevent", "r");
	char pregpu[128];

	fgets(pregpu, sizeof(pregpu), fptr);

	printf("GPU: ");

	for (int gpu = 7; gpu <= 15; gpu++) {
		printf("%c", pregpu[gpu]);
	}
	fclose(fptr);
}

void dewm() {
	const char *de = getenv("XDG_CURRENT_DESKTOP");
	printf("DE/WM: %s\n", de ? de : "Unknown");
}

void session() {
	const char *session = getenv("XDG_SESSION_TYPE");
	printf("Session: %s\n", session ? session : "Unknown");
}


int main () {
	os();
	cpu();
	gpu();
	dewm();
	session();
	return 0;
}
