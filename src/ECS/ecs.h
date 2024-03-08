#ifndef ECS_H
#define ECS_H
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextID;
};

template <typename TComp>
class Component: public IComponent {
    // returns the unique id of Component<TComp>
    static int getID() {
        static auto id = nextID++;
        return id;
    }
};

class Entity {
    private:
        int id;
    
    public:
        bool operator ==(Entity const& e2) {id == e2.getID();};
        bool operator !=(Entity const& e2) {id != e2.getID();};
        Entity(int id): id(id){};
        int getID() const;
};


class System {
    private:
        Signature component_signature;
        std::vector<Entity> entities;
    
    public:
        System() = default;
        ~System() = default;

        void addEntity(Entity entity);
        void removeEntity(Entity entity);
        std::vector<Entity> getEntities() const;
        const Signature& getComponentSig() const;

        template <typename T> void requireComponent();
};
// templates are implimented in the header
template <typename TComp>
void System::requireComponent() {
    const auto componentID = Component<TComp>::getID();
    component_signature.set(componentID);
}

class IPool {
    public:
        virtual ~IPool() {}
};

// Pool is a vector of type T
template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(int size=100) {
            data.resize(size);
        }
        virtual ~Pool() = default;

        bool isEmpty() const {
            return data.empty();
        }
        
        int getSize() const {
            return data.size();
        }

        void resize(int n) {
            data.resize(n);
        }

        void clear() {
            data.clear();
        }

        void add(T obj) {
            data.push_back(obj)
        }

        void get(int index) {
            return static_cast<T&>(data[index]);
        }

        operator [](unsigned int index) {
            return data[index];
        }

};

class Registry {
    private:
        u_int numEntities = 0;

        // Vector of component pools 
        // each pool contains all the data for a certain component type
        // [vector index = component type id]
        // [index within pool = entity id]
        std::vector<IPool*> componentPools;

        // Vector of component signatures per entity
        // [Vector index = entity id]
        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, System*> systems;

        std::set<Entity> entitiesToAdd();
        std::set<Entity> entitiesToRemove();
    
    public:
        Registry() = default;
        Entity createEntity();
        void addEntityToSystem();
        void removeEntity();
        void update();
};



#endif