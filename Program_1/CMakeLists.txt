cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME "Program_1")
project(${PROJECT_NAME})

add_executable(
    ${PROJECT_NAME}    
    src/NetworkManager.hpp
    src/BufferProcessor.hpp
    src/StatusCodes.hpp
    
    main.cpp
    src/NetworkManager.cpp
    src/BufferProcessor.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  nlohmann_json::nlohmann_json
)
