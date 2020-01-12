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

std::vector <int> findSubstrings(const std::string &inputString, const std::string &pattern)
    {
        const int patternSize = pattern.size();
        const int inputStringSize = inputString.size();
        int left = 0;
        int right = 0;
        int currentZFunction = 0;
        std::vector<int> zFunction(patternSize, 0);
        std::vector<int> result;


        for (int position = 1; position < patternSize; position++)  //first calculate z-function for pattern
        {
            zFunction[position] = std::max(0, std::min(zFunction[position - left], right - position + 1));

            while ((position + zFunction[position] < inputStringSize) &&
                   (pattern[zFunction[position]] == pattern[position + zFunction[position]]))
            {
                zFunction[position]++;
            }

            if (position + zFunction[position] - 1 > right)
            {
                left = position;
                right = position + zFunction[position] - 1;
            }
        }


        left = 0;
        right = 0;
        for (int position = 0;
             position < inputStringSize; position++) //calculate z-function for current position in input text
        {
            currentZFunction = std::max(0, std::min(zFunction[position - left], right - position + 1));

            while ((position + currentZFunction < inputStringSize) &&
                   (pattern[currentZFunction] == inputString[position + currentZFunction]))
            {
                currentZFunction++;
            }

            if (position + currentZFunction - 1 > right)
            {
                left = position;
                right = position + currentZFunction - 1;
            }

            if (currentZFunction == patternSize) // save position to answer
            {
                result.push_back(position);
            }
        }
        return result;
    }

int main()
    {
        std::string pattern, inputString;
        std::vector <int> result; //to output only in main
        std::cin >> pattern >> inputString;

        result = findSubstrings(inputString, pattern);
        for (auto a: result)
        {
            std::cout << a << " ";
        }
        return 0;
    }
