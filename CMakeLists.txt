cmake_minimum_required(VERSION 3.17)
project(LogicGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS -Wall)

set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

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
        src/Graphics/LevelComponents/StaticLogicalComponentsBlock
        src/Graphics/LevelComponents/DocumentationBlock
        src/Graphics/Shapes
        src/Graphics/GUI
)

add_executable(LogicGameEngine main.cpp src/Window/Window.cpp src/Game.cpp src/Events/EventManager.cpp src/Resources/ResourceHolder.cpp src/States/StateManager.cpp src/States/MainMenuState.cpp src/States/MainMenuState.h src/States/LevelState.cpp src/States/LevelState.h src/Simulation/SimulationManager.cpp src/Simulation/SimulationManager.h src/Simulation/Components/LogicalComponents/ActingLogicalComponent.cpp src/Simulation/Components/Connector.cpp src/Simulation/Components/Connector.h src/Simulation/Graphics/LogicalComponentShape.cpp src/Simulation/Graphics/ConnectorShape.cpp src/Simulation/Graphics/LogicalComponentShape.cpp src/Simulation/Graphics/ConnectorShape.cpp src/Simulation/Components/LogicalComponents/And.h src/Simulation/Graphics/WireShape.cpp src/Simulation/Graphics/WireShape.h src/Graphics/LevelComponents/StaticLogicalComponentsBlock/StaticComponentsBlock.cpp src/Graphics/LevelComponents/StaticLogicalComponentsBlock/StaticLogicalComponent.cpp src/Graphics/Shapes/RoundedRectangle.cpp src/Graphics/LevelComponents/DocumentationBlock/DocumentationBlock.cpp src/Graphics/GUI/WrappingText.cpp)

# include SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics)

target_link_libraries(LogicGameEngine ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR})


# include TGUI
#find_package(TGUI 0.9.2)

file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../lib/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})


# Copy resources to build
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})