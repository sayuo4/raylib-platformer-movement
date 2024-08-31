cmake_minimum_required(VERSION 3.25.1)
project(RaylibTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/utility.cpp
    src/physics_system.cpp
    src/physics_bodies.cpp
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

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CUSTOM_HEADER_PATH})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

add_custom_target(build
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}
    COMMENT "Building ${PROJECT_NAME}")

add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}
    COMMAND ${CMAKE_BINARY_DIR}/${BUILD_DIR}/${PROJECT_NAME}
    COMMENT "Building and Running ${PROJECT_NAME}")