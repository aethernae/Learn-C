#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen() { printf("\033[H\033[2J"); }

void waitUserInput() {
  printf("Waiting User Input...                  ");
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int optionEvent(char *prompt, int min, int max, int defaultVal) {
  char buffer[100] = {0};
  int choice = 0;

  while (1) {
    /* code here */
    printf("%s", prompt);
    if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Input Stream Closed. Exiting...\n");
      exit(0);
    }

    if(buffer[0] == '\n' && defaultVal >= min && defaultVal <= max) {
      return defaultVal;
    }

    if (sscanf(buffer, "%d", &choice) == 1 && choice >= min && choice <= max) {
      return choice;
    }

    printf("Invalid input! Please input number between %d-%d\n", min, max);
    waitUserInput();
    return -1;
  }
}

void grindBattle(int *hp, int *mp, int def, int atk, int *gold, float skillMult){
  int enemyHp = 50;
  int enemyAtk = 18;

  while (enemyHp > 0 && *hp > 0) {
      clearScreen();

      printf("=== Slime Found ===\n");
      printf("Hero Hp : %d | Mp : %d | VS Slime Hp : %d\n\n", *hp, *mp, enemyHp);
      printf("1. Basic Attack (0 Mp)\n");
      printf("2. Heavy Skill (20 Mp)\n");
      printf("3. Run\n");

      int act = optionEvent("\nAction [Input Number & Enter to Submit]\n\n", 1, 3, 1);
      if( act == -1) continue;
      if( act == 3 ) return;

      if(act == 1) {
        enemyHp -= atk;
        printf("Basic Attack, Deal -%d Dmg!\n", atk);
      } else if (act == 2) {
        if (*mp >= 20) {
          *mp -= 20;
          int dmg = (int)(atk * skillMult);
          enemyHp -= dmg;
          printf("Heavy Skill, Deal -%d Dmg!\n", dmg);
        } else {
          printf("Mp Insufficient\n");
        }
      }
      if(enemyHp > 0) {
        int dmgTaken = (enemyAtk - def > 0) ? (enemyAtk - def) : 1;
        *hp -= dmgTaken;
        printf("Slime Deal -%d Dmg!\n", dmgTaken);
      } else {
        break;
      }
      waitUserInput();
  }
  if (*hp > 0) {
    *gold += 25;
    printf("\n=== Slime has been defeated ===\n\n");
    waitUserInput();
  }
}

void startScreen() {
  printf("\n========================================\n");
  printf("||             Dungeon RPG            ||\n");
  printf("========================================");
  printf("\n||                                    ||");
  printf("\n||       [Press Enter to Start]       ||");
  printf("\n||                                    ||");
  printf("\n========================================\n\n");
}

int menuScreen() {
  printf("\n========================================\n");
  printf("||             Screen Menu            ||\n");
  printf("========================================");
  printf("\n||                                    ||");
  printf("\n||         1. [Start Game]            ||");
  printf("\n||         2. [Exit]                  ||");
  printf("\n||                                    ||");
  printf("\n========================================\n\n");

  return optionEvent("Choose Menu...                         ", 1, 2, 1);
}

int exitConfirmScreen() {
  printf("\n========================================\n");
  printf("||            Exit Confirm            ||\n");
  printf("========================================");
  printf("\n||                                    ||");
  printf("\n||         1.   [Cancel]              ||");
  printf("\n||         2.   [Exit]                ||");
  printf("\n||                                    ||");
  printf("\n========================================\n\n");

  return optionEvent("Choose Menu...                         ", 1, 2, 1);
}


void showStats(int hp, int mp, int maxMp, int maxHp, int atk, int def, int gold,
               float skillMult) {
  clearScreen();
  printf("\n========================================\n");
  printf("||           Hero's Stats             ||\n");
  printf("========================================\n");
  printf("|| HP \t\t\t: %d/%d     ||\n", hp, maxHp);
  printf("|| MP \t\t\t: %d/%d     ||\n", mp, maxMp);
  printf("|| ATK \t\t\t: %d          ||\n", atk);
  printf("|| DEF \t\t\t: %d          ||\n", def);
  printf("|| Skill Multiplier \t: %.1f%%        ||\n", skillMult);
  printf("========================================\n");
}

void skillShop(int *hp, int maxHp, int *mp, int maxMp, int *atk, int *def,
               int *gold, float *skillMult) {

  while (1) {
    clearScreen();

    printf("\n=============================================\n");
    printf("||            ||| Skill Shop |||           ||\n");
    printf("=============================================\n");
    printf("|| Gold : %d | HP : %d/%d | MP : %d/%d ||\n", *gold, *hp, maxHp,
           *mp, maxMp);
    printf("=============================================\n");
    printf("|| 1. Rest (Restore HP + MP) \t[20 Gold]  ||\n");
    printf("|| 2. Upgrade ATK (5) \t\t[10 Gold]  ||\n");
    printf("|| 3. Upgrade DEF (5) \t\t[10 Gold]  ||\n");
    printf("|| 4. Upgrade multiplier (0.2) \t[30 Gold]  ||\n");
    printf("|| 5. Back                                 ||\n");
    printf("=============================================\n\n");

    int choice = optionEvent("Choose Menu...                         ", 1, 5,-1);
    if (choice == -1){
      continue;
    }
    switch (choice) {
    case 1:
      if (*hp == maxHp && *mp == maxMp) {
        printf("HP & MP Already full!\n");
      } else if (*gold >= 20) {
        *gold -= 20;
        *hp = maxHp;
        *mp = maxMp;

        printf("HP & MP has been fully restored\n");
      } else {
        printf("Insufficient gold!\n");
      }
      break;

    case 2:
      if (*gold >= 10) {
        *gold -= 10;
        *atk += 5;

        printf("Atk +%d! (+5)\n", *atk);
      } else {
        printf("Insufficient gold!\n");
      }
      break;

    case 3:
      if (*gold >= 10) {
        *gold -= 10;
        *def += 5;

        printf("Def +%d! (+5)\n", *def);
      } else {
        printf("Insufficient gold!\n");
      }
      break;

    case 4:
      if (*gold >= 30) {
        *gold -= 30;
        *skillMult += 0.2;

        printf("Skill Multiplier +%.1fx! (+0.2)\n", *skillMult);
      } else {
        printf("Insufficient gold!\n");
      }
      break;

    case 5:
      return;
    }

    waitUserInput();
  }
}

void playGame() {
  int hp = 100;
  int maxHp = 100;
  int mp = 100;
  int maxMp = 100;
  int atk = 15;
  int def = 10;
  int gold = 50;
  float skillMult = 1.5f;

  while (1) {
    clearScreen();

    printf("\n========================================\n");
    printf("||           Game Started             ||\n");
    printf("========================================\n");
    printf("||  HP : %d/%d  |||    Gold : %d    ||\n", hp, maxHp, gold);
    printf("========================================");
    printf("\n||                                    ||");
    printf("\n||           1.  [Grind]              ||");
    printf("\n||           2.  [Stats]              ||");
    printf("\n||           3.  [Skill Shop]         ||");
    printf("\n||           4.  [Back]               ||");
    printf("\n||                                    ||");
    printf("\n========================================\n\n");

    int action = optionEvent("Choose Menu...                         ", 1, 4, -1);

    switch (action) {
    case 1:
      grindBattle(&hp, &mp, def, atk, &gold, skillMult);
      if(hp <= 0){
        printf("\n=== Game Over ===\n");
        waitUserInput();
        return;
      }
      break;
    case 2:
      showStats(hp, mp, maxMp, maxHp, atk, def, gold, skillMult);
      waitUserInput();
      break;
    case 3:
      skillShop(&hp, maxHp, &mp, maxMp, &atk, &def, &gold, &skillMult);
      break;
    case 4:
      return;
    }
  }
}

int main() {
  clearScreen();
  startScreen();
  waitUserInput();

  while (1) {
    /* code here */
    clearScreen();
    int userChoice = menuScreen();

    switch (userChoice) {
    case 1:
      playGame();
      break;

    case 2: {
      clearScreen();
      int confimedExit = exitConfirmScreen();

      if (confimedExit == 2) {
        /* code here */
        printf("Thanks for Playing!");
        return 0;
      }
      break;
    }
    }
  }

  return 0;
}