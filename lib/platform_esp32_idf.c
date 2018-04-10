#include "platform.h"

#ifdef ESP_PLATFORM
#include "esp_system.h"
#include <sys/time.h>

char chipID[8];

char *platform_create_id_string()
{
    uint8_t mac[6], len = 0;
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    
    for(uint8_t i=2; i<6; i++)
    {
        len += sprintf(chipID+len, "%02X", mac[i]);
    }

    return chipID;
}

int platform_random(int max)
{
    return esp_random()%max;
}

long long platform_tick_get_ms()
{
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}
#endif
