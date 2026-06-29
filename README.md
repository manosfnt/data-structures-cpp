# Data Structures Toolkit in C++

A C++ project implementing and testing fundamental data structures and algorithms.

## Implemented Structures

- Min Heap
- Max Heap
- AVL Tree
- Hash Table with separate chaining
- Weighted Graph
- Linked List used for Hash Table buckets
- Helper functions for file input and dynamic arrays

## How the Program Works

The program reads commands from `commands.txt`.

Depending on each command, it builds or modifies a data structure, performs searches or graph operations, and writes the results to `output.txt`.

The sample commands use:

- `a.txt` for integer data
- `b.txt` for graph edges

## Build

Compile all source files together:

```bash
g++ -std=c++17 main.cpp MINHEAP.cpp MAXHEAP.cpp AVLTREE.cpp HASHTABLE.cpp List.cpp GRAPH.cpp -o data_structures.exe
