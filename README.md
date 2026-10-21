# s21_containers — STL-style containers in C++

A learning project implementing a collection of C++ containers inspired by the Standard Template Library (STL). The goal is to explore data structures, templates, iterators, object lifetime, dynamic memory management, and algorithmic complexity by building containers from scratch.

**Language:** C++20  
**Build:** GNU Make / g++  
**Tests:** GoogleTest

## Implemented components

| Component | Underlying idea |
| --- | --- |
| `s21::vector` | Dynamically sized contiguous storage |
| `s21::list` | Linked list |
| `s21::map` | Ordered key–value associative container |
| `s21::set` | Ordered unique-key container |
| `s21::multiset` | Ordered container allowing duplicate keys |
| `s21::array` | Fixed-size array |
| `s21::stack` | LIFO container adaptor |
| `s21::queue` | FIFO container adaptor |
| `s21::deque` | Double-ended sequence implementation (source available) |
| AVL tree | Tree operations and rebalancing used by the project |

The implementation takes inspiration from STL interfaces, but **is not a drop-in replacement for the standard library**. Some interfaces and behaviors may differ.

## What this project explores

- Generic programming with C++ templates and `.h` / `.tpp` implementations.
- Copy and move operations, constructors, destructors, and ownership of allocated memory.
- Container iterators, element access, insertion, removal, and traversal.
- Tree-based ordered associative containers and AVL rotations.
- Automated unit testing and memory diagnostics.

## Repository layout

```text
src/
├── s21_containers.h          # Main container header
├── s21_containersplus.h      # Additional containers
├── s21_containers/           # Vector, list, map, set, stack, queue, AVL tree, ...
├── s21_containersplus/       # Array and multiset
├── tests/                    # GoogleTest test suites
└── Makefile                  # Build, tests, coverage, diagnostics
```

> Note: A `deque` implementation exists in the source tree but is not included by the two umbrella headers listed above.

## Build and test

Prerequisites: a C++20-compatible compiler, GNU Make, GoogleTest development headers and libraries. `lcov`/`genhtml` and Valgrind are optional.

From the repository root:

```bash
cd src
make test
```

The Makefile builds the project test executable and runs it. Other available commands:

```bash
make clean           # Remove generated files
make rebuild         # Clean and rebuild
make gcov_report     # Generate coverage report (requires lcov/genhtml)
make clang           # Check formatting (requires clang-format)
make valgrind        # Run Valgrind checks (requires Valgrind)
```

The build currently links GoogleTest and includes a GoogleTest header from the main container header, so GoogleTest is a build dependency for the current version, not only a test dependency.

## Example usage

```cpp
#include "s21_containers.h"

int main() {
    s21::vector<int> values;
    values.push_back(10);
    values.push_back(20);

    for (auto it = values.begin(); it != values.end(); ++it) {
        // Work with *it
    }
}
```

To use this code in a separate project, add `src/` to your include paths and account for the current GoogleTest dependency in `s21_containers.h`.

## Current limitations

This is an educational implementation. It has not been certified for production use or for full STL conformance. In particular, review iterator semantics, move assignment, edge cases, and memory lifetime before reusing it in other software.

## Background

Developed as a School 21 educational project. The repository contains a team-project codebase; contributions should be attributed according to the project's actual history.
