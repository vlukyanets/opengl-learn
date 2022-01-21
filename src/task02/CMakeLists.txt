project(task02 LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL development files not found!")
endif()

set(SRCS main.cpp ${GLAD_SRCS})

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw dl)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
