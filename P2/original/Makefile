CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
LDFLAGS =

SRC = Cell.cc Lattice.cc main.cc
OBJ = $(SRC:.cc=.o)
EXEC = automata

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)