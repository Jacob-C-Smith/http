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
    
    // Initialized data
    char _http_request[1<<16] = { 0 };

    // Generate an HTTP request
    http_serialize_request(
        &_http_request,
        HTTP_REQUEST_GET,
        "/index.html",
        "%d %e %fo %fr %h %m %o %ua %up %v",         // Format string
                                                     // TODO: Accept                         
                                                     // TODO: Accept-Encoding                
                                                     // TODO: Access-Control-Request-Headers 
                                                     // TODO: Accept-Language                
                                                     // TODO: Access-Control-Request-Method  
                                                     // TODO: Accept-Charset                 
                                                     // TODO: Accept-Datetime                
                                                     // TODO: A-IM                           
                                                     // TODO: Authorization                  
                                                     // TODO: Cookie                         
                                                     // TODO: Cache-Control                  
                                                     // TODO: Connection                     
                                                     // TODO: Content-Encoding               
                                                     // TODO: Content-Length                 
                                                     // TODO: Content-Type                   
        "Wed, 21 Oct 2015 07:28:00 GMT",             // Date
        "100-continue",                              // Expect
        "for=192.0.2.60;proto=http;by=203.0.113.43", // Forwarded
        "webmaster@example.org",                     // From
        "en.wikipedia.org",                          // Host
                                                     // TODO: If-Match           
                                                     // TODO: If-Modified-Since  
                                                     // TODO: If-None-Match      
                                                     // TODO: If-Range           
                                                     // TODO: If-Unmodified-Since
        "10",                                        // Max-Forwards
        "https://developer.mozilla.org",             // Origin
                                                     // TODO: Pragma
                                                     // TODO: Prefer
                                                     // TODO: Proxy-Authorization
                                                     // TODO: Range
                                                     // TODO: Referer
                                                     // TODO: TE
                                                     // TODO: Trailer
                                                     // TODO: Transfer-Encoding
        "Mozilla/5.0 Chrome/48.0.2564",              // User-Agent
        "websocket",                                 // Upgrade
        "1.0 fred, 1.1 p.example.net"                // Via
    );

    // Write the generated HTTP request to standard out
    printf(
    "http_request returned: \n" \
    "================================================================================\n" \
    "%s" \
    "================================================================================\n",
    _http_request);
    
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
