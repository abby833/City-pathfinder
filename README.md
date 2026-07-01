# City PathFinder

[![C++ Unit Tests](https://github.com/abby833/City-pathfinder/actions/workflows/ci.yml/badge.svg)](https://github.com/abby833/City-pathfinder/actions)

A high-performance hybrid navigation system that calculates the shortest path between two street addresses using real-world data from OpenStreetMap.

![Navigation Demo](demo0.png)
![Navigation Demo](demo1.png)

## Tech Stack
- **Backend/Engine:** C++17 (Dijkstra's Algorithm, Trie lookup with O(L) complexity).
- **Testing:** Catch2 (Behavior-Driven Development methodology).
- **Frontend/Visualization:** Python (Streamlit, Folium).
- **Data Source:** OpenStreetMap API (via OSMnx).
- **Build System & CI/CD:** CMake and GitHub Actions.

## System Architecture
This project follows a "Separation of Concerns" modular design to ensure high performance, maintainability, and testability:

1. **Data Processing (`server.py`):** Python script that extracts the street network from OSM and serializes it into structured files.
2. **Computation Engine (C++):** An optimized engine leveraging `std::unordered_map` for O(1) lookup times and memory-safe STL containers. It handles the core routing logic using Dijkstra's algorithm.
3. **Automated Testing (`tests/`):** A dedicated testing suite ensuring the reliability of the core algorithms (Graph and Trie data structures) in isolated, fast-running environments.
4. **Web Interface (`web_app.py`):** Provides an autocomplete-enabled UI and acts as the bridge between the user and the C++ computation engine.
5. **Visualization:** The computed route is rendered as an interactive Polyline.

## How to Build and Run

To get the system running, follow these steps in order:

### Part 1: Core Engine & Tests
```bash
# 1. Build the C++ Engine using CMake
mkdir build
cd build
cmake ..
cmake --build .

# 2. Run the Unit Tests to verify the engine
# On Windows:
.\Debug\run_tests.exe
# On Linux/Mac:
./run_tests