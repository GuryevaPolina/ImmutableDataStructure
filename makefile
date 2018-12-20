COMPILER=g++ -std=c++0x
EXT=cpp
CFLAGS=-Wall -Werror
EXECUTABLE=start

SOURCES=$(shell find . -name "*.$(EXT)")

all: $(SOURCES)
	$(COMPILER) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) -lpthread
clean:
	rm -f *.o $(EXECUTABLE)
