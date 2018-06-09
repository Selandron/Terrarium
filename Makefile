CC=g++

MAIN=main.o

EXEC=terrarium.exe
HEADERS=
BIN=./bin/
PATH_SFML=D:\Bibliotheque\SFML-2.4.2
CFLAGS=-W -Wall -ansi -std=c++11 -pedantic -I$(PATH_SFML)\include $(HEADERS)
LDFLAGS=-L$(PATH_SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(BIN)$(EXEC) 


$(BIN)$(EXEC): $(MAIN) 
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: src/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)