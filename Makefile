TARGET = castle
DATA=castle.dat
CC = gcc
CFLAGS = -Wall -ansi -pedantic -c -g

LDFLAGS = -L. -lscreen 

$(TARGET): command.o game_loop.o game.o graphic_engine.o space.o game_reader.o object.o player.o game_actions.o set.o character.o link.o inventory.o
	$(CC) -o $(TARGET) command.o game_loop.o game.o graphic_engine.o space.o game_reader.o object.o player.o game_actions.o set.o character.o link.o  inventory.o $(LDFLAGS)

command.o: command.c command.h
	$(CC) $(CFLAGS) command.c

game_loop.o: game_loop.c graphic_engine.h game.h command.h
	$(CC) $(CFLAGS) game_loop.c

game.o: game.c game.h game_reader.h
	$(CC) $(CFLAGS) game.c

graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h command.h
	$(CC) $(CFLAGS) graphic_engine.c

space.o: space.h space.c set.h
	$(CC) $(CFLAGS) space.c

game_reader.o: game_reader.c game_reader.h character.h
	$(CC) $(CFLAGS) game_reader.c

object.o: object.c object.h
	$(CC) $(CFLAGS) object.c

game_actions.o: game_actions.c game_actions.h
	$(CC) $(CFLAGS) game_actions.c

player.o: player.c player.h
	$(CC) $(CFLAGS) player.c

set.o: set.h set.c
	$(CC) $(CFLAGS) set.c

character.o: character.h character.c
	$(CC) $(CFLAGS) character.c

link.o: link.c link.h
	$(CC) $(CFLAGS) link.c

inventory.o: inventory.c inventory.h
	$(CC) $(CFLAGS) inventory.c
clean:
	rm -rf *.o $(TARGET)
run:
	./$(TARGET) $(DATA)
runlog:
	./$(TARGET) $(DATA) -l logfile.log