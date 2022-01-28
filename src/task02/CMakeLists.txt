project(task02 LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL development files not found!")
endif()

set(SRCS ${GLAD_SRCS} main.cpp
    shader.cpp shader.hpp
    window_manager.cpp window_manager.hpp
    shader_program.cpp shader_program.hpp)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw dl)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)

set(SHADER_FILES vertex_shader_01.glsl fragment_shader_01.glsl)
foreach(SHADER_FILE ${SHADER_FILES})
    configure_file(shaders/${SHADER_FILE} ${CMAKE_SHADERS_OUTPUT_DIRECTORY}/${SHADER_FILE})
endforeach()
