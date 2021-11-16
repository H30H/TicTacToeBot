cmake_minimum_required(VERSION 3.16.3)
project(TicTacToeBot)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(GoogleTests)

include_directories(
        Bot
        Console
        DynamicArray
        Field
        Sequence
)

add_executable(TicTacToeBot
        main.cpp
        Field/myField.cpp
        )