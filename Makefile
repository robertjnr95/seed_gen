# Compiler
CXX = g++

# Flags for compiling
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = seed_gen

# Source files
SRCS = seed_gen.cpp crypto_library.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Libraries (if any)
LIBS = -lcrypto -lboost_system

# Default rule to build the target executable
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build (removes the executable and object files)
clean:
	rm -f $(TARGET) $(OBJS)
