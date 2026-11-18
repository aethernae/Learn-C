#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("penggunaan : %s <nama_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if(file == NULL) {
        printf("Gagal membuka file : %s\n", argv[1]);
        return 1;
    }

    unsigned char buffer[16];
    size_t bytes_read;
    size_t offset = 0;

    printf("=== Mini HexDump : %s ===\n", argv[1]);

    while((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        printf("%08ZX  ", offset);

        for (size_t i = 0; i < 16; i++) {
            if ( i < bytes_read) {
                printf("%02X", buffer[i]);
            } else {
                printf("   ");
            }
        }

        printf(" |");

        for (size_t i = 0; i < bytes_read; i++) {
            if(isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }
        printf("|\n");

        offset += bytes_read;
    }

    fclose(file);
    return 0;
}