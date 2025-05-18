cmake_minimum_required(VERSION 3.20)

project(UUEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(flatbuffers REQUIRED)

message(STATUS "FlatBuffers_FOUND: ${flatbuffers_FOUND}")
message(STATUS "FlatBuffers_INCLUDE_DIRS: ${flatbuffers_INCLUDE_DIRS}")
message(STATUS "FlatBuffers_LIBRARIES: ${flatbuffers_LIBRARIES}")
message(STATUS "FlatBuffers_VERSION: ${flatbuffers_VERSION}")

set(FLATBUFFERS_SCHEMA 
    ${CMAKE_CURRENT_SOURCE_DIR}/schemas/BaseEngineObject.fbs
    ${CMAKE_CURRENT_SOURCE_DIR}/schemas/Scene.fbs
)

set(FLATBUFFERS_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/)

build_flatbuffers("${FLATBUFFERS_SCHEMA}" "" fbschemas "" "${FLATBUFFERS_GENERATED_DIR}" "" "")

set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGLWidgets)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "src/*.h"
)

file(GLOB UI_FILES src/*.ui)
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

file(GLOB RESOURCE_FILES src/UI/*.qrc)
qt6_add_resources(RESOURCE_SOURCES ${RESOURCE_FILES})

add_library(FlatbuffersTarget INTERFACE)
target_include_directories(FlatbuffersTarget INTERFACE ${flatbuffers_INCLUDE_DIR})
add_dependencies(FlatbuffersTarget fbschemas)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
    ${UI_SOURCES}
    ${RESOURCE_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGLWidgets
    flatbuffers
    FlatbuffersTarget
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/src
    ${FLATBUFFERS_GENERATED_DIR}
)

get_target_property(QtGui_INCLUDE_DIR Qt6::Gui INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "QtGui include directories: ${QtGui_INCLUDE_DIR}")
