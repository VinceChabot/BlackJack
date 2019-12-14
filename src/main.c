/*
Deck is face down
Position 52 is the top of the deck (first card to be drawn)
*/

#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "gameplay.h"
#include "graphics.h"

//Figure out how to set up SDL2
//#include <SDL2/SDL.h>

int main() {

    struct deck deck;
    struct hand player_hand;
    struct hand dealer_hand;
    struct card card_drawn;
    char player_decision;
    int bet_amount;

    struct player player1;

    init_player(&player1, "male");

    //Initialize start of game
    init_game(&deck);
    //init_hand(&player1.hand);
    init_hand(&dealer_hand);

    print_deck(&deck);


    printf("Enter amount to bet\n");
    scanf("%d", &bet_amount);
    while(bet_amount < 0 || bet_amount > 500)
    {
        printf("Enter valid amount to bet\n");
        scanf("%d", &bet_amount);
    }
    printf("Entered: %d \n", bet_amount);

    //Card to player
    deal_card(&deck, &player1.hand);

    //Card to dealer
    deal_card(&deck, &dealer_hand);

    //Card to player
    deal_card(&deck, &player1.hand);

    //Card to dealer
    deal_card(&deck, &dealer_hand);

    printf("\n");

    //Show both hands
    printf("Player hand:\n");
    print_hand(&player1.hand);
    printf("\nDealer hand:\n");
    print_hand(&dealer_hand);

    /*PLAYER DECISION PHASE*/
    printf("\nPLAYER DECISION PHASE\n");
    printf("Player has:\n");
    print_hand(&player1.hand);
    printf("Total is %d \n\n", player1.hand.total);

    player_decision = read_player_decision();
    while(player_decision == 'h')
    {
        deal_card(&deck, &player1.hand);
        if(player1.hand.total > 21)
        {
            printf("Player busted at %d, you lose \n", player1.hand.total);
            lose(&player1, bet_amount);
            return 0;
        }

        player_decision = read_player_decision();
    }

    if(player_decision == 's')
    {
        printf("Player stayed at %d \n", player1.hand.total);
    }

    /*DEALER DECISION PHASE*/
    printf("\nDEALER DECISION PHASE\n");
    printf("Dealer has:\n");
    print_hand(&dealer_hand);
    printf("Total is %d \n\n", dealer_hand.total);
    while(dealer_hand.total < 17 || dealer_hand.total < player1.hand.total)
    {
        deal_card(&deck, &dealer_hand);

        if(dealer_hand.total > 21)
        {
            printf("dealer bust at %d, you win \n", dealer_hand.total);
            win(&player1, bet_amount);
            return 0;
        }
    }
    printf("dealer stays at %d \n", dealer_hand.total);

    /*END OF GAME*/
    printf("\n");
    printf("Player total is %d \n", player1.hand.total);
    printf("Dealer total is %d \n", dealer_hand.total);

    if(player1.hand.total > dealer_hand.total)
    {
        printf("\nYou win!");
        win(&player1, bet_amount);
    }
    else if(player1.hand.total < dealer_hand.total)
    {
        printf("\nYou lose!");
        lose(&player1, bet_amount);
    }
    else if(player1.hand.total == dealer_hand.total)
    {
        printf("\nEqual, push");
    }

    return 0;
}