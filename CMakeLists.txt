cmake_minimum_required(VERSION 3.24)
project(imgui_node_editor)

if(WIN32) 
    set(CMAKE_DEBUG_POSTFIX d)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(lux-cmake-toolset CONFIG REQUIRED)

# Query actually installed imgui components via lux-cmake-toolset
query_package_components(
    PACKAGE_NAME imgui
    RESULT       _IMGUI_AVAILABLE_COMPONENTS
    REQUIRED
)
message(STATUS "Available ImGui components: ${_IMGUI_AVAILABLE_COMPONENTS}")
find_package(imgui CONFIG REQUIRED COMPONENTS ${_IMGUI_AVAILABLE_COMPONENTS})

set(IMGUI_NODE_EDITOR_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_api.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_api.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/crude_json.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_canvas.cpp
)

set(IMGUI_NODE_EDITOR_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/crude_json.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_bezier_math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_bezier_math.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_canvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_extra_math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_extra_math.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_internal.inl
)

add_component(
    COMPONENT_NAME node_editor
    STATIC 
    NAMESPACE      imgui
    SOURCE_FILES   ${IMGUI_NODE_EDITOR_SRCS}
    OUTPUT_NAME    imgui_node_editor
)

component_include_directories(
    node_editor
    BUILD_TIME_SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}
    INSTALL_TIME
        include
)

target_link_libraries(
    node_editor
    PUBLIC
        imgui::core
)

install_components(
	PROJECT_NAME	node_editor
	VERSION			0.0.0
	NAMESPACE		imgui
	COMPONENTS		node_editor
)

install(
    FILES       ${IMGUI_NODE_EDITOR_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

set(ENABLE_EXAMPLE OFF CACHE BOOL "Enable example")
if(ENABLE_EXAMPLE)
    add_subdirectory(examples)
endif()

# ── Packaging (CPack → .deb). LUX fork of imgui-node-editor. Depends on the imgui
# fork (links imgui::core), so the imgui package is declared.
lux_configure_packaging(
    NAME     node_editor
    VERSION  0.0.0
    SUMMARY  "imgui-node-editor (LUX fork): node/graph editor for Dear ImGui"
    VENDOR   "LUX-YU"
    CONTACT  "LUX-YU <chenhui.lux.yu@outlook.com>"
    HOMEPAGE "https://github.com/LUX-YU/imgui-node-editor"
    DEB_DEPENDS  "imgui" "lux-cmake-toolset (>= 0.5.0)"
    RPM_REQUIRES "imgui" "lux-cmake-toolset >= 0.5.0"
)
