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


struct HornerHash
    {
        int operator()(const std::string& str, int m)
        {
            int hash = 0;
            const int a = 31;
            for (char i : str) {
                hash = (hash*a + i) % m; //according to our task conditions

            }
            return hash;
        }
    };

template <class T, class THashFunction>
class HashTable
    {
        public:
            explicit HashTable(int initialSize, T initEmptyValue, T initDeletedValue);
            ~HashTable() = default;
            HashTable(const HashTable&) = delete; //according to five-rule, as was said on seminar
            HashTable(HashTable&&) = delete; //according to five-rule, as was said on seminar
            HashTable& operator=(const HashTable&)=delete; //according to five-rule, as was said on seminar
            HashTable& operator=(const HashTable&&)=delete; //according to five-rule, as was said on seminar
            bool Has(const T& key) const;
            bool Add(const T& key);
            bool Remove(const T& key);
        private:
            int bufferSize;
            T deletedValue;
            T emptyValue;
            std::vector<T> buffer;
            void ReHash();
    };

template <class T, class THashFunction>
HashTable<T, THashFunction>::HashTable(int initialSize,  T initEmptyValue, T initDeletedValue)
{
    emptyValue = initEmptyValue;
    deletedValue = initDeletedValue;
    buffer = std::vector<T>(initialSize, emptyValue);
}

template <class T, class THashFunction>
bool HashTable<T, THashFunction>::Has(const T& key) const
    {
        assert(!key.empty());

        THashFunction hashFunction;
        int index = 0;
        int hash = hashFunction(key, buffer.size());

        while (buffer[hash] != emptyValue && buffer[hash] != deletedValue)
        {
            if (buffer[hash] == key)
            {
                return true;
            }
            index++;
            hash = (hash + index + 1) % buffer.size();
        }

        return false;
    }

template <class T, class THashFunction>
bool HashTable<T, THashFunction>::Add(const T& key)
    {
        assert(key != emptyValue);
        if (key == deletedValue)
            return false;

        THashFunction hashFunction;
        if (bufferSize*4 >=  buffer.size()*3)
        {
            ReHash();
        }

        int hash = hashFunction(key, buffer.size());
        int  index = 0;
        int flag = false;
        while (index < buffer.size())
        {

            if (buffer[hash] == emptyValue)
            {
                buffer[hash] = key;
                bufferSize++;
                return true;
            }
            if (buffer[hash] == key)
            {
                return false;
            }

            if (buffer[hash] == deletedValue && !flag)
            {
                flag = true;
            }

            index++;
            hash = (hash+index+1)%buffer.size();
        }

        if (flag)
        {
            buffer[hash] = key;
            bufferSize++;
            return true;
        }

        return false;
    }

template <class T, class THashFunction>
bool HashTable<T, THashFunction>::Remove(const T& key)
    {
        assert(key != emptyValue);
        THashFunction hashFunction;
        if (key == deletedValue)
        {
            return false;
        }

        int hash = hashFunction(key, buffer.size());
        int index = 0;

        while (buffer[hash] != emptyValue)
        {
            if (buffer[hash] == key)
            {
                buffer[hash] = deletedValue;
                bufferSize--;
                return true;
            }
            index++;
            hash = (hash+index+1)%buffer.size();
        }

        return false;
    }

template <class T, class THashFunction>
void HashTable<T, THashFunction>::ReHash()
    {
        std::vector<T> oldBuffer = buffer;
        bufferSize = 0;
        buffer.assign(oldBuffer.size() * 2, nullptr);

        for (int i = 0; i < oldBuffer.size(); i++)
        {
            if (oldBuffer[i] != deletedValue && oldBuffer[i] != emptyValue)
            {
                    Add(oldBuffer[i]);
                    bufferSize++;
            }
        }
    }

int main()
    {
        HashTable<std::string, HornerHash>  hashTable(8, "", "_deleted_");
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
