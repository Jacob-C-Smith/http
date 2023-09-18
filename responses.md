 Field Name                      | Format specifier | Implemented? |
---------------------------------|------------------|--------------|
Accept-CH                        | %TODO            | NO           |
Access-Control-Allow-Origin      | %TODO            | NO           |
Access-Control-Allow-Credentials | %TODO            | NO           |
Access-Control-Expose-Headers    | %TODO            | NO           |
Access-Control-Max-Age           | %TODO            | NO           |
Access-Control-Allow-Methods     | %TODO            | NO           |
Access-Control-Allow-Headers     | %TODO            | NO           |
Accept-Patch                     | %TODO            | NO           |
Accept-Ranges                    | %TODO            | NO           |
Age                              | %TODO            | NO           |
Allow                            | %TODO            | NO           |
Alt-Svc                          | %TODO            | NO           |
Cache-Control                    | %TODO            | NO           |
Connection                       | %TODO            | NO           |
Content-Disposition              | %TODO            | NO           |
Content-Encoding                 | %TODO            | NO           |
Content-Language                 | %TODO            | NO           |
Content-Length                   | %TODO            | NO           |
Content-Location                 | %TODO            | NO           |
Content-MD5                      | %TODO            | NO           |
Content-Range                    | %TODO            | NO           |
Content-Type                     | %TODO            | NO           |
Date                             | %TODO            | NO           |
Delta-Base                       | %TODO            | NO           |
ETag                             | %TODO            | NO           |
Expires                          | %TODO            | NO           |
IM                               | %TODO            | NO           |
Last-Modified	                 | %TODO            | NO           |
Link                             | %TODO            | NO           |
Location	                     | %TODO            | NO           |
P3P	                             | %TODO            | NO           |
Pragma	                         | %TODO            | NO           |
Preference-Applied	             | %TODO            | NO           |
Proxy-Authenticate	             | %TODO            | NO           |
Public-Key-Pins                  | %TODO            | NO           |
Retry-After                      | %TODO            | NO           |
Server                           | %TODO            | NO           |
Set-Cookie                       | %TODO            | NO           |
Strict-Transport-Security        | %TODO            | NO           | 
Trailer	                         | %TODO            | NO           | 
Transfer-Encoding                | %TODO            | NO           | 
Tk	                             | %TODO            | NO           | 
Upgrade	                         | %TODO            | NO           | 
Vary	                         | %TODO            | NO           | 
Via	                             | %TODO            | NO           | 
Warning	                         | %TODO            | NO           | 
WWW-Authenticate	             | %TODO            | NO           | 
X-Frame-Options                  | %TODO            | NO           | 

```c

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
```

Such that the following code
```c
// TODO
```
Would produce the following output
```
// TODO
```