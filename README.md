# **R-Type**

---

### **File Architecture Overview**

- **`client/`**  
  Contains the source code and header files for the client.

- **`graphical/`**  
  Currently under development.

- **`include/`**  
  Shared header files used by both server and client.

- **`lib/`**  
  Directory for shared libraries.

- **`server/`**  
  Contains the source code and header files for the server.

- **`include/`**  
  Shared source files used by both server and client.

---

### **Entity Component System**
An entity component system is a design pattern used to create a modular and scalable architecture for video games.

- **`Entity`**  
  An entity is a container for components. An entity is a unique identifier.

- **`Component`**
  A component is a container for data. Components are used to store data for entities.

- **`System`**
  A system is a container for logic. Systems are used to process entities.
  Systems use components data to process entities.

### **Entity Component System Overview**
#### **Entity**
An entity is an unsigned integer that is used to identify an entity.
```cpp
typedef unsigned int Entity;
```

#### **Component**
A component is a structure that contains data.
```cpp
#include "Vector3.hpp"
struct TransformComponent {
    LE::Vector3<float> position;
    LE::Vector3<float> rotation;
    LE::Vector3<float> scale;
};
```

#### **System**
A system is a class that contains logic.
```cpp
#include "System.hpp"

class GravitySystem : public LE::System {
public:
    void update() override {
        for (auto& entity : entities) {
            auto& transform = entity.getComponent<TransformComponent>();
            transform.position.y -= 9.8f * 0.01f;
        }
    }
};
```
