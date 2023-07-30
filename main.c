#include <stdio.h> // standar input output C
#include <stdlib.h> // standar library C
#include <string.h> // Biar bisa make String
#include <conio.h>
#include <stdbool.h> // Biar bisa make Boolean

// Final Project Fundamental Algoritma C Course
// Membuat Basic System RPG Game
// Built by Fadel Achmad Daniswara, Teknik Elektro UI 2022


// Data Monster
typedef struct{
    char name[50];
    int monsterHealth;
    int expGained;
    int goldGained;
    int monsterDamage;

}monster;

// Data Player
typedef struct{
    char name[50];
    int heroHealth;
    int basicAttack;
    int skillAttack;

}classes;

int isNew = false;
// Array of Struct Monsters
monster monsters[] = {
    {"Goblin", 150, 15, 15, 10},
    {"Wolf", 120, 15, 15, 10},
    {"Insect", 120, 15, 15, 10},
    {"Elf", 150, 15, 15, 10}
};

// Array of Struct Hero
classes hero[] = {
    {"Knight", 150, 12, 20, 100},
    {"Archer", 120, 15, 30, 100},
    {"Tanker", 200, 10, 20, 100},
    {"Assassin", 130, 15, 30, 100},
    {"Mage", 110, 15, 35, 100}
};

// Character
typedef struct{
    char charName[50];
    classes hero;
    int charExp;
    int charGold;
    int charHealth;
    int charLevel;
}character;

character playerCharacter;
// Buat Class
classes loadClass(char x[]){
    if(strcmp(x, "Knight")== 0){
        playerCharacter.hero = hero[0];
    }
    else if(strcmp(x, "Archer") == 0){
        playerCharacter.hero = hero[1];
    }
    else if(strcmp(x, "Tanker") == 0){
        playerCharacter.hero = hero[2];
    }
    else if(strcmp(x, "Assassin") == 0){
        playerCharacter.hero = hero[3];
    }
    else{ // Mage
        playerCharacter.hero = hero[4];
    }
    return playerCharacter.hero;
}
// New Game
void newGame(){
    char tempClass[200];

    printf("Input your character name : ");
    scanf("%s", playerCharacter.charName); getchar();

    do{
        printf("Choose your class [Knight|Archer|Tanker|Assassin|Mage] : ");
        scanf("%s", tempClass); getchar();
    }while(strcmp(tempClass, "Knight") == 1 &&
           strcmp(tempClass, "Archer") == 1 &&
           strcmp(tempClass, "Tanker") == 1 &&
           strcmp(tempClass, "Assassin") == 1 &&
           strcmp(tempClass, "Mage") == 1);
    playerCharacter.charExp = 0;
    playerCharacter.charLevel = 1;
    playerCharacter.charGold = 0;

    playerCharacter.charHealth = loadClass(tempClass).heroHealth;
    saveAccount();
}
// Save Account
void saveAccount(){
    FILE *fp;
    fp = fopen("account.txt", "w");
    fprintf(fp, "%s#%s#%d#%d#%d#%d#",
           playerCharacter.charName,
           playerCharacter.hero.name,
           playerCharacter.charExp,
           playerCharacter.charLevel,
           playerCharacter.charGold,
           playerCharacter.charHealth);
    fclose(fp);
}
// Load Account
void loadAccount(){
    FILE *fp;
    fp = fopen("account.txt", "r");
    char tempClass[200]; // Buat ngecek Classnya apa
    // Load Account karakter
    if(fp == NULL){ // Karakter Baru
        isNew = true;
        fclose(fp);
        return;
    }
    // Sudah ada karakter, tinggal nge load Account
    fscanf(fp, "%[^#]#%[^#]#%d#%d#%d#%d#",
           playerCharacter.charName, tempClass,
           &playerCharacter.charExp,
           &playerCharacter.charLevel,
           &playerCharacter.charGold,
           &playerCharacter.charHealth);
    fclose(fp);
    loadClass(tempClass);
}
// Menu Pertama
void firstMenu(){
    int input;
    do{
        printf("1. New Game\n");
        if(!isNew){
            printf("2. Continue Game\n");
        }
        printf(">> ");
        scanf("%d", &input); getchar();
        switch(input){
            case 1:
                newGame();
            break;

        }
    }while(input > (isNew == true ? 1 : 2) || input < 1);
}
// Fighting Monsters
void fight(monster m){
    int input;

    int exp = m.expGained;
    int gold = m.goldGained;
    int damage = m.monsterDamage;
    int health = m.monsterHealth;
    char name[100];
    strcpy(name, m.name);

    do{
        system("cls");
        printf("%s\nHealth : %d\nDamage : %d\n\n", name, health, damage);
        printf("%s\nHealth : %d\nBasic Attack Damage : %d\nSkill Attack Damage : %d\n\n", playerCharacter.charName,
                                                    playerCharacter.charHealth,
                                                    playerCharacter.hero.basicAttack,
                                                    playerCharacter.hero.skillAttack);
        printf("1. Basic Attack\n");
        printf("2. Skill Attack\n");
        printf("3. Run\n");
        printf(">> ");

        scanf("%d", &input); getchar();

        switch(input){ //Player menang atau berhasil ngebunuh monster
            case 1:
                health -= playerCharacter.hero.basicAttack;
                if(health <= 0){
                    playerCharacter.charGold += gold;
                    playerCharacter.charExp += exp;
                    printf("You killed a monster\nYou gained %d gold and %d exp\n", gold, exp);
                    // Level Up
                    if(playerCharacter.charExp >= 100){
                        printf("You've leveled up!\n");
                        playerCharacter.charExp -= 100;
                        playerCharacter.charLevel += 1;
                    }
                    printf("Press any key to continue...");
                    getchar();
                    return;
                }
                playerCharacter.charHealth -= damage;
                if(playerCharacter.charHealth <= 0){ // Player kalah atau tidak berhasil ngebunuh monster
                    playerCharacter.charGold = 0;
                    playerCharacter.charExp = 0;
                    playerCharacter.charHealth = playerCharacter.hero.heroHealth;
                    printf("You lose\nYou lost all your golds and exps\n");
                    printf("Press any key to continue...");
                    getchar();
                    return;
                }
            break;
            case 2:
                health -= playerCharacter.hero.skillAttack;
                if(health <= 0){
                    playerCharacter.charGold += gold;
                    playerCharacter.charExp += exp;
                    printf("You killed a monster\nYou gained %d gold and %d exp\n", gold, exp);
                    // Level Up
                    if(playerCharacter.charExp >= 100){
                        printf("You've leveled up!\n");
                        playerCharacter.charExp -= 100;
                        playerCharacter.charLevel += 1;
                    }
                    printf("Press any key to continue...");
                    getchar();
                    return;
                }
                playerCharacter.charHealth -= damage;
                if(playerCharacter.charHealth <= 0){ // Player kalah atau tidak berhasil ngebunuh monster
                    playerCharacter.charGold = 0;
                    playerCharacter.charExp = 0;
                    playerCharacter.charHealth = playerCharacter.hero.heroHealth;
                    printf("You lose\nYou lost all your golds and exps\n");
                    printf("Press any key to continue...");
                    getchar();
                    return;
                }
            break;
            case 3:
                printf("You ran away!\n");
                printf("Press any key to continue...");
                getchar();
                return;
        }
    }while(true);
}

// Fight Menu
void fightMenu(){
    int input;
    do{
        system("cls");
        printf("Fight Menu\n=============\n");
        printf("1. Goblin\n");
        printf("2. Wolf\n");
        printf("3. insect\n");
        printf("4. Dark Elf\n");
        printf("5. Back\n");
        printf(">> ");

        scanf("%d", &input); getchar();

        switch(input){
            case 1:
                fight(monsters[0]);
                break;
            case 2:
                fight(monsters[1]);
                break;
            case 3:
                fight(monsters[2]);
                break;
            case 4:
                fight(monsters[3]);
                break;
        }
    }while(input != 5);
}
// HeaL Menu
void healMenu(){
    int gold = playerCharacter.charGold;
    int healPrice = 20;

    if(playerCharacter.charHealth == playerCharacter.hero.heroHealth){
        printf("You're already at max health\n");
    }
    else if(gold >= healPrice){
        int input;
        do{
            printf("Do you want to heal for %d gold ?\n", healPrice);
            printf("1. Yes\n");
            printf("2. No\n");
            printf(">> ");
            scanf("%d", &input); getchar();
        }while(input != 1 && input != 2);

        if(input == 2){
            printf("Press any key to continue...");
            getchar();
            return;
        }
        playerCharacter.charHealth = playerCharacter.hero.heroHealth;
        playerCharacter.charGold -= healPrice;
        printf("Healed Succesfully!\n");


    }
    else if(gold <= healPrice){
        printf("You dont have enough gold!\n");
    }
    printf("Press any key to continue...");
    getchar();
}
// Main Function
int main()
{
    loadAccount();
    int input;

    firstMenu();
    // Loop Pilihan
    do{
        system("cls");
        printf("%s's Status\n================\n\n", playerCharacter.charName);
        printf("Class : %s\nLevel : %d\nEXP : %d/100\nGold : %d\nHealth : %d/%d\n\n",
               playerCharacter.hero.name, playerCharacter.charLevel, playerCharacter.charExp,
               playerCharacter.charGold, playerCharacter.charHealth,playerCharacter.hero.heroHealth);
        printf("1. Attack\n");
        printf("2. Heal\n");
        printf("3. Save\n");
        printf("4. Quit Game\n");
        printf(">> ");
        // Menerima Input
        scanf("%d", &input); getchar();

        // Main Menu
        switch(input){
            case 1:
                fightMenu();
                break;
            case 2:
                healMenu();
                break;
            case 3:
                saveAccount();
                printf("Saved Succesfully!!\nPress any key to continue...");
                getchar();
                break;
        }
    }while(input != 4);
    return 0;
}
