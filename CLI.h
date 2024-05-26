#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include "retsepti_otsing.h"

class CLI {
public:
    std::string otsinguTerm;

    void start();
    void otsiRetsept(bool koostisainetePohjal);
    void kuvaDetailid(const std::vector<Recipe>& retseptid, const std::string& detail, void (CLI::*kuvaFunktsioon)(const std::vector<Recipe>&));
    static std::string koostaOtsinguTerm(const std::vector<std::string>& koostisained);
    static bool prooviUuesti();
    void kuvaRetseptid(std::vector<Recipe>& retseptid, size_t offset);
    void kuvaToitained(const std::vector<Recipe>& toitained);
    void kuvaAllergeenid(const std::vector<Recipe>& retseptid);
    static std::vector<Recipe> genereeriRohkemRetsepte(const std::string& otsinguTerm, std::vector<Recipe>& retseptid, int indeks);
    static void setRetseptiIndeks(int indeks) { retseptiIndeks = indeks; }

private:
    static int retseptiIndeks;
};

#endif // CLI_H
