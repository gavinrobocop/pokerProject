#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//Structures

struct card{
	char suit[9];
	int value; //jack = 11 queen = 12 king = 13 ace = 14
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

void userDecision_1(int* userDecision, struct player* userPlayer, int* smallBlind, int* bigBlind, int* potTotal){
	fflush(stdout);
	scanf("%d", userDecision);

	//user decision for 1st hand
	if(*userDecision == 1) { //user chooses to call
		printf("\nUser chose to call");
		userPlayer->chips -= *bigBlind;
		printf("\nUser puts %d chips in pot with %d remaining\n\n", *bigBlind, userPlayer->chips);
		*potTotal += *bigBlind;
	} else if(*userDecision == 2) { //user chooses to raise
		printf("\nUser chose to raise");
		printf("\nPlease enter how much you would like to raise:");
		fflush(stdout);
		scanf("%d", userDecision);
		printf("\nUser raises %d", *userDecision);
		userPlayer->chips -= *userDecision;
		*potTotal += *userDecision;
	
	} else if(*userDecision == 3){ //user chooses to fold (announce winner of hand and move on to next round) FIXME
		printf("\nUser chose to fold");
	} else if(*userDecision == 4){ //user chooses to leave (game is over and end game result is displayed) FIXME
		printf("\nUser chose to leave game");
	} else { //user chose invalid input
		printf("\nInvalid input, good job dumbass");
	}

}

//user decision after the 1st hand if user going first
void userDecision_2(int* userDecision, struct player* userPlayer, int* potTotal){ 
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
		*potTotal += *userDecision;
	} else if(*userDecision == 3){ //user chooses to fold (announce winner of hand and move on to next round) FIXME
		printf("\nUser chose to fold"); //will use the continue keyword after displaying winner of round
	} else if(*userDecision == 4){ //user chooses to leave (game is over and end game result is displayed) FIXME
		printf("\nUser chose to leave game"); //will use break keyword to breakout of loop to then show final stats of game
	} else { //user chose invalid input 
		printf("\nInvalid input, good job dumbass"); //will give player a second chance to answer, if incorrect again will then put input as one FIXME
	}
	
}

//Helper Functions for determinePoints() function

void swap(struct card* card_1, struct card* card_2){
	struct card tempCard = *card_1;
	*card_1 = *card_2;
	*card_2 = tempCard;
}


void bubbleSort(struct player* player_1, int n){
	int i, j;
	int swapped;
	for(i = 0; i < n - 1; i++){
		swapped = 0;
		for(j = 0; j < n - i - 1; j++){
			if(player_1->playerDeck[j].value > player_1->playerDeck[j+1].value){
				swap(&player_1->playerDeck[j], &player_1->playerDeck[j+1]);
				swapped = 1;
			}
		}
		if(swapped == 0){
			break;
		}
	}
}

//determines if cards are a flush or not (five cards have same suit)
//if a flush returns one if not a flush returns zero
int determineFlush(struct player* player_1){
	int diamondsTotal = 0;
	int spadesTotal = 0;
	int clubsTotal = 0;
	int heartsTotal = 0;

	//using strcmp() to determine if strings are equal (same suit), will return zero if equal
	for(int i = 0; i < 7; i++){
		if(strcmp(player_1->playerDeck[i].suit, "diamonds") == 0){
			diamondsTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "spades") == 0){
			spadesTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "clubs") == 0){
			clubsTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "hearts") == 0){
			heartsTotal++;
		} else {
			printf("Something is not working with the determineFlush function");
		}
	}

	//checking if any are above suit totals are above five
	if(diamondsTotal >= 5){
		return 1;
	} else if(spadesTotal >= 5){
		return 1;
	} else if(clubsTotal >= 5){
		return 1;
	} else if(heartsTotal >= 5){
		return 1;
	} else {
		return 0;
	}
}

//determine if cards are a straight or not, will return a one if a straight and will return zero if not
int determineStraight(struct player* player_1){
	int cardPoints = 0;
	int thisCardValue = 0;
	int nextCardValue = 0;
	
	for(int i = 0; i < 6; i++){
		//To check if straight has been achieved
		if(cardPoints >= 4){
			return 1;
			break;
		}
		thisCardValue = player_1->playerDeck[i].value;
		nextCardValue = player_1->playerDeck[i+1].value;
		if(thisCardValue == nextCardValue - 1){
			cardPoints++;
		} else if(thisCardValue == nextCardValue){
			continue;
		} else {
			cardPoints = 0;
		}
	}

	if(cardPoints >= 4){
		return 1;
	} else {
		return 0;
	}

}

//return one if royal flush and zero if not
int determineRoyalFlush(struct player* player_1){
	int tenOfSameSuit = 0;
	int jokerOfSameSuit = 0;
	int queenOfSameSuit = 0;
	int kingOfSameSuit = 0;
	char sameSuit[9];

	for(int i = 6; i >= 0; i--){
		strcpy(sameSuit, player_1->playerDeck.suit);
		tenOfSameSuit = 0;
		jokerOfSameSuit = 0;
		queenOfSameSuit = 0;
		kingOfSameSuit = 0;

	}
}

//beginning of determinePoints() function
//Going to return points based on the hand the player posseses
int determinePoints(struct player* player_1){ //Determines which hand a player has and returns the score of his hand FIXME

	//if statement to determine which hand player has, will then return score based on hand
	//going to have to have to create a function for each of the ten hands
	//a royal flush returns ten and a single highcard returns a one
	
	//Sorting
	
	int size = 7;
	bubbleSort(player_1, size);
	printf("\nSorted array: ");
	for(int i = 0; i < size; i++){
		printf("%d ", player_1->playerDeck[i].value);
	}

	//going to determine if royal flush
	

	//Testing
	if(determineStraight(player_1) == 1){
		printf("shit straight");
	} else {
		printf("shit ain't straight at all");
	}


}

//Comp player functions

void compDecision_1(struct player* compPlayer, int* maxBet, int* potTotal){
	srand(time(NULL)); //if when function gets called throughs an error might be because we seeded before
	int compDecision = rand() % 100 + 1; //generates a random number between one and one hundred
	
	//will now initiate comp decision
	if(compDecision <= 75){ //comp chose to call
		printf("\nComputer chose to call");
	} else if(compDecision < 95){ //comp chose to raise
		printf("\nComputer chose to raise");
		compDecision = rand() % *maxBet + 1;
		compPlayer->chips -= compDecision;
		printf("\n\nComputer chose to raise %d", compDecision);
		*potTotal += compDecision;
		//Player should now have the option to call or fold FIXME
	} else {
		printf("\nComputer chose to fold"); //Computer chooses to fold (will use continue keyword after displaying winner of the round)FIXME
	}
	
}

void compDecision_2(struct player* compPlayer, int* maxBet, int* potTotal){

	int compDecision = rand() % 100 + 1;

	if(compDecision <= 66){ //computer chooses to check 
		printf("\nComputer chose to check");
	} else if(compDecision <= 90){ //computer chooses to bet
		printf("\nComputer chose to bet");
		compDecision = rand() % *maxBet;
		printf("\nComputer bet %d", compDecision);
		compPlayer->chips -= compDecision;
		*potTotal += compDecision;
	} else { //computer chooses to fold (announce winner of hand and move on to next round) FIXME
		printf("\nComputer chose to fold"); //will use the continue keyword after displaying winner of round
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


void printPlayerUI_3(struct player* userPlayer, int* totalPot){
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
	printf("[%d %s] ", userPlayer->playerDeck[5].value, userPlayer->playerDeck[5].suit);
}


void printPlayerUI_4(struct player* userPlayer, int* totalPot){
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
	printf("[%d %s] ", userPlayer->playerDeck[5].value, userPlayer->playerDeck[5].suit);
	printf("[%d %s] ", userPlayer->playerDeck[6].value, userPlayer->playerDeck[6].suit);
}



int main() {

	//printing the intro

	printIntro();

	//initializing card structures and tableDeck structure
	struct tableDeck table_deck;

	for(int i = 0; i < 13; i++){
		table_deck.deck[i] = (struct card){"diamonds", i + 2};
	}

	for(int i = 13; i < 26; i++){
		table_deck.deck[i] = (struct card){"spades", i - 11};
	}

	for(int i = 26; i < 39; i++){
		table_deck.deck[i] = (struct card){"hearts", i - 24};
	}

	for(int i = 39; i < 52; i++){
		table_deck.deck[i] = (struct card){"clubs", i - 37};
	}

	printTableDeck(&table_deck);

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
	userPlayer.chips -= smallBlind;
	computerPlayer.chips -= bigBlind;

	//initial bets have been placed into the pot, for the first round of poker the users can either choose to: (one) call the big blind,
	//(two) fold and end the round, (three) raise and give a number for how much you would like to
	
	//beginning of ui
	
	printPlayerUI_1(&userPlayer, &potTotal);
	printOptions_1();
	userDecision_1(&userDecision, &userPlayer, &smallBlind, &bigBlind, &potTotal);
	compDecision_1(&computerPlayer, &maxBet, &potTotal);

	//beginning of 2nd round
	
	printPlayerUI_2(&userPlayer, &potTotal);
	printOptions_2();
	userDecision_2(&userDecision, &userPlayer, &potTotal);
	compDecision_2(&computerPlayer, &maxBet, &potTotal);

	//beginning of 3rd round
	
	printPlayerUI_3(&userPlayer, &potTotal);
	printOptions_2();
	userDecision_2(&userDecision, &userPlayer, &potTotal);
	compDecision_2(&computerPlayer, &maxBet, &potTotal);

	//beginning of 4th and final round
	
	printPlayerUI_4(&userPlayer, &potTotal);
	printOptions_2();
	userDecision_2(&userDecision, &userPlayer, &potTotal);
	compDecision_2(&computerPlayer, &maxBet, &potTotal);

	//determining winner
	
	int userPoints = determinePoints(&userPlayer);


}
