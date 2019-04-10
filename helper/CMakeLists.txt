add_library(helper INTERFACE)
target_sources(helper INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/helper.h")
target_include_directories(helper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
