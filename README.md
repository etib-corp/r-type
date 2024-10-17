**R-Type** project:

# **R-Type**

---

### **Description**

R-Type is a classic side-scrolling shoot-em-up arcade game originally produced by Irem in 1987. The player controls the R-9 space fighter to defend humanity against the powerful alien life-form known as the Bydo.

---

### **Requirements**

#### **Supported Platforms**

- **Windows**
- **Linux**
- **MacOS**

#### **Dependencies**

- **CMake**
- **C++20**

---

### **Build Instructions**

To build the project, follow these steps:

```bash
cmake -S . -B build
cmake --build build
```

---

### **Usage**

#### **Starting the Server**

Run the following command to start the server:

```bash
./build/r-type_server
```

#### **Starting the Client**

Run the following command to start the client:

```bash
./build/r-type_client
```

---

### **File Architecture Overview**

- **`client/`**: Source code and headers for the client.
- **`server/`**: Source code and headers for the server.
- **`include/`**: Shared headers used by both the client and server.
- **`lib/`**: Shared libraries.
- **`dependencies/`**: External dependencies for CMakeLists.txt.

---

### **Entity Component System (ECS)**

R-Type uses an Entity Component System (ECS) architecture, which is a modular and scalable pattern for game development.

#### **Entity**

An entity is a unique identifier for a collection of components.

```cpp
typedef unsigned int Entity;
```

#### **Component**

Components are structures that hold data.

```cpp
#include "Vector3.hpp"
struct TransformComponent {
    LE::Vector3<float> position;
    LE::Vector3<float> rotation;
    LE::Vector3<float> scale;
};
```

#### **System**

Systems contain the logic to process entities. They manipulate component data based on game rules.

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

---

### **Modules**

- **`AsioNetworkModule`**: Networking module using Asio library.
- **`ClientCoreModule`**: Core module for the client.
- **`ServerCoreModule`**: Core module for the server.
- **`TestClientCoreModule`**: Module for testing the client core.
- **`TestNetworkModule`**: Module for testing network functionality.
- **`TestServerCoreModule`**: Module for testing the server core.

---

### **Contribute**

To contribute, follow these steps:

1. **Fork** the repository.
2. **Clone** your fork.
3. **Create** a new branch.
4. **Commit** your changes.
5. **Push** the changes to your fork.
6. **Submit** a pull request.
7. Once approved, **merge** the pull request.
8. **Close** the pull request.
9. Optionally, **delete** the branch.

---

### **Contributors**

- **SizzleUnrlsd**
- **xavierclement**
- **MAILLOTNathan**
- **ju-lit-hein**
- **ElPepitaux**

---

### **License**

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.

---

### **RFC**

For more information, refer to the [RFC document](./RFC.md).

---

This revised structure offers better readability and consistency. Let me know if you'd like further changes!