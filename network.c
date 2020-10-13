//
// Created by rhys on 13/10/2020.
//

#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

struct string{
    unsigned long len;
    char* data;
};

static size_t curl_char_callback(void *contents, size_t size, size_t nmemb, struct string* str){
    unsigned long str_len = size*nmemb;

    str->len += str_len;

    str->data = realloc(str->data, sizeof(char)*str->len);

    strncat(str->data, (char*) contents, str_len);

    return str_len;
}

const char* get_url(const char* url){
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    struct string str = {
            0,
            NULL
    };

    if(curl){

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_char_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "identity");

        res = curl_easy_perform(curl);

        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return NULL;
        }

        curl_easy_cleanup(curl);

    }

    return str.data;
}