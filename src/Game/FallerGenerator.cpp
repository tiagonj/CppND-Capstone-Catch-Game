#include "FallerGenerator.h"
#include "AvocadoFactory.h"
#include "BroccoliFactory.h"
#include "MushroomFactory.h"
#include "OliveFactory.h"
#include "OnionFactory.h"

FallerGenerator::FallerGenerator(std::weak_ptr<FallerQueue> queue)
{
    // Create all factories
    _factories.push_back(std::make_unique<AvocadoFactory>(queue));
    _factories.push_back(std::make_unique<BroccoliFactory>(queue));
    _factories.push_back(std::make_unique<MushroomFactory>(queue));
    _factories.push_back(std::make_unique<OliveFactory>(queue));
    _factories.push_back(std::make_unique<OnionFactory>(queue));

    // Launch one thread for each of the factories instantiated above
    for (auto& f : _factories)
    {
        _factoryThreads.emplace_back(std::thread(&FallerFactory::Run, f.get()));
    }
}

FallerGenerator::~FallerGenerator()
{
    for (auto& f : _factories)
    {
        f->Terminate();
    }

    for (auto& t : _factoryThreads)
    {
        t.join();
    }
}

void FallerGenerator::Pause()
{
    for (auto& f : _factories)
    {
        f->Pause();
    }
}

void FallerGenerator::Resume()
{
    for (auto& f : _factories)
    {
        f->Resume();
    }
}
