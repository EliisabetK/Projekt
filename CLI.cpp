#include "CLI.h"
#include "retsepti_otsing.h"
#include <iostream>

using namespace std;

void CLI::start() {
    while (true) {
        cout << "Vali tegevus: \n";
        cout << "a) Leia retsept koostisainete pohjal\n";
        cout << "b) Leia kindel retsept\n";
        cout << "c) Tee toitumiskava\n";
        cout << "Sisesta oma valik (a, b, c): ";
        char choice;
        cin >> choice;
        cin.ignore(); // Tühjendab puhvri

        switch(choice) {
            case 'a': otsiKoostisainetePõhjal(); break;
            case 'b': otsiNimega(); break;
            case 'c': teeToiduKava(); break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }

        if (!prooviUuesti()) break;
    }
}
void CLI::otsiKoostisainetePõhjal() {
    while (true) {
        vector<string> koostisained;
        string koostisaine;
        cout << "Sisesta toiduained (inglise keeles, eraldi ridadel, lopetamiseks vajuta enterit 2 korda):" << endl;
        while (getline(cin, koostisaine) && !koostisaine.empty()) {
            koostisained.push_back(koostisaine);
        }
        kuvaRetseptid(leiaRetseptid(koostaOtsinguTerm(koostisained)));
        kuvaToitained(leiaRetseptid(koostaOtsinguTerm(koostisained)));
        kuvaAllergeenid(leiaRetseptid(koostaOtsinguTerm(koostisained)));
        if (!prooviUuesti()) break;
    }
}

void CLI::otsiNimega() {
    while (true) {
        cout << "Sisesta soovitud retsept (nt 'chicken noodle soup'): ";
        string retsept;
        getline(cin, retsept);
        kuvaRetseptid(leiaRetseptid(koostaOtsinguTerm({retsept})));
        if (!prooviUuesti()) break;
    }
}

string CLI::koostaOtsinguTerm(const vector<string>& koostisained) {
    string otsinguTerm;
    for (size_t i = 0; i < koostisained.size(); ++i) {
        for (char c : koostisained[i]) {
            otsinguTerm += (c == ' ' ? "%20" : string(1, c));
        }
        if (i != koostisained.size() - 1) {
            otsinguTerm += "%20";
        }
    }
    return otsinguTerm;
}

bool CLI::prooviUuesti() {
    char valik;
    cout << "Kas tahad uuesti proovida (Y/N)? ";
    cin >> valik;
    cin.ignore(); // Tühjendab puhvri
    return (valik == 'Y' || valik == 'y');
}


void CLI::kuvaRetseptid(const vector<Recipe>& retseptid) {
    if (retseptid.empty()) {
        cout << "Probleem 1 voi enama toiduainega. Palun proovi uuesti" << endl;
    } else {
        for (const auto& retsept : retseptid) {
            cout << "Roog: " << retsept.name << endl;
            cout << "Koostisained:" << endl;
            for (const auto& koostisaine : retsept.ingredients) {
                string asendus = koostisaine;
                map<string, string> fractions = {{"½", "1/2"}, {"⅛", "1/8"}, {"¼", "1/4"}, {"¾", "3/4"}, {"⅓", "1/3"}};
                for (const auto& fraction : fractions) {
                    size_t pos = asendus.find(fraction.first);
                    while (pos != string::npos) {
                        asendus.replace(pos, 2, fraction.second);
                        pos = asendus.find(fraction.first, pos + 1);
                    }
                }
                cout << "- " << asendus << endl;
            }
            cout << endl;
        }
    }
}

void CLI::kuvaToitained(const vector<Recipe> &toitained) {
    if (toitained.empty()) {
        cout << "Probleem 1 voi enama toiduainega. Palun proovi uuesti" << endl;
    } else {
        for (const auto& retsept : toitained) {
            cout << "Roog: " << retsept.name << endl;
            cout << "Toitained:" << endl;
            for (const auto& toitaine : retsept.nutrients) {
                cout << "- " << toitaine.first << ": " << toitaine.second << endl;
            }
            cout << endl;
        }
    }
}

void CLI::kuvaAllergeenid(const vector<Recipe>& retseptid) {
    if (retseptid.empty()) {
        cout << "Probleem 1 voi enama toiduainega. Palun proovi uuesti" << endl;
    } else {
        for (const auto& retsept : retseptid) {
            cout << "Roog: " << retsept.name << endl;
            cout << "Allergeenid:" << endl;
            for (const auto& allergen : retsept.allergies) {
                cout << "- " << allergen << endl;
            }
            cout << endl;
        }
    }
}


