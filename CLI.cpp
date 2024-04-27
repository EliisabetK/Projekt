#include "CLI.h"
#include "retsepti_otsing.h"
#include <iostream>

using namespace std;

void CLI::start() {
    bool continueLoop = true; // Muutuja, mis näitab, kas programm peaks uuesti alustama
    while (continueLoop) { // Algab loop
        vector<string> koostisained;
        string koostisaine;

        // Küsib kasutajalt toiduained, kuni kasutaja sisestab tühja rea
        cout << "Sisesta toiduained (inglise keeles, eraldi ridadel, lopetamiseks vajuta enterit 2 korda):" << endl;
        while (getline(cin, koostisaine)) {
            if (koostisaine.empty()) {
                break; // Lõpeta tsükkel, kui kasutaja sisestab tühja rea
            }
            koostisained.push_back(koostisaine);
        }

        // Koostab otsingutermini koostisainete põhjal
        string otsinguTerm = "";
        for(size_t i = 0; i < koostisained.size(); ++i) {
            for (char c : koostisained[i]) {
                if (c == ' ') { // Asendab tühikud %20ga, et mitte lõhkuda URL-i
                    otsinguTerm += "%20";
                } else {
                    otsinguTerm += c;
                }
            }
            if (i != koostisained.size() - 1) {
                otsinguTerm += "%20";
            }
        }

        // Leiab retseptid
        map<string, vector<string>> retseptid = leiaRetseptid(otsinguTerm);
        kuvaRetseptid(otsinguTerm, retseptid);

        // Küsib kasutajalt, kas nad soovivad uuesti proovida
        char valik;
        cout << "Kas tahad uuesti proovida (Y/N)? ";
        cin >> valik;
        cin.ignore(); // Tühjendab puhvri

        if (valik != 'Y' && valik != 'y') {  // Kui vastus ei ole Y või y, siis lõpeta loop
            continueLoop = false;
        }
    }
}

void CLI::kuvaRetseptid(const string& otsinguTerm, const map<string, vector<string>>& retseptid) {
    if (retseptid.empty()) { // Kui retsepte ei leitud
        cout << "Probleem 1 voi enama toiduainega. Palun proovi uuesti" << endl;
    } else {
        for (const auto &retsept: retseptid) {
            cout << "Roog: " << retsept.first << endl;
            cout << "Koostisained:" << endl;
            for (const auto &koostisaine: retsept.second) {
                string asendus = koostisaine;
                map<string, string> fractions = {{"½", "1/2"}, {"⅛", "1/8"}, {"¼", "1/4"}, {"¾", "3/4"}, {"⅓", "1/3"}}; // Neid sümboleid ei kuvata korrektselt
                for (const auto &fraction : fractions) {
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



