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
    int i;
    struct gameState* state = newGame();
    int kingdomCards[10] = {adventurer, feast, gardens, mine, village, baron, 
                            minion, ambassador, tribute, remodel};

    printf("\n\n******************** TESTING AMBASSADOR ********************\n\n");
    initializeGame(3, kingdomCards, time(0), state);
    for (i=0; i < 5; i++)
    {
        drawCard(1, state);
        drawCard(2, state);
    }
    for(i = 0; i < 4; i++)
    { 
        printf("hand count player %d: %d\n", i, state->handCount[i]);
    }
    int choice1 = 0;
    state->hand[0][4] = ambassador;
    state->hand[0][0] = copper;

    printf("Testing choice2 too high...\n");
    assert(cardEffectAmbasssador(choice1, 3, state, 4, 0), -1);
    
    //Test ic hoice2 is too low
    printf("Testing if choice2 too low...\n");
    assert(cardEffectAmbasssador(choice1, -1, state, 4, 0), -1);
    
    //Test if your choice of card is ambassador
    for (i=1; i<4; i++)
    {
        state->hand[0][i] = estate;
    }
    printf("Testing if choice1 is card being played...\n");
    assert(cardEffectAmbasssador(4, 1, state, 4, 0), -1);
    
    //Test if you don't have enough of choice1
    printf("Testing if there are not enough copies of choice 1...\n");
    state->hand[0][1] = copper;
    assert(cardEffectAmbasssador(choice1, 2, state, 4, 0), -1);
  
    //Test with no errors
    printf("Testing with enough copies...\n");
    int hand = state->handCount[0];
    int prevSupply = state->supplyCount[state->hand[0][choice1]];
    int discardCount1 = state->discardCount[1];
    int discardCount2 = state->discardCount[2];
    cardEffectAmbasssador(choice1, 1, state, 4, 0);
    printf("Testing if supply was incremented...\n");
    assert(state->supplyCount[state->hand[0][choice1]], prevSupply+1);
    printf("Testing if discard count of player 1 increased by 2...\n");
    assert(state->discardCount[1], 2);
    printf("Testing if discard count of player 2 increased by 2...\n");
    assert(state->discardCount[2], 2);
    printf("Testing if hand count of current player is decremented...\n");
    assert(state->handCount[0], hand - 3);
    printf("Testing if discard pile of current player is trashed not discard...");
    assert(state->discardCount[0], 0);
    
    return 0;
}
