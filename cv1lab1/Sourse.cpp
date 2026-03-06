#include "Header.h"

#include <climits>

FSelectionResult SolveArtifactsSelection(
    int MinRequiredWeight,
    const std::vector<int>& Weights,
    const std::vector<int>& Taxes)
{
    FSelectionResult Result;

    const int ItemCount = static_cast<int>(Weights.size());

    // Максимально возможный вес (если взять все предметы)
    int MaxPossibleWeight = 0;
    for (const int Weight : Weights)
    {
        MaxPossibleWeight += Weight;
    }

    // dp[w] = минимальный налог для получения веса w
    std::vector<int> MinTaxForWeight(MaxPossibleWeight + 1, INT_MAX);
    MinTaxForWeight[0] = 0;

    // Хранит набор предметов, дающий конкретный вес
    std::vector<std::vector<bool>> SelectedItems(
        MaxPossibleWeight + 1,
        std::vector<bool>(ItemCount, false));

    for (int ItemIndex = 0; ItemIndex < ItemCount; ++ItemIndex)
    {
        const int CurrentWeight = Weights[ItemIndex];
        const int CurrentTax = Taxes[ItemIndex];

        // Идём назад по весам, чтобы каждый предмет использовался только один раз
        for (int Weight = MaxPossibleWeight; Weight >= CurrentWeight; --Weight)
        {
            if (MinTaxForWeight[Weight - CurrentWeight] == INT_MAX)
            {
                continue;
            }

            const int NewTax = MinTaxForWeight[Weight - CurrentWeight] + CurrentTax;

            // Если нашли вариант с меньшим налогом — обновляем
            if (NewTax < MinTaxForWeight[Weight])
            {
                MinTaxForWeight[Weight] = NewTax;
                SelectedItems[Weight] = SelectedItems[Weight - CurrentWeight];
                SelectedItems[Weight][ItemIndex] = true;
            }
        }
    }

    int BestWeight = 0;
    int BestTax = INT_MAX;
    std::vector<bool> BestSelection(ItemCount, false);

    // Ищем лучший вариант среди всех весов >= требуемого
    for (int Weight = MinRequiredWeight + 1; Weight <= MaxPossibleWeight; ++Weight)
    {
        if (MinTaxForWeight[Weight] < BestTax)
        {
            BestTax = MinTaxForWeight[Weight];
            BestWeight = Weight;
            BestSelection = SelectedItems[Weight];
        }
    }

    if (BestTax == INT_MAX)
    {
        return Result;
    }

    Result.bIsValid = true;
    Result.TotalWeight = BestWeight;
    Result.TotalTax = BestTax;

    // Формируем список выбранных предметов
    for (int ItemIndex = 0; ItemIndex < ItemCount; ++ItemIndex)
    {
        if (BestSelection[ItemIndex])
        {
            Result.SelectedIndices.push_back(ItemIndex + 1);
        }
    }

    return Result;
}