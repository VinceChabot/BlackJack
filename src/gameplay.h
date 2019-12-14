//
// Created by Vince on 2019-11-29.
//

#ifndef BLACKJACK_GAMEPLAY_H
#define BLACKJACK_GAMEPLAY_H

struct player
{
    struct hand hand;
    int money;
    char* sex;
};

void init_game(struct deck *deck);
void init_player(struct player *player, char* sex);
void init_hand(struct hand *hand);
char read_player_decision();
void win(struct player *player, int bet_amount);
void lose(struct player *player, int bet_amount);

#endif //BLACKJACK_GAMEPLAY_H
