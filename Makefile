.PHONY: clean all


SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)   ## $(VAR:PATERN=REPLACEMENT)
CXXFLAGS = -Wall $(shell sdl2-config --cflags --libs)
LDFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2
CXX = g++


all: out/flexCE


clean:
	@rm -rf out/* obj/*


out/flexCE: $(OBJ) | out   ## create the executable from the objects
	@echo "Linking objects..."
	@$(CXX) $(OBJ) -o out/flexCE $(LDFLAGS)


obj/%.o: src/%.cpp | obj     ## build the objects from the .cpp files  ($< is dependency, $@ is name)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@



out:   ## ensure the out dir exist
	@mkdir -p out

obj:   ## ensure the obj dir exist
	@mkdir -p obj
