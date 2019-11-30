//
// Created by Vince on 2019-11-29.
//

#include "deck.h"
#include "gameplay.h"

void init_game(struct deck *deck)
{
    deck->cards = malloc(52*sizeof(struct card));
    create_deck(deck);
    shuffle_deck(deck);
}

void init_hand(struct hand *hand)
{
    hand->cards = malloc(0*sizeof(struct card));
    hand->size = 0;
}