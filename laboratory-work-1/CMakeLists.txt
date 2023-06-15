CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(Lab1Project LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
qt_standard_project_setup()

set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(QCUSTOMPLOTINCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/qcustomplot")

#add_subdirectory(sample)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(qcustomplot)
