#ifndef CATCH_GAME_AVOCADO_FACTORY_H
#define CATCH_GAME_AVOCADO_FACTORY_H

#include "FallerFactory.h"

#include <memory>

// Specialization which generates Avocado faller objects
class AvocadoFactory : public FallerFactory
{
  public:
    AvocadoFactory(std::weak_ptr<FallerQueue>& queue);
    ~AvocadoFactory();

  private:
    std::unique_ptr<Faller> CreateFaller(float x, float vy) override;

    AvocadoFactory() = delete;
    AvocadoFactory(AvocadoFactory&) = delete;
    AvocadoFactory(AvocadoFactory&&) = delete;
    AvocadoFactory& operator=(AvocadoFactory&) = delete;
    AvocadoFactory& operator=(AvocadoFactory&&) = delete;
};

#endif
