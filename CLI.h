//
// Created by lhoogand on 24.04.2024.
//

#ifndef PROJEKT_CLI_H
#define PROJEKT_CLI_H
#include <string>
#include <vector>
#include <map>

class CLI {
public:
    void start();
private:
    std::string FetchData(const std::string& searchTerms);
    void displayRecipes(const std::string& otsinguTerm, const std::map<std::string, std::vector<std::string>>& recipes);
};

#endif //PROJEKT_CLI_H
