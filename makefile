CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Iinclude -O2

TARGET = build/main
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o) #changes .cpp files to .o files in the OBJ list

$(TARGET): $(OBJ) # Rule to create target : dependencies
	$(CXX) $(CXXFLAGS) $^ -o $@ 	
	#$^ becomes the dependencies -> OBJ
	#$@ becomes target -> TARGET
	# Full rule is: clang++ -std=c++17 -Wall -Iinclude build/main.o build/vec3.o -o build/main

build/%.o: src/%.cpp # rule to create .o files, each 1 comes from matching file in src/
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@
	# $< becomes the input cpp file
	# $@ becomes the 

clean:
	rm -rf build