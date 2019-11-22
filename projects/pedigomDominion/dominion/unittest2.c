#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int assert(int actual, int expected)
{
    if (actual == expected)
    {
        printf("Passed\n");
        return 0;
    }
    else
    {
        printf("FAILED\nActual: %d Expected: %d\n", actual, expected);
        return 1;
    }
}

int main()
{
    printf("\n\n************************ TESTING MINION ************************\n");

    struct gameState* state = newGame();
    int kingdomCards[10] = {adventurer, feast, gardens, mine, village, baron, minion, ambassador, tribute, remodel};
    
    //intialize the game
    initializeGame(4, kingdomCards, time(0), state);
    //decrease a players hand count to < 5
    state->handCount[3] = 4;
    state->hand[3][4] = -1;
    //make current player have a minion
    state->hand[0][4] = minion;
   
    //draw 5 cards for 2 players
    int i = 0;
    for (i; i < 5; i++)
    {
        drawCard(1, state);
        drawCard(2, state);
    }
   
    //test with choice being 2 coins
    printf("TESTING CHOICE TO TAKE TWO COINS\n"); 
    int preCoins = state->coins;
    cardEffectMinion(1, 0, state, 4, 0);
    assert(state->coins, state->coins+2);
    
    //Test for option 2
    
    //intialize the game
    initializeGame(4, kingdomCards, time(0), state);
    //decrease a players hand count to < 
    state->handCount[3] = 3;
    state->hand[3][4] = -1;
    state->hand[3][3] = -1;
    state->deckCount[3] += 2;
    //make current player have a minion
    state->hand[0][4] = minion;
   
    //draw 5 cards for 2 players
    i = 0;
    for (i; i < 5; i++)
    {
        drawCard(1, state);
        drawCard(2, state);
    }

   
    cardEffectMinion(0, 1, state, 4, 0);

    //Test for current player 
    printf("Current Player tests\n");
    printf("Hand: ");
    assert(state->handCount[0], 4);
    printf("Deck: ");
    assert(state->deckCount[0], 1);
    printf("Discard: ");
    assert(state->discardCount[0], 5);

    //Test for player with > 5 cards 
    printf("Player 2 (hand > 5) tests\n");
    printf("Hand: ");
    assert(state->handCount[0], 4);
    printf("Deck: ");
    assert(state->deckCount[0], 1);
    printf("Discard: ");
    assert(state->discardCount[0], 5);
   
    //Test for second player with >5 card
    printf("Player 3 (hand > 5) tests\n");
    printf("Hand: ");
    assert(state->handCount[0], 4);
    printf("Deck: ");
    assert(state->deckCount[0], 1);
    printf("Discard: ");
    assert(state->discardCount[0], 5);

    //Test for third player with <5 cards in hands
    printf("Player 3 (hand < 5) tests\n");
    printf("Hand: ");
    assert(state->handCount[0], 3);
    printf("Deck: ");
    assert(state->deckCount[0], 7);
    printf("Discard: ");
    assert(state->discardCount[0], 0);

    
    return 0;

}
