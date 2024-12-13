# Hive Engine project

Welcome to this simple game engine built using the Entity-Component-System (ECS) architecture. This project is primarily designed to help you learn and practice ECS concepts by building a small, modular, and expandable game engine. The goal is to help you understand how to separate data and behavior, leading to more flexible and scalable game design.

## Overview
This game engine is built with C++ and uses the Entity-Component-System (ECS) design pattern. The ECS pattern is a popular method in game development for organizing the game's data and logic in a decoupled way. It allows for high performance and easy maintenance of game code.

### Key Features:
Entity-Component-System Architecture: Separate game data (components) and behavior (systems) for better organization.
Modular: Easily extendable with new components and systems.
Simple: Provides a basic foundation to understand ECS and build more complex features.

## Getting Started

In order to build the project you will need:
- C++ compiler. We support gcc (linux) and msvc (windows)
- cmake 

We use c++ 20 so make sure your compiler support that

### Building the project 
#### Command Line

```git clone https://github.com/HiveEngine/HiveEngine.git```

```mkdir build && cd build```

```cmake .. && cmake --build .```

#### IDE 
- CLion: Openning the project repo in CLion should automatically setup everything for you. The only thing you might need to change is the default compiler and select MSVC if you are on Windows
- Visual Studio: ```cmake -G "Visual Studio 17 2022"``` will create the solution file in order to open it in visual studio


## Project Structure 
The project structure is as follows:
- Core: All the core engine feature like windowing, input handling, etc
- Driver: All the specific code related to different supported graphics library like Vulkan, OpenGL, Metal
- Platform: All the specific code related to different supported operating system

Each folder can have more subfolder to make clear boundary of the code