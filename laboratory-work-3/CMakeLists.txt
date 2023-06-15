cmake_minimum_required(VERSION 3.5)
project(Lab3Project LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
qt_standard_project_setup()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(QCUSTOMPLOTINCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/qcustomplot")

add_subdirectory(src)
add_subdirectory(sample)
add_subdirectory(qcustomplot)
add_subdirectory(app)
