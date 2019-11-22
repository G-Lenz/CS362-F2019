#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int cardEffectBaron(int choice1, struct gameState *state, int currentPlayer);
int cardEffectMinion(int choice1, int choice2, struct gameState *state, 
                int handPos, int currentPlayer);
int cardEffectAmbasssador(int choice1, int choice2, struct gameState *state, 
                int handPos, int currentPlayer);
int cardEffectTribute(struct gameState *state, int *tributeRevealedCards, 
                int currentPlayer);
int cardEffectMine(int choice1, int choice2, struct gameState *state, 
                int handPos, int currentPlayer);

#endif
