project(task01 LANGUAGES CXX)

file(GLOB SRCS "*.cpp" "*.c" "*.hpp" "*.h")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL development files not found!")
endif()

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw dl)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
