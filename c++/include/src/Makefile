TEST = tests.o
PERFORMANCE = performances.o

DEFINES = NONE
CXX = c++
TESTSRC = BST_Tests.cpp 
PERFSRC = BST_TestPerformances.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D $(DEFINES)

all: $(TEST) $(PERFORMANCE) 

docs: 
	doxygen docs/Doxyfile

$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

$(PERFORMANCE): $(PERFSRC)
	$(CXX) -g $< -o $(PERFORMANCE) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

.PHONY: all docs
