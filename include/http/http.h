/** !
 * @file HTTP/HTTP.h 
 * 
 * @author Jacob Smith
 * 
 * Include header for HTTP library
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <errno.h>
#include <ctype.h>

// sync submodule
#include <sync/sync.h>

// dict submodule
#include <dict/dict.h>

// Platform dependent macros
#ifdef _WIN64
    #define DLLEXPORT extern __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

// Set the reallocator for the dict submodule
#ifdef DICT_REALLOC
    #undef DICT_REALLOC
    #define DICT_REALLOC(p, sz) realloc(p, sz)
#endif

// Memory management macro
#ifndef HTTP_REALLOC
    #define HTTP_REALLOC(p, sz) realloc(p,sz)
#endif

// Definitions
#define HTTP_REQUEST_TYPE_COUNT    9
#define HTTP_VERSION_COUNT         3
#define HTTP_RESPONSE_STATUS_COUNT 7

// Enumerations
enum http_request_type_e
{
    HTTP_REQUEST_GET     = 0,
    HTTP_REQUEST_HEAD    = 1,
    HTTP_REQUEST_POST    = 2,
    HTTP_REQUEST_PUT     = 3,
    HTTP_REQUEST_DELETE  = 4,
    HTTP_REQUEST_CONNECT = 5,
    HTTP_REQUEST_OPTIONS = 6,
    HTTP_REQUEST_TRACE   = 7,
    HTTP_REQUEST_PATCH   = 8
};

enum http_response_status_e
{
    HTTP_OK                     = 0,
    HTTP_MOVED_PERMANENTLY      = 1,
    HTTP_FOUND                  = 2,
    HTTP_NOT_MODIFIED           = 3,
    HTTP_FORBIDDEN              = 4,
    HTTP_NOT_FOUND              = 5,
    HTTP_INTERNAL_SERVER_ERROR  = 6
};

const char *http_request_types [HTTP_REQUEST_TYPE_COUNT] =
{
    "GET",
    "HEAD",
    "POST",
    "PUT",
    "DELETE",
    "CONNECT",
    "OPTIONS",
    "TRACE",
    "PATCH"
};

const short http_response_status_codes[HTTP_RESPONSE_STATUS_COUNT] = 
{
    200,
    301,
    302,
    304,
    403,
    404,
    500
};

const char *http_response_status_phrases [HTTP_RESPONSE_STATUS_COUNT] = 
{
    "OK",
    "Moved Permanently",
    "Found",
    "Not Modified",
    "Forbidden",
    "Not Found",
    "Internal Server Error"
};

// Structures
struct http_request_s
{
    enum http_request_type_e request_type;
    char *path;
    dict *p_header_fields;
};

struct http_response_s
{
    enum http_response_status_e code;
    dict *p_header_fields;
};

// Type definitions
typedef struct http_request_s http_request;
typedef struct http_response_s http_response;