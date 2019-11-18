/********************************************************************
 * Author: George Lenz
 * Program: randomtestcard3.c
 * Class: CS362 - Software Engineering II
 * Description: Random testing for Tribute card effect function
 *******************************************************************/

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

//random hand of players
for (i=0; i < state->numPlayers; i++)
{
   state->handCount[i] = rand() % MAX_HAND + 1;
}

//Create hand of players
for(i = 0; i < state->numPlayers; i++)
{
   int j;

    for (j=0; j < state->handCount[i]; j++)
    {
        state->hand[i][j] = rand() % 27;
    }
}

//random deck count
for(i = 0; i < state->numPlayers; i++)
{
    state->deckCount[i] = rand() % MAX_DECK + 1;
}
memset(state->deck[i], -1, sizeof(state->deck[state->whoseTurn]));

//create player decks
for(i = 0; i < state->numPlayers; i++)
{
   int j;
   for(j=0; j < state->deckCount[i]; j++)
   {
       state->deck[i][j] = rand() % 27;
   }
}

//random discard count
for(i = 0; i < state->numPlayers; i++)
{ 
    state->discardCount[i] = rand() % 500;
}
memset(state->discard[state->whoseTurn], -1, sizeof(state->discard[state->whoseTurn]));

//create player discard piles
for(i = 0; i < state->numPlayers; i++)
{
   int j;
   for(j=0; j < state->discardCount[i]; j++)
   {
       state->discard[i][j] = rand() % 27;
   }
}

//function parametes and pre-function variables
int tributeRevealedCards[2];
int handPos = rand() % state->handCount[state->whoseTurn];
state->hand[state->whoseTurn][handPos] = tribute;
int preBuys = state->numBuys;
int preDiscard = state->discardCount[state->whoseTurn];
int preHandCount = state->handCount[state->whoseTurn];
int preSupply = state->supplyCount[estate];
int preCoins = state->coins;
int preActions = state->numActions;
int nextPlayer = state->whoseTurn + 1;
int firstCard = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
int secondCard = state->deck[nextPlayer][state->deckCount[nextPlayer] - 2];
int firstType = 0;
int secondType = 0;

//get first cards type
if (firstCard > 7)
{
    firstType = 3;
}
else if (firstCard > 3)
{
    firstType = 2;
} 
else if (firstCard > 0)
{
    firstType = 1;
}

//get second cards type
if (secondCard > 7)
{
    secondType = 3;
}
else if (secondCard > 3)
{
    secondType = 2;
} 
else if (secondCard > 0)
{
    secondType = 1;
}

//run tribtue effct
tributeEffect(state, tributeRevealedCards, state->whoseTurn, state->whoseTurn + 1);

//Check reward if duplicates
if (firstType == secondType)
{
    int failures = 0;
    if (firstType == 3)
    {
        failures += assert(state->numActions, preActions + 2);
    }

    else if (firstType == 2)
    {
        failures += assert(state->coins, preCoins + 2);
    }
    else if (firstType == 1)
    {
        failures += assert(state->handCount[state->whoseTurn], preHandCount+2);
    }
    
    if (failures > 0)
    {
        printf("Failure handling duplicates\n");
    }
}

//check rewards if not duplicate
else
{
    
    if (firstType == 3)
    {
        if(assert(state->numActions, preActions + 2), 1)
        {
            printf("Failure incrementing actions for first card\n"); 
        }
    }

    else if (firstType == 2)
    {
        if(assert(state->coins, preCoins+2), 1)
        {
            printf("Failiure incrementing coins for first card\n");
        }
    }
    else if (firstType == 1)
    {
        if(assert(state->handCount[state->whoseTurn], preHandCount+2), 1)
        {
            printf("Failure incrementing hand for first card\n");
        }
    }

    if (secondType == 3)
    {
        if(assert(state->numActions, preActions + 2), 1)
        {
            printf("Failure incrementing actions for second card\n"); 
        }
    }

    else if (secondType == 2)
    {
        if(assert(state->coins, preCoins+2), 1)
        {
            printf("Failiure incrementing coins for second card\n");
        }
    }
    else if (secondType == 1)
    {
        if(assert(state->handCount[state->whoseTurn], preHandCount+2), 1)
        {
            printf("Failure incrementing hand for second card\n");
        }
    }

}
    return 0;
}

int main()
{
    printf("\n\n************************ TESTING TRIBUTE ************************\n");

    int i = 0;
 
    //run tests 999 times
    for(i = 0; i< 1000; i++)
    {
        test();
    }
    
    return 0;
}
