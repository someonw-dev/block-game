SRC_DIR = src

# gets all sources in src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

LIBS = -lSDL3

all:
	g++ $(SRCS) $(LIBS) main.cpp -o main.o

