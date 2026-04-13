TARGET = castle
DATA   = castle.dat
CC     = gcc
CFLAGS = -Wall -ansi -pedantic -c -g
LDFLAGS = -L. -lscreen
TESTS = set_test object_test link_test space_test inventory_test player_test character_test
 
$(TARGET): command.o game_loop.o game.o graphic_engine.o space.o game_reader.o \
           object.o player.o game_actions.o set.o character.o link.o inventory.o
	$(CC) -o $(TARGET) command.o game_loop.o game.o graphic_engine.o space.o \
	      game_reader.o object.o player.o game_actions.o set.o character.o \
	      link.o inventory.o $(LDFLAGS)
 
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
 
tests: $(TESTS)
 
set_test: set_test.o set.o
	$(CC) -o set_test set_test.o set.o
 
set_test.o: set_test.c set_test.h set.h test.h
	$(CC) $(CFLAGS) set_test.c
 
object_test: object_test.o object.o
	$(CC) -o object_test object_test.o object.o
 
object_test.o: object_test.c object_test.h object.h test.h
	$(CC) $(CFLAGS) object_test.c
 
link_test: link_test.o link.o
	$(CC) -o link_test link_test.o link.o
 
link_test.o: link_test.c link_test.h link.h test.h
	$(CC) $(CFLAGS) link_test.c
 
space_test: space_test.o space.o set.o
	$(CC) -o space_test space_test.o space.o set.o
 
space_test.o: space_test.c space_test.h space.h test.h
	$(CC) $(CFLAGS) space_test.c
 
inventory_test: inventory_test.o inventory.o set.o
	$(CC) -o inventory_test inventory_test.o inventory.o set.o
 
inventory_test.o: inventory_test.c inventory_test.h inventory.h test.h
	$(CC) $(CFLAGS) inventory_test.c
 
player_test: player_test.o player.o inventory.o set.o
	$(CC) -o player_test player_test.o player.o inventory.o set.o
 
player_test.o: player_test.c player_test.h player.h test.h
	$(CC) $(CFLAGS) player_test.c
 
character_test: character_test.o character.o
	$(CC) -o character_test character_test.o character.o
 
character_test.o: character_test.c character_test.h character.h test.h
	$(CC) $(CFLAGS) character_test.c

clean:
	rm -rf *.o $(TARGET) $(TESTS)
 
run:
	./$(TARGET) $(DATA)
 
runlog:
	./$(TARGET) $(DATA) -l logfile.log
 