#include "retsepti_otsing.h"
#include "api_suhtlus.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

vector<Recipe> leiaRetseptid(const string& otsinguTerm, int startIndex) {
    APISuhtlus& apiSuhtlus = APISuhtlus::getInstance();
    string jsonString = apiSuhtlus.FetchData(otsinguTerm);
    vector<Recipe> retseptid;

    string key = "\"text\":\"";
    string labelKey = "\"label\":\"";
    size_t start, end;

    size_t retseptStart = jsonString.find("\"recipe\":{");

    for (int i = 0; i < startIndex; ++i) {
        if (retseptStart != string::npos) {
            retseptStart = jsonString.find("\"recipe\":{", retseptStart + 1);
        } else {
            return retseptid;
        }
    }

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

                    // Leiab toitained
                    map<string, double> toitaineteInfo;
                    string nutrientsKey = "\"totalNutrients\":{";
                    start = retsept.find(nutrientsKey);
                    if (start != string::npos) {
                        start += nutrientsKey.length();
                        end = retsept.find("]}}", start); // leiab retsepti lõpu
                        string toitained = retsept.substr(start, end - start);
                        // Otsib proteiinid, kalorid, rasvad ja suhkrud
                        vector<pair<string, string>> toitaineNimed = {
                                {"PROCNT", "Protein"},
                                {"ENERC_KCAL", "Energy"},
                                {"FAT", "Fat"},
                                {"CHOCDF", "Carbs"},
                                {"SUGAR", "Sugars"}
                        };

                        for (const auto& toitaine : toitaineNimed) {
                            size_t toitaineStart = toitained.find(toitaine.first);
                            if (toitaineStart != string::npos) {
                                size_t quantityStart = toitained.find("\"quantity\":", toitaineStart);
                                if (quantityStart != string::npos) {
                                    quantityStart += 11; // szee on "\"quantity\":" pikkus
                                    size_t quantityEnd = toitained.find(",", quantityStart);
                                    double quantity = stod(toitained.substr(quantityStart, quantityEnd - quantityStart));
                                    toitaineteInfo[toitaine.second] = quantity;
                                }
                            }
                        }
                    }

                    // Leiab allergiad
                    vector<string> allergiad;
                    string allergiaKey = "\"healthLabels\":[";  // Eeldame, et allergia teave on salvestatud "healthLabels" võtme all
                    start = retsept.find(allergiaKey);
                    if (start != string::npos) {
                        start += allergiaKey.length();
                        end = retsept.find("]", start);
                        string allergiaString = retsept.substr(start, end - start);

                        size_t allergiaStart = 0;
                        size_t allergiaEnd = allergiaString.find(",");
                        while (allergiaEnd != string::npos) {
                            allergiad.push_back(allergiaString.substr(allergiaStart, allergiaEnd - allergiaStart));
                            allergiaStart = allergiaEnd + 1;
                            allergiaEnd = allergiaString.find(",", allergiaStart);
                        }
                        allergiad.push_back(allergiaString.substr(allergiaStart));
                    }

                    // Lisab retsepti vektorisse
                    retseptid.push_back(Recipe(toiduNimi, koostisained, toitaineteInfo, allergiad, false));
                }

                // Otsib järgmise retsepti alguse
                retseptStart = jsonString.find("\"recipe\":{", retseptLopp);
            }
        }
    }
    return retseptid;
}




