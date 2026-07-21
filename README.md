# Minesweeper

A classic Minesweeper game for Linux originally made for an Arduino project.

## Start

BUILD
 g++ -Wfatal-errors -Iinc -Iinc/help -std=c++23 src/*.cpp src/help/*.cpp -o bin/minesweeper

RUN
 ./bin/minesweeper


## Controls

At the moment you have to press enter after every input.

### Menu

START/QUIT
 w - up
 s - down
 e - choose option
 
SIZE
 w - increase
 s - decrease
 e - choose size **(x/y)**
 
### Game

 w - up
 s - down
 a - left
 d - right
 e - uncover
 f - set/remove flag
 
## Requirements

Linux - only tested with Debian 13
C++ - Compiler with **c++23** (might work with an older standard)
UTF-8 support (recommended) - e.g. KDE Plasma Console

## Known Problems

After starting the game there has to be an input before navigating the Menu works.
The Menu needs UTF-8 support. 
After loosing a row might get shifted to the right.

## Plans

Add a save file system to continue playing the last session.
Add support for other platforms.
Give an option to not use UTF-8.
Add the chance for a mine to every element.
