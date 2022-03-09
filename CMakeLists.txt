cmake_minimum_required(VERSION 3.17)
project(LogicGameEngine)

set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_OSX_ARCHITECTURES "arm64")

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
        src/Graphics/
        src/Graphics/GUI
        src/Graphics/LevelComponents/GUI
        src/Levels
        src/Graphics/LevelComponents
        src/Constants
)

add_executable(LogicGameEngine main.cpp src/Window/Window.cpp src/Game.cpp src/Events/EventManager.cpp src/Resources/ResourceHolder.cpp src/States/StateManager.cpp src/States/MainMenuState.cpp src/States/MainMenuState.h src/States/LevelState.cpp src/States/LevelState.h src/Simulation/SimulationManager.cpp src/Simulation/SimulationManager.h src/Simulation/Components/LogicalComponents/ActingLogicalComponent.cpp src/Simulation/Components/Connector.cpp src/Simulation/Components/Connector.h src/Simulation/Graphics/LogicalComponentShape.cpp src/Simulation/Graphics/ConnectorShape.cpp src/Simulation/Graphics/LogicalComponentShape.cpp src/Simulation/Graphics/ConnectorShape.cpp src/Simulation/Components/LogicalComponents/And.h src/Simulation/Graphics/WireShape.cpp src/Simulation/Graphics/WireShape.h src/Graphics/LevelComponents/StaticLogicalComponentsBlock/StaticComponentsBlock.cpp src/Graphics/LevelComponents/StaticLogicalComponentsBlock/StaticLogicalComponent.cpp src/Graphics/Shapes/RoundedRectangle.cpp src/Graphics/LevelComponents/DocumentationBlock/DocumentationBlock.cpp src/Graphics/WrappingText.cpp src/Graphics/LevelComponents/LevelControls.cpp src/Graphics/LevelComponents/LevelControls.h src/Graphics/GUI/Button.cpp src/Graphics/GUI/Button.h src/States/LevelResultState.cpp src/States/LevelResultState.h src/Simulation/SimulationConnectorsManager.cpp src/Simulation/SimulationConnectorsManager.h src/Graphics/GUI/ScrollBox.cpp src/Graphics/GUI/ScrollBox.h src/States/LevelChooseState.cpp src/States/LevelChooseState.h src/Levels/LevelManager.cpp src/Levels/LevelManager.h src/Levels/LevelsLoader.cpp src/Levels/LevelsLoader.h src/Levels/Level.h src/States/GameCompleteState.cpp src/States/GameCompleteState.h src/Graphics/LevelComponents/LevelLayout.cpp src/Graphics/LevelComponents/LevelLayout.h src/Graphics/LevelComponents/DocumentationBlock/Documentation.cpp src/Graphics/LevelComponents/DocumentationBlock/Documentation.h src/Graphics/LevelComponents/DocumentationBlock/TruthTable.cpp src/Graphics/LevelComponents/DocumentationBlock/TruthTable.h src/Resources/SmoothTexture.h src/Simulation/Components/LogicalComponents/ComponentsDataFactory.cpp src/Simulation/Components/LogicalComponents/ComponentsDataFactory.h src/States/FetchingLevelsState.cpp src/States/FetchingLevelsState.h src/Simulation/Components/LogicalComponents/Xor.h src/Constants/Colors.cpp src/Constants/Colors.h src/Constants/Positions.cpp src/Constants/Positions.h src/Constants/Paths.cpp src/Constants/Paths.h)

# include SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics)

target_link_libraries(LogicGameEngine ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR})

# include tinyxml
find_path(TINYXML2_INCLUDE_DIR NAMES tinyxml2.h PATH_SUFFIXES include PATHS /usr/local)
find_library(TINYXML2_LIBRARY NAMES tinyxml2)

message(${TINYXML2_LIBRARY})

message(${TINYXML2_INCLUDE_DIR})

target_link_libraries(LogicGameEngine ${TINYXML2_LIBRARY})

include_directories(${TINYXML2_INCLUDE_DIR})


# include TGUI
#find_package(TGUI 0.9.2)
#target_link_libraries(LogicGameEngine ${TGUI_LIBRARY} ${SFML_LIBRARIES})

#include_directories(${TGUI_INClUDE_DIR})

file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../lib/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})


find_package(CURL)

include_directories(${CURL_INCLUDE_DIRS})

target_link_libraries(LogicGameEngine ${CURL_LIBRARIES})

# Copy resources to build
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})