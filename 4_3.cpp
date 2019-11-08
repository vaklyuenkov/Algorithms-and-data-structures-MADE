/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 8.11.19

Порядковая статистика
 4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число,
которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
Напишите нерекурсивный алгоритм.
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:

    1) Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
    2) Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
        Затем располагаются элементы, строго бОльшие опорного.
        В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
    3) Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
    4) Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
    5) Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
    6) Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
    7) В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).

Пример:
Input:
10 4
1 2 3 4 5 6 7 8 9 10
Output:
5
*/

#include <iostream>
#include <cassert>

int choosePivotIndex(int beginIndex, int EndIndex)
{
    return  (rand() %(EndIndex - beginIndex) + beginIndex); //according to our strategy, including borders: begin and end
}

void swap(int *array, int firstIndex, int secondIndex)
{
    if (firstIndex == secondIndex) // to avoid meaningless operations
    {
        return;
    }
    else
    {
        std::swap(array[firstIndex], array[secondIndex]);
    }
}

int partition(int *array, int beginIndex, int endIndex)
{
    int randPivotPosition = choosePivotIndex(beginIndex, endIndex);
    swap(array, randPivotPosition, endIndex); // swap pivot and last element of array

    int i = beginIndex;
    int j = beginIndex;
    while(j < endIndex) // we should check all elements from begin to pivot
    { // implementation according to instructions
        if (array[j] > array[endIndex])
        {
            j++;
        }
        else
        {
            swap(array, i, j);
            j++;
            i++;
        }
    }
    swap(array, i, endIndex);
    return i;
}

int findKThOrderStatistic(int *array, int inputSize, int kThOrder) // looks like we dont need class in this task
{
    int pivotPosition;
    int beginIndex = 0;
    int endIndex = inputSize-1; // functions use numeration from zero

    while(endIndex > beginIndex) //we constantly make boundaries close, in some cases answer when beginIndex==endIndex
    {
        pivotPosition = partition(array, beginIndex, endIndex);

        if (pivotPosition == kThOrder)
        {
            return array[pivotPosition];
        }
        else if (pivotPosition < kThOrder)
        {
            beginIndex = pivotPosition+1; // not including pivot
        }
        else
        {
            endIndex = pivotPosition-1;   // not including pivot
        }
    }

    return array[endIndex]; //in case when beginIndex==endIndex
}

int main () {
    int inputSize = 0; // length of input array
    int kThOrder = 0;  // k
    srand(time( 0 )); //init random with different random seeds

    std::cin >> inputSize >> kThOrder;
    assert(inputSize > kThOrder); // check that input is valid

    int * array = new int[inputSize];

    for (int i = 0; i<inputSize; i++)
    {
        std::cin >> array[i];
    }

    std::cout << findKThOrderStatistic(array, inputSize, kThOrder);

    delete[] array;

    return 0;
}