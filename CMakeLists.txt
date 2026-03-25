cmake_minimum_required(VERSION 3.20)
project(Project2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Project2
        src/main.cpp
        src/Transaction.cpp
        src/CSVReader.cpp
)