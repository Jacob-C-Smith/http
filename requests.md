 Field Name                    | Format specifier | Implemented? |
-------------------------------|------------------|--------------|
Accept                         | %a               | NO           |
Accept-Datetime                | %ad              | NO           |
Accept-Encoding                | %ae              | NO           |
Access-Control-Request-Headers | %ah              | NO           |
A-IM                           | %ai              | NO           |
Accept-Language                | %al              | NO           |
Access-Control-Request-Method  | %am              | NO           |
Authorization                  | %au              | NO           |
Cache-Control                  | %cc              | NO           |
Content-Encoding               | %ce              | NO           |
Content-Length                 | %cl              | NO           |
Connection                     | %cn              | NO           |
Cookie                         | %co              | NO           |
Content-Type                   | %ct              | YES          |
Date                           | %d               | YES          |
Expect                         | %e               | YES          |
Forwarded                      | %fo              | YES          |
From                           | %fr              | YES          |
Host                           | %h               | NO           |
If-Match                       | %im              | NO           |
If-Modified-Since              | %ims             | NO           |
If-None-Match                  | %inm             | NO           |
If-Range                       | %ir              | NO           |
If-Unmodified-Since            | %iu              | YES          |
Max-Forwards                   | %m               | YES          |
Origin                         | %o               | NO           |
Proxy-Authorization            | %pa              | NO           |
Prefer                         | %pr              | NO           |
Range                          | %ra              | NO           |
Referer                        | %re              | NO           |
TE                             | %t               | YES          |
Trailer                        | %tr              | YES          |
Transfer-Encoding              | %te              | YES          |
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
    "en.wikipedia.org",
    "Mozilla/5.0 Chrome/48.0.2564"
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