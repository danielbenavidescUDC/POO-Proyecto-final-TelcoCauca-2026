CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# En Windows agregar LDLIBS = -lws2_32
telcocauca: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) telcocauca
