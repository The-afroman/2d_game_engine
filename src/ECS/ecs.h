#ifndef ECS_H
#define ECS_H
#include "../Logger/logger.h"
#include <bitset>
#include <deque>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
protected:
  static int nextID;
};

template <typename TComp> class Component : public IComponent {
  // returns the unique id of Component<TComp>
public:
  static int getID() {
    static auto id = nextID++;
    return id;
  }
};

class Entity {
private:
  int id;

public:
  Entity(int id) : id(id){};
  Entity(const Entity &entity) = default;
  int getID() const;

  Entity &operator=(const Entity &e2) = default;
  bool operator==(const Entity &e2) const { return id == e2.getID(); }
  bool operator!=(const Entity &e2) const { return id != e2.getID(); }
  bool operator<(const Entity &e2) const { return id < e2.getID(); }
  bool operator>(const Entity &e2) const { return id > e2.getID(); }

  // hold a pointer to the entity's owner registry
  // class keyword allows for implicit forward declaration of registry
  class Registry *registry;

  void kill();
  // component management
  template <typename TComp, typename... TArgs>
  void addComponent(TArgs &&...args);
  template <typename TComp> void removeComponent();
  template <typename TComp> bool hasComponent() const;
  template <typename TComp> TComp &getComponent() const;
};

class System {
private:
  Signature component_signature;

protected:
  std::vector<Entity> entities;

public:
  System() = default;
  ~System() = default;

  void addEntity(Entity entity);
  void removeEntity(Entity entity);
  std::vector<Entity> getEntities() const;
  const Signature &getComponentSig() const;

  template <typename T> void requireComponent();
};

class IPool {
public:
  virtual ~IPool() {}
};

// Pool is a vector of type T
template <typename T> class Pool : public IPool {
private:
  std::vector<T> data;

public:
  Pool(int size = 100) { data.resize(size); }
  virtual ~Pool() = default;

  bool isEmpty() const { return data.empty(); }

  int getSize() const { return data.size(); }

  void resize(int n) { data.resize(n); }

  void clear() { data.clear(); }

  void add(T obj) { data.push_back(obj); }

  void set(int index, T obj) { data[index] = obj; }

  T &get(int index) { return static_cast<T &>(data[index]); }

  T &operator[](unsigned int index) { return data[index]; }
};

class Registry {
private:
  u_int numEntities = 0;

  // Vector of component pools
  // each pool contains all the data for a certain component type
  // [vector index = component type id]
  // [index within pool = entity id]
  std::vector<std::shared_ptr<IPool>> componentPools;

  // Vector of component signatures per entity
  // [Vector index = entity id]
  std::vector<Signature> entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

  // entities to be added or removed at the end of the next Registry update()
  std::set<Entity> entitiesToAdd;
  std::set<Entity> entitiesToRemove;
  std::deque<int> freeIds;

public:
  Registry() = default;
  void update();

  // entity management
  Entity createEntity();
  void removeEntity(Entity entity);

  // component management
  template <typename TComp, typename... TArgs>
  void addComponent(Entity entity, TArgs &&...args);
  template <typename TComp> void removeComponent(Entity entity);
  template <typename TComp> bool hasComponent(Entity entity) const;
  template <typename TComp> TComp &getComponent(Entity entity) const;

  // system management
  template <typename TSys, typename... TArgs> void addSystem(TArgs &&...args);
  template <typename TSys> void removeSystem();
  template <typename TSys> bool hasSystem() const;
  template <typename TSys> TSys &getSystem() const;

  void addEntityToSystems(Entity entity);
  void removeEntityFromSystems(Entity entity);
};

// templates are implimented in the header
// component management impl
template <typename TComp, typename... TArgs>
void Registry::addComponent(Entity entity, TArgs &&...args) {
  const size_t componentID = Component<TComp>::getID();
  const auto entityID = entity.getID();

  if (componentPools.size() <= componentID) {
    componentPools.resize(componentID + 1, nullptr);
  }

  if (!componentPools[componentID]) {
    std::shared_ptr<Pool<TComp>> newCPool = std::make_shared<Pool<TComp>>();
    componentPools[componentID] = newCPool;
  }

  std::shared_ptr<Pool<TComp>> cPool =
      static_pointer_cast<Pool<TComp>>(componentPools[componentID]);

  if (cPool->getSize() <= entityID) {
    cPool->resize(numEntities);
  }

  TComp newComponent(std::forward<TArgs>(args)...);
  cPool->set(entityID, newComponent);

  entityComponentSignatures[entityID].set(componentID);

  Logger::info("Component id = " + std::to_string(componentID) +
               " added to entity = " + std::to_string(entityID));
}

template <typename TComp> void Registry::removeComponent(Entity entity) {
  const auto componentID = Component<TComp>::getID();
  const int entityID = entity.getID();

  entityComponentSignatures[entityID].reset(componentID);
  Logger::info("Component id = " + std::to_string(componentID) +
               " removed from entity = " + std::to_string(entityID));
}

template <typename TComp> bool Registry::hasComponent(Entity entity) const {
  const auto componentID = Component<TComp>::getID();
  const int entityID = entity.getID();

  Signature entitySig = entityComponentSignatures[entityID];

  return entitySig & componentID;
}

template <typename TComp> TComp &Registry::getComponent(Entity entity) const {
  const auto componentID = Component<TComp>::getID();
  const auto entityID = entity.getID();

  auto cPool =
      std::static_pointer_cast<Pool<TComp>>(componentPools[componentID]);
  return cPool->get(entityID);
}

template <typename TComp, typename... TArgs>
void Entity::addComponent(TArgs &&...args) {
  registry->addComponent<TComp>(*this, std::forward<TArgs>(args)...);
}

template <typename TComp> void Entity::removeComponent() {
  registry->removeComponent<TComp>(*this);
}

template <typename TComp> bool Entity::hasComponent() const {
  return registry->hasComponent<TComp>(*this);
}

template <typename TComp> TComp &Entity::getComponent() const {
  return registry->getComponent<TComp>(*this);
}

// system management impl
template <typename TComp> void System::requireComponent() {
  const auto componentID = Component<TComp>::getID();
  component_signature.set(componentID);
}

template <typename TSys, typename... TArgs>
void Registry::addSystem(TArgs &&...args) {
  std::shared_ptr<TSys> newSystem =
      std::make_shared<TSys>(std::forward<TArgs>(args)...);
  systems.insert(std::make_pair(std::type_index(typeid(TSys)), newSystem));
}

template <typename TSys> void Registry::removeSystem() {
  auto system = systems.find(std::type_index(typeid(TSys)));
  systems.erase(system);
}

template <typename TSys> bool Registry::hasSystem() const {
  return systems.find(std::type_index(typeid(TSys))) != systems.end();
}

template <typename TSys> TSys &Registry::getSystem() const {
  auto system = systems.find(std::type_index(typeid(TSys)));
  return *(std::static_pointer_cast<TSys>(system->second));
}

#endif