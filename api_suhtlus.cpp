#include "api_suhtlus.h"
#include <curl/curl.h>
#include <iostream>
using namespace std;

APISuhtlus::APISuhtlus(const std::string& apiKey, const std::string& appId)
        : apiKey(apiKey), appId(appId) {}

APISuhtlus& APISuhtlus::getInstance() { // App key ja app id otsingute jaoks
    static APISuhtlus instance("1cbfe671329790b26036d65a8719b890", "9503ebdc");
    return instance;
}


// Funktsioon, mida kasutatakse cURL-i poolt andmete kirjutamiseks
size_t APISuhtlus::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb; // Tagastab töödeldud andmete suuruse
}

// Funktsioon, mis teeb API päringu ja tagastab saadud andmed
std::string APISuhtlus::FetchData(const std::string& otsinguTerm) {
    std::string url = "https://api.edamam.com/search?q=" + otsinguTerm + "&app_id=" + appId + "&app_key=" + apiKey;

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
