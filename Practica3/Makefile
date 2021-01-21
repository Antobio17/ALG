CXX = g++
INCLUDE = include
CPPFLAGS = -Wall -g -c
OBJ = obj
SRC = src
BIN = bin

all : run

run : $(BIN)/problema3
	  $(BIN)/problema3 ejemplo
		$(BIN)/problema3 9 13
		$(BIN)/problema3 20 25
		$(BIN)/problema3 40 50

$(BIN)/problema3 : $(OBJ)/problema3.o
	$(CXX) -o $(BIN)/problema3 $(OBJ)/problema3.o -I$(INCLUDE)

$(OBJ)/problema3.o : $(SRC)/problema3.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/problema3.o $(SRC)/problema3.cpp -I$(INCLUDE)

clean :
	@echo "Eliminando archivos..."
	rm $(OBJ)/problema3.o
	rm $(BIN)/problema3
