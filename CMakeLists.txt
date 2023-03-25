cmake_minimum_required(VERSION 3.26.1)
project(quantum_sim)

# Set include directories
include_directories(include)

# Set C++ compiler
set(CMAKE_CXX_COMPILER "g++")

# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Add source files
set(SOURCES
    src/run_quantum.cpp 
    src/QuantumCircuit.cpp 
    src/InitialState.cpp
)

add_executable(quantum_sim ${SOURCES})
