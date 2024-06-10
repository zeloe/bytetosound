# Add all source files to the list of sources for the executable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS source/*.cpp source/*.h)

 





add_executable(to_sound) 

 


# Add all sources to the target
target_sources(to_sound PRIVATE ${SOURCES})


 