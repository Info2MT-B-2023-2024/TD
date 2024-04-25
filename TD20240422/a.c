#include <stdio.h>
#include <time.h>
#include "a.h"

static void help(void)
{
    puts("help from A");
    return;
}

static void print_current_time(void)
{
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);
    printf("UTC time: %02d:%02d:%02d\n", localTime->tm_hour, localTime->tm_min + 1, localTime->tm_sec);
    return;
}

void my_time_help(void)
{
    print_current_time();
    help();
    return;
}
