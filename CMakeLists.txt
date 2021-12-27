cmake_minimum_required(VERSION 3.17)
project(LogicGameEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        src_old
        src_old/States
        src_old/Window
        src_old/Resources
        src_old/Resources/Resources
        src_old/Events
)

add_executable(LogicGameEngine main.cpp src_old/Window/Window.cpp src_old/Game.cpp src_old/Events/EventManager.cpp src_old/Resources/ResourceHolder.cpp src_old/States/StateManager.cpp src_old/States/MainMenuState.cpp src_old/States/MainMenuState.h)

# include SFML
set(SFML_ROOT D:/Programs/CLionProjects/Libraries/SFML-debug/)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics)

target_link_libraries(LogicGameEngine ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR})

# include TGUI
set(TGUI_DIR D:/Programs/CLionProjects/Libraries/TGUI/)

find_library(TGUI_LIBRARY_DEBUG
        NAMES libtgui-d
        PATH_SUFFIXES lib
        PATHS ${TGUI_DIR})
target_link_libraries(LogicGameEngine ${TGUI_LIBRARY_DEBUG})

include_directories(${TGUI_DIR}/include)

file(GLOB BINARY_DEP_DLLS "${TGUI_DIR}/include/*.dll")

# Copy dlls to build
file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../lib/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB MINGW_DEP_DLLS "D:/Program Files/MinGW/mingw64/bin/*.dll")
file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

# Copy resources to build
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})