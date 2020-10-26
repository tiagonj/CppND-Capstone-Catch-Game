#ifndef CATCH_GAME_FALLER_GENERATOR_H
#define CATCH_GAME_FALLER_GENERATOR_H

#include "FallerFactory.h"

#include <memory>
#include <thread>
#include <vector>

class FallerGenerator
{
  public:
    FallerGenerator(std::weak_ptr<FallerQueue> queue);
    ~FallerGenerator();
    void Pause();
    void Resume();

  private:
    FallerGenerator() = delete;
    FallerGenerator(FallerGenerator&) = delete;
    FallerGenerator(FallerGenerator&&) = delete;
    FallerGenerator& operator=(FallerGenerator&) = delete;
    FallerGenerator& operator=(FallerGenerator&&) = delete;

  private:
    std::vector<std::unique_ptr<FallerFactory>> _factories;
    std::vector<std::thread> _factoryThreads;
};

#endif
