# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Linker Hardening Flags
# 1. -Wl,-z,relro: Makes certain sections of the binary read-only after relocation.
# 2. -Wl,-z,now: Resolves all symbols at startup to prevent PLT/GOT hijacking.
LDFLAGS = -lssl -lcrypto -Wl,-z,relro -Wl,-z,now

# Security Hardening Flags
# 1. -fstack-protector-all: Adds stack canaries to all functions to prevent stack smashing.
# 2. -D_FORTIFY_SOURCE=2: Adds checks for dangerous buffer operations at compile/runtime.
# 3. -O2: Required for _FORTIFY_SOURCE to work effectively.
HARDENING_FLAGS = -fstack-protector-all -D_FORTIFY_SOURCE=2 -O2

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
	$(CXX) $(CXXFLAGS) $(HARDENING_FLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(HARDENING_FLAGS) -c $< -o $@

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