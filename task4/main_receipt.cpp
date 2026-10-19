#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

import fines;
import receipt;

namespace
{

    bool filesEqual(const std::string &leftPath, const std::string &rightPath)
    {
        std::ifstream left(leftPath);
        std::ifstream right(rightPath);
        if (!left || !right)
        {
            return false;
        }
        std::ostringstream a;
        std::ostringstream b;
        a << left.rdbuf();
        b << right.rdbuf();
        return a.str() == b.str();
    }

    bool fileExists(const std::string &path)
    {
        std::ifstream in(path);
        return static_cast<bool>(in);
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

    std::string line;
    int lineNo = 0;
    int failures = 0;

    while (std::getline(in, line))
    {
        ++lineNo;
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::istringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "RESET")
        {
            reset();
            continue;
        }
        if (cmd == "FINE")
        {
            double amount = 0.0;
            ss >> amount;
            addFine(amount);
            continue;
        }
        if (cmd == "UNDO")
        {
            undoLast();
            continue;
        }
        if (cmd == "WRITE")
        {
            std::string outPath;
            double minTotal = 0.0;
            std::string expectedWord;
            ss >> outPath >> minTotal >> expectedWord;
            const bool expected = expectedWord == "true";
            const bool actual = writeFineReceipt(outPath.c_str(), minTotal);
            if (actual != expected)
            {
                std::cout << "FAIL line " << lineNo << ": writeFineReceipt(\""
                          << outPath << "\", " << minTotal << ") -> "
                          << std::boolalpha << actual << ", expected " << expected
                          << '\n';
                ++failures;
            }
            continue;
        }
        if (cmd == "EXPECT_MISSING")
        {
            std::string outPath;
            ss >> outPath;
            if (fileExists(outPath))
            {
                std::cout << "FAIL line " << lineNo << ": file should not exist: "
                          << outPath << '\n';
                ++failures;
            }
            continue;
        }
        if (cmd == "EXPECT_FILE")
        {
            std::string outPath;
            std::string goldenPath;
            ss >> outPath >> goldenPath;
            if (!filesEqual(outPath, goldenPath))
            {
                std::cout << "FAIL line " << lineNo << ": " << outPath
                          << " differs from " << goldenPath << '\n';
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
