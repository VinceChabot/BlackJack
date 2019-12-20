//
// Created by Vince on 2019-11-28.
//

#include "constants.h"
#include "deck.h"
#include "string.h"

void create_deck(struct deck *deck)
{
    int i,j;

    int current_suit = spades;
    int deck_position = 0;

    deck->nb_cards = 52;

    //go through suits
    for(i = 1; i <= 4; i++)
    {
        //go through values
        for(j = 1; j <= 13; j++)
        {

            //assign value
            if(j>10)
            {
                deck->cards[deck_position].value = 10;
            }
            else
            {
                deck->cards[deck_position].value = j;
            }

            //assign face
            switch(j)
            {
                case 11:
                    deck->cards[deck_position].face = "jack";
                    break;

                case 12:
                    deck->cards[deck_position].face = "queen";
                    break;

                case 13:
                    deck->cards[deck_position].face = "king";
                    break;

                default:
                    deck->cards[deck_position].face = "none";
                    break;

            }

            //assign suit
            switch(i-1)
            {
                case spades:
                    deck->cards[deck_position].suit = "spades";
                    break;
                case hearts:
                    deck->cards[deck_position].suit = "hearts";
                    break;
                case diamonds:
                    deck->cards[deck_position].suit = "diamonds";
                    break;
                case clubs:
                    deck->cards[deck_position].suit = "clubs";
                    break;

            }

            //assign position in deck
            deck->cards[deck_position].position = deck_position;
            deck_position ++;
        }
    }
}


void shuffle_deck(struct deck *deck)
{
    time_t t;
    srand((unsigned) time(&t));

    int first_card_to_swap;
    int second_card_to_swap;

    char *temp_suit;
    char* temp_face;
    int temp_value;


    for(int i = 0; i < 150; i++)
    {
        //randomly choose two cards to swap
        first_card_to_swap = rand() % deck->nb_cards;
        second_card_to_swap = rand() % deck->nb_cards;

        //temp values used to store a card while doing the swap
        temp_suit =  deck->cards[first_card_to_swap].suit;
        temp_face = deck->cards[first_card_to_swap].face;
        temp_value = deck->cards[first_card_to_swap].value;


        //swap the two cards
        deck->cards[first_card_to_swap].suit = deck->cards[second_card_to_swap].suit;
        deck->cards[first_card_to_swap].face = deck->cards[second_card_to_swap].face;
        deck->cards[first_card_to_swap].value = deck->cards[second_card_to_swap].value;

        deck->cards[second_card_to_swap].suit = temp_suit;
        deck->cards[second_card_to_swap].face = temp_face;
        deck->cards[second_card_to_swap].value = temp_value;
    }
}


void draw_card(struct deck *deck, struct card *card_drawn)
{
    deck->nb_cards --;
    *card_drawn = deck->cards[deck->nb_cards];
    deck->cards = realloc(deck->cards, deck->nb_cards * sizeof(struct card));
}


void put_card_on_top_of_deck(struct deck *deck, struct card card_given)
{
    //increment deck size
    deck->nb_cards ++;
    deck->cards = realloc(deck->cards, deck->nb_cards * sizeof(struct card));

    //insert card on top of deck
    deck->cards[deck->nb_cards - 1].value = card_given.value;
    deck->cards[deck->nb_cards - 1].suit = card_given.suit;
    deck->cards[deck->nb_cards - 1].face = card_given.face;
    deck->cards[deck->nb_cards - 1].position = deck->nb_cards - 1;
}


void put_card_at_bottom_of_deck(struct deck *deck, struct card card_given)
{
    //increment deck size
    deck->nb_cards ++;
    deck->cards = realloc(deck->cards, deck->nb_cards * sizeof(struct card));

    //move all cards up by one position
    for(int i = deck->nb_cards - 1; i >= 0; i--)
    {
        deck->cards[i].value = deck->cards[i-1].value;
        deck->cards[i].suit = deck->cards[i-1].suit;
        deck->cards[i].face = deck->cards[i-1].face;
        deck->cards[i].position = i;
    }

    //insert card at bottom of deck
    deck->cards[0].value = card_given.value;
    deck->cards[0].suit = card_given.suit;
    deck->cards[0].face = card_given.face;
    deck->cards[0].position = 0;

}


void put_card_in_deck_randomly(struct deck *deck, struct card card_given)
{
    time_t t;
    srand((unsigned) time(&t));

    //choose random position in deck
    int random_position = rand() % deck->nb_cards;

    printf("position is %d \n", random_position);

    //increment deck size
    deck->nb_cards ++;
    deck->cards = realloc(deck->cards, deck->nb_cards * sizeof(struct card));

    if(random_position == 0)
    {
        put_card_at_bottom_of_deck(deck, card_given);
    }
    else if(random_position == deck->nb_cards - 1)
    {
        put_card_on_top_of_deck(deck, card_given);
    }
    else
    {
        //move up cards above the random position
        for(int i = deck->nb_cards - 1; i >= random_position; i--)
        {
            deck->cards[i].value = deck->cards[i-1].value;
            deck->cards[i].suit = deck->cards[i-1].suit;
            deck->cards[i].face = deck->cards[i-1].face;
            deck->cards[i].position = i;
        }

        //insert card at random position
        deck->cards[random_position].value = card_given.value;
        deck->cards[random_position].suit = card_given.suit;
        deck->cards[random_position].face = card_given.face;
        deck->cards[random_position].position = random_position;
    }
}


void add_card_to_hand(struct hand *hand, struct card card_given)
{
    //increase hand size
    hand->nb_cards ++;
    hand->cards = realloc(hand->cards, hand->nb_cards * sizeof(struct card));

    //insert card in hand
    hand->cards[hand->nb_cards - 1].value = card_given.value;
    hand->cards[hand->nb_cards - 1].suit = card_given.suit;
    hand->cards[hand->nb_cards - 1].face = card_given.face;
    hand->cards[hand->nb_cards - 1].position = -1;

    hand->total = compute_hand_sum(hand);
}


void deal_card(struct deck *deck, struct hand *hand)
{
    struct card card_drawn;

    draw_card(deck, &card_drawn);
    add_card_to_hand(hand, card_drawn);

    if(DEBUG_MODE == 1)
    {
        if (strcmp(card_drawn.face, "none") == 0) {
            printf("dealt %d of %s \n", card_drawn.value, card_drawn.suit);
        } else {
            printf("dealt %s of %s \n", card_drawn.face, card_drawn.suit);
        }

        printf("hand total is now %d \n\n", hand->total);
    }
}

void discard_hand(struct hand *hand, struct deck *discard_pile)
{
    int i;

    //Copy cards to discard pile
    for(i = 0; i < hand->nb_cards; i++)
    {
        put_card_on_top_of_deck(discard_pile, hand->cards[i]);
    }

    //Empty hand
    hand->total = 0;
    hand->nb_cards = 0;
    hand->cards = realloc(hand->cards, hand->nb_cards * sizeof(struct card));
}

int compute_hand_sum(struct hand *hand_given)
{
    int sum = 0;

    for(int i = 0; i < hand_given->nb_cards; i++)
    {
        sum = sum + hand_given->cards[i].value;
    }

    return sum;
}


void print_deck(struct deck *deck)
{
    if(deck->nb_cards == 0)
    {
        printf("\nDeck is empty");
    }
    else
    {
        for (int i = 0; i < deck->nb_cards; i++) {
            if (strcmp(deck->cards[i].face, "none") == 0) {
                printf("%d of %-15s  -  position: %d", deck->cards[i].value, deck->cards[i].suit,
                       deck->cards[i].position);
            } else {
                printf("%s of %-12s  -  position: %d", deck->cards[i].face, deck->cards[i].suit,
                       deck->cards[i].position);
            }

            printf("\n");
        }

        printf("\n");
    }
}


void print_hand(struct hand *hand_given)
{
    if(hand_given->nb_cards == 0)
    {
        printf("\nHand is empty");
    }
    else
    {
        for (int i = 0; i < hand_given->nb_cards; i++) {
            if (strcmp(hand_given->cards[i].face, "none") == 0) {
                printf("%d of %s", hand_given->cards[i].value, hand_given->cards[i].suit);
            } else {
                printf("%s of %s", hand_given->cards[i].face, hand_given->cards[i].suit);
            }

            printf("\n");
        }
    }
}


void print_card(struct card card_given)
{
    printf("%d of %s  -  position: %d", card_given.value, card_given.suit, card_given.position);

    if(card_given.face == "none") {
        printf("%d of %s  -  position: %d", card_given.value, card_given.suit, card_given.position);
    }
    else
    {
        printf("%s of %s  -  position: %d", card_given.face, card_given.suit, card_given.position);
    }

    printf("\n");
}
