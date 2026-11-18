#include <inttypes.h>
#include <stdio.h>
#include <string.h>

void header() {
    printf("\n================================\n");
    printf("   RPG Stats & Dmg Calculator   \n");
    printf("================================\n");
}

float damageCalculator(int atk, int def, float multiplier){
    float rawDamage = (float)atk * multiplier;
    float finalDamage = rawDamage - ((float)def * 0.4f);

    if (finalDamage < 0.0f) {
        finalDamage = 0.0f;
    }
    return finalDamage;
}

void statSheet(char hero[], int atk, int def, float damage) {
    printf("\n================================\n");
    printf("       Summary Stats Hero       \n");
    printf("================================\n");
    printf("Nama Hero \t: %s\n", hero);
    printf("Base Attack \t: %d\n", atk);
    printf("Enemy Defense \t: %d\n", def);
    printf("Final Damage \t: %.2f HP\n", damage);
    if (damage > 500.0f){
        printf("Evaluasi \t: CRITICAL HIT!\n");
    } else {
        printf("Evaluasi \t: NORMAL HIT\n");
    }
    printf("================================\n");
}

int main() {
    char buffer[100];
    char namaHero[100];
    int atk, def;
    float multiplier;

    header();

    // input char name
    printf("Masukkan Nama Hero \t: ");
    fgets(namaHero, sizeof(namaHero), stdin);
    namaHero[strcspn(namaHero, "\n")] = 0;

    //input char attack stats
    printf("Masukkan Base Attack \t: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &atk);

    //input enemy defense stats
    printf("Masukkan Defense Musuh \t: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &def);

    //input multiplier
    printf("Masukkan multiplier \t: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &multiplier);
    
    float totalDamage = damageCalculator(atk, def, multiplier);
    statSheet(namaHero, atk, def, totalDamage);

    return 0;
}


