cmake_minimum_required(VERSION 3.30)
project(CPPCA3)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPPCA3 main.cpp Crawler.cpp Board.cpp Bug.cpp Hopper.cpp BugRenderer.cpp SuperBug.cpp)

# Tell CMake where SFML is installed
set(SFML_DIR "C:/sfml-2.6.2/lib/cmake/SFML")

# Find SFML and the components you need
find_package(SFML 2.6.2 REQUIRED COMPONENTS system window graphics network)

# Link the required libraries
include_directories(C:/sfml-2.6.2/include)
target_link_libraries(CPPCA3 sfml-system sfml-window sfml-graphics)

# Copy resources to output directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
