#include <http/http.h>

int http_serialize_request (
    char              *request_text, 
    http_request_type  request_type,
    const char        *path,
    const char        *format,
    ...
)
{

    // Argument check
    if ( request_text == (void *) 0 ) goto no_request_text;
    if ( path         == (void *) 0 ) goto no_path;
    if ( format       == (void *) 0 ) goto no_format;
    
    // Uninitialized data
    va_list parameters;

    // Initialized data
    size_t written_characters = 0;

    // Print the start line
    written_characters += sprintf(&request_text[written_characters], "%s %s HTTP/1.1\n", http_request_types[request_type], path);
    
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
                 * Accept
                 * Accept-Encoding
                 * Access-Control-Request-Headers
                 * Accept-Language
                 * Access-Control-Request-Method
                 * Accept-Charset
                 * Accept-Datetime
                 * A-IM
                 * Authorization
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
                                    const char* accept = va_arg(parameters, const char*);

                                    // Print the Accept field
                                    written_characters += sprintf(&request_text[written_characters], "Accept: %s\n", accept);

                                    // Break
                                    break;
                                }
                            }

                            // Break
                            break;
                        }

                        // Accept-Datetime field
                        case 'd':
                        {

                            // Initialized data
                            const char* accept_date_time = va_arg(parameters, const char*);

                            // Print the Accept-Datetime field
                            written_characters += sprintf(&request_text[written_characters], "Accept-Datetime: %s\n", accept_date_time);

                            // Break
                            break;
                        }

                        // A-IM field
                        case 'i':
                        {

                            // Initialized data
                            const char* a_im = va_arg(parameters, const char*);

                            // Print the A-IM field
                            written_characters += sprintf(&request_text[written_characters], "A-IM: %s\n", a_im);

                            // Break
                            break;
                        }

                        // Authorization field
                        case 'u':
                        {

                            // Initialized data
                            const char* authorization = va_arg(parameters, const char*);

                            // Print the Authorization field
                            written_characters += sprintf(&request_text[written_characters], "Authorization: %s\n", authorization);

                            // Break
                            break;
                        }
                        
                        
                        default: break;

                    }
                }
            
                /*
                 * Cookie
                 * Cache-Control
                 * Connection
                 * Content-Encoding
                 * Content-Length
                 * Content-Type
                 */
                case 'c':
                {
                    break;
                }

                // Date
                case 'd':
                {
                    // Initialized data
                    const char* date = va_arg(parameters, const char*);

                    // Print the Host field
                    written_characters += sprintf(&request_text[written_characters], "Date: %s\n", date);

                    // Break
                    break;
                }

                // Expect
                case 'e':
                {
                    // Initialized data
                    const char* expect = va_arg(parameters, const char*);

                    // Print the Host field
                    written_characters += sprintf(&request_text[written_characters], "Expect: %s\n", expect);

                    // Break
                    break;
                }

                /*
                 * Forwarded
                 * From
                 */
                case 'f':
                {
                    
                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {

                        // Forwarded
                        case 'o':
                        {
                            // Initialized data
                            const char* forwarded = va_arg(parameters, const char*);

                            // Print the Forwarded field
                            written_characters += sprintf(&request_text[written_characters], "Forwarded: %s\n", forwarded);

                            // Break
                            break;
                        }

                        // From
                        case 'r':
                        {
                            // Initialized data
                            const char* from = va_arg(parameters, const char*);

                            // Print the From field
                            written_characters += sprintf(&request_text[written_characters], "From: %s\n", from);

                            // Break
                            break;
                        }
                    }

                    // Break
                    break;
                }

                // Host
                case 'h':
                {
                    // Initialized data
                    const char* host = va_arg(parameters, const char*);

                    // Print the Host field
                    written_characters += sprintf(&request_text[written_characters], "Host: %s\n", host);

                    // Break
                    break;
                }

                /*
                 * If-Match
                 * If-Modified-Since
                 * If-None-Match
                 * If-Range
                 * If-Unmodified-Since
                 */
                case 'i':
                {
                    break;
                }

                // Max-Forwards
                case 'm':
                {
                    // Initialized data
                    const char* max_forwards = va_arg(parameters, const char*);

                    // Print the Host field
                    written_characters += sprintf(&request_text[written_characters], "Max-Forwards: %s\n", max_forwards);

                    // Break
                    break;
                }
                
                // Origin
                case 'o':
                {
                    // Initialized data
                    const char* origin = va_arg(parameters, const char*);

                    // Print the Host field
                    written_characters += sprintf(&request_text[written_characters], "Origin: %s\n", origin);

                    // Break
                    break;
                }

                /*
                 * Pragma
                 * Prefer
                 * Proxy-Authorization
                 */
                case 'p':
                {
                    break;
                }

                /*
                 * Range
                 * Referer
                 */
                case 'r':
                {
                    break;
                }

                /*
                 * TE
                 * Trailer
                 * Transfer-Encoding
                 */
                case 't':
                {

                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {
                        
                        // TE
                        case 'e':
                        {
                            // Initialized data
                            const char* te = va_arg(parameters, const char*);

                            // Print the TE field
                            written_characters += sprintf(&request_text[written_characters], "TE: %s\n", te);

                            // Break
                            break;
                        }

                        /*
                         * Trailer
                         * Transfer-Encoding
                         */
                        case 'r':
                        {
                            
                            // Increment the format specifier
                            format++;

                            // Parse the format specifier
                            switch ( *format )
                            {

                                // Trailer
                                case 'a':
                                {

                                    // Initialized data
                                    const char* trailer = va_arg(parameters, const char*);

                                    // Print the Trailer field
                                    written_characters += sprintf(&request_text[written_characters], "Trailer: %s\n", trailer);

                                    // Break         
                                    break;
                                }

                                // Transfer-Encoding
                                case 'e':
                                {

                                    // Initialized data
                                    const char* transfer_encoding = va_arg(parameters, const char*);

                                    // Print the Transfer-Encoding field
                                    written_characters += sprintf(&request_text[written_characters], "Transfer-Encoding: %s\n", transfer_encoding);

                                    // Break         
                                    break;
                                }

                                default:
                                    break;
                            }
                        }

                        default:

                            // Break
                            break;
                    }

                    // Break
                    break;
                }

                /*
                 * User-Agent
                 * Upgrade
                 */
                case 'u':
                {

                    // Increment the format string pointer
                    format++;

                    // Parse the format specifier
                    switch ( *format )
                    {

                        // User-Agent
                        case 'a':
                        {
                            // Initialized data
                            const char* user_agent = va_arg(parameters, const char*);

                            // Print the User-Agent field
                            written_characters += sprintf(&request_text[written_characters], "User-Agent: %s\n", user_agent);

                            // Break
                            break;
                        }

                        // Upgrade
                        case 'p':
                        {
                            // Initialized data
                            const char* upgrade = va_arg(parameters, const char*);

                            // Print the Upgrade field
                            written_characters += sprintf(&request_text[written_characters], "Upgrade: %s\n", upgrade);

                            // Break
                            break;
                        }
                    }

                    // Break
                    break;
                }

                // Via
                case 'v':
                {
                    // Initialized data
                    const char* via = va_arg(parameters, const char*);

                    // Print the Host field
                    written_characters += sprintf(&request_text[written_characters], "Via: %s\n", via);

                    // Break
                    break;
                }
            }
        }
	
        format++;
    }

	va_end(parameters);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_request_text:
                #ifndef NDEBUG
                    printf("[HTTP] Null pointer provided for parameter \"request_text\" in call to function \"%s\"\n", __FUNCTION__);
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

int http_serialize_response (
    char                 *response_text, 
    http_response_status  response_status,
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
                 * ...
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
                 * ...
                 */
                case 'c':
                {
                    break;
                }
            }
        }
	
        format++;
    }

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