CXX=g++
OBJ= src/wcc.o src/human.o src/ork.o src/elves.o src/undead.o src/race.o src/settings.o 
CXXFLAGS= -O3
LIBS=
TARGET=wcc

all:  $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS) 

clean: 
	@rm -f src/*.o
	@rm -vf $(TARGET)
	@echo "done."
