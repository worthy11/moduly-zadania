#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

import waitlist;

namespace
{

    bool parseBool(const std::string &word)
    {
        return word == "true";
    }

} // namespace

int main(int argc, char *argv[])
{
    const char *path = argc > 1 ? argv[1] : "data/cases.txt";
    std::ifstream in(path);
    if (!in)
    {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    Waitlist waitlist{0, 1};
    std::string token;
    std::string runName;
    int failures = 0;
    int lineNo = 0;

    while (std::getline(in, token))
    {
        ++lineNo;
        if (token.empty() || token[0] == '#')
        {
            continue;
        }

        std::istringstream line(token);
        std::string cmd;
        line >> cmd;
        if (cmd.empty())
        {
            continue;
        }

        if (cmd == "RUN")
        {
            line >> runName;
            continue;
        }
        if (cmd == "END")
        {
            runName.clear();
            continue;
        }
        if (cmd == "SET")
        {
            line >> waitlist.seated >> waitlist.capacity;
            continue;
        }
        if (cmd == "CONSISTENT")
        {
            int seated = 0;
            int capacity = 0;
            std::string expectedWord;
            line >> seated >> capacity >> expectedWord;
            Waitlist probe{seated, capacity};
            const bool actual = isConsistent(probe);
            const bool expected = parseBool(expectedWord);
            if (actual != expected)
            {
                std::cout << "FAIL line " << lineNo << " (" << runName
                          << "): isConsistent({" << seated << ", " << capacity
                          << "}) -> " << std::boolalpha << actual << ", expected "
                          << expected << '\n';
                ++failures;
            }
            continue;
        }
        if (cmd == "JOIN")
        {
            std::string expectedOkWord;
            int expectedSeated = 0;
            line >> expectedOkWord >> expectedSeated;
            const bool expectedOk = parseBool(expectedOkWord);
            const bool actualOk = tryJoin(waitlist);
            if (actualOk != expectedOk || waitlist.seated != expectedSeated)
            {
                std::cout << "FAIL line " << lineNo << " (" << runName
                          << "): tryJoin -> " << std::boolalpha << actualOk
                          << " seated=" << waitlist.seated << ", expected "
                          << expectedOk << " seated=" << expectedSeated << '\n';
                ++failures;
            }
            continue;
        }
        if (cmd == "LEAVE")
        {
            std::string expectedOkWord;
            int expectedSeated = 0;
            line >> expectedOkWord >> expectedSeated;
            const bool expectedOk = parseBool(expectedOkWord);
            const bool actualOk = tryLeave(waitlist);
            if (actualOk != expectedOk || waitlist.seated != expectedSeated)
            {
                std::cout << "FAIL line " << lineNo << " (" << runName
                          << "): tryLeave -> " << std::boolalpha << actualOk
                          << " seated=" << waitlist.seated << ", expected "
                          << expectedOk << " seated=" << expectedSeated << '\n';
                ++failures;
            }
            continue;
        }

        std::cout << "Unknown command on line " << lineNo << ": " << cmd << '\n';
        ++failures;
    }

    if (failures == 0)
    {
        std::cout << "OK\n";
        return 0;
    }
    return 1;
}
