#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <http/http.h>

// Helper functions
/**!
 * Return the size of a file IF buffer == 0 ELSE read a file into buffer
 * 
 * @param path path to the file
 * @param buffer buffer
 * @param binary_mode "wb" IF true ELSE "w"
 * 
 * @return 1 on success, 0 on error
 */
size_t load_file ( const char *path, void *buffer, bool binary_mode );

// Entry point
int main ( int argc, const char* argv[] )
{

    http_request _http_request = {
        .path = "/index.html",
        .request_type = HTTP_REQUEST_GET,
        .p_header_fields = 0
    };
    http_response _http_response = {
        .code = HTTP_NOT_FOUND,
        .p_header_fields = 0
    };
   
    char __http_req[(1<<16)] = { 0 };
    char __http_res[(1<<16)] = { 0 };
 
    {
        dict_construct(&_http_request.p_header_fields, 10);
        dict_construct(&_http_response.p_header_fields, 10);
    }

    // Add request fields
    dict_add(_http_request.p_header_fields, "Host", "en.wikipedia.org");
    dict_add(_http_request.p_header_fields, "User-Agent", "Mozilla/5.0 Chrome/48.0.2564");
    
    // Add response fields
    dict_add(_http_response.p_header_fields, "Connection", "Keep-Alive");
    dict_add(_http_response.p_header_fields, "Content-Encoding", "gzip");
    dict_add(_http_response.p_header_fields, "Content-Type", "text/html; charset=utf-8");
    
    // Encode the HTTP request
    // [ IN ]  http_request struct
    // [ OUT ] HTTP request text
    // int http_encode_request ( _http_request, __http_req ) 
    {

        size_t prop_cnt = 0;

        char *keys[32] = { 0 };
        char *values[32] = { 0 };
        char *http_req = __http_req;

        // http_req
        http_req += sprintf(http_req,"%s %s HTTP/1.1\n\r",http_request_types[_http_request.request_type], _http_request.path);

        prop_cnt = dict_keys(_http_request.p_header_fields, 0);

        // Dump keys and values
        dict_keys(_http_request.p_header_fields,keys);
        dict_values(_http_request.p_header_fields,values);
        
        // Iterate over each header field
        for ( size_t i = 0; i < prop_cnt; i++ )
            http_req += sprintf(http_req,"%s: %s\n\r",keys[i], values[i]);
    }
    
    // Encode the HTTP response
    // [ IN ] http_response struct
    // [ OUT ] HTTP response text
    // int http_encode_request ( _http_response, __http_res ) 
    {
        size_t prop_cnt = 0;

        char *keys[32] = { 0 };
        char *values[32] = { 0 };

        char *http_res = __http_res;

        // http_res
        http_res += sprintf(http_res,"%d %s\n\r", http_response_status_codes[_http_response.code], http_response_status_phrases[_http_response.code]);

        prop_cnt = dict_keys(_http_response.p_header_fields, 0);

        // Dump keys and values
        dict_keys(_http_response.p_header_fields,keys);
        dict_values(_http_response.p_header_fields,values);
        
        // Iterate over each header field
        for ( size_t i = 0; i < prop_cnt; i++ )
            http_res += sprintf(http_res,"%s: %s\n\r",keys[i], values[i]);
    }

    // Print the HTTP request
    printf("============\nHTTP REQUEST\n============\n%s\n", __http_req);

    // Print the HTTP response
    printf("=============\nHTTP RESPONSE\n=============\n%s\n", __http_res);

    // Success
    return EXIT_SUCCESS;
}

size_t load_file ( const char *path, void *buffer, bool binary_mode )
{

    // Argument checking 
    #ifndef NDEBUG
        if ( path == 0 ) goto no_path;
    #endif

    // Initialized data
    size_t  ret = 0;
    FILE   *f   = fopen(path, (binary_mode) ? "rb" : "r");
    
    // Check if file is valid
    if ( f == NULL ) goto invalid_file;

    // Find file size and prep for read
    fseek(f, 0, SEEK_END);
    ret = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Read to data
    if ( buffer ) 
        ret = fread(buffer, 1, ret, f);

    // The file is no longer needed
    fclose(f);
    
    // Success
    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_path:
                #ifndef NDEBUG
                    printf("[HTTP] Null path provided to function \"%s\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // File errors
        {
            invalid_file:
                #ifndef NDEBUG
                    printf("[Standard library] Failed to load file \"%s\". %s\n",path, strerror(errno));
                #endif

                // Error
                return 0;
        }
    }
}
