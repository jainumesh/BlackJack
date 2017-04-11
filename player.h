#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <string>

#define SUIT_SIZE 13
#define CARDS_PER_SUITE 4
#define ACE_VALUE 11
#define FACE_VALUE 10
#define MIN_CARD_COUNT 2
#define ACE_INDEX 1
#define SOFT_TARGET  17
#define BLACKJACK 21
enum suites{
        HEART,
        BLACK,
        SPADE,
        DIAMOND,
        SUITE_MAX
};
enum _gameWinner{
	_PLAYER_WINS_ = 1,
	_DEALER_WINS_ =2,
	_GAME_WINNER_MAX = 3
};
extern void printLine();
extern int getuserInput();
class player{
private:	
	/*Private member List*/
	bool isDealer;
	bool hasAce;		
	std::vector <int> dealtCards;
	std::vector <std::string> cardNames;

	/*Private member Functions*/
	int getValueFromCard(int cardOrder);
	std::string getSuite(int cardOrder);
	std::string getCardName(int cardOrder);	
	
public:
	/*public Member List*/		
	std::string PlayerName;
	//int errno = -1;

	/*Public Member Functions*/
	player();
	void clear();
	void printNewCard(int cardOrder);
	int dealertotalwithoutAces();
	int totalWithoutAces();
	int playerTotal();

	/*Inline member functions */
	void setDealer(bool dealer){
		isDealer = dealer;
	}
	void setAce(){
		hasAce = 1;
	}	
	bool getAce(){
		return hasAce;
	}
	int cardCount(){
		return dealtCards.size();
	}
	void addNewCard(int newCard){
		dealtCards.push_back(newCard);	
	}

};
/*End of Class */
#endif 
