#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include <map>
#include "api_suhtlus.h"

class CLI {
public:
    static void start();
    static void kuvaRetseptid(const std::string& otsinguTerm, const std::map<std::string, std::vector<std::string>>& recipes);
};

#endif // CLI_H
