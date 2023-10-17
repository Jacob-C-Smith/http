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
#include <stdarg.h>
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
#define HTTP_REQUEST_TYPE_COUNT                  9
#define HTTP_VERSION_COUNT                       3
#define HTTP_RESPONSE_STATUS_COUNT               7
#define HTTP_REQUEST_TYPE_MMH64_HASH_TABLE_COUNT 21

// Enumerations
enum http_request_type_e
{
    HTTP_REQUEST_GET     = 1,
    HTTP_REQUEST_HEAD    = 2,
    HTTP_REQUEST_POST    = 3,
    HTTP_REQUEST_PUT     = 4,
    HTTP_REQUEST_DELETE  = 5,
    HTTP_REQUEST_CONNECT = 6,
    HTTP_REQUEST_OPTIONS = 7,
    HTTP_REQUEST_TRACE   = 8,
    HTTP_REQUEST_PATCH   = 9
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

enum http_request_type_e http_request_type_hash_table_mmh64[HTTP_REQUEST_TYPE_MMH64_HASH_TABLE_COUNT] = 
{
    0, 0, HTTP_REQUEST_PUT, 0, HTTP_REQUEST_OPTIONS, HTTP_REQUEST_GET, HTTP_REQUEST_DELETE, 
    HTTP_REQUEST_PATCH, 0, 0, 0, 0, HTTP_REQUEST_CONNECT, 0,
    HTTP_REQUEST_POST, HTTP_REQUEST_TRACE, 0, 0, 0, 0, HTTP_REQUEST_HEAD
};

// Type definitions
typedef enum http_request_type_e    http_request_type;
typedef enum http_response_status_e http_response_status;

// Serializers
/** !
 * Generate an HTTP request text
 * 
 * @param request_text return
 * @param request_type enumeration of request methods < GET | HEAD | POST | PATCH | etc >
 * @param path         the path of the requested resource
 * @param format       a percent delimited string of format specifiers
 * @param ...          The values specified in the format string
 * 
 * @return 1 on success, 0 on error        
 */
DLLEXPORT int http_serialize_request (
    char              *request_text, 
    http_request_type  request_type,
    const char        *path,
    const char        *format,
    ...
);

/** !
 * Generate an HTTP response text
 * 
 * @param response_text   return
 * @param response_status enumeration of response codes < OK | Moved Permanently | Found | etc >
 * @param format          a percent delimited string of format specifiers
 * @param ...             The values specified in the format string
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int http_serialize_response (
    char                 *response_text, 
    http_response_status  response_status,
    const char           *format,
    ...
);

/** !
 * Destructivly parse an HTTP request
 * 
 * @param request_text      the HTTP request text
 * @param p_request_type    returns the request methods < GET | HEAD | POST | PATCH | etc >
 * @param p_path            returns the requested path
 * @param pp_request_fields the request fields, encoded in a dictionary
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int http_parse_request (
    char               *request_text,
    http_request_type  *p_request_type,
    char              **pp_path,
    dict              **pp_request_fields
);