cmake_minimum_required(VERSION 3.25.1)
project(RaylibTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/utility.cpp
    src/input_manager.cpp
    src/object.cpp
    src/timer.cpp
    src/raycast.cpp
    src/physics_object.cpp
    src/moving_object.cpp
    src/solid_object.cpp
    src/player.cpp 
    src/player_state_machine.cpp
    src/player_states.cpp
)
set(CUSTOM_HEADER_PATH "include/")
set(LIBRARIES raylib)

set(BUILD_DIR "build/linux/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CUSTOM_HEADER_PATH})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
