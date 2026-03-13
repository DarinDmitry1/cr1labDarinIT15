#include <fstream>
#include <iostream>
#include <vector>

#include "Header.h"

int main()
{
    std::ifstream InputFile("t.txt");

    if (!InputFile.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл t.txt" << std::endl;
        return 1;
    }

    int ItemCount = 0;
    int MinRequiredWeight = 0;

    // Читаем N и Z
    if (!(InputFile >> ItemCount >> MinRequiredWeight))
    {
        std::cout << "Ошибка: неверный формат первой строки файла." << std::endl;
        return 1;
    }

    // Проверка валидности N и Z
    if (ItemCount <= 0)
    {
        std::cout << "Ошибка: количество артефактов N должно быть больше 0." << std::endl;
        return 1;
    }

    if (MinRequiredWeight <= 0)
    {
        std::cout << "Ошибка: минимальный вес Z должен быть больше 0." << std::endl;
        return 1;
    }

    std::vector<int> Weights(ItemCount);
    std::vector<int> Taxes(ItemCount);

    // Читаем веса
    for (int Index = 0; Index < ItemCount; ++Index)
    {
        if (!(InputFile >> Weights[Index]))
        {
            std::cout << "Ошибка: недостаточно данных о весах." << std::endl;
            return 1;
        }

        if (Weights[Index] <= 0)
        {
            std::cout << "Ошибка: веса должны быть положительными." << std::endl;
            return 1;
        }
    }

    // Читаем налоги
    for (int Index = 0; Index < ItemCount; ++Index)
    {
        if (!(InputFile >> Taxes[Index]))
        {
            std::cout << "Ошибка: недостаточно данных о налогах." << std::endl;
            return 1;
        }

        if (Taxes[Index] < 0)
        {
            std::cout << "Ошибка: налог не может быть отрицательным." << std::endl;
            return 1;
        }
    }

    InputFile.close();

    const FSelectionResult Result = SolveArtifactsSelection(
        MinRequiredWeight,
        Weights,
        Taxes);

    if (!Result.bIsValid)
    {
        std::cout << "Невозможно набрать вес больше "
            << MinRequiredWeight << " кг." << std::endl;
        return 0;
    }

    std::cout << "Порядковые номера выбранных предметов: ";
    for (const int Index : Result.SelectedIndices)
    {
        std::cout << Index << " ";
    }

    std::cout << std::endl;
    std::cout << "Суммарный вес: " << Result.TotalWeight << " кг" << std::endl;
    std::cout << "Общее налоговое бремя: " << Result.TotalTax << std::endl;

    return 0;
}