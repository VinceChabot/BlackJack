/*
Deck is face down
Position 52 is the top of the deck (first card to be drawn)
*/

#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "gameplay.h"

//Figure out how to set up SDL2
//#include <SDL2/SDL.h>

int main() {

    struct deck deck;
    struct hand player_hand;
    struct hand dealer_hand;
    struct card card_drawn;

    //Initialize start of game
    init_game(&deck);
    init_hand(&player_hand);
    init_hand(&dealer_hand);

    print_deck(&deck);

    //Deal hand
    //Card to player
    draw_card(&deck, &card_drawn);
    add_card_to_hand(&player_hand, card_drawn);

    //Card to dealer
    draw_card(&deck, &card_drawn);
    add_card_to_hand(&dealer_hand, card_drawn);

    //Card to player
    draw_card(&deck, &card_drawn);
    add_card_to_hand(&player_hand, card_drawn);

    //Card to dealer
    draw_card(&deck, &card_drawn);
    add_card_to_hand(&dealer_hand, card_drawn);

    
    print_hand(&player_hand);
    print_hand(&dealer_hand);


    return 0;
}