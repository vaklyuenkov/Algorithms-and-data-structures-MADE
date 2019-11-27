/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 26.11.19

8_1. Хеш-таблица

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми.
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.

Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба: g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

 Формат входных данных:
Каждая строка входных данных задает одну операцию над множеством.
Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

 Формат выходных данных:
Программа должна вывести для каждой операции одну из двух строк OK или FAIL.
Для операции '?': OK, если элемент присутствует во множестве. FAIL иначе.
Для операции '+': FAIL, если добавляемый элемент уже присутствует во множестве и потому не может быть добавлен. OK иначе.
Для операции '-': OK, если элемент


Ввод:
+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello

Вывод:
OK
OK
OK
FAIL
OK
FAIL
OK
*/

#include <iostream>
#include <cassert>
#include <vector> //in this task we can use vector according to seminar

int HornerHash(const std::string& str, int m) //let m size of buffer - buffer size is power of 2
    {
        const int a = 31;
        int hash = 0;
        for (char i : str)
        {
            hash = (hash*a + i)%m; //according to our task conditions
        }
        return hash;
    }

class HashTable
    {
        public:
            explicit HashTable(int initialSize);
            ~HashTable();
            HashTable(const HashTable&) = delete; //according to five-rule, as was said on seminar
            HashTable(HashTable&&) = delete; //according to five-rule, as was said on seminar
            HashTable& operator=(const HashTable&)=delete; //according to five-rule, as was said on seminar
            HashTable& operator=(const HashTable&&)=delete; //according to five-rule, as was said on seminar
            bool Has(const std::string& key) const;
            bool Add(const std::string& key);
            bool Remove(const std::string& key);
        private:
            int bufferSize;
            struct HashTableNode
            {
                std::string key;
                explicit HashTableNode(std::string key_) : key(std::move(key_)) {}
            };
            std::vector<HashTableNode*> buffer;
            void ReHash();
    };

HashTable::HashTable(int initialSize) : buffer(initialSize, nullptr), bufferSize(0) {}

HashTable::~HashTable()
    {
        for (int i = 0; i < (int)buffer.size(); i++)
        {
            if (buffer[i])
            {
                delete buffer[i];
            }
        }
    }

bool HashTable::Has(const std::string& key) const
    {
        assert(!key.empty());
        const int hash = HornerHash(key, buffer.size());
        if (buffer[hash] == nullptr)
        {
            return false;
        }
        else  if (buffer[hash]->key == key)
        {
            return true;
        }
        else
        {
            int probe = hash;
            for (int i = 0; i < buffer.size(); i++)
            {
                probe = (probe+i+1) % (int)buffer.size();
                if (buffer[probe] == nullptr)
                {
                    return false;
                }
                else if (buffer[probe]->key == key)
                {
                    return true;
                }
            }
            return true;
        }
    }

bool HashTable::Add(const std::string& key)
    {
        if (bufferSize*4 >=  buffer.size()*3)
        {
            ReHash();
        }
        int hash = HornerHash(key, buffer.size());
        if (buffer[hash] == nullptr)
        {
            buffer[hash] = new HashTableNode(key);
            bufferSize++;
            return true;
        }
        else
        {
            int probe = hash;
            if (buffer[hash]-> key == key)
            {
                return false;
            }
            for (size_t i = 0; i < buffer.size(); i++)
            {
                probe = (probe + i + 1) % buffer.size();
                if (buffer[probe] == nullptr)
                {
                    buffer[probe] = new HashTableNode(key);
                    bufferSize++;
                    return true;
                }
                else if (buffer[probe]-> key == key)
                {
                    return false;
                }
            }
            return false;
        }
    }

bool HashTable::Remove(const std::string& key)
    {
        const int hash = HornerHash(key, buffer.size());
        if (buffer[hash] == nullptr)
        {
            return false;
        }
        else if (buffer[hash]->key == key)
        {
            buffer[hash]->key = "";
            return true;
        }
        else
        {
            int probe = hash;
            for (size_t i = 0; i < buffer.size(); i++)
            {
                probe = (probe + i + 1) % buffer.size();
                if (buffer[probe] == nullptr)
                {
                    return false;
                }
                else if (buffer[probe]->key == key)
                {
                    buffer[probe]->key = "";
                    return true;
                }

            }
            return false;
        }
    }

void HashTable::ReHash()
    {
        std::vector<HashTableNode*> oldBuffer = buffer;
        bufferSize = 0;

        buffer.assign(oldBuffer.size() * 2, nullptr);

        for (int i = 0; i < oldBuffer.size(); i++)
        {
            if (oldBuffer[i])
            {

                if (oldBuffer[i]->key.empty())
                {
                    delete oldBuffer[i];
                }
                else
                {
                    Add(oldBuffer[i]->key);
                    bufferSize++;
                    delete oldBuffer[i];
                }
            }
        }
    }

int main()
    {
        HashTable hashTable(8);
        char command = ' ';
        std::string value;
        while (std::cin >> command >> value)
        {
            switch(command)
            {
                case '?':
                    std::cout << (hashTable.Has(value) ? "OK" : "FAIL") << std::endl;
                    break;
                case '+':
                    std::cout << (hashTable.Add(value) ? "OK" : "FAIL") << std::endl;
                    break;
                case '-':
                    std::cout << (hashTable.Remove(value) ? "OK" : "FAIL") << std::endl;
                    break;
                default:
                    break;
            }
        }
        return 0;
    }