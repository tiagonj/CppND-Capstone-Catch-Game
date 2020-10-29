# Udacity C++ Nanodegree Capstone project: Catch!

## Background

Back in 2006 the final project for my Microprocessors course (later renamed to Computer Architeture) in university was to program a game from scratch, in assembly language, that would run on a simulated processor, [P3](https://goncalomb.github.io/p3doc/).

Dubbed _Apanha da Azeitona_ (_Olive Harvest_), the game consisted of:
* An ASCII representation of a basket (`\______/`), located at the bottom of the screen, which could be moved left and right, and
* Pseudo-randomly generated ASCII olives (`O`) which would drop down from the top of the screen.

Points, shown on an array of four 7-segment displays, would be accrued whenever the player successfully managed to catch an olive. Additionally the game could be paused, and there may have been further (minor) features which I've forgotten by now.

I have fond memories of feeling a great sense of pride for having created something which at the time seemed so complex and involved, and which I could interact with in the form of a game.


## Catch!

Fast forward to 2020. For my Udacity C++ Nanodegree Capstone project I have decided to honour my 2006 bright-eyed self by implementing a game which uses the same gameplay elements of _Apanha da Azeitona_, and thus showcase some learnings from this Nanodegree.

The game, _Catch!_, features the same gameplay style as its spiritual predecessor:
* A "basket" which can be moved left and right, and
* Pseudo-randomly generated objects which the player must catch in order to score points.


# How to build

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * For Ubuntu this is: `sudo apt-get install libsdl2-dev`
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)


## Basic Build Instructions

After cloning this repo you can

1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run: `./catch_game`.

or you can simply

1. Compile: `make build` (or `make debug`)
2. Run: `make run`

*Note:* as it stands, the game must be run from the `build` folder due to hardcoded file paths.


# How to play

Use the `left-arrow` and `right-arrow` keys on your keyboard to move the basket. Score points by catching falling objects. And beware of any objects that you're not supposed to catch ...

Press `P` to pause (and then unpause) the game.


# File / class structure

* `Application.h` / `Application.cpp`
  * Entry point (`main()`) and game loop management
* `Metronome.h` / `Metronome.cpp`
  * Automatic adjustment of frames/second based on measured game loop execution duration
* (...)

**TODO complete**

**TODO complete**

**TODO complete**

**TODO complete**


# Project rubric points addressed

## README
* ✅ A README with instructions is included with the project
* ✅ The README indicates which project is chosen
* ❌ [**TODO: INFO STILL BEING PUT TOGETHER!**] The README includes information about each rubric point addressed

## Compiling and Testing
* ✅ The submission must compile and run

## Loops, Functions, I/O
* ✅ The project demonstrates an understanding of C++ functions and control structures
  * **TODO** example
* ❌ [**TODO SPRITES**] The project reads data from a file and process the data, or the program writes data to a file
  * **TODO** examples
* ✅ The project accepts user input and processes the input
  * The `InputReader::ReadInputs()` method reads inputs from the keyboard  (using SDL library calls), specifically left & right arrow, as well as the `P` key (pause)

## Object Oriented Programming
* ✅ The project uses Object Oriented Programming techniques
  * The whole project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
* ✅ Classes use appropriate access specifiers for class members.
  * **TODO** examples
* ✅ Class constructors utilize member initialization lists
  * **TODO** examples
* ✅ Classes abstract implementation details from their interfaces
  * **TODO** examples
* ✅ Classes encapsulate behavior
  * **TODO** examples
* ✅ Classes follow an appropriate inheritance hierarchy
  * **TODO** examples
* ✅ Overloaded functions allow the same function to operate on different parameters
  * **TODO** examples
* ✅ Derived class functions override virtual base class functions
  * **TODO** examples
* ❌ Templates generalize functions in the project

## Memory Management
* ✅ The project makes use of references in function declarations
  * **TODO** examples
* ✅ The project uses destructors appropriately
  * **TODO** examples
* ✅ The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate
  * **TODO** examples
* ❌/✅ The project follows the Rule of 5
  * For this project we have not needed to use copy or move semantics on any of the project classes (they are used on smart pointer classes)
* ✅ The project uses move semantics to move data, instead of copying it, where possible
  * **TODO** examples
* ✅ The project uses smart pointers instead of raw pointers
  * **TODO** examples

## Concurrency
* ✅ The project uses multithreading
  * **TODO** examples
* ❌ A promise and future is used in the project
* ✅ A mutex or lock is used in the project
  * **TODO** examples
* ❌ A condition variable is used in the project
