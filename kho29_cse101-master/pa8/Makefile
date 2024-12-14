#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN2		   = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
SOURCE2        = $(MAIN2).cpp
OBJECT2        = $(MAIN2).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

all: WordFrequency Order

WordFrequency: WordFrequency.o Dictionary.o
	g++ -std=c++17 -Wall -o WordFrequency WordFrequency.o Dictionary.o

WordFrequency.o: WordFrequency.cpp Dictionary.h
	g++ -std=c++17 -Wall -c WordFrequency.cpp

Order: Order.o Dictionary.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

Order.o: Order.cpp Dictionary.h
	g++ -std=c++17 -Wall -c Order.cpp

DictionaryTest: DictionaryTest.o Dictionary.o
	g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryTest.o: Dictionary.h DictionaryTest.cpp
	g++ -std=c++17 -Wall -c DictionaryTest.cpp

Dictionary.o: Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -c Dictionary.cpp

clean:
	rm -f WordFrequency WordFrequency.o Order Order.o DictionaryTest DictionaryTest.o Dictionary.o

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) GutenBerg.txt

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)