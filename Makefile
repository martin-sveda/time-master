# Root Makefile
COMPONENTS_DIR := components
APPLICATIONS_DIR := app

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra


# Directories
COMPONENTS := time-sources master-clock timer clock
APPLICATIONS := main

# Export common variables for sub-makefiles
export CXX CXXFLAGS 
export PROJECT_ROOT := $(CURDIR)

# Default target
all: components applications

components:
	for dir in $(COMPONENTS); do \
		$(MAKE) -C $(COMPONENTS_DIR)/$$dir; \
	done

applications: components
	for dir in $(APPLICATIONS); do \
		$(MAKE) -C $(APPLICATIONS_DIR)/$$dir; \
	done

clean:
	for dir in $(COMPONENTS); do \
		$(MAKE) -C $(COMPONENTS_DIR)/$$dir clean; \
	done
	for dir in $(APPLICATIONS); do \
		$(MAKE) -C $(APPLICATIONS_DIR)/$$dir clean; \
	done

.PHONY: all components applications clean