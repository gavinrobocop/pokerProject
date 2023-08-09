#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Structures

struct card{
	char suit[9];
	int value; //jack = 10 queen = 11 king = 12 ace = 13
};

struct tableDeck{
	struct card deck[52];
};

struct player{
	struct card playerDeck[7];
	int chips;
};

//tableDeck functions

void shuffleDeck(struct tableDeck* deck){

	srand(time(NULL));
	int randomSwap;
	struct card carryOver;

	for(int i = 0; i < 52; i++){
		randomSwap = rand() % 52;
		carryOver = deck->deck[randomSwap];
		deck->deck[randomSwap] = deck->deck[i];
		deck->deck[i] = carryOver;
	}

}

//player functions

void userDecision_1(int* userDecision, struct player* userPlayer, int* smallBlind, int* bigBlind){
	fflush(stdout);
	scanf("%d", userDecision);

	//user decision for 1st hand
	if(*userDecision == 1) { //user chooses to call
		printf("\nUser chose to call");
		userPlayer->chips -= *bigBlind;
		printf("\nUser puts %d chips in pot with %d remaining\n\n", *bigBlind, userPlayer->chips);
	} else if(*userDecision == 2) { //user chooses to raise
		printf("\nUser chose to raise");
		printf("\nPlease enter how much you would like to raise:");
		fflush(stdout);
		scanf("%d", userDecision);
		printf("\nUser raises %d", *userDecision);
		userPlayer->chips -= *userDecision;
	
	} else if(*userDecision == 3){ //user chooses to fold (announce winner of hand and move on to next round) FIXME
		printf("\nUser chose to fold");
	} else if(*userDecision == 4){ //user chooses to leave (game is over and end game result is displayed) FIXME
		printf("\nUser chose to leave game");
	} else { //user chose invalid input
		printf("\nInvalid input, good job dumbass");
	}

}

//user decision after the 1st hand if user going first
void userDecision_2(int* userDecision, struct player* userPlayer){ 
	fflush(stdout);
	scanf("%d", userDecision);

	//user decision for 2nd hand
	if(*userDecision == 1){ //user chooses to check 
		printf("\nUser chose to check");
	} else if(*userDecision == 2){ //user chooses to bet
		printf("\nUser chose to bet");
		printf("\nPlease enter how much you would like to bet: ");
		fflush(stdout);
		scanf("%d", userDecision);
		printf("\nUser bet %d", *userDecision);
		userPlayer->chips -= *userDecision;
	} else if(*userDecision == 3){ //user chooses to fold (announce winner of hand and move on to next round) FIXME
		printf("\nUser chose to fold");
	} else if(*userDecision == 4){ //user chooses to leave (game is over and end game result is displayed) FIXME
		printf("\nUser chose to leave game");
	} else { //user chose invalid input 
		printf("\nInvalid input, good job dumbass");
	}
	
}


//Print Functions

void printIntro(void){
	printf("\n\n***Texas Hold'em Poker 2023***\n\n");
}

void printTableDeck(struct tableDeck* deck){
	for(int i = 0; i < 52; i++){
		printf("%s %d\n", deck->deck[i].suit, deck->deck[i].value);
	}
}

void printPlayerUI_1(struct player* userPlayer, int* totalPot){
	printf("\nPot: %d\n", *totalPot);
	printf("\nPlayer Chips: %d\n", userPlayer->chips);
	
	//printing player's cards 
	
	printf("\nYour deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[0].value, userPlayer->playerDeck[0].suit);
	printf("[%d %s]\n", userPlayer->playerDeck[1].value, userPlayer->playerDeck[1].suit);
}

void printOptions_1() {
	printf("\nPlease enter your next move:\n");
	printf("1.) Call\n");
	printf("2.) Raise\n");
	printf("3.) Fold\n");
	printf("4.) Leave\n");
	printf("\nEnter here: ");
}


void printPlayerUI_2(struct player* userPlayer, int* totalPot){
	printf("\nPot: %d\n", *totalPot);
	printf("\nPlayer Chips: %d\n", userPlayer->chips);
	
	//printing player's cards 
	
	printf("\nYour deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[0].value, userPlayer->playerDeck[0].suit);
	printf("[%d %s]\n", userPlayer->playerDeck[1].value, userPlayer->playerDeck[1].suit);

	//printing table deck
	
	printf("\nTable deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[2].value, userPlayer->playerDeck[2].suit);
	printf("[%d %s] ", userPlayer->playerDeck[3].value, userPlayer->playerDeck[3].suit);
	printf("[%d %s] ", userPlayer->playerDeck[4].value, userPlayer->playerDeck[4].suit);
}

void printOptions_2() {
	printf("\nPlease enter your next move:\n");
	printf("1.) Check\n");
	printf("2.) Bet\n");
	printf("3.) Fold\n");
	printf("4.) Leave\n");
	printf("\nEnter here: ");
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

	shuffleDeck(&table_deck);


	//Cards are now initialized using compound literals, and are in the array table_deck.deck, going to handout cards and initialize players now
	
	struct player userPlayer;
	struct player computerPlayer;
	int chipCount = 5000;
	int maxBet = 500;
	int potTotal = 0;
	int smallBlind = 10;
	int bigBlind = 20;
	int userDecision;
	int computerDecision;

	userPlayer.chips = chipCount;
	computerPlayer.chips = chipCount;

	//beginning of game (card handout)
	
	userPlayer.playerDeck[0] = table_deck.deck[0];
	userPlayer.playerDeck[1] = table_deck.deck[1];

	computerPlayer.playerDeck[0] = table_deck.deck[2];
	computerPlayer.playerDeck[1] = table_deck.deck[3];

	//will now input input the five table deck cards in the player's player deck, although they will not be aware, we will simulate it being on the
	//table by keeping it hidden during gameplay, only the first two cards will be shown to the player. This will make the program more efficient
	
	userPlayer.playerDeck[2] = table_deck.deck[4];
	userPlayer.playerDeck[3] = table_deck.deck[5];
	userPlayer.playerDeck[4] = table_deck.deck[6];
	userPlayer.playerDeck[5] = table_deck.deck[7];
	userPlayer.playerDeck[6] = table_deck.deck[8];

	computerPlayer.playerDeck[2] = table_deck.deck[4];
	computerPlayer.playerDeck[3] = table_deck.deck[5];
	computerPlayer.playerDeck[4] = table_deck.deck[6];
	computerPlayer.playerDeck[5] = table_deck.deck[7];
	computerPlayer.playerDeck[6] = table_deck.deck[8];

	//player deck and table deck have been initialized, chips have given to their players and a max bet has been put in place
	//will now being initial bets and decisions
	
	potTotal += smallBlind + bigBlind;
	userPlayer.chips -= bigBlind;
	computerPlayer.chips -= smallBlind;

	//initial bets have been placed into the pot, for the first round of poker the users can either choose to: (one) call the big blind,
	//(two) fold and end the round, (three) raise and give a number for how much you would like to
	
	//beginning of ui
	
	printPlayerUI_1(&userPlayer, &potTotal);
	printOptions_1();
	userDecision_1(&userDecision, &userPlayer, &smallBlind, &bigBlind);

	//beginning of 2nd round
	
	printPlayerUI_2(&userPlayer, &potTotal);
	printOptions_2();
	userDecision_2(&userDecision, &userPlayer);


}
