SHELL = /bin/bash
CXX = g++
CXXFLAGS = -Wall -g -mavx2

TARGET = theTensor.out

# Define the source files
SRCS = $(shell find src -name "*.cc")
MAINFILE = test/test_01.cc

override TARGET ?= $(TARGET)
override MAINFILE ?= $(MAINFILE)

OBJS = $(SRCS:.cc=.o)

$(TARGET): $(OBJS)
	@if [ ! -d "dist" ]; then \
		echo "creating dist/ folder"; \
		mkdir dist; \
	fi
	$(CXX) $(CXXFLAGS) -o $(FileName) dist/$(TARGET) $(OBJS) $(MAINFILE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
