#include <iostream>
#include <string>

import fines;

int main()
{
    std::string command;
    while (std::cin >> command)
    {
        if (command == "fine")
        {
            double amount;
            if (!(std::cin >> amount))
            {
                std::cout << "Invalid fine amount.\n";
                return 1;
            }
            addFine(amount);
        }
        else if (command == "summary")
        {
            const Totals totals = getTotals();
            std::cout << totals.count << ' ' << totals.total << ' '
                      << totals.minFine << ' ' << totals.maxFine << ' '
                      << totals.average << '\n';
        }
        else if (command == "undo")
        {
            std::cout << (undoLast() ? "ok" : "fail") << '\n';
        }
        else if (command == "reset")
        {
            reset();
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command.\n";
        }
    }
}
