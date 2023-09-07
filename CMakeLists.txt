# Need CMake 3.20
cmake_minimum_required (VERSION 3.20)

# This is the name of the repository
project ("http")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif ()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Log
    message("[HTTP] Adding dict project")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    set(HAS_DICT true PARENT_SCOPE)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[HTTP] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Find the HTTP module
if ( NOT "${HAS_HTTP}")

    # Log
    message("[HTTP] Adding http project")

    # Let any parent project know that it has the http project
    set(HAS_HTTP true PARENT_SCOPE)
endif()

# Add source to this project's executable.
add_executable (http_example "main.c")
add_dependencies(http_example dict sync)
target_include_directories(http_example PUBLIC include include/http ${CMAKE_SOURCE_DIR}/extern/dict/include/ ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(http_example http dict sync)

# Add source to this project's library
add_library (http SHARED "http.c")
add_dependencies(http dict sync)
target_include_directories(http PUBLIC include include/http)
target_link_libraries(http PRIVATE dict sync)
