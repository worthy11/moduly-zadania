#include "legacy_fines.h"

#include <vector>

namespace
{
    std::vector<double> storage;
}

void legacy_add(double amount)
{
    storage.push_back(amount);
}

bool legacy_undo()
{
    if (storage.empty())
    {
        return false;
    }
    storage.pop_back();
    return true;
}

void legacy_clear()
{
    storage.clear();
}

int legacy_count()
{
    return static_cast<int>(storage.size());
}

double legacy_at(int index)
{
    return storage.at(static_cast<std::size_t>(index));
}
