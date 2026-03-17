# K-D Tree Word Embeddings & KNN Search

An efficient C++ implementation of a **K-D Tree** data structure specifically designed for managing and searching **Word Embeddings** in N-dimensional space.

## Features
- **N-Dimensional Spatial Partitioning**: Efficiently organizes high-dimensional vector data.
- **K-Nearest Neighbors (KNN)**: Optimized search for the most similar words using a priority queue.
- **Vector Arithmetic**: Supports embedding addition, subtraction, and magnitude calculation via operator overloading.
- **Cosine Similarity**: Built-in calculation for angular proximity between vectors.
- **Tree Merging**: Capability to merge multiple trees/datasets while handling duplicates.

## Technical Highlights
- **Modern C++**: Utilizing custom exception handling and operator overloading.
- **Memory Management**: Recursive tree destruction to prevent memory leaks.
- **Robust Parsing**: CSV data parsing for word-vector pairs.

## How to run
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the source files: ```g++ -std=c++11 *.cpp -o main```
4. Run the executable ```./main```
