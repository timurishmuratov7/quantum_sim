cmake_minimum_required(VERSION 3.26.1)
project(quantum_sim)

# Set include directories
include_directories(include)

# Set C++ compiler
set(CMAKE_CXX_COMPILER "g++")

# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Add source files
set(SOURCES1
    src/run_quantum.cpp 
    src/QuantumCircuit.cpp 
    src/Gate.cpp 
)

set(SOURCES2
    src/BellState.cpp 
    src/QuantumCircuit.cpp 
    src/Gate.cpp 
)

set(SOURCES3
    src/QuantumTeleportation.cpp 
    src/QuantumCircuit.cpp 
    src/Gate.cpp 
)

add_executable(quantum_sim ${SOURCES1})

add_executable(bell_state ${SOURCES2})

add_executable(quantum_teleport ${SOURCES3})
