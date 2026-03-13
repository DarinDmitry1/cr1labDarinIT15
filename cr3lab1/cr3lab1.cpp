#include <fstream>
#include <iomanip>
#include <iostream>

#include "Header.h"

int main()
{
    setlocale(LC_ALL, "ru");
    std::ifstream InputFile("input.txt");
    if (!InputFile.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл input.txt" << std::endl;
        return 1;
    }

    std::ofstream OutputFile("output.txt");
    if (!OutputFile.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл output.txt" << std::endl;
        return 1;
    }

    int DigitCount = 0;
    int Base = 0;

    // Ожидаем два числа: N и K.
    if (!(InputFile >> DigitCount >> Base))
    {
        std::cout << "Ошибка: неверный формат входных данных." << std::endl;
        return 1;
    }

    // Проверяем ограничения из условия.
    if (DigitCount <= 1 || DigitCount >= 20)
    {
        std::cout << "Ошибка: N должно удовлетворять условию 1 < N < 20." << std::endl;
        return 1;
    }

    if (Base < 2 || Base > 10)
    {
        std::cout << "Ошибка: K должно удовлетворять условию 2 <= K <= 10." << std::endl;
        return 1;
    }

    if (DigitCount + Base >= 26)
    {
        std::cout << "Ошибка: должно выполняться условие N + K < 26." << std::endl;
        return 1;
    }

    // Проверяем, нет ли лишних данных.
    int ExtraValue = 0;
    if (InputFile >> ExtraValue)
    {
        std::cout << "Ошибка: файл содержит лишние данные." << std::endl;
        return 1;
    }

    const FCountResult Result = CountNumbersWithFourZeroesInRow(DigitCount, Base);
    if (!Result.bIsValid)
    {
        std::cout << "Ошибка: не удалось вычислить результат." << std::endl;
        return 1;
    }

    // По условию ответ нужно представить в виде вещественного числа.
    OutputFile << std::fixed << std::setprecision(0) << Result.Count << std::endl;

    InputFile.close();
    OutputFile.close();

    return 0;
}