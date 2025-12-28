# Computer Graphics Lab Programs

OpenGL/GLUT programs demonstrating fundamental computer graphics algorithms and concepts.

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

### Windows (MSYS2/MinGW)

General compilation pattern:
```bash
cd lab_name
g++ -o program.exe program.cpp -lopengl32 -lglu32 -lfreeglut
./program.exe
```

### Linux

General compilation pattern:
```bash
cd lab_name
g++ program.cpp -o program -lGL -lGLU -lglut
./program
```

## Lab Programs

### Lab 1: Basic Graphics
- **`name.cpp`** - Draws "SAFAL" text using polygons
- **`res.cpp`** - Gets and displays screen resolution

### Lab 2: Line and Circle Drawing Algorithms
- **`algo.cpp`** - Interactive menu-driven program featuring:
  - DDA Line Drawing Algorithm
  - Bresenham's Line Drawing Algorithm
  - Midpoint Circle Algorithm
  - Graph plotting
  - Pie Chart visualization
  - *Right-click for menu options*

### Lab 3: 2D Transformations
- **`2d_translation.cpp`** - Demonstrates 2D translation with visual vector representation
- **`2d_rotation.cpp`** - Shows 2D rotation transformation around origin
- **`2d_scaling.cpp`** - Illustrates 2D scaling transformation
- **`2d_shearing.cpp`** - Demonstrates 2D shearing transformation
- **`2d_reflection.cpp`** - Shows reflection across various axes
- **`composite_transformations.cpp`** - Combines multiple transformations (scale → rotate → shear → translate) with step-by-step visualization
- **`ellipse_algorithm.cpp`** - Implements Midpoint Ellipse Drawing Algorithm

### Lab 4: Clipping Algorithms
- **`cohen_sutherland_line_clipping.cpp`** - Cohen-Sutherland line clipping algorithm with region codes
  - Clips lines against rectangular window
  - Shows original and clipped line segments
  - Displays region code information
  
- **`liang_barsky.cpp`** - Liang-Barsky parametric line clipping algorithm
  - Uses parametric line equations for efficient clipping
  - Shows parametric values (u_entry, u_exit)
  - Visual comparison with original line
  
- **`sutherland_hodgeman.cpp`** - Sutherland-Hodgeman polygon clipping algorithm
  - Clips polygons against rectangular window
  - Sequential clipping against four edges
  - Shows before/after polygon comparison

## Notes

- All programs include visual grids and coordinate axes for better understanding
- Programs use color coding to distinguish between original and transformed/clipped objects
- Interactive features available in some programs (check individual program descriptions)
