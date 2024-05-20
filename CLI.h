#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include <map>
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

    void start();

    void otsiRetsept(bool koostisainetePohjal);

    static bool prooviUuesti();

    static std::string koostaOtsinguTerm(const std::vector<std::string>& koostisained);

    void kuvaDetailid(const std::vector<Recipe>& retseptid, const std::string& detail, void (CLI::*kuvaFunktsioon)(const std::vector<Recipe>&));

    void kuvaRetseptid(std::vector<Recipe>& retseptid);

    void kuvaToitained(const std::vector<Recipe>& toitained);

    void kuvaAllergeenid(const std::vector<Recipe>& retseptid);

    static std::vector<Recipe> genereeriRohkemRetsepte(const std::string& otsinguTerm, std::vector<Recipe>& retseptid, int indeks);
};

#endif // CLI_H
