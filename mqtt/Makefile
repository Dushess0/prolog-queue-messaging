CXX = g++
CXXFLAGS = -std=c++11 -fPIC $(shell pkg-config swipl --cflags)  # Ensure both SWI-Prolog flags are included
LD = swipl-ld
LDFLAGS = -shared -lstdc++ -lmosquitto -std=c++11  # Correct linking with C++ stdlib and Mosquitto

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)
EXEC = mqtt.so

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^  # Link using swipl-ld

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<  # Compile source files into object files

clean:
	rm -f $(SRC_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
