/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 5.11.19

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
            int parentPosition(int position) const;     //to reuse calculations of index position
            int lefChildPosition(int position) const;   //to reuse calculations of index position
            int rightChildPosition(int position) const; //to reuse calculations of index position
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

int PriorityQueue::parentPosition(int position) const
    {
        return (position-1)/2;
    }

int PriorityQueue::lefChildPosition(int position)  const
    {
        return (2*position+1);
    }

int PriorityQueue::rightChildPosition(int position) const
    {
        return (2*position+2);
    }

void PriorityQueue::siftUp(int position)
    {
        // use while because it is more safe than recursion
        while (position > 0 && heap_array[parentPosition(position)] > heap_array[position])
        {
            std::swap(heap_array[position], heap_array[parentPosition(position)]);
            position = parentPosition(position);
        }
    }

void PriorityQueue::siftDown(int position)
    {
        // use while because it is more safe than recursion
        while(position*2+1 <= heap_size-1) // check that current position could have at least one child
        {
            int left_child_position = lefChildPosition(position);
            int right_child_position = rightChildPosition(position);
            int position_of_minimum = position;

            if (left_child_position <= heap_size-1 && heap_array[left_child_position] < heap_array[position])
                position_of_minimum = left_child_position;

            if (right_child_position <= heap_size-1 && heap_array[right_child_position] < heap_array[position_of_minimum])
                position_of_minimum = right_child_position;

            if (position != position_of_minimum)
                {
                    std::swap(heap_array[position], heap_array[position_of_minimum]);
                    position = position_of_minimum;
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