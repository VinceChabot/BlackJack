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
    hand->nb_cards = 0;
    hand->total = 0;
}

char read_player_decision()
{
    char decision;

    printf("Press h to hit \nPress s to stay \n");
    scanf("%c", &decision);

    while(decision != 'h' && decision != 's')
    {
        printf("Please select valid entry \n");
        scanf("%c", &decision);
    }

    return decision;

}