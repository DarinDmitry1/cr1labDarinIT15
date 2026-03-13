#pragma once
#include <vector>

// Результат решения задачи
struct FSelectionResult
{
    bool bIsValid = false;          // найдено ли решение
    int TotalWeight = 0;            // итоговый вес
    int TotalTax = 0;               // итоговое налоговое бремя
    std::vector<int> SelectedIndices; // номера выбранных предметов
};

// Решает задачу выбора артефактов
FSelectionResult SolveArtifactsSelection(
    int MinRequiredWeight,
    const std::vector<int>& Weights,
    const std::vector<int>& Taxes);
