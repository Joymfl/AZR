cmake_minimum_required(VERSION 4.0)
project(Azr_Engine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)


FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.2
)
FetchContent_MakeAvailable(assimp)

add_library(glad ThirdParty/src/glad.c)

target_include_directories(glad PUBLIC ThirdParty/include)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.h")
add_library(imgui STATIC ${PROJECT_SOURCES} imgui/backends/imgui_impl_opengl3.h imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_glfw.h)
target_include_directories(imgui PUBLIC imgui imgui/backends)

add_library(stb_image STATIC ImageLoader/stb_image.cpp)
target_include_directories(stb_image PUBLIC ImageLoader/)

add_executable(Azr_Engine main.cpp
        Shader/Shader.cpp
        Shader/Shader.h)
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
target_link_libraries(Azr_Engine PRIVATE glad glfw OpenGL::GL glm imgui stb_image assimp)
