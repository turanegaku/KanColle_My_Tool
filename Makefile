CXX				= g++
CXXFLAGS	= -std=c++11 -Wall
SRCDIR		= ./source

origin: $(SRCDIR)/aircalc.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@.o

upstream: $(SRCDIR)/KanColle_Tool.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@.o

clean:
	-rm -f upstream
