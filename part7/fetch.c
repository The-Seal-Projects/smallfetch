//how to make good fetch in C
//part 7

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char cpu_name[128] = "Unknown";
char os_name[128] = "Unknown";
char gpu_name[128] = "Unknown";

void os() {
    FILE *fptr = fopen("/etc/os-release", "r");
    if (fptr == NULL) {
        perror("Error opening /etc/os-release");
        return;
    }

    char line[128];

    while (fgets(line, sizeof(line), fptr)) {
        if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
            char *start = line + 12;

			if (*start == '"') {
                start++;
            }

            strncpy(os_name, start, sizeof(os_name) - 1);
            os_name[sizeof(os_name) - 1] = '\0';
            os_name[strcspn(os_name, "\"\r\n")] = '\0';
            
            break;
        }
    }

    printf("OS: %s\n", os_name);
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

///sys/class/drm/card0/device/uevent

void gpu() {
    FILE *fptr = fopen("/sys/class/drm/card0/device/uevent", "r");
    if (fptr == NULL) {
        perror("Error opening /sys/class/drm/card0/device/uevent");
        return;
    }

    char line[128];

    while (fgets(line, sizeof(line), fptr)) {
        if (strncmp(line, "DRIVER=", 7) == 0) {
            char *start = line + 7;

			if (*start == '"') {
                start++;
            }

            strncpy(gpu_name, start, sizeof(gpu_name) - 1);
            gpu_name[sizeof(gpu_name) - 1] = '\0';
            gpu_name[strcspn(gpu_name, "\"\r\n")] = '\0';
            
            break;
        }
    }

    printf("GPU: %s\n", gpu_name);
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
