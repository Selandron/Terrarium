CC=g++

MAIN=main.o
TINYXML2=tinyxml2.o
ENGINE=resourcemanager.o resourcetexture.o resourcesoundbuffer.o resourcemusic.o resourcefont.o

EXEC=terrarium.exe
HEADERS=-Iheaders\tinyxml2 -Iheaders\engine
BIN=./bin/
PATH_SFML=D:\Bibliotheque\SFML-2.4.2
CFLAGS=-W -Wall -ansi -std=c++11 -pedantic -I$(PATH_SFML)\include $(HEADERS)
LDFLAGS=-L$(PATH_SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(BIN)$(EXEC) 


$(BIN)$(EXEC): $(MAIN) $(TINYXML2) $(ENGINE)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: src/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

%.o: src/tinyxml2/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)  

%.o: src/engine/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)