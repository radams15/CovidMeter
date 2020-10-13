#include <stdio.h>
#include "covid.c"

#define AREA "Liverpool"

#define DAY (60*60*24)

int main() {
    time_t secs = time(NULL)-2*DAY;

    struct covid_data data = get_data(AREA, localtime(&secs));

    printf("%s\tCases: %d, Deaths: %d", asctime(&data.date), data.today_cases, data.today_deaths);

    return 0;
}
