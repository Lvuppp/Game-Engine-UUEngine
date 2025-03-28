file(GLOB_RECURSE SOURCES 
    *.cpp 
    *.h 
    *.ui
)

add_library(UI ${SOURCES})

target_link_libraries(UI PUBLIC 
    Core 
    Entities
    Qt6::Core 
    Qt6::Gui 
    Qt6::OpenGLWidgets
)

target_include_directories(UI PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src/UI
)
