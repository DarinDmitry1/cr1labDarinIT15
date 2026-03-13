#include <fstream>
#include <iostream>
#include <vector>

#include "Header.h"

int main()
{
    setlocale(LC_ALL, "ru");
    std::ifstream InputFile("a.txt");
    if (!InputFile.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл a.txt" << std::endl;
        return 1;
    }

    std::ofstream OutputFile("b.txt");
    if (!OutputFile.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл b.txt" << std::endl;
        return 1;
    }

    int BoardSize = 0;
    if (!(InputFile >> BoardSize))
    {
        std::cout << "Ошибка: неверный формат первой строки файла." << std::endl;
        return 1;
    }

    if (BoardSize <= 1 || BoardSize >= 80)
    {
        std::cout << "Ошибка: размер доски N должен удовлетворять условию 1 < N < 80." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> Board(BoardSize, std::vector<int>(BoardSize, 0));

    for (int Row = 0; Row < BoardSize; ++Row)
    {
        for (int Col = 0; Col < BoardSize; ++Col)
        {
            if (!(InputFile >> Board[Row][Col]))
            {
                std::cout << "Ошибка: недостаточно данных для заполнения доски." << std::endl;
                return 1;
            }

            if (Board[Row][Col] < 1 || Board[Row][Col] > 100)
            {
                std::cout << "Ошибка: значение монеты должно быть в диапазоне от 1 до 100." << std::endl;
                return 1;
            }
        }
    }

    int ExtraValue = 0;
    if (InputFile >> ExtraValue)
    {
        std::cout << "Ошибка: файл содержит лишние данные." << std::endl;
        return 1;
    }

    const FKingPathResult Result = SolveKingPath(Board);
    if (!Result.bIsValid)
    {
        std::cout << "Ошибка: не удалось найти путь." << std::endl;
        return 1;
    }

    OutputFile << Result.MaxSum << std::endl;
    OutputFile << Result.Path << std::endl;

    InputFile.close();
    OutputFile.close();

    return 0;
}