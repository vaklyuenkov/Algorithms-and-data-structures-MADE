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
void merge (const T *firstArray, const T *secondArray, T *result, int firstArraySize, int secondArraySize)
    {
        int i=0; //index of element to compare in first array
        int j=0; //index of element to compare in second array

        while (i != firstArraySize && j != secondArraySize) // to check not all values was taken from one of arrays
        {
            if (firstArray[i] < secondArray[j])
            {
                result[i+j]=firstArray[i];
                i++;
            }

            else
            {
                result[i+j]=secondArray[j];
                j++;
            }
        }

        // copy the rest of the the remaining array into the result according to the lecture
        if (i == firstArraySize)
        {
            for (; j < secondArraySize; j++)
            {
                result[i+j]=secondArray[j];
            }

        }

        else if (j == secondArraySize)
        {
            for (; i < firstArraySize; i++)
            {
                result[i+j]=firstArray[i];
            }
        }
    }

template <class T, class TLess>
std::vector <T> sortAlmostSorted(T *inputArray, int offset, int inputSize, TLess comparator)
    {
        T* firstArray = new int[offset];
        T* secondArray = new int[offset];
        T* mergedArray = new int[2 * offset]; // we allocate memory in sum 4*k == O(k)
        std::vector <T> answer;

        int globalCounter = 0; // to store len of all data we already read
        int localCounter = 0;  // to store len of data we read in current array

        while (globalCounter < inputSize)
        {
            if (globalCounter == 0)
            {
                for (int i=0; i < offset;  i++)
                {
                    firstArray[i] = inputArray[i];
                    localCounter+=1;
                    globalCounter+=1;
                }
                heapSort(firstArray, offset,comparator); // heap sort
            }

            localCounter=0;
            for (int i=0; i < offset && globalCounter < inputSize;  i++)
            {
                secondArray[i] = inputArray[globalCounter];
                localCounter+=1;
                globalCounter+=1;
            }

            heapSort(secondArray, localCounter, comparator); // heap sort
            merge(firstArray, secondArray, mergedArray, offset, localCounter);

            for (int i=0; i < offset; i++) //we can be sure only in first half of merged array
            {
                answer.push_back(mergedArray[i]);
            }

            for (int i=0; i < offset;  i++) //move second half of merged array to firsArray to merge with next batch of data
            {
                firstArray[i]=mergedArray[i + offset];
            }
        }

        for (int i=offset; i < offset + localCounter; i++) //print the rest
        {
            answer.push_back(mergedArray[i]);
        }

        delete [] firstArray;
        delete [] secondArray;
        delete [] mergedArray;

        return answer;
    }

int main ()
    {
        int inputSize = 0; // length of input array
        int offset = 0;    // k

        std::cin >> inputSize >> offset;
        int* input = new int[inputSize];
        for (int i = 0; i < inputSize; i++)
        {
            std::cin >> input[i];
        }
        std::vector <int> answer;
        answer = sortAlmostSorted(input, offset, inputSize, std::less<int>());
        for (auto element: answer)
        {
            std::cout << element << " ";
        }

        delete [] input;
        return 0;
    }
