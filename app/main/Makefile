# Application-specific makefile
APP_NAME := main

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Include paths for all components
INCLUDES := -I$(INC_DIR) \
           -I$(PROJECT_ROOT)/components/time-sources/include \
           -I$(PROJECT_ROOT)/components/master-clock/include \

# Libraries
LIBS := -L$(PROJECT_ROOT)/components/time-sources/lib -ltime-sources \
        -L$(PROJECT_ROOT)/components/master-clock/lib -lmaster-clock \

# Flags
CXXFLAGS += $(INCLUDES)
LDFLAGS := $(LIBS)

# Output binary
BIN := $(BIN_DIR)/$(APP_NAME)

# Targets
all: directories $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all directories clean