project(application)

set(_Application_Sources
    include/application.h
    source/application.cpp
    source/entry_point.cpp
    source/imgui_extra_keys.h
    source/config.h.in
    source/setup.h
    source/platform.h
    source/platform_glfw.cpp
    source/renderer.h
    source/renderer_ogl3.cpp
    source/imgui_extend.cpp
)

add_library(application STATIC)

target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Stb REQUIRED)
target_link_libraries(application PUBLIC node_editor imgui::glfw imgui::opengl3)

target_include_directories(
    application PRIVATE
    ${Stb_INCLUDE_DIR}
)

if (APPLE)
    target_link_libraries(application PRIVATE
        "-framework CoreFoundation"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()

set(HAVE_OPENGL YES)
set(HAVE_GLFW3 YES)

configure_file(
    source/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/source/config.h
)

target_compile_definitions(application PRIVATE
    #BACKEND_CONFIG=IMGUI_GLFW
    #RENDERER_CONFIG=IMGUI_OGL3
)

target_include_directories(application PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/source)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${_Application_Sources})

target_sources(application PRIVATE ${_Application_Sources})

set_property(TARGET application PROPERTY FOLDER "examples")