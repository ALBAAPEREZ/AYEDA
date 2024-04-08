CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = CellACE110.cc CellACE30.cc CellLife23_3.cc CellLife51_346.cc Lattice1D.cc Lattice1D_open.cc Lattice1D_periodic.cc Lattice2D.cc Lattice2D_noborder.cc Lattice2D_reflective.cc main.cc Position.cc
OBJ = $(SRC:.cc=.o)
EXEC = juegovida

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)