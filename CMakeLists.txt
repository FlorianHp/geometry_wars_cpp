cmake_minimum_required(VERSION 3.15)
project(geometry_wars_cpp)

set(CMAKE_CXX_STANDARD 17)

# vcpkg kümmert sich um das Include-Verzeichnis von SFML, daher entfernen wir alle hartkodierten Pfade
include_directories(
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/systems
)

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

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System Audio Network)

target_link_libraries(geometry_wars_cpp
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network
)