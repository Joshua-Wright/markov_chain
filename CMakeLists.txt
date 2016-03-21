cmake_minimum_required(VERSION 3.3)
project(markov)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#project(assembler C ASM) # this enables building the assembly part of the code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfltk -lfltk_images")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lginac -lcln") # for ginac

add_executable(find_unique_words find_unique_words.cpp)

add_executable(markov_demo
        markov_chain.cpp
        markov_demo.cpp
)