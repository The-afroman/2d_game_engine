#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>

#include "../Logger/logger.h"

class Event {
 public:
  Event() = default;
};

class IEventCallback {
 private:
  virtual void Call(Event &e) = 0;

 public:
  virtual ~IEventCallback() = default;
  void Execute(Event &e) { Call(e); };
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
 private:
  typedef void (TOwner::*CallbackFunction)(TEvent &);
  TOwner *ownerInstance;
  CallbackFunction callbackFunction;

  virtual void Call(Event &e) override {
    std::invoke(callbackFunction, ownerInstance, static_cast<TEvent &>(e));
  }

 public:
  EventCallback(TOwner *ownerInstance, CallbackFunction callbackFunction) {
    this->ownerInstance = ownerInstance;
    this->callbackFunction = callbackFunction;
  }
  virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
 private:
  std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

 public:
  EventBus() { Logger::info("EventBus created"); }
  ~EventBus() { Logger::info("EventBus destroyed"); }
  void reset() { subscribers.clear(); }
  /*
    Subscribe a callback function to a specific event type TEvent
    Example eventBus->subscribe<CollisionEvent>(&Game::onCollision);
  */

  template <typename TEvent, typename TOwner>
  void subscribe(TOwner *ownerInstance,
                 void (TOwner::*callbackFunction)(TEvent &)) {
    if (!subscribers[typeid(TEvent)].get()) {
      subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
    }
    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(
        ownerInstance, callbackFunction);
    // need to use std::move in order to change the unique pointer's owner
    subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
  }

  /*
    Emit an event of a type TEvent and execute all callbacks associated with
    the event Example: eventBus->emitEvent<CollisionEvent>(player, enemy);
  */
  template <typename TEvent, typename... TArgs>
  void emitEvent(TArgs &&...args) {
    auto handlers = subscribers[typeid(TEvent)].get();
    if (!handlers) {
      return;
    }
    for (auto it = handlers->begin(); it != handlers->end(); it++) {
      auto h = it->get();
      TEvent event(std::forward<TArgs>(args)...);
      h->Execute(event);
    }
  }
};

#endif