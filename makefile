PROGRAM = tetris
VERSION = 0.1

OUT = $(PROGRAM)-$(VERSION)

SRC_DIR = src
# gets all sources in src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

LIBS = -lSDL3

all:
	g++ $(SRCS) $(LIBS) main.cpp -o $(OUT)

run: all
	./$(OUT)
