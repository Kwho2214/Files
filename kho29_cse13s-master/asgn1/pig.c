//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "names.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {
    int players = 0;
    printf("How many players? ");
    scanf("%d", &players);

    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        players = 2;
    }

    int seed = 0;
    printf("Random seed: ");
    scanf("%d", &seed);

    if (seed < 0) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead \n");
        seed = 2021;
    }

    srandom(seed);

    int points[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    bool turn = true;
    int curr_player = 0;
    while (turn) {
        //2nd while loop to kepp rolling
        printf("%s rolls the pig...", names[curr_player]);
        while (turn) {
            int rolls = random() % 7;
            //printf("%d \n", rolls);
            if (pig[rolls] == SIDE) {
                printf(" pig lands on side\n");
                curr_player = (curr_player + 1) % players;
                printf("%s rolls the pig...", names[curr_player]);
                //printf("%d", points[curr_player]);
            }
            if (pig[rolls] == RAZORBACK) {
                printf(" pig lands on back");
                points[curr_player] += 10;
                //printf("%d", points[curr_player]);
            }
            if (pig[rolls] == TROTTER) {
                printf(" pig lands upright");
                points[curr_player] += 10;
                //printf("%d", points[curr_player]);
            }
            if (pig[rolls] == SNOUTER) {
                printf(" pig lands on snout");
                points[curr_player] += 15;
                //printf("%d", points[curr_player]);
            }
            if (pig[rolls] == JOWLER) {
                printf(" pig lands on ear");
                points[curr_player] += 5;
                //printf("%d", points[curr_player]);
            }
            if (points[curr_player] >= 100) {
                printf("\n%s wins with %d points!\n", names[curr_player], points[curr_player]);
                //to end game
                turn = false;
            }
        }
    }
    return 0;
}
