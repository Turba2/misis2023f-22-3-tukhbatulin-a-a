cmake_minimum_required(VERSION 3.18)
project(prj.cw)
#include(CTest)
#enable_testing()
set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# include(/opt/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/User/Desktop/test/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(stb REQUIRED)



add_subdirectory(points)


#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
