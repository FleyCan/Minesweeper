CPPFLAGS = -std=c++23
INC = -Iinc
LIBS = -lncurses -lstdc++

HEADERS = $(wildcard inc/*.hpp) $(wildcard inc/help/*.hpp)
FILES = $(wildcard src/*.cpp) $(wildcard src/help/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(FILES))
DEPENDS := $(OBJECTS:.o=.d)

bin/minesweeper: $(OBJECTS)
	g++ $(OBJECTS) -o $@ $(LIBS)

obj/%.o: src/%.cpp
	g++ $(CPPFLAGS) $(INC) -MMD -MP -c $< -o $@

.PHONY: clean

clean:
	rm -f obj/*.o
	rm -f obj/help/*.o
	rm -f obj/*.d
	rm -f obj/help/*.d

-include $(DEPENDS)
