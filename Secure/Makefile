# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lssl -lcrypto

# Target executable
TARGET = secure_login

# Source files
SRCS = secure_login.cpp functions.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = headers.hpp

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Clean the database file
clean-db:
	rm -f database

# Rebuild from scratch
rebuild: clean all

# Phony targets
.PHONY: all clean clean-db rebuild