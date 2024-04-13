//TODO: data fetchimine
// api_suhtlus.cpp
#include "api_suhtlus.h"
#include <curl/curl.h>
#include <iostream>

size_t APISuhtlus::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string APISuhtlus::FetchData(const std::string& searchTerm) {
    std::string url = "https://api.edamam.com/search?q=" + searchTerm + "&app_id=9503ebdc&app_key=1cbfe671329790b26036d65a8719b890";

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Disable SSL peer certificate verification
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}


