CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 # -Wformat -g
LDFLAGS = -lcurl -lglfw -lGL -ldl # dodać dodatkowe biblioteki

# Ścieżki do plików nagłówkowych
INCLUDES = -Isrc/api # dodać -Isrc/folder
INCLUDES += -Isrc/interface/imgui -Isrc/interface/backends -Isrc/interface/implot -Isrc/interface/code

# Pliki źródłowe
SRCS = $(wildcard src/api/*.cpp) main.cpp # dodać $(wildcard src/folder/*.cpp)
SRCS += $(wildcard src/interface/backends/*.cpp)
SRCS += $(wildcard src/interface/code/*.cpp)
SRCS += $(wildcard src/interface/imgui/*.cpp)
SRCS += $(wildcard src/interface/implot/*.cpp)

OBJS = $(addprefix build/,$(notdir $(SRCS:.cpp=.o)))
TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(addprefix build/,$(notdir $(TEST_SRCS:.cpp=.o)))
EXECUTABLE = stock_assistant

.PHONY: all clean tests

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

build/%.o: src/api/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# przykładowy build do kopiowania
#
# build/%.o: src/folder/%.cpp
#     $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


build/%.o: src/interface/imgui/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: src/interface/backends/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: src/interface/implot/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: src/interface/code/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

tests: $(TEST_OBJS) $(filter-out build/main.o,$(OBJS))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o run_all_tests $^ $(LDFLAGS)

clean:
	rm -f build/*.o run_all_tests proi $(EXECUTABLE) $(OBJS)