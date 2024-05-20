//TODO: võiks teha et kui vale input pannakse siis annab mingi custom errori et vigane sisend ja küsib uuesti
//TODO: teha nii et saab valida ühe kuvatud retseptidest ja selle ained salvestada poenimekirja
//TODO: output võiks olla ilusam ja võiks olla arusaadavam, et mis olekus ollakse, kui "proovi uuesti" küsitakse + mingid random tühikud on
//TODO: see prindib millegi pärast selle lingi iga kord?? see tuleks parandada

#include "CLI.h"
#include "retsepti_otsing.h"
#include <iostream>

using namespace std;

int CLI::retseptiIndeks = 0;

void CLI::start() {
    while (true) {
        cout << "Vali tegevus: \n";
        cout << "a) Leia retsept koostisainete pohjal\n";
        cout << "b) Leia kindel retsept\n";
        cout << "Sisesta oma valik (a, b): ";
        char valik;
        cin >> valik;
        cin.ignore(); // Tühjendab puhvri

        switch (valik) {
            case 'a': otsiRetsept(true); break;
            case 'b': otsiRetsept(false); break;
            default: cout << "Ebasobiv valik. Vali uuesti.\n"; break;
        }

        if (!prooviUuesti()) break;
    }
}

void CLI::otsiRetsept(bool koostisainetePohjal) {
    while (true) {
        vector<string> koostisained;
        string otsinguTerm;

        if (koostisainetePohjal) {
            cout << "Sisesta toiduained (inglise keeles, eraldi ridadel, lopetamiseks vajuta enterit 2 korda):" << endl;
            string koostisaine;
            while (getline(cin, koostisaine) && !koostisaine.empty()) {
                koostisained.push_back(koostisaine);
            }
            otsinguTerm = koostaOtsinguTerm(koostisained);
        } else {
            cout << "Sisesta soovitud retsept (nt 'chicken noodle soup'): ";
            string retsept;
            getline(cin, retsept);
            otsinguTerm = koostaOtsinguTerm({retsept});
        }

        vector<Recipe> retseptid = leiaRetseptid(otsinguTerm, 0);
        kuvaRetseptid(retseptid);

        if (retseptid.empty()) {
            if (!prooviUuesti()) break;
            continue;
        }

        kuvaDetailid(retseptid, "toitaineinfot", &CLI::kuvaToitained);
        kuvaDetailid(retseptid, "allergeene", &CLI::kuvaAllergeenid);

        while (true) {
            cout << "Kas tahad leida rohkem retsepte (Y/N)? ";
            char valik;
            cin >> valik;
            cin.ignore(); // Tühjendab puhvri
            if (valik == 'Y' || valik == 'y') {
                genereeriRohkemRetsepte(otsinguTerm, retseptid, retseptiIndeks + 3);
                kuvaRetseptid(retseptid);
            } else {
                setRetseptiIndeks(0);
                break;
            }
        }

        if (!prooviUuesti()) break;
    }
}

void CLI::kuvaDetailid(const vector<Recipe>& retseptid, const string& detail, void (CLI::*kuvaFunktsioon)(const vector<Recipe>&)) {
    char valik;
    cout << "Kas tahad naha " << detail << " (Y/N)? ";
    cin >> valik;
    cin.ignore(); // Tühjendab puhvri
    if (valik == 'Y' || valik == 'y') {
        (this->*kuvaFunktsioon)(retseptid);
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

void CLI::kuvaRetseptid(vector<Recipe>& retseptid) {
    if (retseptid.empty()) {
        cout << "Probleem 1 voi enama toiduainega. Palun proovi uuesti" << endl;
    } else {
        for (Recipe& retsept : retseptid) {
            if (!retsept.näidatud) {
                cout << "Roog: " << retsept.name << endl;
                retsept.näidatud = true;

                cout << "Koostisained:" << endl;
                for (const auto& koostisaine : retsept.koostisained) {
                    string asendus = koostisaine;
                    map<string, string> fractions = {{"½", "1/2"},
                                                     {"⅛", "1/8"},
                                                     {"¼", "1/4"},
                                                     {"¾", "3/4"},
                                                     {"⅓", "1/3"}};
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
}

void CLI::kuvaToitained(const vector<Recipe>& toitained) {
    for (const auto& retsept : toitained) {
        cout << "Roog: " << retsept.name << endl;
        cout << "Toitained:" << endl;
        for (const auto& toitaine : retsept.nutrients) {
            cout << "- " << toitaine.first << ": " << toitaine.second << endl;
        }
        cout << endl;
    }
}

void CLI::kuvaAllergeenid(const vector<Recipe>& retseptid) {
    for (const auto& retsept : retseptid) {
        cout << "Roog: " << retsept.name << endl;
        cout << "Allergeenid:" << endl;
        for (const auto& allergeen : retsept.allergiad) {
            cout << "- " << allergeen << endl;
        }
        cout << endl;
    }
}

vector<Recipe> CLI::genereeriRohkemRetsepte(const string& otsinguTerm, vector<Recipe>& retseptid, int indeks) {
    vector<Recipe> rohkemRetsepte = leiaRetseptid(otsinguTerm, indeks);
    if (rohkemRetsepte.empty()) {
        cout << "Rohkem retsepte ei leidu." << endl;
    } else {
        setRetseptiIndeks(indeks + 3);
        for (Recipe& uusRetsept : rohkemRetsepte) {
            retseptid.push_back(uusRetsept);
        }
    }
    return retseptid;
}
