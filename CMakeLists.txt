cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL LANGUAGES C CXX)

add_executable(LearnOpenGL
    src/main.cpp
    src/glad.c
)

target_compile_features(LearnOpenGL PRIVATE cxx_std_17)

target_include_directories(LearnOpenGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(LearnOpenGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib
)
add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders
        $<TARGET_FILE_DIR:LearnOpenGL>/shaders
)