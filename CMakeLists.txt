cmake_minimum_required(VERSION 3.15)
project(geometry_wars_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/systems
    /opt/homebrew/include
)

find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(geometry_wars_cpp
    src/main.cpp
    src/core/Game.cpp
    src/core/Entity.cpp
    src/core/EntityManager.cpp
    src/systems/SMovement.cpp
    src/systems/SCollisionDetection.cpp
    src/systems/SCollisionResponse.cpp
    src/systems/SEnemySpawner.cpp
    src/systems/SRender.cpp
    src/systems/SUserInput.cpp
    src/systems/SBullet.cpp
    src/systems/SExplosion.cpp
)

target_link_libraries(geometry_wars_cpp
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)