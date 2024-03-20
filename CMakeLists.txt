cmake_minimum_required(VERSION 3.22)
project(Pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}../SFMLlib/)
set(SFML_INCLUDE ${LIBRARY_DIR}include)
set(SFML_LIB ${LIBRARY_DIR}lib)

add_executable(${PROJECT_NAME} main.cpp source/application/Application.cpp source/state/IState.cpp source/drawable/menu/Menu.cpp source/command/ISelectCommand.cpp source/drawable/maze/Maze.cpp source/drawable/entity/PacMan.cpp source/drawable/entity/IEntity.cpp source/context/Context.cpp source/event/IGameEvent.cpp source/builder/GameBuilderDirector.cpp source/builder/SimpleGameBuilder.cpp source/builder/ComplexGameBuilder.cpp source/state/SelectLevelState.cpp source/state/GameState.cpp)

message(${PROJECT_SOURCE_DIR})
find_package(SFML 2.5 COMPONENTS graphics system window audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window sfml-audio)











