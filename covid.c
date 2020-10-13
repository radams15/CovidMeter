//
// Created by rhys on 13/10/2020.
//

#define _XOPEN_SOURCE 700
#include <time.h>


#include "cJSON.c"

#include "network.c"

#define URL_BASE "https://api.coronavirus.data.gov.uk/v1/data"

struct covid_data{
    struct tm date;
    int today_cases;
    int today_deaths;
};

const char* get_raw_data(const char* location){
    const char* url_base = URL_BASE"?filters=areaName=%s&structure={\"date\":\"date\",\"areaName\":\"areaName\",\"areaCode\":\"areaCode\",\"newCasesByPublishDate\":\"newCasesByPublishDate\",\"newDeathsByDeathDate\":\"newDeathsByDeathDate\"}";

    char* url_to_get = calloc(strlen(url_base)+strlen(location), sizeof(char));

    sprintf(url_to_get, url_base, location);

    return get_url(url_to_get);
}

struct covid_data get_data(const char* location, struct tm* date){
    struct covid_data out;
    if(date == NULL){
        time_t tme = time(NULL);
        date = localtime(&tme);
    }

    const char* raw = get_raw_data(location);

    printf("%s\n", raw);

    cJSON* whole = cJSON_Parse(raw);

    cJSON* data = cJSON_GetObjectItemCaseSensitive(whole, "data");

    cJSON* entry;

    int entry_cases;
    int entry_deaths;
    char* entry_date_str;
    struct tm* entry_date = malloc(sizeof(struct tm));

    cJSON_ArrayForEach(entry, data){
        entry_date_str = cJSON_GetObjectItemCaseSensitive(entry, "date")->valuestring;

        entry_cases = cJSON_GetObjectItemCaseSensitive(entry, "newCasesByPublishDate")->valueint;
        entry_deaths = cJSON_GetObjectItemCaseSensitive(entry, "newDeathsByDeathDate")->valueint;

        strptime(entry_date_str, "%Y-%m-%d", entry_date);

        if(date->tm_mday == entry_date->tm_mday && date->tm_mon == entry_date->tm_mon){
            out.date = *entry_date;
            out.today_cases = entry_cases;
            out.today_deaths = entry_deaths;

            goto end;
        }
    }

    end:


    cJSON_Delete(data);

    //cJSON_Delete(whole); // causes double free error

    free((void*)raw);

    return out;
}