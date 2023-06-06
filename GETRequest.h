#ifndef GETRequest_h
#define GETRequest_h

struct GETRequest
{
    char *URI;
    float HTTPVesion;
};

struct GETRequest get_request_constructor(char *request_string);

#endif