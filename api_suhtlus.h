#ifndef API_SUHTLUS_H
#define API_SUHTLUS_H

#include <string>

class APISuhtlus {
public:
    static std::string FetchData(const std::string& searchTerms);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp);
};

#endif // API_SUHTLUS_H
