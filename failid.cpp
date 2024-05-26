#include "failid.h"
#include <fstream>
#include <iostream>

void Failid::salvestaPoenimekiri(const std::string& failinimi, const std::vector<std::string>& koostisained) {
    std::ofstream fail(failinimi);
    if (!fail.is_open()) {
        std::cerr << "Viga: Ei saanud faili avada kirjutamiseks." << std::endl;
        return;
    }
    for (const auto& koostisaine : koostisained) {
        fail << koostisaine << std::endl;
    }
    fail.close();
}
