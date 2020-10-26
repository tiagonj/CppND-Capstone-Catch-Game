#include "FallerGenerator.h"
#include "OliveFactory.h"

FallerGenerator::FallerGenerator(std::weak_ptr<FallerQueue> queue)
{
    // Create all factories
    _factories.push_back(std::make_unique<OliveFactory>(queue));

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
