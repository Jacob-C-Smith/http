# HTTP CMake configuration file:
# This file is meant to be placed in a cmake subfolder of HTTP-devel-2.x.y-VC
cmake_minimum_required(VERSION 3.26)

include(FeatureSummary)
set_package_properties(HTTP PROPERTIES
    URL "https://www.g10.app/status"
    DESCRIPTION "Parse and serialize http requests and responses"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(HTTP_FOUND TRUE)

# For compatibility with autotools HTTP-config.cmake, provide HTTP_* variables.

set_and_check(HTTP_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(HTTP_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(HTTP_INCLUDE_DIR  "${HTTP_PREFIX}/include")
set(HTTP_INCLUDE_DIRS           "${HTTP_INCLUDE_DIR}")
set_and_check(HTTP_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(HTTP_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(HTTP_LIBRARIES http::http)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated HTTP-target.cmake files.

set(_HTTP_library     "${HTTP_LIBDIR}/http.lib")
set(_HTTP_dll_library "${HTTP_BINDIR}/http.dll")
if(EXISTS "${_HTTP_library}" AND EXISTS "${_HTTP_dll_library}")
    if(NOT TARGET http::http)
        add_library(http::http SHARED IMPORTED)
        set_target_properties(http::http
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${HTTP_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_HTTP_library}"
                IMPORTED_LOCATION "${_HTTP_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "HTTP_SHARED"
                INTERFACE_HTTP_SHARED "ON"
        )
    endif()
    set(HTTP_HTTP_FOUND TRUE)
else()
    set(HTTP_HTTP_FOUND FALSE)
endif()
unset(_HTTP_library)
unset(_HTTP_dll_library)

check_required_components(HTTP)
