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
* A `Catcher` (i.e. "basket") which can be moved left and right, and
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
* SDL_Image extension >= 2.0
  * All installation instructions can be found [here](https://www.libsdl.org/projects/SDL_image/)
  * For Linux: `sudo apt-get install libsdl2-image-dev`
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

Use the `left-arrow` and `right-arrow` keys on your keyboard to move the basket. Score points by catching falling objects.

Press `P` to pause the game. Press `P` again to resume.

Close the game by closing the window.


# Disclaimer

This game has been put together as the Capstone project for my Udacity C++ Nanodegree, therefore it is definitely not a well-polished nor finished game! The emphasis has been on fulfiling the project rubric, not creating the best game, so don't judge it too harshly :)

The following is an incomplete list of areas for future development/improvement:
* Game dynamics
  * Levels
  * Lateral wind (varying)
  * Fallers with more varied falling dynamics
  * Physics
    * Fallers can rotate
    * Obstacles in the way of Fallers
    * Collisions between faller objects
    * Fallers can colide with (and bounce off) the sides of the catcher/basket
    * Advanced "obstacles" (e.g. elastics)
* Visuals
  * Make fallers fall all the way to the bottom of the screen
  * Make the catcher look like an actual basket
  * Visual confirmation of a catch
  * (Dynamic) Backgrounds
* Options menus
  * Difficulty settings
  * Game speed setings
* Other features
  * Save/Load game

# File & class structure

## Main application / game loop

* `Application.h` / `Application.cpp`
  * Defines the `Application` class and contains the entry point (`main()`)
  * Encapsulates logic to start, pause (pause loop), resume (game loop) and quit the game
  * Purposely agnostic of the rendering library used (SDL in this case)
* `Metronome.h` / `Metronome.cpp`
  * Defines the `Metronome` class (owned by the `Application`)
  * Provides automatic adjustment of frames/second based on measured game loop execution duration
* `Renderer.h` / `Renderer.cpp`
  * Defines the `Renderer` class (owned exclusively by the `Application`)
  * Uses SDL library to render the game window and all of its contents (Catcher & Fallers)
* `InputsReader.h` / `InputsReader.cpp`
  * Helper `namespace`
  * `InputReader::ReadInputs()` uses SDL library to read input from the keyboard
* `PositionLimits.h`
  * Human-readable position limits for the faller space
  * **Note:** position units are in percentage units (0.0 ~ 1.0) throughout the whole game codebase, and are only translated to pixels by the `Renderer`.

## Game "engine"

* `Game.h` / `Game.cpp`
  * Defines the `Game` class (owned exclusively by the `Application`)
  * Encapsulates game state and some game logic (e.g. interaction between Catcher & Fallers)
* `Catcher.h` / `Catcher.cpp`
  * Defines the `Catcher` class (owned exlusively by the `Game` object)
  * Encapsulates logic for moving the Catcher left & right
* `Faller.h` / `Faller.cpp`
  * Defines the `Faller` interface class
  * Encapsulates common `Faller` logic (e.g. motion equations)
  * Faller objects are initially owned exclusively by the corresponding `FallerFactory`, then ownership is moved to the `Game` object
* `FallerFactory.h` / `FallerFactory.cpp`
  * Defines the `FallerFactory` interface class
  * Encapsulates common `FallerFactory` logic (e.g. thread loop, pausing/resuming execution, generating & adding a new `Faller` to the `Game`)
  * Note these "factories" run as `std::thread`s (see `FallerFactory::Run()`)
* `FallerQueue.h` / `FallerQueue.cpp`
  * Defines the `FallerQueue` class (owned exclusively by the `Game` object)
  * Staging container into which `Faller` objects are pushed after they get generated by their corresponding `FallerFactory`
  * The `Game` object pops all `Faller`s stored in this container (thereby adding them to the game) at each game update
  * Insertion & removal are protected by a mutex (threads: `Game` and each `FallerFactory`)
* `FallerGenerator.h` / `FallerGenerator.cpp`
  * Defines the `FallerGenerator` class (owned exclusively by the `Game` object)
  * Helper object which encapsulates all the `FallerFactories` and manages their lifecycle (pause/resume/terminate)
  * The `FallerGenerator` is owned exclusively by the `Game` object

## Faller objects
* `Avocado.h` / `Avocado.cpp`
  * Defines the `Avocado` class
  * Specialisation of the `Faller` class, worth `10` point when caught
* `Broccoli.h` / `Broccoli.cpp`
  * Defines the `Broccoli` class
  * Specialisation of the `Faller` class, worth `5` point when caught
* `Mushroom.h` / `Mushroom.cpp`
  * Defines the `Mushroom` class
  * Specialisation of the `Faller` class, worth `25` point when caught
* `Olive.h` / `Olive.cpp`
  * Defines the `Olive` class
  * Specialisation of the `Faller` class, worth `1` point when caught
* `Onion.h` / `Onion.cpp`
  * Defines the `Onion` class
  * Specialisation of the `Faller` class, worth `2` point when caught

## Faller factories
* `AvocadoFactory.h` / `AvocadoFactory.cpp`
  * Defines the `AvocadoFactory` class
  * Specialisation of the `FallerFactory` class; Generates `Avocado` objects
* `BroccoliFactory.h` / `BroccoliFactory.cpp`
  * Defines the `BroccoliFactory` class
  * Specialisation of the `FallerFactory` class; Generates `Broccoli` objects
* `MushroomFactory.h` / `MushroomFactory.cpp`
  * Defines the `MushroomFactory` class
  * Specialisation of the `FallerFactory` class; Generates `Mushroom` objects
* `OliveFactory.h` / `OliveFactory.cpp`
  * Defines the `OliveFactory` class
  * Specialisation of the `FallerFactory` class; Generates `Olive` objects
* `OnionFactory.h` / `OnionFactory.cpp`
  * Defines the `OnionFactory` class
  * Specialisation of the `FallerFactory` class; Generates `Onion` objects


# Project rubric points addressed

## README
* ✅ A README with instructions is included with the project
* ✅ The README indicates which project is chosen
* ✅ The README includes information about each rubric point addressed (this whole section!)

## Compiling and Testing
* ✅ The submission must compile and run

## Loops, Functions, I/O
* ✅ The project demonstrates an understanding of C++ functions and control structures
  * A variety of control structures are used in the project (`if`, `for`, `while`, `switch`)
  * The project code is cleary organised into functions
* ✅ The project reads data from a file and process the data, or the program writes data to a file
  * All sprite files (`./sprites/*.png`) are read into the application at launch, to be rendered as Fallers during the game
* ✅ The project accepts user input and processes the input
  * The `InputReader::ReadInputs()` method (`InputReader.cpp`) reads inputs from the keyboard  (using SDL library calls), specifically left & right arrow, as well as the `P` key (pause)

## Object Oriented Programming
* ✅ The project uses Object Oriented Programming techniques
  * The whole project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  * See `File & class` section above for a listing of the classes and the files they are declared/defined in.
* ✅ Classes use appropriate access specifiers for class members.
  * E.g. see `Game.h` or `Faller.h` for examples of the usage of access specifiers
* ✅ Class constructors utilize member initialization lists
  * E.g. see `Faller.cpp` (circa line `48`) or `Renderer.cpp` (circa line `23`)
* ✅ Classes abstract implementation details from their interfaces
  * E.g. `FallerFactory::AddFallerToGame()` (`FallerFactory.cpp` circa line `87`) and `Application::CreateNewGame()` (`Application.cpp` circa line `78`)
* ✅ Classes encapsulate behavior
  * The only example of non-class definitions is the `InputReader` namespace (`InputReader.[cpp|h]`)
  * E.g. the `Metronome` class encapsulates all the behaviour for adjusting the game loop period in accordance with the average *measured* game loop execution duration, limited to a min & max updates/second value, and it exposes the average updates/second via `UpdatesPerSecond()` (`Metronome.cpp` circa line `53`)
* ✅ Classes follow an appropriate inheritance hierarchy
  * The only examples of base classes which are inherited from are the `Faller` and `FallerFactory` classes
  * Composition is heavily used, e.g. the `Game` class object (`Game.h` circa line `48`) is composed of a `Catcher`, a `FallerQueue` and `FallerGenerator` objects, as well as a `std::list` of `unique_ptr`s to all the `Faller` objects which are currently in the game.
* ✅ Overloaded functions allow the same function to operate on different parameters
  * Example (`Renderer.h` circa line `44`):
    * `void SetRenderColour(const Colour c);`
    * `void SetRenderColour(const Colour c, const Uint8 alpha)`
* ✅ Derived class functions override virtual base class functions
  * E.g. pure virtual `virtual std::string& Name() const = 0` (`Faller.h` circa line `19`) is overriden in all of its derived classes, e.g. `std::string& Name() const override;` in `Onion.h` circa line `13`
* ❌ Templates generalize functions in the project
  * Unfortunately (user-defined) template classes/functions have not been used for this project

## Memory Management
* ✅ The project makes use of references in function declarations
  * E.g. `void Update(double tickDurationInSeconds, GameInputs& inputs)` (`Game.h` circa line `28`) takes a reference argument (`inputs`)
  * E.g. All the arguments of `void ReadInputs(ApplicationInputs& appInputs, GameInputs& gameInputs, Renderer& renderer)` (`InputReader.h` circa line `9`) are of reference types
* ✅ The project uses destructors appropriately
  * E.g. `Renderer::~Renderer()` (`Renderer.cpp` circa line `41`) tears down some unmanaged dynamically allocated memory (`SDL_Texture`s)
* ✅ The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate
  * E.g. `Game::Game()` (`Game.cpp` circa line `12`) instantiates the `Game` object's instances of `Catcher`, `FallerQueue` and `FallerGenerator` objects (which are later automatically destroyed by `Game::~Game()`)
* ❌/✅ The project follows the Rule of 5
  * For this project we have not needed to use copy or move semantics on any of the user-defined classes
  * Default copy/move constructors and assignment operators have been explicitly deleted to avoid potential misuse
* ✅ The project uses move semantics to move data, instead of copying it, where possible
  * The copy/move constructors of the user-defined classes are not used
  * Move semantics is used throughout when manipulating smart pointers, e.g.
    * In `FallerFactory::AddFallerToGame()` (`FallerFactory.cpp` circa line `97`)
    * In `FallerQueue::Push(...)` (`FallerQueue.cpp` circa line `14`)
* ✅ The project uses smart pointers instead of raw pointers
  * Smart pointers are used throughout, e.g. see `Game.h` circa line `51` (and below) for objects owned by the `Game` object, which it keeps track of via the use of smart pointers.

## Concurrency
* ✅ The project uses multithreading
  * The `FallerGenerator` object instantiates one `std::thread` per each of the Faller factories, see `FallerGenerator::FallerGenerator(...)` (`FallerGenerator.cpp` circa line `20`)
* ❌ A promise and future is used in the project
* ✅ A mutex or lock is used in the project
  * `std::mutex` and `std::lock_guard` are used in the critical sections that lie on the interface between the main execution thread (`Application`, `Game`, `Renderer`) and the Faller factory threads (e.g. `AvocadoFactory`), in particular:
     * Pausing, resuming and ordering termination of the factory threads (`FallerFactory.cpp` circa line `55` and below)
     * Passing a created `Faller` object from its factory into the `FallerQueue` (`FallerQueue.cpp` circa line `11`) and the removal of these `Faller` objects from the `FallerQueue` by the `Game` object (`FallerQueue.cpp` circa line `17`)
* ✅ A condition variable is used in the project
  * When the game becomes paused, a `std::condition_variable` is used in the `FallerFactory` class to wait (`WaitUntilNoLongerPaused()` in `FallerFactory.cpp` circa line `85`) until the thread receives the order to either resume (circa line `65`) or terminate (circa line `73`)


# Copyright information

All sprite images are emojis created by OpenMoji.

All emojis designed by [OpenMoji](https://openmoji.org/) – the open-source emoji and icon project. License: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/#)
