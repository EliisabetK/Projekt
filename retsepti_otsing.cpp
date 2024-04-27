#include "retsepti_otsing.h"
#include "api_suhtlus.h"
#include <map>
#include <vector>

using namespace std;

map<string, vector<string>> leiaRetseptid(const string& otsinguTerm){
    // Hangib retseptid API abil
    APISuhtlus apiSuhtlus;
    string jsonString = apiSuhtlus.FetchData(otsinguTerm);
    map<string, vector<string>> retseptid;

    string key = "\"text\":\"";
    string labelKey = "\"label\":\"";
    size_t start, end;

    // Esimese retsepti algus
    size_t retseptStart = jsonString.find("\"recipe\":{");

    // Leiab esimesed viis retsepti
    for (int i = 0; i < 5; ++i) {
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
    return retseptid;
}
