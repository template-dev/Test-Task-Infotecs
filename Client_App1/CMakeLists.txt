cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME "Client App1")
project(${PROJECT_NAME})

find_package(nlohmann_json)

add_executable(
    ${PROJECT_NAME}
    client.cpp
    src/BufferProcessor.hpp
    src/BufferProcessor.cpp
)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)