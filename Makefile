CXX				= g++
CXXFLAGS	= -std=c++11 -Wall
SRCDIR		= ./source

upstream: $(SRCDIR)/KanColle_Tool.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	-rm -f upstream
