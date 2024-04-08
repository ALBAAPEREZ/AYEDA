CXX = g++
CXXFLAGS = -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = FuncionesAuxiliares.cc main.cc
OBJ = $(SRC:.cc=.o)
EXEC = ordenacion

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)