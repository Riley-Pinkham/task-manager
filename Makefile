# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Iinclude -Iinclude/model -Iinclude/repository -Iinclude/service -Iinclude/shared -Iinclude/controller
LDFLAGS = -lsqlite3

# Shared source files (used by both server and client)
SHARED_SOURCES = src/model/Task.cpp \
                 src/model/Column.cpp \
                 src/shared/TaskSerializer.cpp \
                 src/shared/ColumnSerializer.cpp \
                 src/shared/NetworkUtils.cpp \
                 src/shared/CommandModels.cpp \
                 src/shared/CommandSerializer.cpp

# Server-specific sources
SERVER_SOURCES = src/server/server.cpp \
                 $(SHARED_SOURCES) \
                 src/repository/TaskRepository.cpp \
                 src/service/TaskService.cpp \
                 src/controller/NotificationManager.cpp \
                 src/controller/TaskCommandDispatcher.cpp

SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
SERVER_TARGET = server

# Client-specific sources
CLIENT_SOURCES = src/client/client.cpp \
                 src/shared/NetworkUtils.cpp \
                 src/shared/CommandSerializer.cpp \
                 src/shared/CommandModels.cpp \
                 src/model/Task.cpp

CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)
CLIENT_TARGET = client

# Default target - build both server and client
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Build server executable
$(SERVER_TARGET): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJECTS) -o $(SERVER_TARGET) $(LDFLAGS) -lpthread

# Build client executable
$(CLIENT_TARGET): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJECTS) -o $(CLIENT_TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(SERVER_TARGET) $(CLIENT_TARGET)
	find . -type f -name "*.o" -delete

# Individual build targets
server: $(SERVER_TARGET)
client: $(CLIENT_TARGET)

# Phony targets
.PHONY: all clean server client
