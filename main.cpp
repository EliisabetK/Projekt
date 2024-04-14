#include <iostream>
#include <vector>
#include <map>
#include "api_suhtlus.h"
using namespace std;
int main() {
    APISuhtlus apiSuhtlus;

    vector<string> koostisaineteList = {"soup", "chicken", "noodles"};
    string otsinguTerm = "";
    for(string koostisaine : koostisaineteList){
        otsinguTerm += koostisaine;
        otsinguTerm += "%20";
    }
    string jsonString = apiSuhtlus.FetchData(otsinguTerm);
    map<string, vector<string>> retseptid;

    string key = "\"text\":\"";
    string labelKey = "\"label\":\"";
    size_t start, end;

    // esimese retsepti algus
    size_t retseptStart = jsonString.find("\"recipe\":{");

    for (int i = 0; i < 3; ++i) {  // leiab esimesed kolm retsepti
        if (retseptStart != string::npos) {
            // leiab retsepti lõpu
            size_t retseptLõpp = jsonString.find("}}", retseptStart);

            if (retseptLõpp != string::npos) {
                string retsept = jsonString.substr(retseptStart, retseptLõpp - retseptStart);

                // otsib toidu nime
                start = retsept.find(labelKey);
                if (start != string::npos) {
                    start += labelKey.length();
                    end = retsept.find("\"", start);
                    string toiduNimi = retsept.substr(start, end - start);

                    // leiab koostisained
                    vector<string> koostisained;
                    start = retsept.find(key);
                    while (start != string::npos) {
                        start += key.length();
                        end = retsept.find("\"", start);
                        koostisained.push_back(retsept.substr(start, end - start));
                        start = retsept.find(key, end);
                    }

                    // lisab koostisained mappi vastava nimega toidu juurde
                    retseptid[toiduNimi] = koostisained;
                }

                // otsib järgmise retsepti alguse
                retseptStart = jsonString.find("\"recipe\":{", retseptLõpp);
            }
        }
    }

    for (const auto& retsept : retseptid) {
        cout << "Dish: " << retsept.first << endl;
        cout << "Ingredients:" << endl;
        for (const auto& koostisaine : retsept.second) {
            cout << "- " << koostisaine << endl;
        }
        cout << endl;
    }

    return 0;
}
