# Add all source files to the list of sources for the executable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS source/*.cpp source/*.h)

# Add all sources to the target
target_sources(${TARGET_NAME} PRIVATE ${SOURCES})