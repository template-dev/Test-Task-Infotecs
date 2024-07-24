cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME "Program_1")
project(${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(
    ${PROJECT_NAME}    
    src/NetworkManager.hpp
    src/DataProcessor.hpp
    
    main.cpp
    src/NetworkManager.cpp
    src/DataProcessor.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
