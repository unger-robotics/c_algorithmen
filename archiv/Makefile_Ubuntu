# -*- Makefile -*-
# Ubuntu
# gcc -v // Version 7.2
# sudo apt -y install gcc-7 g++-7 
# 14.1.18

TARGETS=\
	halloC_001.x \
	halloC++_001.x \
	bitweisesEinerkomplement.x \
	bitweisesODER.x \
	bitweisesUND.x \
	bitweisesXOR.x \
	bitweiseVerschiebung.x \
	halloWelt.x \
	logik.x \
	mitZuruecklegen.x \
	modulo.x \

CC:=gcc-7
CLIBS=-lz meineFkt.c meineFkt.h -lm
CFLAGS=-Wall -Wextra -std=c11 -lpthread -pthread -O0 -Wno-missing-field-initializers -g
CXX:=g++-7
CXXLIBS=-lz meineFkt.c meineFkt.h -lm
CXXFLAGS=-Wall -Wextra -std=c++11 -lpthread -pthread -O0 -Wno-missing-field-initializers -g
CXX14FLAGS=-Wall -Wextra -std=c++1y -lpthread -pthread -O0 -Wno-missing-field-initializers -g
CXX17FLAGS=-Wall -Wextra -std=c++17 -lpthread -pthread -O0 -Wno-missing-field-initializers -g

all: $(TARGETS)

%.x: %.cpp
	$(CXX) $(CXX17FLAGS) -o $@ $< $(CXXLIBS)

%.x: %.c
	$(CC) $(CFLAGS) -o $@ $< $(CLIBS)

clean:
	#rm -f *.o 
	rm -f *.x

