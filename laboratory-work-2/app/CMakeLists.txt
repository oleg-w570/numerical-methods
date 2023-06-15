file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cpp")
file(GLOB UI "*.ui")

add_executable(app ${SRCS} ${HDRS} ${UI})
target_link_libraries(app PRIVATE lib Qt6::Widgets Qt6::Charts)
target_include_directories(app PRIVATE ${INCLUDE})
set_target_properties(app PROPERTIES WIN32_EXECUTABLE ON)

