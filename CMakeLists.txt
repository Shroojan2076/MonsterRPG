cmake_minimum_required(VERSION 3.28)

# Disable GCC LTO because the MSYS2 LTO plugin is failing to load
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fno-lto")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fno-lto")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fno-lto")

project(MonsterRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

add_executable(MonsterRPG
    src/main.cpp
    src/Game.cpp
    src/ResourceManager.cpp
    src/Tile.cpp
    src/TileMap.cpp
    src/Character.cpp
    src/Player.cpp
    src/NPC.cpp
    src/WorldObject.cpp
    src/Monster.cpp
    src/Item.cpp
    src/StateManager.cpp
    src/OverworldState.cpp
    src/DialogueState.cpp
    src/BattleState.cpp
)

target_include_directories(MonsterRPG PRIVATE src)

target_link_libraries(MonsterRPG PRIVATE
    SFML::Graphics
    SFML::Audio
)