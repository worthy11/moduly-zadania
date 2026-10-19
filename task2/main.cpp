#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

import dorm;

int main(int argc, char *argv[])
{
    const char *path = argc > 1 ? argv[1] : "data/cases.txt";
    std::ifstream in(path);
    if (!in)
    {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    std::string idA;
    std::string idB;
    std::string expected;
    int lineNo = 0;
    int failures = 0;

    while (in >> idA >> idB >> expected)
    {
        ++lineNo;
        if (idA == "EMPTY")
        {
            idA.clear();
        }
        if (idB == "EMPTY")
        {
            idB.clear();
        }

        const char *actual = roomDecision(idA.c_str(), idB.c_str());
        if (std::strcmp(actual, expected.c_str()) != 0)
        {
            std::cout << "FAIL line " << lineNo << ": roomDecision(\"" << idA
                      << "\", \"" << idB << "\") -> " << actual << ", expected "
                      << expected << '\n';
            ++failures;
        }
    }

    if (failures == 0)
    {
        std::cout << "OK\n";
        return 0;
    }
    return 1;
}
