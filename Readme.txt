========= Introduction: ========================
This project implements blackjack also known as 21.
The objective of blackjack is to beat the dealer. 
To beat the dealer the player must first not bust (go over 21) 
and second either outscore the dealer or have the dealer bust. 
Here are the full rules of this version of the  game.
	1) One single Deck of Cards is used.
	2)Aces may be counted as 1 or 11 points, 2 to 9 according to pip value, 
		and tens and face cards count as ten points.
	3)The value of a hand is the sum of the point values of the individual cards. 
		Except, a "blackjack" is the highest hand, consisting of an ace and any 10-point card, 
		and it outranks all other 21-point hands.
	4)	Dealer deals 2 cards to each player and himself.
		Player cards are revealed and dealer cards are kept hidden in this version of the game.
	5) Player can either "HIT", ask to be dealt another card or Stop. 
	6)Dealer reveals his cards , if his total is less than 18 or Player total, he deals himself a new card
	7) Any player with more than 21 as total is considered Busted and out of the game.
	8) If dealer busts, all non-busted players win.
	9) Any player with a Blackjack(an ace and a face card) wins unless dealer too has a blackjack(which is called a PUSH)
	All rules can be found at: https://en.wikipedia.org/wiki/Blackjack
	
This project is implemented using C++ 11 

=========Requirement===========================
•   Dealer must hit on soft 17
•   Single Deck. The deck is shuffled every 6 rounds.
•   Player is not allowed to split cards.
•   Keep track of win percentage for the player.
•   Provide a readme file explaining how to compile the source and other info that might be interesting.

=========System Requirement====================
GCC Compiler to compile the code
This project is tested on GCC Version 5.4.0
User Access to read/write to Standard IO

=========Installation=============================
Project consists of below files:
	1)Player.h
	2)Player.cpp
	3)Blackjack.h
	4)Blackjack.cpp
	5)Makefile
All tied together in blackjack.tar, the delivered/downloaded module.
Untar the blackjack.tar to a folder and run make from inside the folder.
This will create an executable called "blackjack"
Run the executable to play the game.

=======How To Play==============================
Upon Running the executable the Program asks Player's name
Type your name and hit enter
Player is dealt with two cards and card details are shown.
Type 1 for Hit else press any key to stop.
Player total will be displayed.
Now dealer will play and deal cards until he hits a soft Target of 17+.
Program will evaluate the winner and print player name or Dealer if dealer wins
To play another game , Type 1 , or press any other key to stop playing and exit the game.
	
=======File Descriptions =========================
1)player.h:  This contains the class Player.
Blackjack instantiates an object of the class for each player as 
well as the dealer. Dealer is differentiated using "isDealer".
dealtCards: stores the cardOrder values of cards dealt to this player.(emulates a HAND)
hasAce: whether Player 's hand contains one or more Aces.
cardNames: Helps print cardname for cardOrder .

2)player.cpp:A list of helper functions to help player play the game.
Blackjack game class contains objects of player class.
Individual Function descriptions are associated with each  function definition.

3)Blackjack.h: This contains the Blackjack class.
The program instantiates a single object of this class and runs through it to help play the game.
decksize is the size of the deck. In case we use multiple decks, we can increment this size.
cardused a pointer to the top of the deck, pointing to the next card that can be dealt.
deckorder: An array that contains the sequence of cards , size is same as decksize.
	This is implemented as an array instead of vector,as no additions/deletions to this array is allowed.
player1,/dealer A couple of objects of player class for each player is created.
winner: A pointer to the player class to point to the winning player.

4)Blackjack.cpp: A list of helper functions to run the game.
Description of each function can be found in the file.

=======Design Discussion:========================
BlackjackGame is the game class . PlayGame() starts with playing for the player using playGameForPlayer(), this 
deals two cards to the player and then evaluates if next card can be dealt(use rules or user input)
If Player gets a Blackjack /busts, winner is set and no need to deal to dealer.
In this case program prints the winner and Round ends, 
Else in next step program deals cards to dealer, until
dealer hits soft target or busts or wins.
The above is evaluated as per the game rules in the function getDecision().
Program continues to deal the dealer unless a decision for the game is available.
Important points: 1) Soft Target is set at 17(dealer will deal new cards until he wins or reaches 18)
						 2) Aces are a special case and dealt with the help of below 2 functions
							 playerTotal(): Maximum possible total of all cards dealt to player, i.e we count at max 1 available Ace as 11,if total <21.
							 playerTotalWithoutAces(): : Player Total value considering all aces as 1.
After each game ends program resets the Data structure for all players including Dealer.
After playing 6 continuous rounds, the program shuffles the cards for the next round, This makes the entire deck of cards 
available for dealing and hence previously seen cards can be dealt again.
At the end of each game program prints the winning percentage of the player, using 2 digit precision.
A user input after each round guides whether to continue the program or terminate.

=========Extension==============================
Two extensions are desirable in the program

1) Error State determination: An errno can be introduced in the program to keep a track of errors and help reinit the entire Blackjackgame object
in case the program finds itself at an error state. Comments in the program explain places to introduce errno. Some Unit testing can add more cases to be dealt with using errno.

2) Multiplayer version: This program can be extended to be made a Multiplayer version , below are the major changes needed for the same.
Each player plays only against the dealer and not with each other, this makes implementation easier.
1)Update Blackjack Class with a limited maximum number of players and convert individual player objects to an array of player pointers
2) Create player objects as needed  upto a maximum limit using  a new  API in Blackjack class.
3)Update Blackjackgame.winner as an array of winners[]
4) Update playGame() to  play for each player.
5)Dealer plays until busted, reaches soft target, or else wins against all players.
6) call getDecision for all players  and update winners array.
7)playGameForPlayer: extend this 	to make interface simpler, possibly by providing playerName , or adding GUI ,i.e a text box for each player.
8)printWinner() prints a list of winners.
9) Preferably use more than one decks, i.e increase decksize from 52 to relavent number based on actual limit on number of players.
10) Introduce playerId's to each player object for easier interfacing between Blackjackgame object and player objects.

=========Known Variation From Popular Version=====
This version of Blackjack does not deal cards to the dealer at all if Player busts
or gets a Blackjack, i.e first all the cards to players are dealt and if need be then dealer is dealt with the cards.
This is a variation from the popular version of the game where the dealer too is dealt with 2 cards at the beginning of the game , 
one of which is available to the players to see.
The popular version can be implemented by introducing a simple API to deal 2 cards to dealer as well in the beginning
by calling dealCards() twice and displaying(printNewCard()) for only the first of the two cards.

=======References==============================
1)https://en.wikipedia.org/wiki/Blackjack
2)http://www.bicyclecards.com/how-to-play/blackjack/
