SHELL = /bin/bash
CXX = g++
CXXFLAGS = -Wall -g -mavx2

TARGET = theTensor.out

# Define the source files
SRCS = $(shell find src -name "*.cc")
MAINFILE = test/test_03.cc

OBJS = $(SRCS:.cc=.o)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(FileName) $(TARGET) $(OBJS) $(MAINFILE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
