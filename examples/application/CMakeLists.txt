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

# Stb from vcpkg provides a FindStb.cmake module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_PREFIX_PATH}")
foreach(_prefix ${CMAKE_PREFIX_PATH})
    if(EXISTS "${_prefix}/share/stb")
        list(APPEND CMAKE_MODULE_PATH "${_prefix}/share/stb")
    endif()
endforeach()
find_package(Stb REQUIRED)

# Link imgui backend components
set(_app_imgui_libs node_editor)
if(TARGET imgui::glfw3)
    list(APPEND _app_imgui_libs imgui::glfw3)
endif()
if(TARGET imgui::opengl3)
    list(APPEND _app_imgui_libs imgui::opengl3)
endif()
target_link_libraries(application PUBLIC ${_app_imgui_libs})

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

# Force GLFW/OpenGL3 backend (DX11/Win32 backends not available)
target_compile_definitions(application PRIVATE
    BACKEND_CONFIG=IMGUI_GLFW
    RENDERER_CONFIG=IMGUI_OGL3
)

target_include_directories(application PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/source)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${_Application_Sources})

target_sources(application PRIVATE ${_Application_Sources})

set_property(TARGET application PROPERTY FOLDER "examples")