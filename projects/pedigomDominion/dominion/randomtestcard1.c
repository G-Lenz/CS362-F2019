/********************************************************************
 * Author: George Lenz
 * Program: randomtestcard1.c
 * Class: CS362 - Software Engineering II
 * Description: Random testing for Baron card effect function
 *******************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//assert function to check test
int assert(int actual, int expected)
{
    if (actual == expected)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int test()
{

int i;
//initialize game
struct gameState* state = newGame();

//get between 2 and MAX_PLAYERS player count
state->numPlayers = rand() % (MAX_PLAYERS - 1) + 2;

//set embargo tokens to 0, (irrelevant to baron tests)
memset(state->embargoTokens, 0, sizeof(state->embargoTokens));

//set kingdom cards
int kingdomCards[10];
for (i = 0; i < 10; i++)
{
    //random action card (adventure = 7 to treasure_map = 26) 
    kingdomCards[i] = rand() %  20 + 7;
}

//set up supply counts
memset(state->supplyCount, 0, sizeof(state->supplyCount));
//randomly add victory supply count
for(i = 0; i < copper; i++)
{
    state->supplyCount[i] = rand() % 13;
}

//randmly add action cards

for(i = 0; i < 10; i++)
{
    state->supplyCount[kingdomCards[i]] = rand() % 12;
}

//randomly add treasure supply count
for(i = copper; i<= gold; i++);
{
    state->supplyCount[i] = rand() % 60;
}


//randomly select whose turn
state->whoseTurn = rand() % state->numPlayers;

//randomly add number of actions
state->numActions = rand();

//random number of coins
state->coins = rand();

//random number of buys
state->numBuys = rand();

//random hand of current player
state->handCount[state->whoseTurn] = rand() % MAX_HAND + 1;

for (i=0; i< state->handCount[state->whoseTurn]; i++)
{
    state->hand[state->whoseTurn][i] = rand() % 28;
}

//random deck count
state->deckCount[state->whoseTurn] = rand() % MAX_DECK + 1;

memset(state->deck[state->whoseTurn], -1, sizeof(state->deck[state->whoseTurn]));
//random discard count 
state->discardCount[state->whoseTurn] = rand() % 500;
memset(state->discard[state->whoseTurn], -1, sizeof(state->discard[state->whoseTurn]));

//Parameters and pre function variables
int choice = rand() % 2;
int handPos = rand() % state->handCount[state->whoseTurn];
state->hand[state->whoseTurn][handPos] = baron;
int preBuys = state->numBuys;
int preDiscard = state->discardCount[state->whoseTurn];
int preHandCount = state->handCount[state->whoseTurn];
int preSupply = state->supplyCount[estate];
int preCoins = state->coins;
cardEffectBaron(choice, state, state->whoseTurn);

//Check if buys incremented
if(assert(state->numBuys, preBuys + 2) == 1)
{
    printf("Failure incrementing numBuys\n");
}

//Checks if choice is to discard estate
if (choice > 0)
{   
    //check coins incremented by 4
    if( assert(state->coins, preCoins + 4) == 1)
    {
        printf("Failure incrementing number of coins\n");
    }

    //check discard incremented
    if( assert(state->discardCount[state->whoseTurn], preDiscard+1), 1)
    {
        printf("Failure incrementing discard count for estate\n");
    }

    //check top of idscard pile for estate
    if(assert(state->discard[state->whoseTurn][preDiscard], estate) == 1)
    {
        printf("Failed to put estate in discard\n");
    }

    //check hand count
    if(assert(state->handCount[state->whoseTurn], preHandCount -1) == 1)
    {
        printf("Failed to decrement estate from hand\n");
    }
}

//Tests if choice is to gain estate
else
{
    //check if nothing happens when estate supply is 0
    if(preSupply == 0)
    {
        if (assert(state->discardCount[state->whoseTurn], preDiscard) == 1)
        {
            printf("Failed to do nothing when supply empty\n");
        }
    }

    else
    {
        //check if discard count incremented 
        if(assert(state->discardCount[state->whoseTurn], preDiscard + 1) == 1)
        {
            printf("Failed to increment discard when gaining estate\n");
        }
       
        //check if gained estate (card on top of discard)
        if( assert(state->discard[state->whoseTurn][preDiscard], estate) == 1)
        {
            printf("failed to gain an estate\n");
        }
    }
}

return 0;
}

int main()
{
int i;

printf("\n\n************************ TEST BARON ************************\n");

srand(time(0));

//run tests 999 times
for (i=0; i < 1000; i++)
{
    test();
}

return 0;
}

