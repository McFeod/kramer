CC=mpic++
NP=11
EQUATIONS=10
CFLAGS=-c -Wall --std=c++14 -fopenmp
LFLAGS=-fopenmp
BIN=bin
SRC=src
EXECUTABLE=kramer
SOURCES=main.cpp square_matrix.cpp determinant.cpp linear_system_input.cpp
OBJECTS=$(SOURCES:.cpp=.o)
OBJ_FILES=$(OBJECTS:%=${BIN}/%)


all: $(SOURCES) $(EXECUTABLE) run


test: equations run


equations:
	python3 generate.py $(EQUATIONS)


run:
	mpiexec -np $(NP) $(BIN)/$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJ_FILES) -o $(BIN)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(BIN)/$@

clean:
	rm -r $(BIN)
	mkdir $(BIN)
