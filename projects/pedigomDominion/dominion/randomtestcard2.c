/********************************************************************
 * Author: George Lenz
 * Program: randomtestcard2.c
 * Class: CS362 - Software Engineering II
 * Description: Random testing for Minion card effect function
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
//create hands of players
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

//create decks of players
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

//create discard pile of players
for(i = 0; i < state->numPlayers; i++)
{
   int j;
   for(j=0; j < state->discardCount[i]; j++)
   {
       state->discard[i][j] = rand() % 27;
   }
}

//initialize function parameters and pre-function variables
int choice1 = rand() % 2;
int choice2;
if ( choice1 == 1 )
{
    choice2 = 0;
}
else
{
    choice2=1;
}
int handPos = rand() % state->handCount[state->whoseTurn];
state->hand[state->whoseTurn][handPos] = minion;
int preBuys = state->numBuys;
int preDiscard = state->discardCount[state->whoseTurn];
int preHandCount = state->handCount[state->whoseTurn];
int preSupply = state->supplyCount[estate];
int preCoins = state->coins;
int playersToDiscard[state->numPlayers];

//Get players who should draw new hand
for(i = 0; i < state->numPlayers; i++)
{
    if(state->handCount[i] > 4)
    {
        playersToDiscard[i] = 1;
    }
    else
    {
        playersToDiscard[i] = 0;
    }

}

//run function
cardEffectMinion(choice1, choice2, state, handPos, state->whoseTurn);

//Test if choise is 2 coins
if(choice1)
{
    //Check coins is incremented by 2
    if(assert(state->coins, preCoins +2) == 1)
    {
        printf("Failed to gain 2 coins\n");
    }
}

//Test if choice is to discard hand and gain 4 cards
else if(choice2)
{

    //check previous discard was incremented by previous hand count
    if(assert(state->discardCount[state->whoseTurn], preDiscard + preHandCount)
       == 1)
    {
        printf("Failure discarding hand\n");
    }
 
    //check players hand has 4 cards
    if(assert(state->handCount[state->whoseTurn], 4) == 1)
    {
        printf("Failure drawing 4 cards\n");
    }
   
    //cjeck other players hands
    int failures = 0;

    for(i = 0; i < state->numPlayers; i++)
    {
        if(i == state->whoseTurn)
        {
            continue;
        }
        
        if(playersToDiscard[i] == 1)
        {
            failures += assert(state->handCount[i], 4);
        }
    }       
    if (failures > 0)
    {
        printf("Failure handling other players discard and redraw\n");
    }
}
    
return 0;

}

int main()
{

    printf("\n\n************************ TESTING MINION ************************\n");

    int i = 0;

    //run 999 tests
    for(; i < 1000; i++)
    {
        test();
    }
}

