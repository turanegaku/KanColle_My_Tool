CXX				= g++
CXXFLAGS	= -std=c++11 -Wall
SRCDIR		= ./source

run: origin.o
	./origin.o

origin.o: $(SRCDIR)/aircalc.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

upstream.o: $(SRCDIR)/KanColle_Tool.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	-rm -f *.o
