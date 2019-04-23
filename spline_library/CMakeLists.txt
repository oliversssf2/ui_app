#adding a header-only library to draw splines
#link boost since it is required in some utilities

find_package(Boost REQUIRED)

add_library(spline INTERFACE)

target_include_directories(spline
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/splines"
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/utils"
    )

target_link_libraries(spline
    INTERFACE Boost::boost
    )
