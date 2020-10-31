#include "FallerQueue.h"

FallerQueue::FallerQueue()
{
}

FallerQueue::~FallerQueue()
{
}

void FallerQueue::Push(std::unique_ptr<Faller>&& f)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _fallers.emplace_back(std::move(f));
}

void FallerQueue::PopAll(std::list<std::unique_ptr<Faller>>& list)
{
    std::lock_guard<std::mutex> lock(_mutex);

    for (auto it = _fallers.begin(); it != _fallers.end();)
    {
        list.emplace_back(std::move(*it));
        it = _fallers.erase(it);
    }
}
