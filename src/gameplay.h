//
// Created by Vince on 2019-11-29.
//

#ifndef BLACKJACK_GAMEPLAY_H
#define BLACKJACK_GAMEPLAY_H



struct player
{
    char* name;
    char* sex;
    struct hand hand;
    int money;
    int bet_amount;
    int isBust;
};

void init_game(struct deck *deck,struct deck *discard_pile);
void init_player(struct player *player, char* sex, char* name);
void init_hand(struct hand *hand);
char enter_bet(struct player *player);
char read_player_action();
char read_player_decision();
void win(struct player *player, int bet_amount);
void lose(struct player *player, int bet_amount);
void push(struct player *player, int bet_amount);

#endif //BLACKJACK_GAMEPLAY_H
