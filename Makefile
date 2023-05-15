CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lcurl # dodać dodatkowe biblioteki
INCLUDES = -Isrc/api
SRCS = $(wildcard src/api/*.cpp) main.cpp
OBJS = $(addprefix build/,$(notdir $(SRCS:.cpp=.o)))
TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(addprefix build/,$(notdir $(TEST_SRCS:.cpp=.o)))
EXECUTABLE = proi

.PHONY: all clean test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

build/%.o: src/api/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# przykładowy build do kopiowania
#
# build/%.o: <ścieżka do plików>%.cpp
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

tests: $(TEST_OBJS) $(filter-out build/main.o,$(OBJS))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o run_tests $^ $(LDFLAGS)

clean:
	rm -f build/*.o run_tests $(EXECUTABLE)
