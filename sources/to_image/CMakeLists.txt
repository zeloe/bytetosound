# Add all source files to the list of sources for the executable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS source/*.cpp source/*.h)



 




add_executable(to_image ${lodepng_SOURCE_DIR}/lodepng.cpp)



# Manually specify include directories and link the library
target_include_directories(to_image PRIVATE ${lodepng_SOURCE_DIR})



# Add all sources to the target
target_sources(to_image PRIVATE ${SOURCES})