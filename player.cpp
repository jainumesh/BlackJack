#include "player.h"

/* Function player
 
   Purpose:  Constructor, Initializes class variables , inits the memeber variables, sets cardNames and shuffles it to make it play ready
				Uses clear() to reset the Vetor of dealtCards.
  Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
 */
player::player()
	:isDealer{0},
	hasAce{0},
	cardNames{"Ace", "2","3","4","5","6","7","8","9","10","J","Q","K"}
{
	dealtCards.clear();
}
/* Function clear
 
   Purpose: Reset the Vetor of dealtCards. and other class variables.
 
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
 */
void player::clear() {
	isDealer= 0;
	hasAce = 0;		
	dealtCards.clear();
}
/* Function getSuite
 
   Purpose: Using Enum getSuite, evaluate the Suite of the dealt Card.
				cardOrder is arranged as "HBSDHBSD......D" for  "AAAA22...52"
 
   Parameters:
		IN: int cardOrder: Sequence Number of the card given by dealtCard.
		OUT: None
		IN/OUT: None
   Returns: string containing the name of the suite.
 */
 std::string player::getSuite(int cardOrder){
	std::string suitename;
	int suite = (int)(cardOrder%CARDS_PER_SUITE);	
	switch(suite){
	case HEART:  suitename = "HEARTS";
					   break;
	case BLACK:  suitename = "BLACK";
					   break;
	case SPADE:  suitename = "SPADE";
					   break;					   		
	case DIAMOND:  suitename = "DIAMOND";
					   break;
	/*TODO: Set errno true here*/
    default: suitename = "Error";
				break;			
	}
	return suitename;	 
}
/* Function getCardName
 
   Purpose: cardOrder is arranged as "HBSDHBSD......D" for  "AAAA22...52".
   Use this cardOrder to getCardname 
 
   Parameters:
		IN: int cardOrder: Sequence Number of the card given by dealtCard.
		OUT: None
		IN/OUT: None
   Returns: string containing the name of the suite.
 */
std::string player::getCardName(int cardOrder){
	cardOrder = cardOrder/CARDS_PER_SUITE;
	return cardNames.at(cardOrder);
}
/* Function printNewCard
 
   Purpose: cardOrder is arranged as "HBSDHBSD......D" for  "AAAA22...52".
				
				Uses this cardOrder to get exact card and Print the card. 
 
   Parameters:
		IN: int cardOrder: Sequence Number of the card given by dealtCard.
		OUT: None
		IN/OUT: None
   Returns: None
 */
void player::printNewCard(int cardOrder){
	std::string suitename =getSuite(cardOrder);
	std::string cardName = getCardName(cardOrder);
	std::cout<<"New Card : "<<cardName<<" of "<<suitename<<std::endl;
	return;
}	
/* Function getValueFromCard
 
   Purpose: cardOrder is arranged as "HBSDHBSD......D" for  "AAAA22...52".
				
				Uses this cardOrder to get exact card number (A,1,2,3...12,13).
 
   Parameters:
		IN: int cardOrder: Sequence Number of the card given by dealtCard.
		OUT: None
		IN/OUT: None
   Returns: INT: Card Number  
 */
int player::getValueFromCard(int cardOrder){
	cardOrder = (cardOrder/CARDS_PER_SUITE) +1;
	if(cardOrder == ACE_INDEX){
		setAce();
	}
	return (cardOrder > FACE_VALUE)?FACE_VALUE:cardOrder;
}
/* Function totalWithoutAces
 
   Purpose: Calculate the total value of dealt Cards to the player but consider all aces as 1 , instead of 11.
 
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: INT:Total card value of user
 */
int player::totalWithoutAces(){
	std::vector <int>::iterator it;
	int count= 0;
	for(it = dealtCards.begin(); it != dealtCards.end(); ++it) {
		count += getValueFromCard(*it);	
	}
	return count;
}
/* Function playerTotal
 
   Purpose: Calculate the highest total value of dealt Cards to the player
				(considering Aces as 1 or 11 whichever gives a higher value less than or equal to 21)
 
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: INT:Highest total card value of user
 */
int player::playerTotal(){
	int count = totalWithoutAces();
	if(getAce() && count <= ACE_VALUE){
			count += FACE_VALUE; 
	}
	return count;
}
