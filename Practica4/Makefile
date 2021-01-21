CXX = g++
INCLUDE = include
CPPFLAGS = -Wall -g -c
OBJ = obj
SRC = src
BIN = bin

all : run

run : $(BIN)/problema4
	  $(BIN)/problema4 ejemplo
		$(BIN)/problema4 aleatorio
		$(BIN)/problema4 6 2 6 8 4 7 5 9 1 3 6 5 5 8 1 3 4

$(BIN)/problema4 : $(OBJ)/problema4.o
	$(CXX) -o $(BIN)/problema4 $(OBJ)/problema4.o -I$(INCLUDE)

$(OBJ)/problema4.o : $(SRC)/problema4.cpp
	$(CXX) $(CPPFLAGS) -o $(OBJ)/problema4.o $(SRC)/problema4.cpp -I$(INCLUDE)

clean :
	@echo "Eliminando archivos..."
	rm $(OBJ)/problema4.o
	rm $(BIN)/problema4
