CXX = g++
CXXFLAGS = -Wall -std=c++17

all: Grammar2CNF

Grammar2CNF: main.o Grammar.o Production.o GrammarConverter.o
	$(CXX) $(CXXFLAGS) -o Grammar2CNF main.o Grammar.o Production.o GrammarConverter.o

main.o: main.cpp Grammar.h GrammarConverter.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Grammar.o: Grammar.cpp Grammar.h Production.h
	$(CXX) $(CXXFLAGS) -c Grammar.cpp

Production.o: Production.cpp Production.h
	$(CXX) $(CXXFLAGS) -c Production.cpp

GrammarConverter.o: GrammarConverter.cpp GrammarConverter.h Grammar.h
	$(CXX) $(CXXFLAGS) -c GrammarConverter.cpp

clean:
	rm -f *.o Grammar2CNF
