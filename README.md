# Computer Graphics Lab Programs

OpenGL/GLUT programs demonstrating computer graphics concepts.

## Prerequisites

- C++ Compiler (g++)
- OpenGL, GLU, GLUT (freeglut)

## Installation

### Windows (MSYS2)

Install and setup MSYS2, then run in MINGW64 terminal:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut
```

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev
```

## Compilation & Running

### Windows (MSYS2)

```bash
g++ lab1/name.cpp -o lab1/name -lfreeglut -lopengl32 -lglu32
./lab1/name

g++ lab2/algo.cpp -o lab2/algo -lfreeglut -lopengl32 -lglu32
./lab2/algo
```

### Linux

```bash
g++ lab1/name.cpp -o lab1/name -lGL -lGLU -lglut
./lab1/name

g++ lab2/algo.cpp -o lab2/algo -lGL -lGLU -lglut
./lab2/algo
```

## Lab Programs

 `name.cpp` | Draws "SAFAL" using polygons |
`res.cpp` | Gets screen resolution |
`algo.cpp` | DDA, Bresenham, Midpoint Circle, Graphs, Pie Chart (right-click for menu) |
