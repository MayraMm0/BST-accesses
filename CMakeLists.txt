cmake_minimum_required(VERSION 4.0)
project(BST_accesses)

set(CMAKE_CXX_STANDARD 20)

add_executable(BST_accesses
        main.cpp
        Node.h
        BinarySearchTree.h
        IP.h
        IP.cpp
        Register.cpp
        Register.h
        LogManager.h
        AccessRecord.h
        LogManager.cpp
)
