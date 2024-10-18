# **R-Type**

---

### __Tech choices__

All the following libraries were chosen for their **efficiency**, and they are **well-known** and **widely used** in the industry:

- **OpenGL**: Used in Minecraft, World of Warcraft, and more.
- **Assimp**: Used in the Godot Engine.
- **OpenAL**: Used in Amnesia: The Dark Descent.
- **Asio**: Part of the Boost library, also used in the JUCE framework.

### **OpenGL**

We encapsulate the **OpenGL API** within our own classes, so users don't need to interact directly with OpenGL. To enhance our usage of OpenGL, we integrate the following libraries:
- **GLFW**: A simple and efficient library that enables easy window creation and input handling.
- **GLM**: A mathematics library specifically designed for 3D graphics, providing a variety of useful functions.
- **Freetype**: A powerful library that simplifies font loading and text rendering.

---

### **Assimp**

For 3D model loading, we use **Assimp**:
- It offers excellent support for **3D models**, making it a perfect fit for our project.

---

### **OpenAL**

For audio handling, we rely on **OpenAL**:
- OpenAL provides robust support for **3D sound**, which is crucial for the immersive audio experience we aim to deliver in the future.

We encapsulate the **OpenAL API** within our classes as well, so users won't need to manage OpenAL directly. Currently, we support **Device**, **Sound**, and **Playlist** components.

---

### **Boost Asio**

For networking, we use **Boost Asio**:
- Asio offers comprehensive support for **TCP** and **UDP** protocols.
- It also excels in providing **asynchronous** operations, crucial for real-time applications.

As with the other libraries, we encapsulate the **Asio API**, so users won’t have to interact with it directly. We currently support **Client** and **Server** components.

---

> **Note:** We use **CMake** to build our project.

---

## **Library Comparisons**

### **Graphics and General Libraries**

| Library | OpenGL | SFML | SDL |
| --- | --- | --- | --- |
| **3D Support** | Yes | No | No |
| **Sound Support** | No | Yes | Yes |
| **Network Support** | No | Yes | Yes |
| **Cross-platform** | Yes | Yes | Yes |
| **Community** | Large | Large | Large |
| **Documentation** | Extensive | Extensive | Extensive |
| **Learning Curve** | Hard | Easy | Easy |

---

### **Sound Libraries**

| Library | OpenAL | FMOD | SDL |
| --- | --- | --- | --- |
| **3D Sound** | Yes | Yes | No |
| **Cross-platform** | Yes | Yes | Yes |
| **Community** | Large | Large | Large |
| **Documentation** | Extensive | Extensive | Extensive |
| **Learning Curve** | Hard | Easy | Easy |

---

### **Networking Libraries**

| Library | Boost Asio | ENet | RakNet |
| --- | --- | --- | --- |
| **TCP Support** | Yes | No | Yes |
| **UDP Support** | Yes | Yes | Yes |
| **Cross-platform** | Yes | Yes | Yes |
| **Community** | Large | Large | Large |
| **Documentation** | Extensive | Extensive | Extensive |
| **Learning Curve** | Hard | Easy | Easy |

---

### Conclusion:

As demonstrated, we have carefully selected the best libraries for our project. While some of these libraries may present a steeper learning curve, they offer significant benefits in terms of performance and capability. We are committed to providing a powerful API for our users, leveraging **3D graphics** and **3D sound** to deliver a richer and more immersive experience.

---

### **File Architecture Overview**

- **`client/`**
  Contains the source code and header files for the client.

- **`include/`**
  Shared header files used by both server and client.

- **`lib/`**
  Directory for shared libraries.

- **`server/`**
  Contains the source code and header files for the server.

- **`dependencies/`**
  Dependencies for the current CMakeLists.txt.


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
### **Module**

- **`AsioNetworkModule`**
  Module for networking using the Asio library.

- **`ClientCoreModule`**
  Module for the client core.

- **`ServerCoreModule`**
  Module for the server core.

- **`TestClientCoreModule`**
  Module for the test client core.

- **`TestNetworkModule`**
  Module for the test network.

- **`TestServerCoreModule`**
  Module for the test server core.

---

### **Graphical User Interface _(GUI)_**

Here’s a more structured and refined version of the provided content:

---

> **Note:** The GUI is a work in progress. While the base components have been implemented, we plan to add more components in the future.

The GUI follows an **atomic design pattern**, drawing inspiration from the **React** library for its component-based architecture.

__Components Overview:__

- **`GUI::Component`**
  An abstract element that can be rendered.

- **`GUI::Container`**
  A component that can contain other components. _(Abstract)_

- **`GUI::Interactable`** _(inherits from `GUI::Container`)_
  A container that supports user interaction. _(Abstract)_

- **`GUI::Button`** _(inherits from `GUI::Interactable`)_
  A clickable button that includes a `GUI::Text` and a `Shape::Rectangle`.

- **`GUI::TextField`** _(inherits from `GUI::Interactable`)_
  A text field providing text input functionality, containing a `GUI::Text` and a `Shape::Rectangle`.

- **`GUI::Text`** _(inherits from `GUI::Component`)_
  A component responsible for displaying text, encapsulating a `GUI::Font`.

- **`GUI::Font`**
  A class that manages a font file through the `Freetype` library.

- **`GUI::Manager`** _(inherits from `GUI::Container`)_
  A manager that holds and manages all GUI components.

---
### **RFC**

- **`RFC`**

![RFC](./RFC.md)
