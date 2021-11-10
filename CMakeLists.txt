cmake_minimum_required(VERSION 3.17)
project(LogicGameEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        src
        src/States
        src/ResourceManager
        src/GUI
        src/GUI/Buttons
        src/GUI/LogicalComponents
        src/GUI/LevelComponents
)

add_executable(LogicGameEngine
        main.cpp
        src/Game.cpp
        src/GUI/Buttons/Button.cpp
        src/GUI/RoundedRectangle.cpp
        src/GUI/LogicalComponents/StaticLogicalComponent.cpp
        src/ResourceManager/ResourceHolder.cpp
        src/States/LevelState.cpp
        src/States/MainMenuState.cpp
        src/GUI/LogicalComponents/ActingLogicalComponent.cpp src/GUI/LogicalComponents/ActingLogicalComponent.h src/GUI/LevelComponents/DocumentationBlock.cpp src/GUI/LevelComponents/DocumentationBlock.h src/GUI/WrappingText.cpp src/GUI/WrappingText.h src/GUI/LogicalComponents/Wire.cpp src/GUI/LogicalComponents/Wire.h src/GUI/LogicalComponents/Input.cpp src/GUI/LogicalComponents/Input.h src/GUI/LogicalComponents/Simulation.cpp src/GUI/LogicalComponents/Simulation.h)

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