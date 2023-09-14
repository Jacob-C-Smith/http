 Field Name                    | Format specifier | Implemented? |
-------------------------------|------------------|--------------|
Accept-Datetime                | %adt             |              |
Access-Control-Request-Method  | %acrm            |              |
Access-Control-Request-Headers | %acrh            |              |
Cookie                         | %coo             |              |
Origin                         | %o               |              |
A-IM                           | %aim             |              |
Accept                         | %ac              |              |
Accept-Charset                 | %acc             |              |
Accept-Encoding                | %ace             |              |
Accept-Language                | %acl             |              |
Authorization                  | %aut             |              |
Cache-Control                  | %cc              |              |
Connection                     | %con             |              |
Content-Encoding               | %ce              |              |
Content-Length                 | %cl              |              |
Content-Type                   | %ct              | YES          |
Date                           | %d               | YES          |
Expect                         | %e               | YES          |
Forwarded                      | %fo              | YES          |
From                           | %fr              | YES          |
Host                           | %h               |              |
If-Match                       | %im              |              |
If-Modified-Since              | %ims             |              |
If-None-Match                  | %inm             |              |
If-Range                       | %ir              |              |
If-Unmodified-Since            | %ius             | YES          |
Max-Forwards                   | %m               | YES          |
Pragma                         | %pra             |              |
Prefer                         | %pre             |              |
Proxy-Authorization            | %pau             |              |
Range                          | %ra              |              |
Referer                        | %re              |              |
TE                             | %te              |              |
Trailer                        | %tra             |              |
Transfer-Encoding              | %tre             |              |
User-Agent                     | %ua              | YES          |
Upgrade                        | %up              | YES          |
Via                            | %v               | YES          |

```c
/**!
 * Generate an http request text
 * 
 * @param request_text return
 * @param request_type enumeration of request methods < GET | HEAD | POST | PATCH | etc >
 * @param path         the path of the requested resource
 * @param format       a percent delimited string of the above format specifiers
 * @param ...          The values specified in the format string
 * 
 * @return 1 on success, 0 on error        
 */
int http_request (
    char             *request_text, 
    request_type_t    request_type,
    const char       *path,
    const char       *format,
    ...
);
```

Such that the following code
```c
// Initialized data
char *http_text[8192] = { 0 };

// Create the text of an HTTP request
http_request(
    http_text,
    HTTP_REQUEST_GET,
    "/index.html",

    "%h %ua",
    
    "en.wikipedia.org",            // %h
    "Mozilla/5.0 Chrome/48.0.2564" // %ua
);

// Print the text of the HTTP request
printf( http_text );
```
Would produce the following output
```
GET /index.html HTTP/1.1
Host: en.wikipedia.org
User-Agent: Mozilla/5.0 Chrome/48.0.2564
```