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

    printf("\n\n******************** TESTING MINE ********************\n\n");

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
    
    state->hand[0][0] = mine;
    //Test with non treasure card chosen to trash
    printf("Testing if card chosen to trash is not a treasure...\n");
    assert(cardEffectMine(copper-1, copper, state, 0, 0), - 1);

    ///Test with non treasure card chosen to gain
    printf("Testing if card chosen to gain is not a treasure...\n");
    assert(cardEffectMine(copper, curse, state, 0, 0), -1);

    //Test wtih card chosen that cost more than 3 card trashed
     printf("Testing if card expense of choice2 is >3 more than choice 1...\n");
     assert(cardEffectMine(copper, gold, state, 0, 0), - 1);

    //Test mine effect without error catch
    printf("Testing mine effect with no error catch...\n");
    int preSupply = state->supplyCount[gold];
    int preDiscardCount = state->discardCount[0];
    int preHandCount = state->handCount[0];
    int cardAdded = 0;
    cardEffectMine(silver, gold, state, 0 , 0);
    printf("Testing if supply decremented...\n");
    assert(state->supplyCount[gold], preSupply -1);
    printf("Testing if card added to hand...\n");
    assert(state->handCount[0], preHandCount + 1);
    printf("Testing if only tribute was discarded...\n");
    assert(state->discardCount[0], preDiscardCount + 1);
    for(i=0; i<state->handCount[0];i++)
    {
        if (state->hand[0][i] == gold)
        {
            cardAdded = 1;
        }
    }
    printf("Testing if card was added to hand...\n");
    assert(cardAdded, 1);

    return 0;
}
