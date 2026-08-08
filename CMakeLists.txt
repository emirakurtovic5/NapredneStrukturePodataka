cmake_minimum_required(VERSION 3.20)

if(WIN32)
    set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe" CACHE FILEPATH "C compiler")
    set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe" CACHE FILEPATH "C++ compiler")
endif()

project(AdvancedDataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(
    AdvancedDataStructures
    src/main.cpp
)