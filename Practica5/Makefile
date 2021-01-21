CXX = g++
INCLUDE = include
CPPFLAGS = -Wall -g -c
OBJ = obj
SRC = src
BIN = bin

all : run

run : $(BIN)/problema9
		$(BIN)/problema9 aleatorio
		$(BIN)/problema9 ejemplo
		$(BIN)/problema9 12 0 -30 35 -13 -31 38 -34 -39 -6 28 16 -34

$(BIN)/problema9 : $(OBJ)/problema9.o
	$(CXX) -o $(BIN)/problema9 $(OBJ)/problema9.o -I$(INCLUDE)

$(OBJ)/problema9.o : $(SRC)/problema9.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/problema9.o $(SRC)/problema9.cpp -I$(INCLUDE)

clean :
	@echo "Eliminando archivos..."
	rm $(OBJ)/problema9.o
	rm $(BIN)/problema9

#$(BIN)/problema9 ejemplo
#$(BIN)/problema9 aleatorio
