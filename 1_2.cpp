/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 3.11.19

1_2. Реализовать дек с динамическим зацикленным буфером.
Обрабатывать команды push * и pop *.
Формат ввода:
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
        a = 1 - push front
        a = 2 - pop front
        a = 3 - push back
        a = 4 - pop back
Если дана команда pop *, то число b - ожидаемое значение.
Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.

Требуется напечатать YES - если все ожидаемые значения совпали.
 Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

#include <iostream>
#include <cassert>
#include <deque>

class Deque
{
    public:
        Deque();

        ~Deque();
        bool empty() const;
        void pushFront(int value);
        void pushBack(int value);
        int popAndReturnFront(); //convenient interface for our task
        int popAndReturnBack(); //convenient interface for our task
        void print(); // to visualise and easy debug

    private:
        int * buffer;
        int buffer_size = 0;
        int buffer_head;
        int buffer_tail;
        int buffer_capacity;
        void recreate_buffer();
        void double_buffer();
};

Deque::Deque() // extra operation because we will recreate the buffer at the first push
{
    buffer = new int[0];
    buffer_capacity = 0;
    buffer_size = 0;
    buffer_head = 0;
    buffer_tail = 0;
}

Deque::~Deque()
{
    delete[] buffer;
}

void Deque::recreate_buffer()
{
    delete[] buffer;
    int init_buffer_size = 3;
    buffer = new int[init_buffer_size];
    buffer_capacity = init_buffer_size;
    buffer_size = 0;
    buffer_head = 0;
    buffer_tail = 1;
}

void Deque::print()
{
    for (int i = 0; i < buffer_capacity; ++i)
    {
        if (i == buffer_head)
        {
            std::cout << "[";
        }
        std::cout << " " << buffer[i];
        if (i == buffer_tail)
        {
            std::cout << " ]";
        }
    }
    std::cout << std::endl;
    std::cout << "Head position: " << buffer_head << std::endl;
    std::cout << "Tail position: " << buffer_tail << std::endl;
    std::cout << "Buffer size: " << buffer_size << std::endl;
}

void Deque::double_buffer()
{
    int new_capacity = buffer_capacity*2;
    int* tmp = new int [new_capacity];
    int old_buffer_position = buffer_head;
    for(int new_buffer_position = 0; new_buffer_position < buffer_size; new_buffer_position++)
        {
            tmp[new_buffer_position] = buffer[old_buffer_position]; //copy circle buffer to beginning of new buffer
            old_buffer_position = (old_buffer_position+1)%buffer_capacity; // iterate circle buffer
        }
    buffer_head = 0;
    buffer_tail = buffer_size;
    delete [] buffer;
    buffer = tmp;
    buffer_capacity = new_capacity;
}

bool Deque::empty() const
{
    return buffer_size == 0;
}

void Deque::pushFront(int value)
{
    if (empty()) //to avoid all situations where head == tail and for correct initial push
    {
        recreate_buffer();
        buffer[buffer_head] = value;
    }
    else
    {
        if(buffer_size + 1 == buffer_capacity)
        {
            this -> double_buffer();
        }
        if (buffer_head == 0) //special border conditions for circle buffer
        {
            buffer_head = buffer_capacity-1;
            buffer[buffer_capacity-1] = value;
        }
        else
        {
            buffer_head--;
            buffer[buffer_head] = value;
        }
    }
    buffer_size++;
}

void Deque::pushBack(int value)
{
    if (empty())  //to avoid all situations where head == tail and for correct initial push
    {
        recreate_buffer();
        buffer[buffer_head] = value;
    }
    else
    {
        if(buffer_size + 1== buffer_capacity)
        {
            this -> double_buffer();
        }
        buffer[buffer_tail] = value;
        buffer_tail = (buffer_tail + 1)%buffer_capacity; //special border conditions for circle buffer
    }
    buffer_size++;
}

int Deque::popAndReturnFront()
{
    assert(!empty());
    int result = buffer[buffer_head];
    buffer_head = (buffer_head + 1)%buffer_capacity;
    buffer_size--;
    return result;
}

int Deque::popAndReturnBack()
{
    assert(!empty());
    int result;
    if (buffer_tail == 0) //special border conditions for circle buffer
    {
        buffer_tail = buffer_capacity -1;
        result = buffer[buffer_tail];
    }
    else
    {
        buffer_tail--;
        result = buffer[buffer_tail];
    }

    buffer_size--;
    return result;
}

int main() // code from Stepan`s seminar
{
    int commands_count = 0;
    std::cin >> commands_count;
    Deque deque;
    for (int i = 0; i < commands_count; ++i) {
        //deque.print(); // for debug and visualisation
        int command = 0;
        int value = 0;
        std::cin >> command >> value;

        if (command == 1) {
            deque.pushFront(value);
        }
        else if (command == 3) {
            deque.pushBack(value);
        }
        else if (command == 2) {
            if (deque.empty()) {
                if (value != -1) {
                    std::cout << "NO";
                    return 0;
                }
            } else if (deque.popAndReturnFront() != value) {
                std::cout << "NO";
                return 0;
            }
        }
        else if (command == 4) {
            if (deque.empty()) {
                if (value != -1) {
                    std::cout << "NO";
                    return 0;
                }
            } else if (deque.popAndReturnBack() != value) {
                std::cout << "NO";
                return 0;
            }
        }
    }
    std::cout << "YES";
    return 0;
}