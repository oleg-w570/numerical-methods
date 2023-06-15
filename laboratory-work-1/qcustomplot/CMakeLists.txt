file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cpp")

add_library(qcustomplot SHARED ${SRCS} ${HDRS})
target_link_libraries(qcustomplot PUBLIC Qt6::Core Qt6::PrintSupport)
target_compile_definitions(qcustomplot PRIVATE QCUSTOMPLOT_COMPILE_LIBRARY)
