TEST = tests.o
BENCHMARK = benchmark.o

DEFINES = NONE
CXX = c++
TESTSRC = BSTtests.cpp 
BENCHSRC = BSTtestBenchmarks.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D $(DEFINES)

all: $(TEST) $(BENCHMARK) 

docs: 
	doxygen docs/Doxyfile

$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

$(BENCHMARK): $(BENCHSRC)
	$(CXX) -g $< -o $(BENCHMARK) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

.PHONY: all docs
