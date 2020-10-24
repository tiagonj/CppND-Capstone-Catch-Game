#include "Game.h"

#include <cassert>
#include <iostream>

Game::Game() : _isPaused(true), _points(0)
{
    _catcher = std::make_unique<Catcher>();
}

Game::~Game()
{
}

void Game::Resume()
{
    assert(IsPaused());
    // TODO
    _isPaused = false;
}

void Game::Pause()
{
    assert(!IsPaused());
    // TODO
    _isPaused = true;
}

void Game::Update(GameInputs &inputs)
{
    assert(!IsPaused());

    for (unsigned int ii = 0; ii < 4294967295; ++ii)
    {
        // Do nothing
        (void)inputs;
    }

    std::cout << "Finished updating game!"
              << "\n";
}

bool Game::IsPaused()
{
    return _isPaused;
}
