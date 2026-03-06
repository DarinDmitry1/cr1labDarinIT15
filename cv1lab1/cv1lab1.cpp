#include <fstream>
#include <iostream>
#include <vector>

#include "Header.h"

int main()
{
    setlocale(LC_ALL, "ru");
    std::ifstream InputFile("t.txt");
    if (!InputFile.is_open())
    {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    int ItemCount = 0;
    int MinRequiredWeight = 0;

    // Первая строка файла: N и Z
    InputFile >> ItemCount >> MinRequiredWeight;

    std::vector<int> Weights(ItemCount);
    std::vector<int> Taxes(ItemCount);

    // Вторая строка — веса
    for (int Index = 0; Index < ItemCount; ++Index)
    {
        InputFile >> Weights[Index];
    }

    // Третья строка — налоги
    for (int Index = 0; Index < ItemCount; ++Index)
    {
        InputFile >> Taxes[Index];
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