cmake_minimum_required(VERSION 3.17)
project(LogicGameEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        src
        src/States
        src/Window
        src/Resources
        src/Resources/Resources
        src/Events
        src/Simulation
        src/Simulation/Components
        src/Simulation/Components/LogicalComponents
        src/Simulation/Graphics
        src/Simulation/Graphics/StaticLogicalComponentsBlock
        src/Graphics/Shapes
)

add_executable(LogicGameEngine main.cpp src/Window/Window.cpp src/Game.cpp src/Events/EventManager.cpp src/Resources/ResourceHolder.cpp src/States/StateManager.cpp src/States/MainMenuState.cpp src/States/MainMenuState.h src/States/LevelState.cpp src/States/LevelState.h src/Simulation/SimulationManager.cpp src/Simulation/SimulationManager.h src/Simulation/Components/LogicalComponents/ActingLogicalComponent.cpp src/Simulation/Components/Connector.cpp src/Simulation/Components/Connector.h src/Simulation/Graphics/LogicalComponentShape.cpp src/Simulation/Graphics/ConnectorShape.cpp src/Simulation/Graphics/LogicalComponentShape.cpp src/Simulation/Graphics/ConnectorShape.cpp src/Simulation/Components/LogicalComponents/And.h src/Simulation/Graphics/WireShape.cpp src/Simulation/Graphics/WireShape.h src/Simulation/Graphics/StaticLogicalComponentsBlock/StaticComponentsBlock.cpp src/Simulation/Graphics/StaticLogicalComponentsBlock/StaticLogicalComponent.cpp src/Graphics/Shapes/RoundedRectangle.cpp)

# include SFML
set(SFML_ROOT D:/Programs/CLionProjects/Libraries/SFML-debug/)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics)

target_link_libraries(LogicGameEngine ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR})

# include TGUI
#set(TGUI_DIR D:/Programs/CLionProjects/Libraries/TGUI/)
#
#find_library(TGUI_LIBRARY_DEBUG
#        NAMES libtgui-d
#        PATH_SUFFIXES lib
#        PATHS ${TGUI_DIR})
#target_link_libraries(LogicGameEngine ${TGUI_LIBRARY_DEBUG})
#
#include_directories(${TGUI_DIR}/include)
#
#file(GLOB BINARY_DEP_DLLS "${TGUI_DIR}/include/*.dll")

# Copy dlls to build
file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../lib/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB MINGW_DEP_DLLS "D:/Program Files/MinGW/mingw64/bin/*.dll")
file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

# Copy resources to build
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})