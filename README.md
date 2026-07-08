# DataStructures

A collection of STL-based implementations of fundamental data structures written in modern C++. The implementations are written for educational purposes and are tested using GoogleTest.

The goal of this repository is to explore low-level aspects of C++ programming:
- manual memory management,
- object lifetime,
- move semantics,
- exception safety,
- generic programming,
- STL-like interfaces and design principles.
- compile-time evaluation

## Implemented Structures

### Containers

- `my_vector`
  - dynamic array implementation similar to `std::vector`
  - manual memory management using raw allocation and placement `new`
  - copy/move semantics (Rule of Five)
  - exception-safe construction and reallocation
  - STL-compatible type aliases (`value_type`, `size_type`, `iterator`, `reference`, etc.)
  - iterator support, including reverse iterators
  - some operations with constexpr support where applicable
