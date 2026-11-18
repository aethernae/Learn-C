#include <stdio.h>

void tambahAtk(int *atkPtr) {
    *atkPtr = *atkPtr + 500;
}

int main() {
    int atkHero = 1000;

    printf("1. Atk Awal \t\t: %d\n", atkHero);
    printf("2. Alamat RAM atkHero \t: %p\n", (void *)&atkHero);

    tambahAtk(&atkHero);
    
    printf("3. Atk Setelah Buff \t: %d\n", atkHero);

    return 0;
}