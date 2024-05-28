# Delivery System Shortest Path Finder

This project implements a delivery system using Dijkstra's algorithm to find the shortest path in a user-defined grid. It is a non-GUI application written in C++ that leverages file handling to manage input and output, calculating the shortest path and estimating delivery time.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Algorithm and Data Structures](#algorithm-and-data-structures)
  - [Grid Representation](#grid-representation)
  - [Dijkstra's Algorithm](#dijkstras-algorithm)
  - [File Handling](#file-handling)
- [Contributing](#contributing)
- [License](#license)

## Overview

This delivery system project is designed to calculate the shortest path for a driver in a grid-based map. Users can define the grid, specifying nodes and edges, and the system will compute the shortest path using Dijkstra's algorithm. The application also estimates the time required for the driver to travel from one node to another and handles orders, restaurant names, riders, nodes, and other relevant data via file handling.

## Features
- **User-Defined Grid**: Users can create a grid by specifying nodes and edges via file input.
- **Shortest Path Calculation**: Utilizes Dijkstra's algorithm to find the shortest path between nodes.
- **Time Estimation**: Provides an estimate of the time required for the driver to travel along the calculated path.
- **File Handling**: Efficiently reads input data from files and outputs results to files, managing orders, restaurant names, riders, nodes, and more.
- **From-Scratch Implementation**: All components, including queues and the adjacency matrix, are implemented from the base, ensuring a deep understanding of the underlying data structures.

## Algorithm and Data Structures

### Grid Representation

The grid is represented as a graph with nodes and edges. Nodes represent locations (e.g., restaurants, delivery points), and edges represent paths between these locations with associated weights (e.g., distances or times).

### Dijkstra's Algorithm

Dijkstra's algorithm is used to find the shortest path from a starting node to a target node in the grid. The algorithm efficiently calculates the minimum distance from the start node to all other nodes, updating the shortest path as it progresses.

### File Handling

The system uses file handling to manage various data inputs and outputs:

- **Output File**: Stores the results, including the shortest path and estimated time.
- **Orders and Restaurants**: Manages data related to orders and restaurant names.
- **Riders and Nodes**: Handles data related to riders and their locations.

### From-Scratch Implementation

All essential components of the system are implemented from scratch to provide a robust understanding of core data structures and algorithms:

- **Queues**: Implemented to manage the processing of nodes during the shortest path calculation.
- **Adjacency Matrix**: Used to represent the grid and the connections between nodes.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
