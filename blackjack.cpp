#include "blackjack.h"
   /*
   Function BlackjackGame
 
   Purpose:  Constructor, Initializes class variables , inits the Deck and shuffles it to make it play ready
 
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
 */
 BlackjackGame::BlackjackGame()
	:cardused{0},
	deckorder{0},
	winner{nullptr}
{
	initializeDeck();
	resetDeck();
}
/*
   Function: shuffleCards
 
   Purpose:Shuffle the Deck using Fisher yates algo . This algo simply runs from n to 1, 
				picking up every card and swapping it with a random card at a position < n.
 
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
 */
 void BlackjackGame::shuffleCards(){
	srand ( time(nullptr) );
	for (int i = decksize-1; i > 0; i--){
		int j = rand() % (i+1);
		swapCards(&deckorder[i], &deckorder[j]);
	}
}
   /*
   Function: resetDeck
 
   Purpose: Resets the Deck by shuffling( uses shuffleCards()) and placing cardUsed at top of the deck.
				Initializes isDealer variable for all players including the dealer.
 
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
 */
 void BlackjackGame::resetDeck(){
	shuffleCards();
	cardused = 0;	
	dealer.setDealer(true);
	player1.setDealer(false);
	return;
}
/*
   Function: initializeDeck
 
   Purpose: Set Deck with Card Values. 
				cards are arranged in this  seqeuence:  "A,A,A,A,2,2,.......Q,Q,K,K,K,K"
			    Among Individual Numbers cards are arranged as {Hearts,Black,spade,diamond}
			    Together these two provide cardOrder as {1,2,3,4,5,6........47,48,49,50,51,52}
				The vector deckorder is initialized with above sequence to emulate cards in this function.
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
 */
void BlackjackGame::initializeDeck() {
	int counter = 0;
	for(;counter <= decksize;++counter){
			deckorder[counter] = counter; 
	}
}
/*
   Function: swapCards
 
   Purpose: swap to integers using reference.
   Parameters:
		IN: int *a: 1st integer,int *b, 2nd integer
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
*/
void BlackjackGame::swapCards(int *a,int*b){
	int temp = *a; 
	*a = *b; 
	*b = temp;
}
/*
   Function: resetPlayers
 
   Purpose: Resets the Datastructures for each individual player in the game by calling respective clear() .
				This prepares them to play the next game.
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns:  Does not return a value
*/
void BlackjackGame::resetPlayers(){
	player1.clear();
	dealer.clear();	
	winner = nullptr;
}
/*
   Function: dealCard
 
   Purpose: Reveals the card at the top of the deck and updates deck's pointer to next card.
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: The card Order of the dealt card,i.e sequence number as per established by initializeDeck().
*/
int BlackjackGame::dealCard(){
	/*  TODO: insert an errno check in  to evaluate if the deck is in an inconsistent state, and  needs to initializeDeck again.*/
	if(cardused == decksize-1){
			resetDeck();
	}
	return deckorder[cardused++];
}
/*
   Function: printWinner
 
   Purpose: Reveals the Winner and prints the Name of the corresponding Player/Dealer on STDOUT
				uses the Winner ptr of the class.
				If winner is not set, nobody Won the round, so declare it a PUSH(same score for all).
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
void BlackjackGame::printWinner(){	
	printLine();
	if(NULL != winner)
		std::cout<<winner->PlayerName<<" is the Winner!!!"<<std::endl;
	else
		std::cout<<"Its a Push,same scores for all players!!!!"<<std::endl;
}
/*
   Function: setWinner
 
   Purpose: Set the Winner Ptr to the Object of the player who won the round.
   Parameters:
		IN: int gameWinner: pset to one of the value from enum _gameWinner, used to set winner to respective player/dealer
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/		
void BlackjackGame::setWinner(int gameWinner){
	switch(gameWinner){	
	default:
				break;
	case _PLAYER_WINS_: 
				winner = &player1;
				break;
	case  _DEALER_WINS_:
				winner = &dealer;
				break;			
	}
	return ;
}
/*
   Function: getHitFromUser
 
   Purpose: Validate if game is still alive and Player can draw more cards. If yes then,
				Get User Input from Player to check if he wants to "Hit"(Deal another Card) or Stop at current Total.
				game is still alive if: User does not Win by getting a blackjack or User does not Lose, by getting busted.
   Parameters:
		IN: int playerCardCount: Current card count of the player.
			  player* currentPlayer:  Pointer to the Current player.
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
int BlackjackGame::getHitFromUser(int playerCardCount, player* currentPlayer){
	if(playerCardCount == MIN_CARD_COUNT && currentPlayer->playerTotal() == BLACKJACK){
		setWinner(_PLAYER_WINS_);;
		return 0;
	}
	else if(currentPlayer->totalWithoutAces() > BLACKJACK){
		setWinner(_DEALER_WINS_);;
		return 0;
	}else if(playerCardCount >= MIN_CARD_COUNT  && currentPlayer->totalWithoutAces() < BLACKJACK){
		printLine();
		std::cout<<"Press 1 to Hit Or any other Key to Stop"<<std::endl;
		return getuserInput();
	}
	return 0;
}
/*
   Function: playGameForPlayer
 
   Purpose: Lets the Player(all apart from Dealer) play the game.
				Deals New Card to Player, add it to Player's list(vector  dealtCards) of Cards,  and evaluates if new card should be dealt.
				uses: getHitFromUser for this evaluation.
				If winner is already decided, sets the winner to respective player.
				Prints Final Total of the Player
   Parameters:
		IN: player* currentPlayer: Ptr to the object of Current Player.
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
void BlackjackGame::playGameForPlayer(player* currentPlayer){
	int hit = 1;
	int newCard = -1;
	int playerCardCount = 0;
	int gameWinner = 0;
	printNewLine();
	printLine();
	std::cout<<"Starting new game, drawing First 2 cards for Player : "<<currentPlayer->PlayerName<<std::endl;
	
	while(playerCardCount < MIN_CARD_COUNT || hit == true){
		newCard = dealCard();
		/*TODO:use and handle errno for error  status from dealcard();*/
		playerCardCount++;
		currentPlayer->addNewCard(newCard);
		currentPlayer->printNewCard(newCard);
		hit = getHitFromUser(playerCardCount,currentPlayer);
	}
	if(gameWinner){
		setWinner(gameWinner);
	}
	std::cout<<"Total Score for  "<<currentPlayer->PlayerName<<" : "<<currentPlayer->playerTotal()<<std::endl;
}
/*
   Function: getDecision
 
   Purpose: Evaluates if the game can be decided at this stage for a Player.
				Evaluation Rules are as per Standards from https://en.wikipedia.org/wiki/Blackjack
				We consider playerTotal with ace as 1 as ewll as ace as 11 using totalWithoutAces and playerTotal.
				Similarly we consider two possible Dealer scores:dealerScoreHigh and dealerScoreLow.
				In absence of an Ace in the Hand, both scores are same.
				Only one of the aces is considered to be used as 11 , in case a player(or Dealer) has more than  1 ace.
				Dealer Hits at Soft target of 17(always).
   Parameters:
		IN: player* currentPlayer: Ptr to the object of Current Player.
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
 bool BlackjackGame::getDecision(player* currentPlayer){
	int playerScore = currentPlayer->playerTotal();
	int dealerScoreHigh =  dealer.playerTotal();	
	int dealerScoreLow = dealer.totalWithoutAces();
	/*re deal*/
	if(dealerScoreHigh <= SOFT_TARGET || (dealerScoreHigh >= SOFT_TARGET && dealerScoreHigh < playerScore )){
		return false;
	}
	
	if(dealerScoreLow <= SOFT_TARGET){
		return false;
	}
		
	if(dealerScoreLow > BLACKJACK) {
		winner = currentPlayer;
		return true;// Player wins
	}
	if(dealerScoreLow > SOFT_TARGET && dealerScoreLow < playerScore) {
		winner = currentPlayer;
		return true; // player wins
	}
	if(dealerScoreLow == playerScore) {
		winner = NULL;
		return true; // push
	}
	if(dealerScoreLow > playerScore) {
		winner = &dealer;
		return true; // Dealer wins
	}
	return false;
}	
/*
   Function: playGameForDealer
 
   Purpose:Similar to playgameForplayers(), this deals new card to Dealer until game over.
			   After dealing each Card, getDecision() is called to evaluate if decision is available.
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
void BlackjackGame::playGameForDealer(){
	int newCard = -1;
	int playerCardCount = 0;
	bool decision = 0;
	printLine();
	std::cout<<"Now dealing for  : "<<dealer.PlayerName<<std::endl;
	while(decision == false){
		newCard = dealCard();
		/*TODO for error  status from dealcard();*/
		playerCardCount++;
		dealer.addNewCard(newCard);
		dealer.printNewCard(newCard);
		decision = getDecision(&player1);		
	}
	/*Print decision, either here or inside getDecision()*/
	std::cout<<"Total Score for  "<<dealer.PlayerName<<" : "<<dealer.playerTotal()<<std::endl;
}
/*
   Function: playGame
 
   Purpose:Start the game , 1st play for all players. At last , if all players are not already Busted, Play for the Dealer.
			  
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
void BlackjackGame::playGame(){
	/*Implement Player's part of the game*/
	playGameForPlayer(&player1);
	if(NULL == winner){
		playGameForDealer();
	}
	return;
}
/*
   Function: printLine
 
   Purpose:Print a seperator Line on STDOUT .
			  
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
void printLine(){
	
	char linebreak[] = "==============================================================================";
	std::cout<<linebreak<<std::endl;
}
void printNewLine(){
	std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
}
/*
   Function: getuserInput
 
   Purpose: Get user Input from STDIN , mainly to evaluate if 
				1) User Wants to deal new card(playGameForPlayer)
				2) User wants to play another Round. (Main())
			  
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: Does not return a value.
*/
int getuserInput(){
    std::string userChoice;
	getline(std::cin,userChoice);
	unsigned int chars = 0;
	std::string in = "";
	for(unsigned int i = 0; i < userChoice.size(); i++){
		if(userChoice[i] != ' ') {
			chars++;
			in += userChoice[i];
		}
	}
	if(chars == 1 && in == "1") {
		return 1;
	}
	return  0;
}
/*
   Function: Main
 
   Purpose: Lets Play the game 
			  
   Parameters:
		IN: None
		OUT: None
		IN/OUT: None
   Returns: INT: Error state , 0 for no error.
*/
int main(){
	unsigned int gameCount = 0;
	unsigned int playerWinCount = 0;
	double playerWinPercent = 0.00;
	BlackjackGame _BlackjackGame_object;
	/*Get the Name of the Player(s) and update player Names
	 * Extend here for multiple players*/
	std::cout<<"Who's playing today?"<<std::endl;
	getline(std::cin,_BlackjackGame_object.player1.PlayerName);
	if(_BlackjackGame_object.player1.PlayerName == ""){
		_BlackjackGame_object.player1.PlayerName = "Player";
	}
	_BlackjackGame_object.dealer.PlayerName = "Dealer";
	
	/*TODO: infinite loop can eventually cause stack overflow. protect it*/
	/*  TODO: insert an errno check in  to evaluate if the program is in an inconsistent state, and  needs to reinit.*/
	while(true){
		printLine();
		/*Shuffle Cards if 6 games have been dealt with same deck*/
		if(gameCount && (!(gameCount% SHUFFLE_AFTER_COUNT))){
			std::cout<<"Lets shuffle the cards!!"<<std::endl;
			_BlackjackGame_object.resetDeck();
			printLine();
		}
		/*Resets the Data Structure for All players and Dealer.*
     	 * Extend here for multiple players*/
		_BlackjackGame_object.resetPlayers();
		/*Play the Game*/
		_BlackjackGame_object.playGame();
		/*Print The Winner( Playername(s) for Player(s) or Dealer)*/
		_BlackjackGame_object.printWinner();
		gameCount++;
		/*Keep track of number of games Won by a Player, calculate Win percent after each game and print on STDOUT*/
		playerWinCount += _BlackjackGame_object.incrementWinCount();
		playerWinPercent = ((double)playerWinCount*100/(double)gameCount);
		printLine();
		std::cout<<"Win Percentage for "<<_BlackjackGame_object.player1.PlayerName<<" is :  "
			<<std::fixed<<std::setprecision(2)<<playerWinPercent<<std::endl;
		/*Get User Input to Play another round or Not.
		 * This User Input breaks the Infinite WHile Loop */	
		std::cout<<"Ready For AnotherRound?"<<std::endl;
		std::cout<<"Press 1 for Yes Or any other Key to Stop."<<std::endl;
			if(1 != getuserInput()){
			break;
		}
	}
	printNewLine();
	printLine();
	return 0;
}
