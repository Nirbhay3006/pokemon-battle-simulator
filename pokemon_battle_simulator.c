#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[20];
    int health;
    int attack;
    int defense;
} Pokemon;

void displayStats(Pokemon p) {
    printf("%s - Health: %d, Attack: %d, Defense: %d\n", p.name, p.health, p.attack, p.defense);
}

int calculateDamage(int attack, int defense) {
    int baseDamage = attack - (defense / 2);
    if (baseDamage <= 0) {
        return 1; 
    }
    return baseDamage; 
}

void playerMove(Pokemon *attacker, Pokemon *defender) {
    int choice, damage;
    printf("\nChoose a move:\n");
    printf("1. Basic Attack\n");
    printf("2. Power Strike (higher damage but lower accuracy)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: 
            damage = calculateDamage(attacker->attack, defender->defense);
            printf("%s used Basic Attack!\n", attacker->name);
            break;
        case 2: 
            if (rand() % 100 < 60) {
                damage = calculateDamage(attacker->attack + 10, defender->defense);
                printf("%s used Power Strike! It's effective!\n", attacker->name);
            } else {
                damage = 0;
                printf("%s used Power Strike, but it missed!\n", attacker->name);
            }
            break;
        default: 
            printf("Invalid move! Defaulting to Basic Attack.\n");
            damage = calculateDamage(attacker->attack, defender->defense);
    }

    if (damage > 0) {
        defender->health -= damage;
        printf("%s dealt %d damage to %s!\n", attacker->name, damage, defender->name);
    } else {
        printf("No damage dealt to %s!\n", defender->name);
    }
}

void opponentMove(Pokemon *attacker, Pokemon *defender) {
    int moveChoice = rand() % 2 + 1;
    int damage;

    switch (moveChoice) {
        case 1: 
            damage = calculateDamage(attacker->attack, defender->defense);
            printf("%s used Basic Attack!\n", attacker->name);
            break;
        case 2: 
            if (rand() % 100 < 60) { 
                damage = calculateDamage(attacker->attack + 10, defender->defense);
                printf("%s used Power Strike! It's effective!\n", attacker->name);
            } else {
                damage = 0;
                printf("%s used Power Strike, but it missed!\n", attacker->name);
            }
            break;
    }

    if (damage > 0) {
        defender->health -= damage;
        printf("%s dealt %d damage to %s!\n", attacker->name, damage, defender->name);
    } else {
        printf("No damage dealt to %s!\n", defender->name);
    }
}

void selectTeam(Pokemon allPokemon[], int total, Pokemon team[], int teamSize) {
    printf("Available Pokémon:\n");
    for (int i = 0; i < total; i++) {
        printf("%d. ", i + 1);
        displayStats(allPokemon[i]);
    }

    printf("\nSelect %d Pokémon for your team (enter numbers 1-%d):\n", teamSize, total);
    for (int i = 0; i < teamSize; i++) {
        int choice;
        printf("Select Pokémon %d: ", i + 1);
        scanf("%d", &choice);
        if (choice >= 1 && choice <= total) {
            team[i] = allPokemon[choice - 1];
        } else {
            printf("Invalid choice. Try again.\n");
            i--;
        }
    }
}

int main() {
    srand(time(NULL)); 

    printf("WELCOME TO POKEMON BATTLE SIMULATOR!!\n\n");
    printf("Choose your Pokémon and battle to become the Champion!\n\n");
    Pokemon allPokemon[] = {
        {"Pikachu", 110, 30, 20},
        {"Charizard", 120, 40, 30},
        {"Blastoise", 110, 35, 40},
        {"Venasaur", 130, 35, 35},
        {"Dragonite", 125, 45, 35},
        {"Gengar", 110, 45, 25},
    };
    int totalPokemon = sizeof(allPokemon) / sizeof(allPokemon[0]);
    
    Pokemon playerTeam[3], opponentTeam[3];

    printf("Player, select your team:\n\n");
    selectTeam(allPokemon, totalPokemon, playerTeam, 3);

    printf("\nOpponent is selecting their team...\n");
    for (int i = 0; i < 3; i++) {
        opponentTeam[i] = allPokemon[rand() % totalPokemon];
    }
    printf("Opponent team selected!\n");

    int playerIndex = 0, opponentIndex = 0;

    while (playerIndex < 3 && opponentIndex < 3) {
        printf("\nYour Pokémon: %s (HP: %d)\n", playerTeam[playerIndex].name, playerTeam[playerIndex].health);
        printf("Opponent's Pokémon: %s (HP: %d)\n", opponentTeam[opponentIndex].name, opponentTeam[opponentIndex].health);

        playerMove(&playerTeam[playerIndex], &opponentTeam[opponentIndex]);

        if (opponentTeam[opponentIndex].health <= 0) {
            printf("%s has fainted!\n", opponentTeam[opponentIndex].name);
            opponentIndex++;
            continue;
        }
        
        opponentMove(&opponentTeam[opponentIndex], &playerTeam[playerIndex]);
        
        if (playerTeam[playerIndex].health <= 0) {
            printf("%s has fainted!\n", playerTeam[playerIndex].name);
            playerIndex++;
        }
    }

    if (playerIndex == 3) {
        printf("\nAll your Pokémon have fainted! You lose.\n");
    } else if (opponentIndex == 3) {
        printf("\nAll opponent's Pokémon have fainted! You win!\n");
    }

    return 0;
}