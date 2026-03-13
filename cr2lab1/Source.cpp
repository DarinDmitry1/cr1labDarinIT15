#include "Header.h"

#include <algorithm>

FKingPathResult SolveKingPath(const std::vector<std::vector<int>>& Board)
{
    FKingPathResult Result;

    const int Size = static_cast<int>(Board.size());
    if (Size == 0)
    {
        return Result;
    }

    std::vector<std::vector<int>> MaxSumTable(Size, std::vector<int>(Size, 0));

    // Начальная клетка для динамики.
    MaxSumTable[0][0] = Board[0][0];

    // Заполняем первую строку.
    for (int Col = 1; Col < Size; ++Col)
    {
        MaxSumTable[0][Col] = MaxSumTable[0][Col - 1] + Board[0][Col];
    }

    // Заполняем первый столбец.
    for (int Row = 1; Row < Size; ++Row)
    {
        MaxSumTable[Row][0] = MaxSumTable[Row - 1][0] + Board[Row][0];
    }

    // Для остальных клеток выбираем лучший из двух возможных путей:
    // сверху или слева.
    for (int Row = 1; Row < Size; ++Row)
    {
        for (int Col = 1; Col < Size; ++Col)
        {
            MaxSumTable[Row][Col] =
                std::max(MaxSumTable[Row - 1][Col], MaxSumTable[Row][Col - 1]) + Board[Row][Col];
        }
    }

    Result.bIsValid = true;
    Result.MaxSum = MaxSumTable[Size - 1][Size - 1];

    int Row = Size - 1;
    int Col = Size - 1;
    std::string ReversedPath;

    // Восстанавливаем путь из правого нижнего угла в левый верхний.
    while (Row > 0 || Col > 0)
    {
        if (Row == 0)
        {
            ReversedPath += 'L';
            --Col;
        }
        else if (Col == 0)
        {
            ReversedPath += 'U';
            --Row;
        }
        else if (MaxSumTable[Row - 1][Col] >= MaxSumTable[Row][Col - 1])
        {
            ReversedPath += 'U';
            --Row;
        }
        else
        {
            ReversedPath += 'L';
            --Col;
        }
    }

    Result.Path = ReversedPath;
    return Result;
}