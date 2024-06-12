# Need CMake 3.28
cmake_minimum_required (VERSION 3.28)

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
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_DICT true PARENT_SCOPE)
        set(DICT_INCLUDE_DIR ${DICT_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the HTTP module
if ( NOT "${HAS_HTTP}")

    # Log
    message("[http] Adding http project")

    # Set the include directory
    set(HTTP_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the http project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_HTTP true PARENT_SCOPE)
        set(HTTP_INCLUDE_DIR ${HTTP_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable (http_example "main.c")
add_dependencies(http_example http hash_cache)
target_include_directories(http_example PUBLIC ${HTTP_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${HASH_CACHE_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(http_example http hash_cache)

# Add source to this project's library
add_library (http SHARED "request.c" "response.c" "http.c")
add_dependencies(http dict hash_cache sync)
target_include_directories(http PUBLIC ${HTTP_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${HASH_CACHE_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(http dict hash_cache sync)