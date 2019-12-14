//
// Created by Vince on 2019-11-27.
//

#ifndef BLACKJACK_DECK_H
#define BLACKJACK_DECK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum suits {spades, hearts, diamonds, clubs};

struct card
{
    int value;      // 1 - 10
    char *face;     // none, jack, queen, king
    char *suit;     // spades, hearts, diamonds, clubs
    int position;   // 0 - 51 , -1 if card is in a hand

};

struct deck
{
    int size;
    struct card *cards;

};

struct hand
{
    int nb_cards;
    struct card *cards;
    int total;

};


/*
 Creates standard deck of 52 cards with 12 card of eats of the 4 suits.
 */
void create_deck(struct deck *deck);


/*
Shuffles a given deck
 */
void shuffle_deck(struct deck *deck);


/*
Draws the first card on top of the deck. (first card is the highest position card)
 */
void draw_card(struct deck *deck, struct card *card_drawn);


/*
 Adds a given card to the top of the deck (highest position)
 */
void put_card_on_top(struct deck *deck, struct card card_given);


/*
 Adds a given card to the bottom of the deck (lowest position)
 */
void put_card_at_bottom(struct deck *deck, struct card card_given);


/*
 Adds a given card at a random position in the deck
 */
void put_card_randomly(struct deck *deck, struct card card_given);


/*
 Adds a given card to a given hand
 */
void add_card_to_hand(struct hand *player_hand, struct card card_given);


/*
 Deal a card to a hand by doing "draw_card" then "add_card_to_hand"
 */
void deal_card(struct deck *deck, struct hand *hand);


/*
 Adds up the sum of all cards in a hand
 */
int compute_hand_sum(struct hand *hand_given);


/*
 Prints out the contents an entire given deck
 */
void print_deck(struct deck *deck);


/*
 Prints out the contents of a given hand
 */
void print_hand(struct hand *hand_given);


/*
 Prints out a single given card
 */
void print_card(struct card card_given);


#endif //BLACKJACK_DECK_H
