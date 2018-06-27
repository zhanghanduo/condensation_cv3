cmake_minimum_required(VERSION 3.0)
project(particle_cv3)

IF(NOT CMAKE_BUILD_TYPE)
    # SET(CMAKE_BUILD_TYPE Debug)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-reorder -O3 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder  -O3")

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    add_definitions(-DCOMPILEDWITHC11)
    message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    add_definitions(-DCOMPILEDWITHC0X)
    message(STATUS "Using flag -std=c++0x.")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(OpenCV 3.1 QUIET)

#if(NOT OpenCV_FOUND)
#    find_package(OpenCV 2.4.13 QUIET)
#    message(STATUS "OpenCV 2.4.13 .")
#    if(NOT OpenCV_FOUND)
#        message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
#    endif()
#endif()
include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(particle_cv3 demo.cpp condens.cpp random.cpp)
target_link_libraries(particle_cv3 ${OpenCV_LIBS})