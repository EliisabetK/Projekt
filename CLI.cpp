//TODO: info ilusalt väljastamine terminali aka CLI

#include "CLI.h"
#include "api_suhtlus.h"
#include <iostream>
using namespace std;

void CLI::start() {
    bool continueLoop = true; // Muutuja, mis näitab, kas programm peaks uuesti alustama
    while (continueLoop) { // Algab loop

        vector<string> koostisained;
        string koostisaine;

        // Küsi kasutajalt toiduained, kuni kasutaja sisestab tühja rea
        cout << "Sisesta toiduained (inglise keeles, eraldi ridadel, lopetamiseks vajuta enterit 2 korda):" << endl;
        while (getline(cin, koostisaine)) {
            if (koostisaine.empty()) {
                break; // Lõpeta tsükkel, kui kasutaja sisestab tühja rea
            }
            koostisained.push_back(koostiscaine);
        }

        // Koosta otsingutermin koostisainete põhjal
        string otsinguTerm = "";
        for(size_t i = 0; i < koostisained.size(); ++i) {
            otsinguTerm += koostisained[i];
            if (i != koostisained.size() - 1) {
                otsinguTerm += "%20";
            }
        }

        // Hangi retseptid API abil
        string jsonString = FetchData(otsinguTerm);
        map<string, vector<string>> retseptid;

        string key = "\"text\":\"";
        string labelKey = "\"label\":\"";
        size_t start, end;

        // Esimese retsepti algus
        size_t retseptStart = jsonString.find("\"recipe\":{");

        // Leiab esimesed kolm retsepti
        for (int i = 0; i < 3; ++i) {
            if (retseptStart != string::npos) {
                // Leiab retsepti lõpu
                size_t retseptLopp = jsonString.find("}}", retseptStart);

                if (retseptLopp != string::npos) {
                    string retsept = jsonString.substr(retseptStart, retseptLopp - retseptStart);

                    // Otsib toidu nime
                    start = retsept.find(labelKey);
                    if (start != string::npos) {
                        start += labelKey.length();
                        end = retsept.find("\"", start);
                        string toiduNimi = retsept.substr(start, end - start);

                        // Leiab koostisained
                        vector<string> koostisained;
                        start = retsept.find(key);
                        while (start != string::npos) {
                            start += key.length();
                            end = retsept.find("\"", start);
                            koostisained.push_back(retsept.substr(start, end - start));
                            start = retsept.find(key, end);
                        }

                        // Lisab koostisained mappi vastava nimega toidu juurde
                        retseptid[toiduNimi] = koostisained;
                    }

                    // Otsib järgmise retsepti alguse
                    retseptStart = jsonString.find("\"recipe\":{", retseptLopp);
                }
            }
        }

        // Kuvab retseptid
        displayRecipes(otsinguTerm, retseptid);

        // Küsi kasutajalt, kas nad soovivad uuesti proovida
        char choice;
        cout << "Kas tahad uuesti proovida (Y/N)? ";
        cin >> choice;
        cin.ignore(); // Tühjendab puhvri

        if (choice != 'Y' && choice != 'y') { // Kui vastus ei ole Y või y, siis lõpeta loop
            continueLoop = false;
        }
    }
}


string CLI::FetchData(const string& searchTerms) {
    APISuhtlus apiSuhtlus;
    return apiSuhtlus.FetchData(searchTerms);
}

void CLI::displayRecipes(const string& otsinguTerm, const map<string, vector<string>>& recipes) {
    if (recipes.empty()) {
        cout << "Probleem 1 voi enama toiduainega. Palun proovi uuesti" << endl;
    } else {
        for (const auto& retsept : recipes) {
            cout << "Roog: " << retsept.first << endl;
            cout << "Koostisained:" << endl;
            for (const auto& koostisaine : retsept.second) {
                cout << "- " << koostisaine << endl;
            }
            cout << endl;
        }
    }
}

