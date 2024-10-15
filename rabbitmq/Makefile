CXX = g++
CXXFLAGS = -std=c++11 -fPIC $(shell pkg-config swipl --cflags)  # Include SWI-Prolog flags
LD = swipl-ld
LDFLAGS = -shared -lstdc++ -lrabbitmq -std=c++11  # Link with C++ stdlib and RabbitMQ library

SRC_DIR = src
BUILD_DIR = build  # Directory for object files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)
EXEC = rabbitmq.so

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^  # Link using swipl-ld

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<  # Compile source files into object files


clean:
	rm -f $(BUILD_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
