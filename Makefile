# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Iinclude -Iinclude/model -Iinclude/repository -Iinclude/service -Iinclude/shared
LDFLAGS = -lsqlite3

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SOURCES = main.cpp \
          src/model/Task.cpp \
          src/model/Column.cpp \
          src/repository/TaskRepository.cpp \
		  src/service/TaskService.cpp \
		  src/shared/TaskSerializer.cpp \
		  src/shared/ColumnSerializer.cpp \
		  src/shared/NetworkUtils.cpp \
		  src/shared/CommandModels.cpp \
		  src/shared/CommandSerializer.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = main

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
