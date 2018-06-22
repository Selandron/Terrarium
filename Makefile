CC=g++

MAIN=main.o
TINYXML2=tinyxml2.o
MANAGER=resourcemanager.o resourcetexture.o resourcesoundbuffer.o resourcemusic.o resourcefont.o resourcetext.o
STATES=gamemanager.o gamestateloading.o gamestatemenu.o

EXEC=terrarium.exe
HEADERS=-Iheaders\tinyxml2 -Iheaders\engine\manager -Iheaders\engine\errors -Iheaders\engine\states -Iheaders\states
BIN=./bin/
PATH_SFML=E:\DataEtienne\Biblio\SFML-2.5.0
CFLAGS=-W -Wall -ansi -std=c++11 -I$(PATH_SFML)\include $(HEADERS)
LDFLAGS=-L$(PATH_SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(BIN)$(EXEC) 


$(BIN)$(EXEC): $(MAIN) $(TINYXML2) $(MANAGER) $(STATES)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: src/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

%.o: src/tinyxml2/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)  

%.o: src/engine/manager/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

%.o: src/engine/states/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: src/states/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)