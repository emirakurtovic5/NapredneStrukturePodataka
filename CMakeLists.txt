cmake_minimum_required(VERSION 3.20)

project(AdvancedDataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Glavni program
add_executable(AdvancedDataStructures
    src/main.cpp
)

target_include_directories(AdvancedDataStructures PRIVATE
    src
    include
)

# Testovi
enable_testing()

# Testovi za AVL stablo
add_executable(AVLTreeTests
    tests/AVLTreeTests.cpp
)

target_include_directories(AVLTreeTests PRIVATE
    src
    include
)

add_test(
    NAME AVLTreeTests
    COMMAND AVLTreeTests
)

# Testovi za Red-Black stablo
add_executable(RedBlackTreeTests
    tests/RedBlackTreeTests.cpp
)

target_include_directories(RedBlackTreeTests PRIVATE
    src
    include
)

add_test(
    NAME RedBlackTreeTests
    COMMAND RedBlackTreeTests
)

# Testovi za Hash tabelu
add_executable(HashTableTests
    tests/HashTableTests.cpp
)

target_include_directories(HashTableTests PRIVATE
    src
    include
)

add_test(
    NAME HashTableTests
    COMMAND HashTableTests
)

# Benchmark za AVL stablo
add_executable(AVLBenchmark
    benchmarks/AVLBenchmark.cpp
)

target_include_directories(AVLBenchmark PRIVATE
    src
    include
)

# Benchmark za Red-Black stablo
add_executable(RedBlackBenchmark
    benchmarks/RedBlackBenchmark.cpp
)

target_include_directories(RedBlackBenchmark PRIVATE
    src
    include
)

# Benchmark za Hash tabelu
add_executable(HashBenchmark
    benchmarks/HashBenchmark.cpp
)

target_include_directories(HashBenchmark PRIVATE
    src
    include
)