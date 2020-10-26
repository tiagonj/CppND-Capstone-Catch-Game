#ifndef CATCH_GAME_OLIVE_FACTORY_H
#define CATCH_GAME_OLIVE_FACTORY_H

#include "FallerFactory.h"

#include <memory>

// Specialization which generates Olive faller objects
class OliveFactory : public FallerFactory
{
  public:
    OliveFactory(std::weak_ptr<FallerQueue>& queue);
    ~OliveFactory();

  private:
    std::unique_ptr<Faller> CreateFaller(float x, float vy);

    OliveFactory() = delete;
    OliveFactory(OliveFactory&) = delete;
    OliveFactory(OliveFactory&&) = delete;
    OliveFactory& operator=(OliveFactory&) = delete;
    OliveFactory& operator=(OliveFactory&&) = delete;
};

#endif
