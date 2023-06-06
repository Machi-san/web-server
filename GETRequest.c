#include "GETRequest.h"

#include <string.h>
#include <stdlib.h>

struct GETRequest get_request_constructor(char *request_string)
{
    struct GETRequest request;
    
    char *request_line = strtok(request_string, "\n");
    char *method = strtok(request_line, " ");

    char *URI = strtok(NULL, " ");
    if(strcmp(URI, "/favicon.ico") == 0)
        strcpy(URI, "/"); 
    request.URI = URI;

    char *HTTPVersion = strtok(NULL, " ");
    HTTPVersion = strtok(HTTPVersion, "/");
    HTTPVersion = strtok(NULL, "/");
    request.HTTPVesion = (float)atof(HTTPVersion);

    return request;
}