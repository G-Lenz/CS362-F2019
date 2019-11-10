#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    int tributeRevealedCards[2];
    printf("\n\n******************** TESTING TRIBUTE ********************\n\n");
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

    //Testing with one card in discard and 0 in deck
    printf("TESTING ONE ACTION IN DISCARD,0 IN DECK...\n");
    state->discardCount[1] = 1;
    memset(state->deck[1], -1, sizeof(state->deck[1]));
    memset(state->discard[1], -1, sizeof(state->discard[1]));
    state->discard[1][0] = tribute;
    state->deckCount[1] = 0;
    int prevActions = state->numActions;
    tributeEffect(state, tributeRevealedCards, 0, 1);
    printf("checking if actions incremented by 2\n");
    assert(state->numActions, prevActions + 2);
   
    //testing with only one card in deck and 0 in discard
    printf("TESTING ONE CARD IN DECK, 0 in DISCARD...\n");
    initializeGame(3, kingdomCards, time(0), state);
    for (i=0; i < 5; i++)
    {
        drawCard(1, state);
        drawCard(2, state);
    }

    state->deckCount[1] = 1;
    state->discardCount[1] =0;
    state->deck[1][0] = estate;
    int prevHandCount = state->handCount[0];
    int prevDeckCount = state->deckCount[0];
    tributeEffect(state, tributeRevealedCards, 0, 1);
    printf("checking if hand count incremented by 2\n");
    assert(state->handCount[0], prevHandCount + 2);
    printf("checking if deck count decremented by 2\n");
    assert(state->deckCount[0] , prevDeckCount - 2);
    
    //Test with multiple card in discard and 0 in deck
    printf("TESTING WITH MULTIPLE CARDS IN DISCARD, 0 IN DECK...\n");
    initializeGame(3, kingdomCards, time(0), state);

    for(i = 0; i < state->deckCount[1]; i++)
    {
        state->discard[1][i] = copper;
        state->deck[1][i] = -1;
        state->discardCount[1]++;
        state->deckCount[1]--;
    } 

    int prevCoins = state->coins;

    tributeEffect(state, tributeRevealedCards, 0, 1);
    printf("checking if coins increased by 2\n");
    assert(state->coins, prevCoins + 2);
    
    
    //Test with multiple cards in deck
    printf("TESTING WITH MULTIPLE CARDS IN DECK...\n");
    initializeGame(3, kingdomCards, time(0), state);
    prevHandCount = state->handCount[0];
    prevActions = state->numActions;
    prevDeckCount = state->deckCount[0];
    prevCoins = state->coins;
    tributeEffect(state, tributeRevealedCards, 0 , 1); 
    if(state->handCount[0] > prevHandCount)
    {
        printf("checking if hand incremented by 2\n");
        assert(state->handCount[0], prevHandCount + 2);
        printf("checking if deck decremented by 2\n");
        assert(state->deckCount[0], prevDeckCount - 2);
    }
    if (state->numActions > prevActions)
    {
        printf("checking actions increased by 2\n");
        assert(state->numActions, prevActions + 2);
    }
    if (state->coins > prevCoins)
    {
        printf("checking if coins increased by 2\n");
        assert(state->coins, prevCoins + 2);
    }

    return 0;
}
