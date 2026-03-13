#include "Header.h"

#include <vector>

FCountResult CountNumbersWithFourZeroesInRow(int DigitCount, int Base)
{
    FCountResult Result;

    if (DigitCount <= 1 || Base < 2 || Base > 10)
    {
        return Result;
    }

    // Dp[Length][ZeroCount]:
    // ZeroCount = 0..3  -> число оканчиваетс€ на соответствующее количество нулей подр€д
    // ZeroCount = 4     -> в числе уже встретилось более трех подр€д идущих нулей
    std::vector<std::vector<double>> Dp(DigitCount + 1, std::vector<double>(5, 0.0));

    // ѕервый разр€д N-значного числа не может быть нулем.
    Dp[1][0] = static_cast<double>(Base - 1);

    for (int Length = 2; Length <= DigitCount; ++Length)
    {
        // ≈сли добавл€ем ненулевую цифру, цепочка нулей обрываетс€.
        for (int ZeroCount = 0; ZeroCount <= 4; ++ZeroCount)
        {
            Dp[Length][0] += Dp[Length - 1][ZeroCount] * static_cast<double>(Base - 1);
        }

        // ≈сли добавл€ем ноль, увеличиваем длину текущей цепочки нулей.
        Dp[Length][1] += Dp[Length - 1][0];
        Dp[Length][2] += Dp[Length - 1][1];
        Dp[Length][3] += Dp[Length - 1][2];

        // ѕри добавлении нул€ к трем подр€д идущим нул€м
        // получаем число, где уже есть более трех нулей подр€д.
        Dp[Length][4] += Dp[Length - 1][3];

        // ≈сли нужное свойство уже выполнено, можно дописывать любую цифру.
        Dp[Length][4] += Dp[Length - 1][4] * static_cast<double>(Base);
    }

    Result.bIsValid = true;
    Result.Count = Dp[DigitCount][4];
    return Result;
}