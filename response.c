#include <http/http.h>

int http_serialize_response (
    char                 *response_text, 
    http_response_status  response_status,
    const char           *response_content,
    const char           *format,
    ...
)
{
    // Argument check
    if ( response_text == (void *) 0 ) goto no_response_text;
    if ( format        == (void *) 0 ) goto no_format;
    
    // Uninitialized data
    va_list parameters;

    // Initialized data
    size_t written_characters = 0;

    // Print the start line
    written_characters += sprintf(&response_text[written_characters], "HTTP/1.1 %d %s\n", http_response_status_codes[response_status], http_response_status_phrases[response_status]);
    
    // Start reading variadic parameters
	va_start(parameters, format); 

    // Iterate through the format string
	while (*format)
    {
        
        // Seek a format specifier
        if ( *format == '%' )
        {
            
            // Increment the format string pointer
            format++;

            // Parse the format specifier
            switch ( *format )
            {

                /*
                 * Accept-CH
                 * Access-Control-Allow-Origin
                 * Access-Control-Allow-Credentials
                 * Access-Control-Expose-Headers
                 * Access-Control-Max-Age
                 * Access-Control-Allow-Methods
                 * Access-Control-Allow-Headers
                 * Accept-Patch
                 * Accept-Ranges
                 * Age
                 * Allow
                 * Alt-Svc
                 */
                case 'a':
                {
                    
                    // Increment the format string pointer
                    format++;

                    // Parse format specifiers starting with 'a'
                    switch ( *format )
                    {

                        // 'ac'
                        case 'c':
                        {

                            // Increment the format string pointer
                            format++;

                            // Parse format specifiers starting with 'ac'
                            switch ( *format )
                            {
                                // Accept field
                                case ' ':
                                case '\0':
                                {
                                
                                    // Initialized data
                                    const char* ABC = va_arg(parameters, const char*);

                                    // Print the Accept field
                                    written_characters += sprintf(&response_text[written_characters], "ABC: %s\n", ABC);

                                    // Break
                                    break;
                                }
                            }

                            // Break
                            break;
                        }

                        default:
                            break;
                    }
                }
            
                /*
                 * Cache-Control
                 * Connection
                 * Content-Disposition
                 * Content-Encoding
                 * Content-Language
                 * Content-Length
                 * Content-Location
                 * Content-MD5
                 * Content-Range
                 * Content-Type
                 */
                case 'c':
                {

                    // Increment the format string pointer
                    format++;

                    // Parse format specifiers starting with 'c'
                    switch ( *format )
                    {


                        // Connection
                        case ' ':
                        case '\0':
                        {

                            // Initialized data
                            const char* connection = va_arg(parameters, const char*);

                            // Print the Connection field
                            written_characters += sprintf(&response_text[written_characters], "Connection: %s\n", connection);

                            // Break
                            break;
                        }

                        // Cache-Control
                        case 'c':
                        {

                            // Initialized data
                            const char* cache_control = va_arg(parameters, const char*);

                            // Print the Cache-Control field
                            written_characters += sprintf(&response_text[written_characters], "Cache-Control: %s\n", cache_control);

                            // Break
                            break;
                        }
                        
                        // Content-Disposition
                        case 'd':
                        {

                            // Initialized data
                            const char* content_disposition = va_arg(parameters, const char*);

                            // Print the content type field
                            written_characters += sprintf(&response_text[written_characters], "Content-Disposition: %s\n", content_disposition);

                            // Break
                            break;
                        }

                        // Content-Encoding
                        case 'e':
                        {

                            // Initialized data
                            const char* content_encoding = va_arg(parameters, const char*);

                            // Print the content encoding type field
                            written_characters += sprintf(&response_text[written_characters], "Content-Encoding: %s\n", content_encoding);

                            // Break
                            break;
                        }

                        // Content-Length
                        // Content-Language
                        // Content-Location
                        case 'l':
                        {

                            // Increment the format string pointer
                            format++;

                            // Parse format specifiers starting with 'c'
                            switch ( *format )
                            {
                                
                                // Content-Length
                                case '\0':
                                case ' ':
                                {

                                    // Initialized data
                                    const char* content_length = va_arg(parameters, const char*);

                                    // Print the Connection field
                                    written_characters += sprintf(&response_text[written_characters], "Content-Length: %s\n", content_length);

                                    // Break
                                    break;
                                }

                                // Content-Language
                                case 'a':
                                {

                                }

                                // Content-Location
                                case 'o':
                                {

                                }
                            }

                            break;
                        }
                    
                        // Content-MD5
                        case 'm':
                        {

                            // Initialized data
                            const char* content_md5 = va_arg(parameters, const char*);

                            // Print the content MD5 field
                            written_characters += sprintf(&response_text[written_characters], "Content-MD5: %s\n", content_md5);

                            // Break
                            break;
                        }

                        // Content-Range
                        case 'r':
                        {

                            // Initialized data
                            const char* content_range = va_arg(parameters, const char*);

                            // Print the content range field
                            written_characters += sprintf(&response_text[written_characters], "Content-Range: %s\n", content_range);

                            // Break
                            break;
                        }  

                        // Content-Type
                        case 't':
                        {

                            // Initialized data
                            const char* content_type = va_arg(parameters, const char*);

                            // Print the content type field
                            written_characters += sprintf(&response_text[written_characters], "Content-Type: %s\n", content_type);

                            // Break
                            break;
                        }                     
                    }
                }

                /*
                 * Date
                 * Delta-Base
                 */
                case 'd':
                {

                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {
                        
                        // Date
                        case ' ':
                        case '\0':
                        {

                            // Initialized data
                            const char* date = va_arg(parameters, const char*);

                            // Print the warning field
                            written_characters += sprintf(&response_text[written_characters], "Date: %s\n", date);

                            // Break
                            break;
                        }

                        // Delta-Base
                        case 'b':
                        {

                            // Initialized data
                            const char* delta_base = va_arg(parameters, const char*);

                            // Print the warning field
                            written_characters += sprintf(&response_text[written_characters], "Delta-Base: %s\n", delta_base);

                            // Break
                            break;
                        }
                    }
                }

                /*
                 * ETag
                 * Expires
                 */
                case 'e':
                {

                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {
                        
                        // Expires
                        case ' ':
                        case '\0':
                        {

                            // Initialized data
                            const char* expires = va_arg(parameters, const char*);

                            // Print the expires field
                            written_characters += sprintf(&response_text[written_characters], "Expires: %s\n", expires);

                            // Break
                            break;
                        }

                        // ETag
                        case 't':
                        {

                            // Initialized data
                            const char* etag = va_arg(parameters, const char*);

                            // Print the etag field
                            written_characters += sprintf(&response_text[written_characters], "ETag: %s\n", etag);

                            // Break
                            break;
                        }
                    }
                }

                // IM
                case 'i':
                {

                    // Initialized data
                    const char* im = va_arg(parameters, const char*);

                    // Print the im field
                    written_characters += sprintf(&response_text[written_characters], "IM: %s\n", im);

                    // Break
                    break;
                }

                /*
                 * Last-Modified
                 * Link
                 * Location
                 */
                case 'l':
                {
                    break;
                }

                /*
                 * P3P
                 * Pragma
                 * Preference-Applied
                 * Proxy-Authenticate
                 * Public-Key-Pins
                 */
                case 'p':
                {

                }

                // Retry-After
                case 'r':
                {

                    // Initialized data
                    const char* retry_after = va_arg(parameters, const char*);

                    // Print the retry after field
                    written_characters += sprintf(&response_text[written_characters], "Retry-After: %s\n", retry_after);

                    // Break
                    break;
                }

                /*
                 * Server
                 * Set-Cookie
                 * Strict-Transport-Security
                 */
                case 's':
                {
                    break;
                }

                /*
                 * Trailer
                 * Transfer-Encoding
                 * Tk 
                 */
                case 't':
                {
                    
                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {
                        
                        // Trailer
                        case ' ':
                        case '\0':
                        {

                        }

                        // Transfer-Encoding
                        case 'e':
                        {

                        }

                        // Tk
                        case 'k':
                        {
                            
                        }
                    }
                }

                // Upgrade
                case 'u':
                {

                    // Initialized data
                    const char* upgrade = va_arg(parameters, const char*);

                    // Print the upgrade field
                    written_characters += sprintf(&response_text[written_characters], "Upgrade: %s\n", upgrade);

                    // Break
                    break;
                }

                /*
                 * Vary
                 * Via
                 */
                case 'v':
                {
                    
                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {
                        
                        // Via
                        case ' ':
                        case '\0':
                        {

                            // Initialized data
                            const char* via = va_arg(parameters, const char*);

                            // Print the via field
                            written_characters += sprintf(&response_text[written_characters], "Via: %s\n", via);

                            // Break
                            break;
                        }

                        // Vary
                        case 'a':
                        {

                            // Initialized data
                            const char* vary = va_arg(parameters, const char*);

                            // Print the vary field
                            written_characters += sprintf(&response_text[written_characters], "Vary: %s\n", vary);

                            // Break
                            break;
                        }
                    }
                }

                /*
                 * Warning
                 * WWW-Authenticate
                 */
                case 'w':
                {
                    
                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {
                        
                        // Warning
                        case ' ':
                        case '\0':
                        {

                            // Initialized data
                            const char* warning = va_arg(parameters, const char*);

                            // Print the warning field
                            written_characters += sprintf(&response_text[written_characters], "Warning: %s\n", warning);

                            // Break
                            break;
                        }

                        // WWW-Authenticate
                        case 'a':
                        {

                            // Initialized data
                            const char* www_authenticate = va_arg(parameters, const char*);

                            // Print the www authenticate field
                            written_characters += sprintf(&response_text[written_characters], "WWW-Authenticate: %s\n", www_authenticate);

                            // Break
                            break;
                        }
                    }
                }

                // X-Frame-Options 
                case 'x':
                {

                    // Initialized data
                    const char* x_frame_options = va_arg(parameters, const char*);

                    // Print the x frame options field
                    written_characters += sprintf(&response_text[written_characters], "X-Frame-Options: %s\n", x_frame_options);

                    // Break
                    break;
                }
            }
        }
        
        // Default
        else

            // Increment the format string pointer
            format++;
    }

    // Stop looking for variadic parameters
	va_end(parameters);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_response_text:
                #ifndef NDEBUG
                    printf("[HTTP] Null pointer provided for parameter \"response_text\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_path:
                #ifndef NDEBUG
                    printf("[HTTP] Null pointer provided for parameter \"path\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_format:
                #ifndef NDEBUG
                    printf("[HTTP] Null pointer provided for parameter \"format\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int http_parse_response ( 
    char *response_text,
    http_response_status *p_response_status,
    dict **pp_response_fields
)
{
    return 0;
}