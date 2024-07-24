cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME "Program_2")
project(${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(
    ${PROJECT_NAME}
    src/DataReceiver.hpp
    main.cpp
    src/DataReceiver.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
