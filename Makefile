CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lcurl # dodać dodatkowe biblioteki

# Ścieżki do plików nagłówkowych
INCLUDES = -Isrc/api -Isrc/sort # dodać -Isrc/folder

# Pliki źródłowe
SRCS = $(wildcard src/api/*.cpp) $(wildcard src/sort/*.cpp) main.cpp # dodać $(wildcard src/folder/*.cpp)

OBJS = $(addprefix build/,$(notdir $(SRCS:.cpp=.o)))
TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(addprefix build/,$(notdir $(TEST_SRCS:.cpp=.o)))
EXECUTABLE = asystent_gieldowy

.PHONY: all clean tests

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

build/%.o: src/api/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# przykładowy build do kopiowania
#
# build/%.o: src/folder/%.cpp
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/%.o: src/sort/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

tests: $(TEST_OBJS) $(filter-out build/main.o,$(OBJS))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o run_all_tests $^ $(LDFLAGS)

clean:
	rm -f build/*.o run_all_tests proi $(EXECUTABLE)
