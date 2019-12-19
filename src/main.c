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
    //struct hand dealer_hand;
    char player_decision;

    struct player player1;
    struct player dealer;

    init_player(&player1, "male", "player1");
    init_player(&dealer, "male", "dealer");

    //Initialize start of game
    init_game(&deck);

    print_deck(&deck);

    //Read player bet
    enter_bet(&player1);

    //Card to player
    deal_card(&deck, &player1.hand);

    //Card to dealer
    deal_card(&deck, &dealer.hand);

    //Card to player
    deal_card(&deck, &player1.hand);

    //Card to dealer
    deal_card(&deck, &dealer.hand);

    printf("\n");

    //Show both hands
    printf("Player hand:\n");
    print_hand(&player1.hand);
    printf("\nDealer hand:\n");
    print_hand(&dealer.hand);

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
            lose(&player1, player1.bet_amount);
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
    print_hand(&dealer.hand);
    printf("Total is %d \n\n", dealer.hand.total);
    while(dealer.hand.total < 17 || dealer.hand.total < player1.hand.total)
    {
        deal_card(&deck, &dealer.hand);

        if(dealer.hand.total > 21)
        {
            printf("dealer bust at %d, you win \n", dealer.hand.total);
            win(&player1, player1.bet_amount);
            return 0;
        }
    }
    printf("dealer stays at %d \n", dealer.hand.total);

    /*END OF GAME*/
    printf("\n");
    printf("Player total is %d \n", player1.hand.total);
    printf("Dealer total is %d \n", dealer.hand.total);

    if(player1.hand.total > dealer.hand.total)
    {
        win(&player1, player1.bet_amount);
    }
    else if(player1.hand.total < dealer.hand.total)
    {
        lose(&player1, player1.bet_amount);
    }
    else if(player1.hand.total == dealer.hand.total)
    {
        push(&player1, player1.bet_amount);
    }

    return 0;
}