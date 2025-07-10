CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread
TARGET = time-master
SRC = main.cpp clock.cpp timer.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

