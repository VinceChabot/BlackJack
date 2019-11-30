//
// Created by Vince on 2019-11-28.
//

#include "deck.h"
#include "string.h"

void create_deck(struct deck *deck)
{
    int i,j;

    int current_suit = spades;
    int deck_position = 0;

    deck->size = 52;

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
        first_card_to_swap = rand() % deck->size;
        second_card_to_swap = rand() % deck->size;

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
    deck->size --;
    *card_drawn = deck->cards[deck->size];
    deck->cards = realloc(deck->cards, deck->size * sizeof(struct card));
}


void put_card_on_top_of_deck(struct deck *deck, struct card card_given)
{
    //increment deck size
    deck->size ++;
    deck->cards = realloc(deck->cards, deck->size * sizeof(struct card));

    //insert card on top of deck
    deck->cards[deck->size - 1].value = card_given.value;
    deck->cards[deck->size - 1].suit = card_given.suit;
    deck->cards[deck->size - 1].face = card_given.face;
    deck->cards[deck->size - 1].position = deck->size - 1;
}


void put_card_at_bottom_of_deck(struct deck *deck, struct card card_given)
{
    //increment deck size
    deck->size ++;
    deck->cards = realloc(deck->cards, deck->size * sizeof(struct card));

    //move all cards up by one position
    for(int i = deck->size - 1; i >= 0; i--)
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
    int random_position = rand() % deck->size;

    printf("position is %d \n", random_position);

    //increment deck size
    deck->size ++;
    deck->cards = realloc(deck->cards, deck->size * sizeof(struct card));

    if(random_position == 0)
    {
        put_card_at_bottom_of_deck(deck, card_given);
    }
    else if(random_position == deck->size - 1)
    {
        put_card_on_top_of_deck(deck, card_given);
    }
    else
    {
        //move up cards above the random position
        for(int i = deck->size - 1; i >= random_position; i--)
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
    hand->size ++;
    hand->cards = realloc(hand->cards, hand->size * sizeof(struct card));

    //insert card in hand
    hand->cards[hand->size - 1].value = card_given.value;
    hand->cards[hand->size - 1].suit = card_given.suit;
    hand->cards[hand->size - 1].face = card_given.face;
    hand->cards[hand->size - 1].position = -1;
}


int compute_hand_sum(struct hand *hand_given)
{
    int sum = 0;

    for(int i = 0; i < hand_given->size; i++)
    {
        sum = sum + hand_given->cards[i].value;
    }

    return sum;
}


void print_deck(struct deck *deck)
{
    for(int i = 0; i < deck->size; i++)
    {
        if(strcmp(deck->cards[i].face, "none") == 0) {
            printf(" %d of %-15s  -  position: %d", deck->cards[i].value, deck->cards[i].suit, deck->cards[i].position);
        }
        else
        {
            printf(" %s of %-12s  -  position: %d", deck->cards[i].face, deck->cards[i].suit, deck->cards[i].position);
        }

        printf("\n");
    }

    printf("\n");
    printf("\n");
}


void print_hand(struct hand *hand_given)
{
    for(int i = 0; i < hand_given->size; i++)
    {
        if(strcmp(hand_given->cards[i].face, "none") == 0) {
            printf(" %d of %s  -  position: %d", hand_given->cards[i].value, hand_given->cards[i].suit, hand_given->cards[i].position);
        }
        else
        {
            printf(" %s of %s  -  position: %d", hand_given->cards[i].face, hand_given->cards[i].suit, hand_given->cards[i].position);
        }

        printf("\n");
    }

    printf("\n");
    printf("\n");


}


void print_card(struct card card_given)
{
    printf(" %d of %s  -  position: %d", card_given.value, card_given.suit, card_given.position);

    if(card_given.face == "none") {
        printf(" %d of %s  -  position: %d", card_given.value, card_given.suit, card_given.position);
    }
    else
    {
        printf(" %s of %s  -  position: %d", card_given.face, card_given.suit, card_given.position);
    }

    printf("\n");
    printf("\n");
}
