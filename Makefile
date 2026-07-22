CPPFLAGS = -std=c++23 -Iinc
LIBS = -lncurses -lstdc++

FILES = $(wildcard src/*.cpp) $(wildcard src/help/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(FILES))

obj/%.o: src/%.cpp
	g++ $(CPPFLAGS) -c $< -o $@

bin/minesweeper: $(OBJECTS)
	g++ $^ -o $@ $(LIBS)

clean:
	rm obj/*.o
	rm obj/help/*.o
