 Field Name                      | Format specifier | Implemented? |
---------------------------------|------------------|--------------|
Accept-CH                        | %ac              | NO           |
Access-Control-Allow-Credentials | %acac            | NO           |
Access-Control-Allow-Headers     | %acah            | NO           |
Access-Control-Allow-Methods     | %acam            | NO           |
Access-Control-Allow-Origin      | %acao            | NO           |
Access-Control-Expose-Headers    | %aceh            | NO           |
Access-Control-Max-Age           | %acma            | NO           |
Age                              | %ag              | NO           |
Allow                            | %al              | NO           |
Accept-Patch                     | %ap              | NO           |
Accept-Ranges                    | %ar              | NO           |
Alt-Svc                          | %as              | NO           |
Connection                       | %c               | NO           |
Cache-Control                    | %cc              | NO           |
Content-Disposition              | %cd              | NO           |
Content-Encoding                 | %ce              | NO           |
Content-Language                 | %cla             | NO           |
Content-Length                   | %cl              | NO           |
Content-Location                 | %clo             | NO           |
Content-MD5                      | %cmd             | NO           |
Content-Range                    | %cr              | NO           |
Content-Type                     | %ct              | NO           |

Date                             | %d               | NO           |
Delta-Base                       | %db              | NO           |

Expires                          | %e               | NO           |
ETag                             | %et              | NO           |

IM                               | %i               | NO           |

Last-Modified	                 | %l               | NO           |
Link                             | %li              | NO           |
Location	                     | %lo              | NO           |
Pragma	                         | %p               | NO           |
Preference-Applied	             | %pa              | NO           |
Public-Key-Pins                  | %pkp             | NO           |
P3P	                             | %pp              | NO           |
Proxy-Authenticate	             | %pra             | NO           |
Retry-After                      | %r               | NO           |
Set-Cookie                       | %sc              | NO           |
Server                           | %se              | NO           |
Strict-Transport-Security        | %st              | NO           | 
Trailer	                         | %t               | NO           | 
Transfer-Encoding                | %te              | NO           | 
Tk	                             | %tk              | NO           | 
Upgrade	                         | %u               | NO           | 
Vary	                         | %va              | NO           | 
Via	                             | %v               | NO           | 
Warning	                         | %w               | NO           | 
WWW-Authenticate	             | %wa              | NO           | 
X-Frame-Options                  | %x               | NO           | 

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