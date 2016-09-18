CXX=g++
FLAGS= -g -Wall -gstats
OBJ= src/wcc.o src/human.o src/ork.o src/elves.o src/undead.o src/race.o src/settings.o src/io.o src/init.o 
TARGET=wcc

all:  $(OBJ)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJ) 

clean: 
	@rm -f src/*.o
	@rm -vf $(TARGET)
	@echo "done."
