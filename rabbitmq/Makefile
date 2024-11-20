CXX = g++
CXXFLAGS = -std=c++11 -fPIC $(shell pkg-config swipl --cflags)
LD = swipl-ld
LDFLAGS = -shared -lstdc++ -lqpid-proton-cpp -lqpid-proton-core -std=c++11

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)
EXEC = rabbitmq.so

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.o

mrproper: clean
	rm -f $(EXEC)
