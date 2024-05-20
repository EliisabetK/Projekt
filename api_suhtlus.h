// api_suhtlus.h
#ifndef API_SUHTLUS_H
#define API_SUHTLUS_H

#include <string>

class APISuhtlus {
public:
    static APISuhtlus& getInstance();
    std::string FetchData(const std::string& otsinguTerm);

private:
    APISuhtlus(const std::string& apiKey, const std::string& appId);
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

    std::string apiKey;
    std::string appId;

    APISuhtlus(const APISuhtlus&) = delete;
    APISuhtlus& operator=(const APISuhtlus&) = delete;
};

#endif // API_SUHTLUS_H
