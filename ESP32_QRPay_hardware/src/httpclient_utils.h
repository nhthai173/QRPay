#ifndef HTTPCLIENT_UTILS_H
#define HTTPCLIENT_UTILS_H

#include <Arduino.h>
#include <HTTPClient.h>

// #define HTTPCLIENT_DEBUG // Uncomment this line to enable debug print

#if defined(HTTPCLIENT_DEBUG)
#define HTTPCLIENT_DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define HTTPCLIENT_DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#define HTTPCLIENT_DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)
#else
#define HTTPCLIENT_DEBUG_PRINT(...) {}
#define HTTPCLIENT_DEBUG_PRINTLN(...) {}
#define HTTPCLIENT_DEBUG_PRINTF(...) {}
#endif


String httpGET(HTTPClient *http, const char *url)
{
    http->begin(url);
    int httpCode = http->GET();
    if (httpCode > 0)
    {
        String payload = http->getString();
        HTTPCLIENT_DEBUG_PRINTF("GET [%d]", httpCode);
        HTTPCLIENT_DEBUG_PRINTLN(payload);
        http->end();
        return payload;
    }
    else
    {
        Serial.println("Error on HTTP request");
    }
    http->end();
    return "";
}


#endif