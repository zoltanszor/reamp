GCC = g++-8

FLAGS = -Wall -O3 
STANDARD = -std=c++11
SOURCE = main.cpp \
	testroutines.cpp \
	fourvector.cpp \
        scalaramplitude.cpp

OBJ = $(addsuffix .o, $(basename $(SOURCE)))

all: $(OBJ)
	$(GCC) $(OBJ)  -o nlo4d.out

%.o: %.cpp
	$(GCC) $(STANDARD) $(FLAGS) -c -o $@ $^
