#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//assert function to check test
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
//initialize game
struct gameState* state = newGame();
int kingdomCards[10] = {adventurer, feast, gardens, mine, village, baron, minion, ambassador, tribute, remodel};

initializeGame(2, kingdomCards, time(0), state);
int preCoins = state->coins;
printf("%d\n", state->coins);

//put an estate and baron in the hand of the current player
state->hand[0][1] = estate;
state->hand[0][4] = baron;

//TEST discard estate with >1 in supply
printf("\n\n************************ TESTING BARON ************************\n");
printf("\nTESTING CHOICE TO DISCARD ESTATE WITH ONE IN HAND AND >1 IN SUPPLY\n");
baronEffect(1, state, 4, 0);
printf("Test if buys were incremented\n");
assert(state->numBuys, 2);
printf("Testing if coins were incremented\n");
assert(state->coins, preCoins + 4);
printf("Testing if estate in discard\n");
assert(state->discard[0][state->discardCount[0]], estate);
printf("Testing if discard count was incremented\n");
assert(state->discardCount[0], 1);
printf("Test if hand count was decremented\n");
assert(state->handCount[0], 4);

//Test baronEffect with no estate cards in hand but supply left
initializeGame(2, kingdomCards, time(0), state);
preCoins = state->coins;
state->hand[0][4] = baron;

//populate hand with coppers
for(i=0; i<state->handCount[0] - 1;i++)
{
    state->hand[0][i] = copper;
}

printf("\nTEST CHOICE TO DISCARD ESTATE WITH NONE IN HAND AND >1 IN SUPPLY\n");
baronEffect(1, state, 4, 0);
printf("Test if buys were incremented\n");
assert(state->numBuys, 2);
printf("Testing if estate gained in discard\n");
assert(state->discard[0][state->discardCount[0]], estate);
printf("Testing if discard count was incremented\n");
assert(state->discardCount[0], 1);
printf("Test if hand count was decremented\n");
assert(state->handCount[0], 4);
printf("Test if estate supply was decremented\n");
assert(state->supplyCount[estate], 7);

//Testing if there is supply left and choice is to gain an estate
initializeGame(2, kingdomCards, time(0), state);
preCoins = state->coins;
state->hand[0][4] = baron;
printf("\nTEST CHOICE TO GAIN ESTATE WITH SUPPLY LEFT\n");
baronEffect(0, state, 4, 0);
printf("Test if buys were incremented\n");
assert(state->numBuys, 2);
printf("Testing if estate gained in discard\n");
assert(state->discard[0][state->discardCount[0]], estate);
printf("Testing if discard count was incremented\n");
assert(state->discardCount[0], 1);
printf("Test if hand count was decremented\n");
assert(state->handCount[0], 4);
printf("Test if estate supply was decremented\n");
assert(state->supplyCount[estate], 7);

//Test if there is no estate supply left and chose to gain an estate

//set estates to 0
state->supplyCount[estate] = 0;
//put an estate in the current players hand
state->hand[0][0] = estate;

baronEffect(0, state, 4, 0);
printf("TEST CHOICE TO GAIN ESTATE WITH NO SUPPLY LEFT\n");
baronEffect(0, state, 4, 0);
printf("Test if hand count was decremented\n");
assert(state->handCount[0], 4);


return 0;

}

