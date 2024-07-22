cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME "Infotecs")
set(EXTERNAL_LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external-libraries")

project(${PROJECT_NAME})

include(FetchContent)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
    SOURCE_DIR ${EXTERNAL_LIBS_DIR}/json
)
FetchContent_MakeAvailable(json)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Program_1)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Program_2)