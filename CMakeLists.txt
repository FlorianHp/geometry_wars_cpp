cmake_minimum_required(VERSION 3.15)
project(geometry_wars_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/include)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(geometry_wars_cpp
    main.cpp
    Game.cpp
    Entity.cpp
    EntityManager.cpp
    Vec2.cpp
)

target_link_libraries(geometry_wars_cpp
    SFML::Graphics
    SFML::Window
    SFML::System
)