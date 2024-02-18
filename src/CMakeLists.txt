cmake_minimum_required(VERSION 3.17)

project(blendJpeg CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp -fopenmp-simd")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopt-info-vec -fopt-info-vec-optimized")

find_package(Boost 1.71 REQUIRED COMPONENTS program_options log)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LibJpeg REQUIRED IMPORTED_TARGET libjpeg)

message(LibJpeg_LDFLAGS="${LibJpeg_LDFLAGS}")
add_executable(blendJpeg main.cpp JpegUtils.cpp)

target_include_directories(blendJpeg PRIVATE ${LibJpeg_INCLUDE_DIRS})

target_link_libraries(blendJpeg 
    ${Boost_LIBRARIES}
    ${LibJpeg_LDFLAGS}
    pthread
    )
