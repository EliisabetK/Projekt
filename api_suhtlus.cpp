#include "api_suhtlus.h"
#include <curl/curl.h>
#include <iostream>
using namespace std;

// Funktsioon, mida kasutatakse cURL-i poolt andmete kirjutamiseks
size_t APISuhtlus::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb; // Tagastab töödeldud andmete suuruse
}

// Funktsioon, mis teeb API päringu ja tagastab saadud andmed
std::string APISuhtlus::FetchData(const std::string& otsinguTerm) {
    // Koostab URLi, lisades otsingutermini ja API võtme
    std::string url = "https://api.edamam.com/search?q=" + otsinguTerm + "&app_id=9503ebdc&app_key=1cbfe671329790b26036d65a8719b890";
    std::cout<< url;

    CURL* curl;
    CURLcode res; // Muutuja kuhu salvestatakse cURLi tulemus
    std::string readBuffer; // Puhver kuhu salvestatakse saadud andmed

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Määrab URL-i
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        res = curl_easy_perform(curl); // Teostab HTTP päringu

        // Kontrollib kas päring õnnestus
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return readBuffer; // Tagastab saadud andmed
}
