CC=g++ --std=c++11

CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: doodleJump.out

doodleJump.out: main.o rsdl.o entities.o doodlejump_game.o enemy.o platforms.o doodler.o other_stuff.o
	$(CC) main.o rsdl.o entities.o doodlejump_game.o enemy.o platforms.o doodler.o other_stuff.o $(CCFLAGS) -o doodleJump.out

main.o: rsdl.hpp entities.hpp enemy.hpp platforms.hpp doodler.hpp other_stuff.hpp main.cpp
	$(CC) -c main.cpp -o main.o

rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o

entities.o: rsdl.hpp entities.hpp entities.cpp
	$(CC) -c entities.cpp -o entities.o

doodlejump_game.o: rsdl.hpp entities.hpp enemy.hpp platforms.hpp doodler.hpp other_stuff.hpp doodlejump_game.hpp doodlejump_game.cpp
	$(CC) -c doodlejump_game.cpp -o doodlejump_game.o

enemy.o: rsdl.hpp entities.hpp enemy.hpp enemy.cpp
	$(CC) -c enemy.cpp -o enemy.o

platforms.o: rsdl.hpp entities.hpp platforms.hpp platforms.cpp
	$(CC) -c platforms.cpp -o platforms.o

doodler.o: rsdl.hpp entities.hpp doodler.hpp doodler.cpp
	$(CC) -c doodler.cpp -o doodler.o

other_stuff.o: rsdl.hpp entities.hpp other_stuff.hpp other_stuff.cpp
	$(CC) -c other_stuff.cpp -o other_stuff.o


.PHONY: clean
clean:
	rm -r *.o