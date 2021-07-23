cmake_minimum_required(VERSION 3.15)

project("LinkedList" VERSION 1.0 DESCRIPTION "Linked List")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(extern/Unity)
add_subdirectory(library)
add_subdirectory(test)
