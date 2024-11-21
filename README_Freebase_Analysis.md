
# Dynamic Graph Analysis Engine for Freebase Data

This project is a dynamic graph analysis engine developed for the BLG 223E - Data Structures course at ITU. It processes and analyzes Freebase data, modeling relationships between entities in a semantic network. The system implements advanced graph algorithms, focusing on traversal, centrality, and pathfinding.

## Overview

Freebase was a large collaborative knowledge base consisting of structured data, later utilized to enhance Google's Knowledge Graph. This project processes Freebase data to explore and analyze the relationships between entities represented as a graph.

### Key Features
1. **Neighbor Discovery**:
   - Retrieve and list all connected entities (neighbors) for a given entity.
2. **Degree Centrality**:
   - Identify the most central entities in the graph based on their connectivity.
3. **Shortest Path Calculation**:
   - Find and display the shortest path between two entities using Breadth-First Search (BFS).

### Graph Structure
- **Nodes** represent unique entities identified by Machine-Identifiable Data (MIDs).
- **Edges** represent relationships between entities.

### Input Files
1. **`freebase.tsv`**: Contains triplet data representing relationships between entities.
2. **`mid2name.tsv`**: Maps MIDs to their human-readable names.

## How to Run

### Prerequisites
- **Compiler**: Requires `g++` for compilation.
- **Environment**: Developed and tested on Ubuntu.

### Compilation
```bash
g++ skeleton.cpp -o freebase_engine
```

### Execution
- **Neighbor Discovery**:
  ```bash
  ./freebase_engine part1 <MID>
  ```
- **Degree Centrality**:
  ```bash
  ./freebase_engine part2
  ```
- **Shortest Path Calculation**:
  ```bash
  ./freebase_engine part3 <MID1> <MID2>
  ```

### Example Commands
```bash
./freebase_engine part1 /m/04mx8h4
./freebase_engine part2
./freebase_engine part3 /m/04mx8h4 /m/0cc81d6
```

## Technologies Used
- **C++**: Implemented with a focus on efficiency and scalability.
- **Data Structures**:
  - Custom graph representation with adjacency lists.
  - Maps for entity lookups and name resolution.
- **Algorithms**:
  - Breadth-First Search (BFS) for pathfinding and traversal.
  - Degree centrality computation.

## Project Highlights
- Demonstrates efficient graph traversal and analysis of large-scale knowledge bases.
- Explores semantic networks using structured data from Freebase.
- Showcases dynamic graph processing with practical algorithm applications.

## Privacy Note

This repository is anonymized to protect academic and personal details, adhering to privacy and plagiarism policies.
This project was personally developed by EonTechie as a project for the BLG 223E - Data Structures course at ITU. It demonstrates individual effort in applying graph algorithms and data structures to analyze Freebase data.

---