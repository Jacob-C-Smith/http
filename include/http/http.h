/** !
 * @file http/http.h 
 * 
 * @author Jacob Smith
 * 
 * Include header for http library
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
#define HTTP_RESPONSE_STATUS_COUNT               27
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
    HTTP_CONTINUE               = 0,
    HTTP_SWITCHING_PROTOCOLS    = 1,
    HTTP_OK                     = 2,
    HTTP_CREATED                = 3,
    HTTP_NO_CONTENT             = 4,
    HTTP_RESET_CONTENT          = 5,
    HTTP_PARTIAL_CONTENT        = 6,    
    HTTP_MOVED_PERMANENTLY      = 7,
    HTTP_FOUND                  = 8,
    HTTP_NOT_MODIFIED           = 9,
    HTTP_TEMPORARY_REDIRECT     = 10,
    HTTP_PERMANENT_REDIRECT     = 11,
    HTTP_BAD_REQUEST            = 12,
    HTTP_UNAUTHORIZED           = 13,
    HTTP_FORBIDDEN              = 14,
    HTTP_NOT_FOUND              = 15,
    HTTP_NOT_ACCEPTABLE         = 16,
    HTTP_LENGTH_REQUIRED        = 17,
    HTTP_PAYLOAD_TOO_LARGE      = 18,
    HTTP_URI_TOO_LONG           = 19,
    HTTP_RANGE_NOT_SATISFIABLE  = 20,
    HTTP_UPGRADE_REQUIRED       = 21,
    HTTP_INTERNAL_SERVER_ERROR  = 22
};

// Lookup
static const char *http_request_types [HTTP_REQUEST_TYPE_COUNT] =
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

static const short http_response_status_codes[HTTP_RESPONSE_STATUS_COUNT] = 
{
    100,
    101,
    200,
    201,
    204,
    205,
    206,
    301,
    302,
    304,
    307,
    308,
    400,
    401,
    403,
    404,
    405,
    411,
    413,
    414,
    416,
    426,
    429,
    500,
    501,
    503,
    505
};

static const char *http_response_status_phrases [HTTP_RESPONSE_STATUS_COUNT] = 
{
    "Continue",
    "Switching Protocols"
    "OK",
    "Created",
    "No Content",
    "Reset Content",
    "Partial Content"
    "Moved Permanently",
    "Found",
    "Not Modified",
    "Temporary Redirect",
    "Permanent Redirect",
    "Bad Request",
    "Unauthorized",
    "Forbidden",
    "Not Found",
    "Method Not Allowed",
    "Length Required",
    "Payload Too Large",
    "URI Too Long",
    "Range Not Satifiable",
    "Upgrade Required",
    "Too Many Requests",
    "Internal Server Error",
    "Not Implemented",
    "Service Unavailable",
    "HTTP Version Not Supported"
};

static enum http_request_type_e http_request_type_hash_table_mmh64[HTTP_REQUEST_TYPE_MMH64_HASH_TABLE_COUNT] = 
{
    0, 0, HTTP_REQUEST_PUT, 0, HTTP_REQUEST_OPTIONS, HTTP_REQUEST_GET, HTTP_REQUEST_DELETE, 
    HTTP_REQUEST_PATCH, 0, 0, 0, 0, HTTP_REQUEST_CONNECT, 0,
    HTTP_REQUEST_POST, HTTP_REQUEST_TRACE, 0, 0, 0, 0, HTTP_REQUEST_HEAD
};

// Forward declarations
struct http_request_s;
struct http_response_s;

// Type definitions
typedef struct   http_message_s http_message;
typedef enum     http_request_type_e    http_request_type;
typedef enum     http_response_status_e http_response_status;
typedef int    (*http_request_response_fn)(http_message _http_request, http_message _http_response);

// Structure definitions
struct http_message_s
{
    int keep_alive;
    char *body;
    bool status;

    struct
    {
        struct 
        {
            char *accept;
            char *language;
            char *encoding;
        } accept_headers;
        char *host;
        char *user_agent;
        char *referrer;
        char *connection;
        http_request_type type;
        char *path;
    } request;

    struct 
    {
        struct
        {
            char *encoding;
            char *type;
            char *date;
        } content;
        struct 
        {
            char *set;
        } cookie;
        http_response_status status_code;
    } response;

    struct 
    {
        char *type;
        char *encoding;
        char *language;
        char *location;
        char *length;
        char *range;
    } representation;

    struct
    {
        char *trailer;
        char *transfer_encoding;
    } payload;
};

// HTTP Requests
/** !
 * Generate an HTTP request text
 *
 * @param pp_request    
 * @param p_request_text 
 * @param max_request_len 
 * 
 * @return 1 on success, 0 on error        
 */
DLLEXPORT int http_serialize_request (
    char *p_request_text,
    http_message *p_http_request
);

/** !
 * Destructively parse an HTTP request header. This function parses some request text, and 
 * calls a function supplied by the user. You can access the p_request struct to process the 
 * the http request. The http request memory is free()'d at the end of the call, so be careful. 
 * 
 * @param p_request_text     pointer to http request text
 * @param pfn_request_parser user function
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int http_parse_request (
    const char *p_request_text,
    http_message *p_http_request
);

// HTTP Responses
/** !
 * Destructively serialize an http request
 * 
 * @param response_text    return
 * @param response_status  enumeration of response codes < OK | Moved Permanently | Found | etc >
 * @param response_content the body of the HTTP response
 * @param format           a percent delimited string of format specifiers
 * @param ...              The values specified in the format string
 * 
 * @return 1 on success, 0 on error
*/
int http_serialize_response (
    const char *p_response_text,
    http_message *p_http_response
);

/** !
 * Destructively parse an HTTP response. This function parses some request text, and 
 * calls a function supplied by the user. You can access the p_request struct to process the 
 * the http request. The http request memory is free()'d at the end of the call, so be careful. 
 * 
 * @param p_request_text     pointer to http request text
 * @param pfn_request_parser user function
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int http_parse_response (
    const char  *p_response_text,
    int        (*pfn_response_parser)(http_message *p_http_response)
);

// Request -> Response
DLLEXPORT int http_request_response (
    const char *p_response_text,
    http_request_response_fn *pfn_http_request_response_function
);
