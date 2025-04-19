cmake_minimum_required(VERSION 3.20)

project(UUEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

get_target_property(QtGui_INCLUDE_DIR Qt6::Gui INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "QtGui include directories: ${QtGui_INCLUDE_DIR}")
