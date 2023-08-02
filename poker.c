#include <stdio.h>

//Structures

struct card{
	char suit[9];
	int value; //jack = 10 queen = 11 king = 12 ace = 13
};

struct tableDeck{
	struct card deck[52];
};

struct player{
	struct card playerDeck[2];
	int chips;
};

//Print Functions

void printIntro(void){
	printf("\n\n***Texas Hold'em Poker 2023***\n");
}

int main() {

	//printing the intro

	printIntro();

	//initializing card structures and tableDeck structure
	struct tableDeck table_deck;

	for(int i = 0; i < 13; i++){
		table_deck.deck[i] = (struct card){"diamonds", i + 1};
	}

	for(int i = 13; i < 26; i++){
		table_deck.deck[i] = (struct card){"spades", i - 12};
	}

	for(int i = 26; i < 39; i++){
		table_deck.deck[i] = (struct card){"hearts", i - 25};
	}

	for(int i = 39; i < 52; i++){
		table_deck.deck[i] = (struct card){"clubs", i - 38};
	}

	for(int i = 0; i < 52; i++){
		printf("%s ", table_deck.deck[i].suit);
		printf("%d\n", table_deck.deck[i].value);
	}


}
