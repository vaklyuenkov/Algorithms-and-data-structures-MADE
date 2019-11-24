/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 7.11.19

2_2. Старый компьютер

Для сложения чисел используется старый компьютер.

Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время,
в зависимости от порядка вычислений.

    ((1+2)+3) -> 1+2 + 3+3 = 9
    ((1+3)+2) -> 1+3 + 4+2 = 10
    ((2+3)+1) -> 2+3 + 5+1 = 11

 Требуется написать программу, которая определяет минимальное время,
достаточное для вычисления суммы заданного набора чисел.

Требуемое время работы O(n*log(n)).

Формат ввода:

Вначале вводится n (n < 100) - количество чисел.
Затем вводится n строк - значения чисел (значение каждого числа не превосходит 1 000 000 000,
сумма всех чисел не превосходит 2 * 1 000 000 000).

Формат вывода:

Натуральное число - минимальное время.
*/

#include <iostream>
#include <cassert>

class PriorityQueue
    {
        public:
            explicit PriorityQueue(int input_size);
            ~PriorityQueue();
            bool empty() const;
            int pop(); //It is convenient interface for our task - use pop with return
            void push(int value);
        private:
            int * heap_array;
            int heap_size;
            void siftDown(int position);
            void siftUp(int position);
            int getParentPosition(int position) const;     //to reuse calculations of index position
            int getLefChildPosition(int position) const;   //to reuse calculations of index position
            int getRightChildPosition(int position) const; //to reuse calculations of index position
    };

PriorityQueue::PriorityQueue(int input_size)
    {
        heap_size = 0;
        heap_array = new int[input_size];
    }

PriorityQueue::~PriorityQueue()
    {
        delete [] heap_array;
    }

bool PriorityQueue::empty() const
    {
        return heap_size == 0;
    }

int PriorityQueue::getParentPosition(int position) const
    {
        return (position-1)/2;
    }

int PriorityQueue::getLefChildPosition(int position)  const
    {
        return (2*position+1);
    }

int PriorityQueue::getRightChildPosition(int position) const
    {
        return (2*position+2);
    }

void PriorityQueue::siftUp(int position)
    {
        // use while because it is more safe than recursion
        while (position > 0 && heap_array[getParentPosition(position)] > heap_array[position])
        {
            std::swap(heap_array[position], heap_array[getParentPosition(position)]);
            position = getParentPosition(position);
        }
    }

void PriorityQueue::siftDown(int position)
    {
        // use while because it is more safe than recursion
        while(position*2+1 <= heap_size-1) // check that current position could have at least one child
        {
            int lefChildPosition = getLefChildPosition(position);
            int rightChildPosition = getRightChildPosition(position);
            int positionOfMinimum = position;

            if (lefChildPosition <= heap_size - 1 && heap_array[lefChildPosition] < heap_array[position])
                positionOfMinimum = lefChildPosition;

            if (rightChildPosition <= heap_size - 1 && heap_array[rightChildPosition] < heap_array[positionOfMinimum])
                positionOfMinimum = rightChildPosition;

            if (position != positionOfMinimum)
                {
                    std::swap(heap_array[position], heap_array[positionOfMinimum]);
                    position = positionOfMinimum;
                }
            else break;
        }
    }

int PriorityQueue::pop()
    {
        assert(!empty());
        int result = heap_array[0];
        heap_array[0] = heap_array[heap_size - 1];
        heap_size--;
        siftDown(0);
        return result;
    }

void PriorityQueue::push(int value)
    {
        heap_size++;
        heap_array[heap_size - 1] = value;
        siftUp(heap_size - 1);
    }

int main()
    {
        // read input and build MinHeap
        int input_size = 0;
        std::cin >> input_size;
        PriorityQueue priorityQueue(input_size);
        for (int i = 0; i < input_size; i++)
        {
            int value;
            std::cin >> value;
            priorityQueue.push(value);
        }

        // calculate time
        // tried to move logic of time counting to separate function but got runtime error on contest
        int result = 0;
        int sum = 0;

        while (!priorityQueue.empty())
        {
            sum = priorityQueue.pop();
            if (priorityQueue.empty()) break;
            sum += priorityQueue.pop();
            result += sum;
            if (!priorityQueue.empty())
            {
                priorityQueue.push(sum);
            }
        }

        std::cout << result;
        return 0;
    }
