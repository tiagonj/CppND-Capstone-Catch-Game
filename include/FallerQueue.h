#ifndef CATCH_GAME_FALLER_QUEUE_H
#define CATCH_GAME_FALLER_QUEUE_H

#include "Faller.h"

#include <list>
#include <memory>
#include <mutex>

class FallerQueue
{
  public:
    FallerQueue();
    ~FallerQueue();
    void Push(std::unique_ptr<Faller>&& f);
    void PopAll(std::list<std::unique_ptr<Faller>>& list);

  private:
    FallerQueue(FallerQueue&) = delete;
    FallerQueue(FallerQueue&&) = delete;
    FallerQueue& operator=(FallerQueue&) = delete;
    FallerQueue& operator=(FallerQueue&&) = delete;

  private:
    std::list<std::unique_ptr<Faller>> _fallers;
    std::mutex _mutex;
};

#endif
