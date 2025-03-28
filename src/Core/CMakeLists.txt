file(GLOB_RECURSE SOURCES *.cpp *.h)
add_library(Core ${SOURCES})

target_link_libraries(Core PUBLIC 
    Entities 
    Qt6::Gui 
    Qt6::OpenGLWidgets
)

target_include_directories(Core PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/Entities
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Gui_INCLUDE_DIRS}
    ${Qt6OpenGLWidgets_INCLUDE_DIRS}
    ${Qt6Core_INCLUDE_DIRS}
)
