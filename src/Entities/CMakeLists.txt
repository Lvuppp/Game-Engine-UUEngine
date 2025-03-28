file(GLOB_RECURSE SOURCES *.cpp *.h)
add_library(Entities ${SOURCES})

target_link_libraries(Entities PUBLIC 
    Qt6::Gui 
    Qt6::OpenGLWidgets
)

target_include_directories(Entities PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Gui_INCLUDE_DIRS}
    ${Qt6OpenGLWidgets_INCLUDE_DIRS}
)
