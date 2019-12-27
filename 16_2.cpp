/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 27.12.19



Найдите все вхождения шаблона в строку.
Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
Вариант 2. С помощью z-функции.
Формат входного файла:

Шаблон, символ перевода строки, строка.

Формат выходного файла:

Позиции вхождения шаблона в строке.

Время: 100мс, память 3Mb.ц

stdin:

aba
abacababa

stdout:

0 4 6

*/

#include <iostream>
#include <vector>
#include <string>

void findSubstrings(const std::string &inputString, const std::string &pattern, std::vector <int> &result)
    {
        std::string concatinatedString = pattern + "|" + inputString; // "|"  to debug

        const int patternSize = pattern.size();
        const int concatinatedStringSize = inputString.size() + patternSize + 1;
        int left = 0;
        int right = 0;
        std::vector <int> zFunction(patternSize, 0);

        for (int i = 1; i < concatinatedStringSize; i++)
        {
            int currentZFunction = 0;
            if (i - left <= patternSize)
                {
                    currentZFunction = std::max(0, std::min(right - i, zFunction[i - left]));
                }
            else
                {
                    currentZFunction = std::max(0, right - i);
                }

            while (i + currentZFunction < concatinatedStringSize && concatinatedString[currentZFunction] == concatinatedString[i + currentZFunction])
                {
                    currentZFunction++;
                }

            if (i + currentZFunction - 1 > right)
                {
                    left = i;
                    right = i + currentZFunction - 1;
                }

            if (i < patternSize)
                {
                    zFunction[i] = currentZFunction;
                }

            if (currentZFunction == patternSize)
                {
                    result.push_back(i - patternSize - 1);
                }
        }
    }


int main()
    {
        std::string pattern, inputString;
        std::vector <int> result; //to output only in main
        std::cin >> pattern >> inputString;

        findSubstrings(inputString, pattern, result);
        for (auto a: result)
        {
            std::cout << a << " ";
        }
        return 0;
    }