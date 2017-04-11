#ifndef __BLACKJACK_H__
#define __BLACKJACK_H__

#include "player.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sstream>
#include <iomanip>
#define SHUFFLE_AFTER_COUNT 6

void printNewLine();
class BlackjackGame {
private:
	/*Private member List*/
	static const int decksize = 52;
	int cardused;
	int deckorder[decksize];	
	
	/*Private member Functions*/
	void shuffleCards();	
	void initializeDeck();
	void swapCards(int *a,int*b);
	void playGameForPlayer(player* currentPlayer);
	void playGameForDealer();

public:	
	/*public Member List*/	
	player player1;
	player dealer;
	player* winner;
	//int errno = -1;
	/*Public Member Functions*/
	BlackjackGame();
	void resetDeck();
	int dealCard();
	void playGame();
	bool getDecision(player* currentPlayer);	
	void printWinner();
	void resetPlayers();
	void setWinner(int gameWinner);
	int getHitFromUser(int playerCardCount, player* currentPlayer);
	int incrementWinCount(){	
		return (winner == &player1)?1:0;
	}
};

/*End of Class */

#endif
