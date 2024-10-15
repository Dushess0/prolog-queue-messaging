CXX = g++
CXXFLAGS = -std=c++11 -fPIC $(shell pkg-config swipl dbus-1 --cflags)
LD = swipl-ld
LDFLAGS = -shared -lstdc++ -ldbus-1 -std=c++11  # Correctly link with C++ standard library and D-Bus

SRC_DIR = source
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)
EXEC = dbus.so

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^  # Link using swipl-ld

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<  # Compile source files into object files

clean:
	rm -f $(SRC_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
