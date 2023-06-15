file(GLOB HEADERS "${include}/*.h")
file(GLOB SOURCES "*.cpp")

add_library(lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(lib PRIVATE ${INCLUDE})