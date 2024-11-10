cmake_minimum_required(VERSION 3.28)
project(mini_project)

set(CMAKE_CXX_STANDARD 17)

# Path to SFML
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Include SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(mini_project
        main.cpp
        question.h
        question.cpp
        graphics.cpp
)

# Link SFML libraries
target_link_libraries(mini_project sfml-graphics sfml-window sfml-system)
