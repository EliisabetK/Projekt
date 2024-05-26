#include "CLI.h"
#include "retsepti_otsing.h"
#include "failid.h"
#include "Utility.h"
#include <iostream>
#include <limits>

int CLI::retseptiIndeks = 0;
int offset = 0;

void CLI::start() {
    while (true) {
        try {
            std::cout << "Vali tegevus: \n";
            std::cout << "a) Leia retsept koostisainete pohjal\n";
            std::cout << "b) Leia kindel retsept\n";
            std::cout << "Sisesta oma valik (a, b): \n";
            char valik;
            std::cin >> valik;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tühjendab puhvri

            switch (valik) {
                case 'a': otsiRetsept(true); break;
                case 'b': otsiRetsept(false); break;
                default: throw ViganeSymbol("Vale sisend.\n");
            }
        } catch (const ViganeSymbol& e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
        std::cout << "Kas tahad uue tegevuse valida (Y/N)? \n";
        if (!prooviUuesti()) break;
    }
}

void CLI::otsiRetsept(bool koostisainetePohjal) {
    while (true) {
        std::vector<std::string> koostisained;
        std::string otsinguTerm;

        if (koostisainetePohjal) {
            std::cout << "Sisesta toiduained (inglise keeles, eraldi ridadel, lopetamiseks vajuta enterit 2 korda):" << std::endl;
            std::string koostisaine;
            while (getline(std::cin, koostisaine) && !koostisaine.empty()) {
                koostisained.push_back(koostisaine);
            }
            otsinguTerm = koostaOtsinguTerm(koostisained);
        } else {
            std::cout << "Sisesta soovitud retsept (nt 'chicken noodle soup'): \n";
            std::string retsept;
            getline(std::cin, retsept);
            otsinguTerm = koostaOtsinguTerm({retsept});
        }

        std::vector<Recipe> retseptid = leiaRetseptid(otsinguTerm, 0);
        if (retseptid.empty()) {
            std::cout << "Ei leitud retsepte. Kas soovid uuesti proovida (Y/N)." << std::endl;
            if (!prooviUuesti()) break;
            continue;
        }
        kuvaRetseptid(retseptid, 0);

        if (retseptid.empty()) {
            if (!prooviUuesti()) break;
            continue;
        }

        while (true) {
            std::cout << "Kas tahad genereerida rohkem retsepte (Y/N)? "<< std::endl;
            char valik = ' ';
            std::cin >> valik;
            std::cin.ignore(); // Tühjendab puhvri
            if (valik == 'Y' || valik == 'y') {
                retseptiIndeks+=3;
                offset+=3;
                genereeriRohkemRetsepte(otsinguTerm, retseptid, offset);
                kuvaRetseptid(retseptid, offset);
            } else {
                setRetseptiIndeks(0);
                break;
            }
        }

        std::cout << "Kas tahad veel retsepte leida (Y/N)? \n";
        if (!prooviUuesti()) break;
    }
}

void CLI::kuvaDetailid(const std::vector<Recipe>& retseptid, const std::string& detail, void (CLI::*kuvaFunktsioon)(const std::vector<Recipe>&)) {
    while (true) {
        try {
            std::string valik;
            std::cout << "Kas tahad naha " << detail << " (Y/N)? \n";
            std::cin >> valik;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tühjendab puhvri
            if (valik == "Y" || valik == "y") {
                (this->*kuvaFunktsioon)(retseptid);
                break;
            } else if (valik == "N" || valik == "n") {
                break;
            } else {
                throw ViganeSymbol("Vale sisend.\n");
            }
        } catch (const ViganeSymbol& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

std::string CLI::koostaOtsinguTerm(const std::vector<std::string>& koostisained) {
    std::string otsinguTerm;
    for (size_t i = 0; i < koostisained.size(); ++i) {
        for (char c : koostisained[i]) {
            otsinguTerm += (c == ' ' ? "%20" : std::string(1, c));
        }
        if (i != koostisained.size() - 1) {
            otsinguTerm += "%20";
        }
    }
    return otsinguTerm;
}

bool CLI::prooviUuesti() {
    while (true) {
        try {
            std::string valik;
            std::cin >> valik;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tühjendab puhvri
            if (valik == "Y" || valik == "y") {
                return true;
            } else if (valik == "N" || valik == "n") {
                return false;
            } else {
                throw ViganeSymbol("Vale sisend.\n");
            }
        } catch (const ViganeSymbol& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void CLI::kuvaRetseptid(std::vector<Recipe>& retseptid, size_t offset) {
    size_t displayed = 0;
    for (size_t i = offset; i < retseptid.size() && displayed < 3; ++i, ++displayed) {
        Recipe& retsept = retseptid[i];
        if (!retsept.näidatud) {
            std::cout << i + 1 << ". Roog: " << retsept.name << std::endl;
            retsept.näidatud = true;

            std::cout << "Koostisained:" << std::endl;
            for (const auto& koostisaine : retsept.koostisained) {
                std::string asendus = koostisaine;
                std::map<std::string, std::string> fractions = {{"½", "1/2"},
                                                 {"⅛", "1/8"},
                                                 {"¼", "1/4"},
                                                 {"¾", "3/4"},
                                                 {"⅓", "1/3"}};
                for (const auto& fraction : fractions) {
                    size_t pos = asendus.find(fraction.first);
                    while (pos != std::string::npos) {
                        asendus.replace(pos, 2, fraction.second);
                        pos = asendus.find(fraction.first, pos + 1);
                    }
                }
                std::cout << "- " << asendus << std::endl;
            }
            std::cout << std::endl;
        }
    }

    kuvaDetailid(retseptid, "toitainete infot", &CLI::kuvaToitained);
    kuvaDetailid(retseptid, "allergeene", &CLI::kuvaAllergeenid);

    while (true) {
        try {
            std::string salvestusValik;
            std::cout << "Kas tahad salvestada retsepti poenimekirja (Y/N)? \n";
            std::cin >> salvestusValik;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tühjendab puhvri
            if (salvestusValik == "Y"|| salvestusValik == "y") {
                int valik;
                std::cout << "Sisesta retsepti number, mida salvestada soovid: \n";
                std::cin >> valik;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tühjendab puhvri
                if (valik > 0 && valik <= retseptid.size()) {
                    size_t tühikPos = retseptid[valik - 1].name.find(' ');
                    std::string nimi = retseptid[valik - 1].name.substr(0, tühikPos); // leiab toidu nime esimese sõna, et see failinimeks panna
                    std::string failinimi = "poenimekiri_" + nimi + ".txt";
                    Failid::salvestaPoenimekiri(failinimi, retseptid[valik - 1].koostisained);
                    std::cout << "Retsept salvestatud faili: " << failinimi << std::endl;
                    break;
                } else {
                    throw ViganeSymbol("Vale sisend.");
                }
            } else if (salvestusValik == "N" || salvestusValik == "n") {
                break;
            } else {
                throw ViganeSymbol("Vale sisend.");
            }
        } catch (const ViganeSymbol& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void CLI::kuvaToitained(const std::vector<Recipe>& toitained) {
    for (const auto& retsept : toitained) {
        std::cout << "Roog: " << retsept.name << std::endl;
        std::cout << "Toitained:" << std::endl;
        for (const auto& toitaine : retsept.nutrients) {
            std::cout << "- " << toitaine.first << ": " << toitaine.second << std::endl;
        }
        std::cout << std::endl;
    }
}

void CLI::kuvaAllergeenid(const std::vector<Recipe>& retseptid) {
    for (const auto& retsept : retseptid) {
        std::cout << "Roog: " << retsept.name << std::endl;
        std::cout << "Allergeenid:" << std::endl;
        for (const auto& allergeen : retsept.allergiad) {
            std::cout << "- " << allergeen << std::endl;
        }
        std::cout << std::endl;
    }
}

std::vector<Recipe> CLI::genereeriRohkemRetsepte(const std::string& otsinguTerm, std::vector<Recipe>& retseptid, int indeks) {
    std::vector<Recipe> rohkemRetsepte = leiaRetseptid(otsinguTerm, indeks);
    if (rohkemRetsepte.empty()) {
        std::cout << "Rohkem retsepte ei leidu." << std::endl;
    } else {
        setRetseptiIndeks(indeks + rohkemRetsepte.size());
        for (Recipe& uusRetsept : rohkemRetsepte) {
            retseptid.push_back(uusRetsept);
        }
    }
    return retseptid;
}

