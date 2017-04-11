
SOURCE=blackjack.cpp blackjack.h player.cpp player.h
GAMEFILE=blackjack
FLAGS=-Werror -Wall
CC=g++ -std=c++11
INCLUDES=/home/ukjain/Programs/blackjack/
all: $(GAMEFILE)

$(GAMEFILE): $(SOURCE)

	$(CC)  $(FLAGS) -I$(INCLUDES) $(SOURCE) -o$(GAMEFILE) 

clean:

	rm -f $(GAMEFILE)
