#ifndef RETSEPTI_OTSING_H
#define RETSEPTI_OTSING_H

#include <string>
#include <map>
#include <vector>
class Recipe {
public:
    std::string name;
    std::vector<std::string> koostisained;
    std::map<std::string, double> nutrients;
    std::vector<std::string> allergiad;  // Lisatud allergiate jaoksõ
    bool näidatud;

    Recipe(const std::string& name, const std::vector<std::string>& koostisained, const std::map<std::string, double>& nutrients, const std::vector<std::string>& allergiad, bool näidatud)
            : name(name), koostisained(koostisained), nutrients(nutrients), allergiad(allergiad), näidatud(näidatud) {}  // Lisatud allergiad
};

std::vector<Recipe> leiaRetseptid(const std::string& otsinguTerm, int indeks);
#endif // RETSEPTI_OTSING_H