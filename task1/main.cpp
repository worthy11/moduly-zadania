#include <fstream>
#include <iostream>
#include <string>

import album;

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
    std::string expectedWord;
    int lineNo = 0;
    int failures = 0;

    while (in >> idA >> idB >> expectedWord)
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

        const bool expected = expectedWord == "true";
        const bool actual = sameStartYear(idA.c_str(), idB.c_str());
        if (actual != expected)
        {
            std::cout << "FAIL line " << lineNo << ": sameStartYear(\"" << idA
                      << "\", \"" << idB << "\") -> " << std::boolalpha << actual
                      << ", expected " << expected << '\n';
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
