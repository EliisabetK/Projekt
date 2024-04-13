#include <iostream>
// TODO: kasutajaga suhtlemine, input handling
#include <iostream>
#include "api_suhtlus.h"

int main() {
    APISuhtlus apiSuhtlus;

    std::string fetchedData = apiSuhtlus.FetchData("pasta");
    std::cout << "Fetched Data:\n" << fetchedData << std::endl;

    return 0;
}
