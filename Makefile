SHELL = /bin/bash
CXX = g++
CXXFLAGS = -Wall -g

TARGET = theTensor.out

# Define the source files
SRCS = $(shell find src -name "*.cc")
MAINFILE = test/test_01.cc

override TARGET ?= $(TARGET)
override MAINFILE ?= $(MAINFILE)

OBJS = $(SRCS:.cc=.o)

# Check for SIMD flag
ifdef SIMD
	CXXFLAGS += $(SIMD)
endif

$(TARGET): $(OBJS)
	@if [ ! -d "dist" ]; then \
		echo "creating dist/ folder"; \
		mkdir dist; \
	fi
	$(CXX) $(CXXFLAGS) -o dist/$(TARGET) $(OBJS) $(MAINFILE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)