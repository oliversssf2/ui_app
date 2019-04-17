add_library(helper INTERFACE)
target_include_directories(helper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(helper INTERFACE helper.h)
