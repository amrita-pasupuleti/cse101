#------------------------------------------------------------------------------
#  Amrita Pasupuleti
#  apasupul
#  2024 Winter CSE101 PA8
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#  make OrderCheck          runs Order under valgrind on Gutenberg
#------------------------------------------------------------------------------

ADT            = Dictionary
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
ADT_TEST       = $(ADT)Client

WORD_MAIN      = WordFrequency
WORD_SOURCE    = $(WORD_MAIN).cpp
WORD_OBJECT    = $(WORD_MAIN).o

ORDER_MAIN     = Order
ORDER_SOURCE   = $(ORDER_MAIN).cpp
ORDER_OBJECT   = $(ORDER_MAIN).o

COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(WORD_MAIN): $(WORD_OBJECT) $(ADT_OBJECT)
	$(LINK) $(WORD_MAIN) $(WORD_OBJECT) $(ADT_OBJECT)

$(WORD_OBJECT): $(WORD_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(WORD_SOURCE)

$(ORDER_MAIN): $(ORDER_OBJECT) $(ADT_OBJECT)
	$(LINK) $(ORDER_MAIN) $(ORDER_OBJECT) $(ADT_OBJECT)

$(ORDER_OBJECT): $(ORDER_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ORDER_SOURCE)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

clean:
	$(REMOVE) $(WORD_MAIN) $(ORDER_MAIN) $(ADT_TEST) $(WORD_OBJECT) $(ORDER_OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

WordFrequencyCheck: $(WORD_MAIN)
	$(MEMCHECK) $(WORD_MAIN) Gutenberg myGutenberg-out

OrderCheck: $(ORDER_MAIN)
	$(MEMCHECK) $(ORDER_MAIN) in5 junk5

DictionaryCheck: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
