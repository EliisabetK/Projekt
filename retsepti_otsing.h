#ifndef RETSEPTI_OTSING_H
#define RETSEPTI_OTSING_H

#include <string>
#include <map>
#include <vector>
class Recipe {
public:
    std::string name;
    std::vector<std::string> ingredients;
    std::map<std::string, double> nutrients;
    std::vector<std::string> allergies;  // Lisatud allergiate jaoks

    Recipe(const std::string& name, const std::vector<std::string>& ingredients, const std::map<std::string, double>& nutrients, const std::vector<std::string>& allergies)
            : name(name), ingredients(ingredients), nutrients(nutrients), allergies(allergies) {}  // Lisatud allergiad
};

std::vector<Recipe> leiaRetseptid(const std::string& otsinguTerm);
#endif // RETSEPTI_OTSING_H