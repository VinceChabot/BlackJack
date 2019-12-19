//
// Created by Vince on 2019-11-29.
//

#include "deck.h"
#include "gameplay.h"
#include <math.h>

void init_game(struct deck *deck)
{
    deck->cards = malloc(52*sizeof(struct card));
    create_deck(deck);
    shuffle_deck(deck);
}


void init_player(struct player *player, char* sex, char* name)
{
    init_hand(&player->hand);
    player->name = name;
    player->money = INITIAL_PLAYER_MONEY;
    player->sex = sex;
    player->bet_amount = 0;
}


void init_hand(struct hand *hand)
{
    hand->cards = malloc(0*sizeof(struct card));
    hand->nb_cards = 0;
    hand->total = 0;
}

char enter_bet(struct player *player)
{
    int scan_return;

    printf("Enter amount to bet\n");
    scan_return = scanf(" %d", &player->bet_amount);
    while(getchar() != '\n'); //Used to empty scanf buffer

    while(player->bet_amount < 0 || player->bet_amount > 500 || scan_return == 0)
    {
        printf("Enter valid amount to bet\n");
        scan_return = scanf(" %d", &player->bet_amount);
        while(getchar() != '\n'); //Used to empty scanf buffer
    }

    round(player->bet_amount);
    printf("Player bet: %d \n", player->bet_amount);
    printf("\n");
}

char read_player_decision()
{
    char decision;


    printf("Press h to hit \n"
           "Press s to stay \n");

    scanf(" %c", &decision);
    while(getchar() != '\n'); //Used to empty scanf buffer

    while(decision != 'h' && decision != 's')
    {
        printf("Please select valid entry \n");
        scanf(" %c", &decision);
        while(getchar() != '\n'); //Used to empty scanf buffer
    }

    return decision;
}


void win(struct player *player, int bet_amount)
{
    printf("\nYou win!");
    player->money = player->money + bet_amount;
    printf("\nplayer now has %d money", player->money);
}


void lose(struct player *player, int bet_amount)
{
    printf("\nYou lose!");
    player->money = player->money - bet_amount;
    printf("\nplayer now has %d money", player->money);
}

void push(struct player *player, int bet_amount)
{
    printf("\nEqual, push");
    printf("\nplayer now has %d money", player->money);
}