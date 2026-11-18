#include <stdio.h>
#include <string.h>

int main() {
    // part 1 *paling dasar
    char buffer[100];
    char nama[100];
    int umur;

    // input nama

    printf("Masukkan namamu: ");
    fgets(nama, sizeof(nama), stdin);

    //untuk menghilangkan \n
    nama[strcspn(nama, "\n")] = 0;

    //Input umur

    printf("Masukkan umurmu: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &umur);

    //Format output
    printf("\nSelf Introduction\nNama\t: %s\nUmur \t: %d tahun\nDan di tahun depan umurmu menjadi %d tahun!\n", nama, umur, umur + 1);

    //Age validation
    if (umur >= 17) {
        printf("Status: Kamu sudah wajib punya KTP!\n");
    } else {
        printf("Status: Kamu belum cukup umur buat bikin KTP!\n");
    }

    return 0;
}