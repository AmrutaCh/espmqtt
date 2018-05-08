#include "platform.h"

char chipID[CHIP_ID_LENGTH]={0};

void platform_get_chipid(char *ptr)
{
    uint8_t mac[6];
    if(chipID[0] == 0)
    {
        esp_read_mac(mac, ESP_MAC_WIFI_STA);
        sprintf(chipID, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2],mac[3], mac[4], mac[5]);
        chipID[CHIP_ID_LENGTH-1] = 0;
        strupr(chipID);
    }
    strcpy(ptr,chipID);
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
    return milliseconds;
}

void ms_to_timeval(int timeout_ms, struct timeval *tv)
{
    tv->tv_sec = timeout_ms / 1000;
    tv->tv_usec = (timeout_ms - (tv->tv_sec * 1000)) * 1000;
}
