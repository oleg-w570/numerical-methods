file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cpp")

add_executable(sample ${SRCS} ${HDRS})
target_link_libraries(sample lib)
target_include_directories(sample PRIVATE ${INCLUDE})