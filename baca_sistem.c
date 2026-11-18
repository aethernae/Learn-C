#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  while(1) {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
      printf("Gagal membuka file /proc/meminfo!\n");
      return 1;
    }

    char line[256];
    long total_ram = 0;
    long avail_ram = 0;

    while (fgets(line, sizeof(line), file)) {
      sscanf(line, "MemTotal : %ld kB", &total_ram);
      sscanf(line, "MemAvailable : %ld kB", &avail_ram);
    }
    fclose(file);

    long used_ram = total_ram - avail_ram;
    float persen= ((float)used_ram / total_ram) * 100;

    printf("\033[H\033[J");

    printf("=== RAM Monitor (Project 1) ===\n");
    printf("Total RAM : %.2f GB\n", (float)total_ram / 1048576);
    printf("RAM Terpakai : %.2f GB (%.2f%%)\n", (float)used_ram / 1048576, persen);

    sleep(1);
  }

  return 0;
}
