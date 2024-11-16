# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Added Features
* User enters name at start; Score, Length and Time elapsed are printed to <Name>.results.txt in local directory
* Game can be paused and restarted by toggling the spacebar
* Player name displayed in window title
* Poison placed on game grid. Lose point if snake passes over it. Game ends when score is negative.
* Randomly moving bomb object placed on grid.

## Rubric Elements

### README (All Rubric Points REQUIRED)

* A README with instructions is included with the project
* The README indicates the new features you added to the game.
* The README includes information about each rubric point addressed.



### Compiling and Testing (All Rubric Points REQUIRED)

### Loops, Functions, I/O - meet at least 2 criteria

* The project reads data from a file and process the data, or the program writes data to a file:
  Score, length and time elapsed are written to a new file, or appended to an existing file
* The project accepts user input and processes the input:
  The name of the player is read in to the console and used as the base for the output file, also player
  name is displayed in the frame of the game. Game reads input from keyboard to pause or restart the game 
  by toggling the spacebar.

### Object Oriented Programming - meet at least 3 criteria
* One or more classes are added to the project with appropriate access specifiers for class members:
Bomb class is added to the program
* Class constructors utilize member initialization lists: Bomb class is initialized with initialization list.
* Templates generalize functions or classes in the project: Game::PlaceItem is defined using a template, to
  accept food and poison variables, or Bomb object.

### Memory Management - meet at least 3 criteria
* The project makes use of references in function declarations: 
  * Game::PlaceItem is called with a reference to variable item in game.cpp. 
  * Snake::Update and Bomb::Update called with references to objects snake and bomb in threads t1 and t2

### Concurrency - meet at least 2 criteria
* The project uses multithreading: Snake::Update() and Bomb::Update() run in separate threads that are joined 
  at the end of Game::Update()

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
