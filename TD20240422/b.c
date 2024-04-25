#include <stdio.h>
#include <time.h>
#include "b.h"

static void help(void)
{
    puts("help from B");
    return;
}


static void print_current_date(void)
{
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime); // UTC
    printf("Current date: %d-%02d-%02d\n", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);
    return;
}

void my_date_help(void)
{
    print_current_date();
    help();
    return;
}
