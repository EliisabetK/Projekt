#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include <map>
#include "api_suhtlus.h"
#include "retsepti_otsing.h"

class CLI {
public:
    void start();

    void otsiKoostisainetePõhjal();

    void teeToiduKava();

    static void otsiNimega();

    static bool prooviUuesti();

    static std::string koostaOtsinguTerm(const std::vector<std::string> &koostisained);

    static void kuvaRetseptid(const std::vector<Recipe> &recipes);

    static void kuvaToitained(const std::vector<Recipe> &toitained);

    static void kuvaAllergeenid(const std::vector<Recipe>& retseptid);

};
#endif // CLI_H
