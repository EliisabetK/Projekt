#ifndef API_SUHTLUS_H
#define API_SUHTLUS_H

#include <string>

class APISuhtlus {
public:
    std::string FetchData(const std::string& url);
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

#endif
