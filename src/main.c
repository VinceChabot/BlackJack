/*
Deck is face down
Position 52 is the top of the deck (first card to be drawn)
*/

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "deck.h"
#include "gameplay.h"
#include "graphics.h"

//Figure out how to set up SDL2
//#include <SDL2/SDL.h>

int main() {

    struct deck deck;
    struct deck discard_pile;
    //struct hand dealer_hand;
    char player_action;
    char player_decision;

    struct player player1;
    struct player dealer;


    printf("\nWelcome to the Blackjack game!\n");


    init_player(&player1, "male", "player1");
    init_player(&dealer, "male", "dealer");

    //Initialize start of game
    init_game(&deck, &discard_pile);

    if(DEBUG_MODE == 1)
    {
        print_deck(&deck);
    }

    NEW_ROUND:

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

    if(DEBUG_MODE == 1)
    {
        //Show both hands
        printf("Player hand:\n");
        print_hand(&player1.hand);
        printf("\nDealer hand:\n");
        print_hand(&dealer.hand);
    }

    /*PLAYER DECISION PHASE*/
    printf("\nPLAYER DECISION PHASE\n");
    printf("\nPlayer has:\n");
    print_hand(&player1.hand);
    printf("\nTotal is %d \n\n", player1.hand.total);

    player_action = read_player_action();
    while(player_action == 'h')
    {
        deal_card(&deck, &player1.hand);
        printf("\nPlayer has:\n");
        print_hand(&player1.hand);
        printf("\nTotal is %d \n\n", player1.hand.total);

        if(player1.hand.total > 21)
        {
            player1.isBust = YES;
            break;
        }
        player_action = read_player_action();
    }

    if(player_action == 's')
    {
        printf("player stays at %d \n", player1.hand.total);
    }

    /*DEALER DECISION PHASE*/
    if(player1.isBust == NO)
    {
        printf("\nDEALER DECISION PHASE\n");
        printf("Dealer has:\n");
        print_hand(&dealer.hand);
        printf("Total is %d \n\n", dealer.hand.total);
        while (dealer.hand.total < 17 || dealer.hand.total < player1.hand.total) {
            deal_card(&deck, &dealer.hand);

            if (dealer.hand.total > 21) {
                dealer.isBust = YES;
            }
        }
        if (dealer.isBust == NO) {
            printf("dealer stays at %d \n", dealer.hand.total);
        }
    }

    /*END OF ROUND*/
    printf("\n");
    printf("Player total is %d \n", player1.hand.total);
    printf("Dealer total is %d \n", dealer.hand.total);

    //Determine the winner
    if(dealer.isBust == YES)
    {
        printf("dealer bust at %d\n", dealer.hand.total);
        win(&player1, player1.bet_amount);
        dealer.isBust = NO;
    }
    else if(player1.isBust == YES)
    {
        printf("you bust at %d\n", player1.hand.total);
        lose(&player1, player1.bet_amount);
        player1.isBust = NO;
    }
    else if(player1.hand.total > dealer.hand.total)
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

    /*PREPARATION FOR NEXT ROUND*/
    discard_hand(&player1.hand, &discard_pile);
    discard_hand(&dealer.hand, &discard_pile);

    player_decision = read_player_decision();

    if(player_decision == 'y')
    {
        printf("\n\nNEW ROUND\n");
        goto NEW_ROUND;
    }
    else
    {
        printf("\nEND OF GAME\n");
    }


    return 0;
}