# Makefile for seed_gen

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./jsoncpp/include -I./csv-parser/include

# Linker flags
LDFLAGS = -L./jsoncpp/lib -ljsoncpp -L./csv-parser/lib -lcsv-parser

# Target executable
TARGET = seed_gen

# Source files
SRCS = seed_gen.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
