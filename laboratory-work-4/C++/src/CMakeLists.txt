file(GLOB HDRS "${INCLUDE}/*.h")
file(GLOB SRCS "*.cpp")

add_library(lib STATIC ${SRCS} ${HDRS})
target_include_directories(lib PRIVATE ${INCLUDE})