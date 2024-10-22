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
### __Tech choices__

All the following libraries were chosen for their **efficiency**, and they are **well-known** and **widely used** in the industry:

- **OpenGL**: Used in Minecraft, World of Warcraft, and more.
- **Assimp**: Used in the Godot Engine.
- **OpenAL**: Used in Amnesia: The Dark Descent.
- **Asio**: Part of the Boost library, also used in the JUCE framework.

### **OpenGL**

(https://www.profolus.com/topics/advantages-disadvantages-of-opengl/)

We encapsulate the **OpenGL API** within our own classes, so users don't need to interact directly with OpenGL. To enhance our usage of OpenGL, we integrate the following libraries:
- **GLFW**: A simple and efficient library that enables easy window creation and input handling.
- **GLM**: A mathematics library specifically designed for 3D graphics, providing a variety of useful functions.
- **Freetype**: A powerful library that simplifies font loading and text rendering.

---

### **Assimp**

(https://www.modelo.io/damf/article/2024/06/26/0748/understanding-the-advantages-of-assimp-in-3d-model-importing?hl=en)

For 3D model loading, we use **Assimp**:
- It offers excellent support for **3D models**, making it a perfect fit for our project.

---

### **OpenAL**

(https://medium.com/@bookmyblogss/what-is-openal-should-i-remove-openal-in-windows-10-or-11-6d4cd04c92d9)

For audio handling, we rely on **OpenAL**:
- OpenAL provides robust support for **3D sound**, which is crucial for the immersive audio experience we aim to deliver in the future.

We encapsulate the **OpenAL API** within our classes as well, so users won't need to manage OpenAL directly. Currently, we support **Device**, **Sound**, and **Playlist** components.

---

### **Boost Asio**

(https://alexott.net/en/cpp/BoostAsioNotes.html)

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

For more information, refer to the [RFC document](./RFC.md).

---

This revised structure offers better readability and consistency. Let me know if you'd like further changes!