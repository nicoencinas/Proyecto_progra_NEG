TARGET   = castle
DATA     = castle.dat
CC       = gcc

CFLAGS   = -Wall -ansi -pedantic -g -Iinclude -Itests
LDFLAGS  = -Llib -lscreen

# Carpetas
SRC_DIR      = src
INC_DIR      = include
OBJ_DIR      = obj
LIB_DIR      = lib
TEST_DIR     = tests
DOC_DIR      = doc
BIN_DIR      = bin
OBJ_TEST_DIR = $(OBJ_DIR)/tests

#MAIN

all: directories $(BIN_DIR)/$(TARGET)

directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(OBJ_TEST_DIR) $(DOC_DIR)

# Castle

$(BIN_DIR)/$(TARGET): $(OBJ_DIR)/command.o $(OBJ_DIR)/game_loop.o $(OBJ_DIR)/game.o \
                      $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/space.o $(OBJ_DIR)/game_reader.o \
                      $(OBJ_DIR)/object.o $(OBJ_DIR)/player.o $(OBJ_DIR)/game_actions.o \
                      $(OBJ_DIR)/set.o $(OBJ_DIR)/character.o $(OBJ_DIR)/link.o \
                      $(OBJ_DIR)/inventory.o
	$(CC) -o $@ $^ $(LDFLAGS)

# .o

$(OBJ_DIR)/command.o: $(SRC_DIR)/command.c $(INC_DIR)/command.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_loop.o: $(SRC_DIR)/game_loop.c $(INC_DIR)/graphic_engine.h $(INC_DIR)/game.h $(INC_DIR)/command.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game.o: $(SRC_DIR)/game.c $(INC_DIR)/game.h $(INC_DIR)/game_reader.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/graphic_engine.o: $(SRC_DIR)/graphic_engine.c $(INC_DIR)/graphic_engine.h $(INC_DIR)/libscreen.h $(INC_DIR)/command.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/space.o: $(SRC_DIR)/space.c $(INC_DIR)/space.h $(INC_DIR)/set.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_reader.o: $(SRC_DIR)/game_reader.c $(INC_DIR)/game_reader.h $(INC_DIR)/character.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/object.o: $(SRC_DIR)/object.c $(INC_DIR)/object.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_actions.o: $(SRC_DIR)/game_actions.c $(INC_DIR)/game_actions.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/player.o: $(SRC_DIR)/player.c $(INC_DIR)/player.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/set.o: $(SRC_DIR)/set.c $(INC_DIR)/set.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/character.o: $(SRC_DIR)/character.c $(INC_DIR)/character.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/link.o: $(SRC_DIR)/link.c $(INC_DIR)/link.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/inventory.o: $(SRC_DIR)/inventory.c $(INC_DIR)/inventory.h 
	$(CC) $(CFLAGS) -c $< -o $@

# Test
$(TEST_DIR)/set_test: $(OBJ_TEST_DIR)/set_test.o $(OBJ_DIR)/set.o 
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_DIR)/object_test: $(OBJ_TEST_DIR)/object_test.o $(OBJ_DIR)/object.o 
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_DIR)/link_test: $(OBJ_TEST_DIR)/link_test.o $(OBJ_DIR)/link.o 
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_DIR)/space_test: $(OBJ_TEST_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_DIR)/inventory_test: $(OBJ_TEST_DIR)/inventory_test.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_DIR)/player_test: $(OBJ_TEST_DIR)/player_test.o $(OBJ_DIR)/player.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(TEST_DIR)/character_test: $(OBJ_TEST_DIR)/character_test.o $(OBJ_DIR)/character.o 
	$(CC) -o $@ $^ $(LDFLAGS)


$(OBJ_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: directories $(TEST_DIR)/set_test $(TEST_DIR)/object_test $(TEST_DIR)/link_test \
                 $(TEST_DIR)/space_test $(TEST_DIR)/inventory_test $(TEST_DIR)/player_test \
                 $(TEST_DIR)/character_test

run: all 
	@# Ejecuta el juego desde bin/ buscando el .dat en la raíz
	cd $(BIN_DIR) && ./$(TARGET) ../$(DATA)

runlog: all 
	cd $(BIN_DIR) && ./$(TARGET) ../$(DATA) -l logfile.log

doxygen:
	@doxygen Doxyfile
	@echo "Documentación generada en $(DOC_DIR)/"

clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)
	rm -f $(TEST_DIR)/*_test
	@echo "Limpieza completada."