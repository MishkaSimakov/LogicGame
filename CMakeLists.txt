cmake_minimum_required(VERSION 3.17)
project(LogicGameEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        src
        src/States
        src/ResourceManager/Resources
        src/ResourceManager
        src/GUI
        src/GUI/Buttons
        src/GUI/LogicalComponents
        src/GUI/LevelComponents
        src/GUI/LevelComponents/Simulation
        src/GUI/LevelComponents/Simulation/LogicalComponents
)

add_executable(LogicGameEngine
        main.cpp
        src/Game.cpp
        src/GUI/Buttons/Button.cpp
        src/GUI/RoundedRectangle.cpp
        src/GUI/LevelComponents/StaticLogicalComponent.cpp
        src/ResourceManager/ResourceHolder.cpp
        src/States/LevelState.cpp
        src/States/MainMenuState.cpp
        src/GUI/LevelComponents/Simulation/ActingLogicalComponent.cpp src/GUI/LevelComponents/Simulation/ActingLogicalComponent.h src/GUI/LevelComponents/DocumentationBlock.cpp src/GUI/LevelComponents/DocumentationBlock.h src/GUI/WrappingText.cpp src/GUI/WrappingText.h src/GUI/LevelComponents/Simulation/Connector.cpp src/GUI/LevelComponents/Simulation/Connector.h src/GUI/LevelComponents/Simulation/Simulation.cpp src/GUI/LevelComponents/Simulation/Simulation.h src/ResourceManager/Resources/LevelResource.h src/GUI/LevelComponents/StaticComponentsBlock.cpp src/GUI/LevelComponents/StaticComponentsBlock.h src/Event.cpp src/Event.h src/GUI/LevelComponents/Simulation/LogicalComponents/BaseLogicalComponent.h src/GUI/LevelComponents/Simulation/LogicalComponents/And.h src/GUI/LevelComponents/Simulation/LogicalComponents/Or.h src/GUI/Tree/Node.h src/GUI/Tree/Node.cpp src/GUI/Tree/Tree.cpp src/GUI/Tree/Tree.h)

# include SFML
set(SFML_ROOT D:/Programs/CLionProjects/Libraries/SFML-debug/)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics)

target_link_libraries(LogicGameEngine ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR})

# Copy dlls to build
file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../lib/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB MINGW_DEP_DLLS "D:/Program Files/MinGW/mingw64/bin/*.dll")
file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

# Copy resources to build
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})