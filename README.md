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

The game, _Catch!_ features the same gameplay style as its spiritual predecessor:
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
