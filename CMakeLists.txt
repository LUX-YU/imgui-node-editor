cmake_minimum_required(VERSION 3.24)
project(imgui_node_editor)

if(WIN32) 
    set(CMAKE_DEBUG_POSTFIX d)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(lux-cmake-toolset CONFIG REQUIRED)
find_package(imgui             CONFIG REQUIRED COMPONENTS core)

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
