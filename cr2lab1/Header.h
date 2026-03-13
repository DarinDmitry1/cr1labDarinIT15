#pragma once

#include <string>
#include <vector>

struct FKingPathResult
{
    bool bIsValid = false;
    int MaxSum = 0;
    std::string Path;
};

// Ќаходит максимальную сумму монет и путь корол€
// из правого нижнего угла в левый верхний.
FKingPathResult SolveKingPath(const std::vector<std::vector<int>>& Board);