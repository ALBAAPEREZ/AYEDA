CXX = g++
CXXFLAGS = -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = AuxiliarFunctions.cc main.cc
OBJ = $(SRC:.cc=.o)
EXEC = hash

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)