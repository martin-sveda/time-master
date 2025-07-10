# Component-specific makefile
COMPONENT_NAME := time-sources

# Directories
SRC_DIR := src/$(COMPONENT_NAME)
INC_DIR := include
OBJ_DIR := obj
LIB_DIR := lib

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Include paths
INCLUDES := -I$(INC_DIR) \
#           -I$(PROJECT_ROOT)/components/xxxxx

# Library name
LIB := $(LIB_DIR)/lib$(COMPONENT_NAME).a

# Additional flags
CXXFLAGS += $(INCLUDES)

# Targets
all: directories $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

directories:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

.PHONY: all directories clean
