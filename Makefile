CC := g++
CFLAGS = -std=c++11 -Wall -Werror -Wpedantic -I$(INCLUDE_DIR) -I$(INCLUDE_PLAYER_DIR) -I$(INCLUDE_GAME_DIR) -I$(INCLUDE_UTILS_DIR)

BUILD_DIR := ./bin

INCLUDE_DIR := ./include
INCLUDE_PLAYER_DIR := $(INCLUDE_DIR)/personas
INCLUDE_GAME_DIR := $(INCLUDE_DIR)/game
INCLUDE_UTILS_DIR := $(INCLUDE_DIR)/utils

OBJ_DIR := ./obj
PLAYER_OBJ_DIR := $(OBJ_DIR)/player
GAME_OBJ_DIR := $(OBJ_DIR)/game
UTILS_OBJ_DIR := $(OBJ_DIR)/utils

SRC_DIR := ./src
PLAYER_SRC_DIR := $(SRC_DIR)/player
GAME_SRC_DIR := $(SRC_DIR)/game
UTILS_SRC_DIR := $(SRC_DIR)/utils

SAVE_DIR := ./saves
TEST_DIR := ./tests
EXECUTABLE := tp

PLAYER_SRC := $(shell find $(PLAYER_SRC_DIR) -name '*.cpp')
GAME_SRC := $(shell find $(GAME_SRC_DIR) -name '*.cpp')
UTILS_SRC := $(shell find $(UTILS_SRC_DIR) -name '*.cpp')

PLAYER_OBJ := $(PLAYER_SRC:${PLAYER_SRC_DIR}/%.cpp=${PLAYER_OBJ_DIR}/%.o)
GAME_OBJ := $(GAME_SRC:${GAME_SRC_DIR}/%.cpp=${GAME_OBJ_DIR}/%.o)
UTILS_OBJ := $(UTILS_SRC:${UTILS_SRC_DIR}/%.cpp=${UTILS_OBJ_DIR}/%.o)

all: $(OBJ_DIR) $(BUILD_DIR) $(SAVE_DIR) $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJ_DIR)/appEntry.o $(PLAYER_OBJ) $(GAME_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/appEntry.o: $(SRC_DIR)/appEntry.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(PLAYER_OBJ_DIR)/%.o: $(PLAYER_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(GAME_OBJ_DIR)/%.o: $(GAME_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_OBJ_DIR)/%.o: $(UTILS_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR) && mkdir -p player game utils

$(SAVE_DIR):
	mkdir -p $(SAVE_DIR)

clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR) *.o
	rm -f $(EXECUTABLE)