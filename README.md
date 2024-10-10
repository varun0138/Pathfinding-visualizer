# Pathfinding Visualizer

This is a C++ and SFML-based visualizer for common pathfinding algorithms, including:

- **Breadth-First Search (BFS)**
- **Depth-First Search (DFS)**
- **Greedy Best-First Search (GBeFS)**

The visualizer showcases how each algorithm explores the grid to find a path between a start and an end point.

## Features
- **Graphical User Interface**: 
  - A GUI to visualize three pathfinding algorithms with the ability to pause the simulation.
  - Allows users to change the size of the grid dynamically.

- **Custom User Controls**:
  - Adjustable noise levels for dynamic grid generation.
  - Path reset functionality to restart the algorithm.
  - Dynamic framerate settings to control simulation speed.


## Demo

Here's a quick look at the visualizer in action:

![Visualization](images/demo.gif)


## Building the Project
**Note**: These instructions are specifically for Windows. For other platforms, adjust the paths and compilation steps accordingly.

### Requirements

- C++17 or higher
- SFML 2.6.1 or higher (prebuilt binaries)

### Setting up SFML

1. **Download SFML**: 
   - Download prebuilt binaries for SFML from the official [SFML website](https://www.sfml-dev.org/index.php).
   
2. **Configure your project**:
   - Extract the SFML binaries and place them in a folder (e.g., `SFML-2.6.1`).
   
3. **Add SFML to your environment**:
   - Update the `Makefile` included in the project with SFML libs and include paths.
   
   Example `Makefile`:
   ```makefile
   all: compile link run clean

   SFML_INCLUDE = C:/SFML-2.6.1/include
   SFML_LIB = C:/SFML-2.6.1/lib

   compile:
      g++ -c *.cpp gui/*.cpp -std=c++17 -g -Wall -m64 -I ${SFML_INCLUDE} -DSFML_STATIC

   link:
      g++ *.o -o main -L ${SFML_LIB}  -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 

   clean:
      del *.o 
      
   run:
      ./main
4. **Compile the project**:
   ```makefile
   make
## Troubleshooting

- **Missing dependencies**: Ensure the SFML library is correctly linked. If there are issues, verify the paths for the SFML `lib` and `include` folders are accurate.
- **Compiler errors**: Make sure you're using **C++17** or later, as the project may rely on language features introduced in these versions.

## Future Improvements

- **Algorithm expansion**: Add more advanced algorithms like **A*** and **Dijkstra's** to enhance the visualizer's functionality.
- **Performance optimization**: Optimize the visualizer for handling larger grids, improving both memory usage and processing speed to accommodate more complex scenarios.
- **Path cost visualization**: Implement functionality to display the cost of the path and the number of steps taken by each algorithm, allowing users to compare the efficiency of different pathfinding methods.


## Contributions

Contributions are welcome! Feel free to open an issue for bugs, feature requests, or suggestions. You can also submit a pull request if you'd like to contribute code.
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.