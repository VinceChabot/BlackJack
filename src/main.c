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

    //Initialize start of game
    init_game(&deck);
    init_hand(&player_hand);
    init_hand(&dealer_hand);

    print_deck(&deck);

    //Card to player
    deal_card(&deck, &player_hand);

    //Card to dealer
    deal_card(&deck, &dealer_hand);

    //Card to player
    deal_card(&deck, &player_hand);

    //Card to dealer
    deal_card(&deck, &dealer_hand);

    //Show both hands
    print_hand(&player_hand);
    print_hand(&dealer_hand);


    printf("PLAYER DECISION PHASE\n");
    player_decision = read_player_decision();
    while(player_decision == 'h')
    {
        deal_card(&deck, &player_hand);
        if(player_hand.total > 21)
        {
            printf("Player busted at %d \n", player_hand.total);
            return 0;
        }

        player_decision = read_player_decision();
    }

    if(player_decision == 's')
    {
        printf("Player stayed at %d \n", player_hand.total);
    }


    printf("PLAYER DECISION PHASE\n");
    if(dealer_hand.total < 17 || dealer_hand.total < player_hand.total)
    {
        deal_card(&deck, &dealer_hand);

        if(dealer_hand.total > 21)
        {
            printf("dealer bust at %d \n", dealer_hand.total);
            return 0;
        }
    }
    else
    {
        //End of hand
    }

    return 0;
}