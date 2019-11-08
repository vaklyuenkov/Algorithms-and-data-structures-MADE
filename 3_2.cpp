/*

Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 7.11.19

3_2. Сортировка почти упорядоченной последовательности

Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j:
если j >= i + k, то a[i] <= a[j].
Требуется отсортировать последовательность.
Последовательность может быть очень длинной.
Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

*/
#include <iostream>

// to sort we will use heap functions from my previous task
int parentPosition(int position)
{
    return (position-1)/2;
}

int lefChildPosition(int position)
{
    return (2*position+1);
}

int rightChildPosition(int position)
{
    return (2*position+2);
}

void siftUp(int *array, int position)
{
    while (position > 0 && array[parentPosition(position)] < array[position])
    {
        std::swap(array[position], array[parentPosition(position)]);
        position = parentPosition(position);
    }
}

void siftDown(int *heapArray, int heapSize,  int position)
{
    while(position*2+1 <= heapSize-1)  // check that current position could have at least one child
    {
        int left_child_position = lefChildPosition(position);
        int right_child_position = rightChildPosition(position);
        int position_of_maximum = position;

        if (left_child_position <= heapSize-1 && heapArray[left_child_position] > heapArray[position])
            position_of_maximum = left_child_position;

        if (right_child_position <= heapSize-1 && heapArray[right_child_position] > heapArray[position_of_maximum])
            position_of_maximum = right_child_position;

        if (position != position_of_maximum)
        {
            std::swap(heapArray[position], heapArray[position_of_maximum]);
            position = position_of_maximum;
        }
        else break;
    }
}

void push(int *array, int heap_size, int value)  //to build heap adding values, like we did in previous task
{
    array[heap_size - 1] = value;
    siftUp(array, heap_size - 1);
}

void sort(int *array, int arraySize) //to sort by heap
{
    for (int i=arraySize-1; i>=0; i--)
    {
        std::swap(array[0], array[i]);
        siftDown(array, i, 0);
    }
}

void merge (const int *firstArray, const int *secondArray, int *result, int firstArraySize, int secondArraySize)
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

void print(int *array, int startPosition, int endPosition)
{
    for (int i=startPosition; i < endPosition; i++)
    {
        std::cout<<array[i]<<" ";
    }
}

int main ()
{
    int inputSize = 0; // length of input array
    int offset = 0;    // k

    std::cin >> inputSize >> offset;

//    we can use this way if we are sure than offset isn`t very big. In This case we dont need `delete [] firstArray;`.
//    int firstArray[offset];
//    int secondArray[offset];
//    int mergedArray[2 * offset];

//  this way to define arrays will be twice as slower compared to `int firstArray[offset];`
//  with the same memory allocation
//  but 2*offset may be huge, so we will use dynamic array
    int* firstArray = new int[offset];
    int* secondArray = new int[offset];
    int* mergedArray = new int[2 * offset]; // we allocate memory in sum 4*k == O(k)

    int globalCounter = 0; // to store len of all data we already read
    int localCounter = 0;  // to store len of data we read in current array

    while (globalCounter < inputSize)
    {
        if (globalCounter == 0)
        {
            for (int i=0; i < offset;  i++)
            {
                int value;
                std::cin >> value;
                localCounter+=1;
                push(firstArray, localCounter, value); //build heap
                globalCounter+=1;
            }
            sort(firstArray, offset); // heap sort
        }

        localCounter=0;
        for (int i=0; i < offset && globalCounter < inputSize;  i++)
        {
            int value;
            std::cin >> value;
            localCounter+=1;
            push(secondArray, localCounter, value);  //build heap
            globalCounter+=1;
        }

        sort(secondArray, localCounter); // heap sort
        merge(firstArray, secondArray, mergedArray, offset, localCounter);
        print(mergedArray, 0, offset); //we can be sure only in first half of merged array

        for (int i=0; i < offset;  i++) //move second half of merged array to firsArray to merge with next batch of data
        {
            firstArray[i]=mergedArray[i + offset];
        }
    }

    print(mergedArray, offset, offset + localCounter); //print the rest

    delete [] firstArray;
    delete [] secondArray;
    delete [] mergedArray;

    return 0;
}