cmake_minimum_required(VERSION 3.15)  # CMake version check
project(BlackJack C)                  # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(deck.h deck.c gameplay.h gameplay.c graphics.c graphics.h ${SOURCE_FILES})