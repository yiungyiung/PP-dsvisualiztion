# Data Structures Visualization

This C++ code provides a visual representation of a linked list and allows users to perform various operations on it. The visualization is built using the Raylib library for graphics and Raygui for user interface elements.

## Overview

The code consists of two main classes: `Node` and `LinkedList`. The `Node` class represents individual nodes in the linked list, and the `LinkedList` class manages the linked list operations.

## How to Run

To run the program, ensure you have the Raylib library and Raygui library properly installed. Compile the code and execute the binary.

```bash
g++ -o LinkedListVisualization LinkedListVisualization.cpp -lraylib -lraygui
./LinkedListVisualization
```

## Features

- **Add Node at End:** Adds a new node with a specified value to the end of the linked list.
- **Add Node at Beginning:** Adds a new node with a specified value to the beginning of the linked list.
- **Add Node at Any Position:** Adds a new node with a specified value at a user-defined position in the linked list.
- **Delete Node at Beginning:** Removes the node from the beginning of the linked list.
- **Delete Node at Any Position:** Removes the node from a user-defined position in the linked list.
- **Delete Node at End:** Removes the last node from the linked list.
- **Search Item:** Highlights and searches for a specific item in the linked list.

## User Interface

The graphical user interface includes buttons for each operation, value boxes to input data, and a search functionality.

- **ADD NODE END:** Adds a node to the end of the linked list.
- **ADD NODE BEGINNING:** Adds a node to the beginning of the linked list.
- **ADD NODE ANY POSITION:** Adds a node to a specified position in the linked list.
- **DELETE NODE BEGINNING:** Deletes the first node in the linked list.
- **DELETE NODE ANY POSITION:** Deletes a node from a specified position in the linked list.
- **DELETE NODE END:** Deletes the last node in the linked list.
- **SEARCH ITEM:** Searches for a specific item in the linked list.
![image](https://github.com/yiungyiung/PP-dsvisualiztion/assets/83068397/290b14ff-d9c3-4670-bb14-0d253849e9fc)
![image](https://github.com/yiungyiung/PP-dsvisualiztion/assets/83068397/2b2e17f9-d653-4628-9757-32968b4a488b)
![image](https://github.com/yiungyiung/PP-dsvisualiztion/assets/83068397/a20158dd-b3be-4b99-abf1-b03b4ec73c81)

## Notes

- The linked list visualization updates in real-time as operations are performed.
- User input is facilitated through value boxes and buttons.

Feel free to explore the visualization and interact with the linked list.

---

*Note: Ensure that the Raylib and Raygui libraries are properly installed and linked before compiling and running the code.*
