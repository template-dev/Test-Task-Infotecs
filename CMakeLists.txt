cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME "Infotecs")
project(${PROJECT_NAME})

#include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

#cmake_policy(SET CMP0091 NEW)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/Client_App1
)

#add_subdirectory(
#        ${CMAKE_CURRENT_SOURCE_DIR}/Server_App2
#)

#target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})