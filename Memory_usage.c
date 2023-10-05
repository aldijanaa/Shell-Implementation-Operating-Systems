#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void pauseProgram() {
    printf("Press Enter to continue...\n");
    while (getchar() != '\n');
}

int main() {
    // Run the program for a long duration
    while (1) {
        pauseProgram();

        // Print process information using `ps` command
        system("ps -p $$ -o pid,vsz,rss,cmd");

        // Access memory information from the proc filesystem
        FILE* file = fopen("/proc/self/statm", "r");
        if (file) {
            unsigned long size, resident, shared, text, lib, data, dt;
            fscanf(file, "%lu %lu %lu %lu %lu %lu %lu", &size, &resident, &shared, &text, &lib, &data, &dt);
            fclose(file);

            printf("Memory usage:\n");
            printf("Virtual Memory Size (VSZ): %lu pages\n", size);
            printf("Resident Set Size (RSS): %lu pages\n", resident);
            printf("Shared pages: %lu\n", shared);
            printf("Text (code) pages: %lu\n", text);
            printf("Library pages: %lu\n", lib);
            printf("Data + Stack pages: %lu\n", data);
            printf("Dirty pages (unused): %lu\n", dt);
        }

        sleep(1);
    }

    return 0;
}
