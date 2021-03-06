//
//  assignment2.c
//  
//
//  Created by user2 on 4/5/16.
//
//

#include <stdio.h>

int smithyAss2(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int currentPlayer, int i)
{
    
    //+3 Cards
    for (i = 1; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }
    
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
    
}

int adventurerAss2(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int drawntreasure, int currentPlayer, int cardDrawn, int temphand[MAX_HAND], int z)
{

    while(drawntreasure<1){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }
    return 0;
    
}

int councilroomAss2(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int i, int currentPlayer)
{
    
    //+4 Cards
    for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }
    
    //+1 Buy
    state->numBuys++;
    
    //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
    {
        if ( i != currentPlayer )
        {
            drawCard(i, state);
        }
    }
    
    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
    
}

int feastAss2(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int i, int temphand[MAX_HAND], int currentPlayer, int x)
{
    
    //gain card with cost up to 5
    //Backup hand
    for (i = 1; i <= state->handCount[currentPlayer]; i++){
        temphand[i] = state->hand[currentPlayer][i];//Backup card
        state->hand[currentPlayer][i] = -1;//Set to nothing
    }
    //Backup hand
    
    //Update Coins for Buy
    updateCoins(currentPlayer, state, 5);
    x = 1;//Condition to loop on
    while( x == 1) {//Buy one card
        if (supplyCount(choice1, state) <= 0){
            if (DEBUG)
                printf("None of that card left, sorry!\n");
            
            if (DEBUG){
                printf("Cards Left: %d\n", supplyCount(choice1, state));
            }
        }
        else if (state->coins < getCost(choice1)){
            printf("That card is too expensive!\n");
            
            if (DEBUG){
                printf("Coins: %d < %d\n", state->coins, getCost(choice1));
            }
        }
        else{
            
            if (DEBUG){
                printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
            }
            
            gainCard(choice1, state, 0, currentPlayer);//Gain the card
            x = 0;//No more buying cards
            
            if (DEBUG){
                printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
            }
            
        }
    }     
    
    //Reset Hand
    for (i = 0; i <= state->handCount[currentPlayer]; i++){
        state->hand[currentPlayer][i] = temphand[i];
        temphand[i] = -1;
    }
    //Reset Hand
    
    return 0;
    

    
}

int gardensAss2()
{
    
    return -1;
    
}