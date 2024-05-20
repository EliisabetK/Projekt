#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include "api_suhtlus.h"
#include "retsepti_otsing.h"

class CLI {
private:
    static int retseptiIndeks;
public:
    int getRetseptiIndeks() const {
        return retseptiIndeks;
    }

    static void setRetseptiIndeks(int retseptiIndeks) {
        CLI::retseptiIndeks = retseptiIndeks;
    }

public:
    void start();

    static void otsiKoostisainetePõhjal();

    static void otsiNimega();

    static bool prooviUuesti();

    static std::string koostaOtsinguTerm(const std::vector<std::string> &koostisained);

    static void kuvaRetseptid(std::vector<Recipe>& retseptid);

    static void kuvaToitained(const std::vector<Recipe> &toitained);

    static void kuvaAllergeenid(const std::vector<Recipe>& retseptid);

    static std::vector<Recipe> genereeriRohkemRetsepte(std::string otsinguTerm, std::vector<Recipe>& retseptid, int indeks);

};
#endif // CLI_H
