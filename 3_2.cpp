/*

Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 7.11.19

3_2. Сортировка почти упорядоченной последовательности

Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j:
если j >= i + k, то a[i] <= a[j].
Требуется отсортировать последовательность.
Последовательность может быть очень длинной.
Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

In:

10 4
0 4 3 2 1 8 7 6 5 9

Out:

0 1 2 3 4 5 6 7 8 9


*/
#include <iostream>
#include <vector>

// to sort we will use heap functions from my previous task
int getParentPosition(int position)
{
    return (position-1)/2;
}

int getLefChildPosition(int position)
{
    return (2*position+1);
}

int getRightChildPosition(int position)
{
    return (2*position+2);
}

template <class T, class TLess>
void siftDown(T *heapArray, int heapSize,  int position, TLess comparator)
{
    while(position*2+1 <= heapSize-1)  // check that current position could have at least one child
    {
        int lefChildPosition = getLefChildPosition(position);
        int rightChildPosition = getRightChildPosition(position);
        int positionOfMaximum = position;

        if (lefChildPosition <= heapSize - 1 && comparator(heapArray[position], heapArray[lefChildPosition]))
            positionOfMaximum = lefChildPosition;

        if (rightChildPosition <= heapSize - 1 && comparator(heapArray[positionOfMaximum],  heapArray[rightChildPosition]))
            positionOfMaximum = rightChildPosition;

        if (position != positionOfMaximum)
        {
            std::swap(heapArray[position], heapArray[positionOfMaximum]);
            position = positionOfMaximum;
        }
        else break;
    }
}

template <class T, class TLess>
void heapSort(T *array, int arraySize, TLess comparator)
{
    for (int i = getParentPosition(arraySize - 1); i >= 0; i--)  //first build heap
    {
        siftDown(array, arraySize, i, comparator);
    }
    for (int i=arraySize-1; i>=0; i--)  // second - sort
    {
        std::swap(array[0], array[i]); // Move current root to end
        siftDown(array, i, 0,  comparator); //heapify
    }
}

template <class T>
void merge (T *buffer, int firstArraySize, int secondArraySize)
{
    T* firstArrayBuffer = new int[firstArraySize];

    for (int i = 0; i< firstArraySize; i++)  // копируем первые k элементов массива в отдельный буфер.
    {
        firstArrayBuffer[i] = buffer[i];
    }

    int i=0; //index of element to compare in first array
    int j=firstArraySize; //index of element to compare in second array

    while (i != firstArraySize && j != firstArraySize+secondArraySize) // to check not all values was taken from one of arrays
    {
        if (firstArrayBuffer[i] < buffer[j])
        {
            buffer[i+j-firstArraySize]=firstArrayBuffer[i];
            i++;
        }

        else
        {
            buffer[i+j-firstArraySize]=buffer[j];
            j++;
        }
    }

    // copy the rest of the the remaining array into the result according to the lecture
    if (i == firstArraySize)
    {
        for (; j < firstArraySize+secondArraySize; j++)
        {
            buffer[i+j-firstArraySize]=buffer[j];
        }

    }

    else if (j == secondArraySize + firstArraySize)
    {
        for (; i < firstArraySize; i++)
        {
            buffer[i+j-firstArraySize]=firstArrayBuffer[i];
        }
    }

    delete [] firstArrayBuffer;
}

int main ()
{
    int inputSize = 0; // length of input array
    int offset = 0;    // k

    std::cin >> inputSize >> offset;
    int* buffer = new int[2*offset];

    if (inputSize < 2*offset) //the very special case
    {
        for (int i = 0; i < inputSize; i++)
        {
            std::cin >> buffer[i];
        }
        heapSort(buffer, inputSize, std::less<int>());

        for (int i = 0; i < inputSize; i++)
        {
            std::cout << buffer[i] << " ";
        }

        return 0;
    }

    for (int i=0; i < 2*offset;  i++)
    {
        std::cin >> buffer[i];
    }

    heapSort(buffer,2*offset,std::less<int>());

    for (int i=0; i < offset; i++)
    {
        std::cout << buffer[i] << " ";
    }

    int offsetsCounter = 2;

    while (offsetsCounter < inputSize / offset)
    {
        for (int i=0; i < offset ; i++) // Считываеем в первую половину.
        {
            std::cin >> buffer[i];
        }
        offsetsCounter+=1;

        heapSort(buffer,offset, std::less<int>()); // Сортируем первую половину
        merge(buffer, offset, offset); // merge'им со второй, записывая ответ в тот же буфер

        for (int i=0; i < offset; i++)
        {
            std::cout << buffer[i] << " ";
        }
    }

    if (offsetsCounter*offset == inputSize)
    {
        for (int i = offset; i < 2*offset; i++)
        {
            std::cout << buffer[i] << " ";
        }
    }
    else
    {
        int rest = inputSize%offset;
        for (int i = 0; i < rest; i++)
        {
            std::cin >> buffer[i];
        }
        heapSort(buffer, rest, std::less<int>());


        int* bufferForCopy = new int[rest];
        for (int i = 0; i < offset; i++)
        {
            if (i < rest)
            {
                bufferForCopy[i] = buffer[i];
            }

            buffer[i] = buffer[i+offset];

            if (i < rest)
            {
                buffer[i+offset] = bufferForCopy[i];
            }
        }

        delete [] bufferForCopy;
        merge(buffer, offset, rest);

        for (int i = 0; i < offset+rest; i++)
        {
            std::cout << buffer[i] << " ";
        }
    }

    delete [] buffer;
    return 0;
}
