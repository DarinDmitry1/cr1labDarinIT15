#pragma once

struct FCountResult
{
    bool bIsValid = false;
    double Count = 0.0;
};

// Считает количество N-значных чисел в системе счисления с основанием K,
// в записи которых есть более трех подряд идущих нулей.
FCountResult CountNumbersWithFourZeroesInRow(int DigitCount, int Base);