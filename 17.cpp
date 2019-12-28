/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 28.12.19

Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает,
что все обычные символы совпадают с соответствующими из текста,
а вместо символа “?” в тексте встречается произвольный символ.
Гарантируется, что сам “?” в тексте не встречается.
Время работы - O(n + m + Z),
где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте. (Ахо-Корасик)

m ≤ 5000, n ≤ 2000000. Время: 10с, память 32Mb.

Формат входного файла:

Шаблон, символ перевода строки, строка.

Формат выходного файла:

Позиции вхождения шаблона в строке.

stdin:

ab??aba
ababacaba

stdout:

2

*/

#include <iostream>
#include <string>
#include <vector>


struct BorNode
    {
    // we will store all nodes in vector. Is it necessary to rewrite with pointers?
        explicit BorNode(int alphabetSize) : IsTerminal(false), Parent(0), StateByChar(0), SuffixLink(-1), UpSuffixsLink(-1)
        {
            NextStates.assign(alphabetSize, -1);
            DeltaFunction.assign(alphabetSize, -1);
        };
        bool IsTerminal;
        int Parent;
        int StateByChar;
        int SuffixLink;
        int UpSuffixsLink;
        std::vector<int> NextStates;
        std::vector<int> DeltaFunction;
        std::vector<int> Lines;
    };

class Trie
    {
        public:
            Trie();
            ~Trie() = default; // we dont need to delete our tree in destructor if store in vector
            Trie(const Trie&) = delete; // according to five-rule
            Trie(Trie&&) = delete;
            Trie& operator=(const Trie&) = delete;
            Trie& operator=(Trie&&) = delete;

            void build(const std::string & pattern);
            void find(const std::string& text);
            std::vector<int> getAnswer();

        private:
            const int  alphabetSize = 26;
            int patternSize;
            unsigned int lastState;
            std::vector <std::string> string_vector;
            std::vector <int> starts;
            std::vector<BorNode> nodes;
            std::vector<int> answer;

            void preprocessPattern(const std::string & pattern);
            void addString(const std::string & string, int index);
            int getSuffixLink(int state);
            int getUpLink(int state);
            int getDelta(int state, int stateByChar);
    };

Trie::Trie()
    {
        BorNode root(alphabetSize);
        nodes.push_back(root);
        lastState = 1;
    }

void Trie::build(const std::string & pattern)
    {
        patternSize = pattern.length();
        preprocessPattern(pattern);
        for (int index = 0; index < string_vector.size(); ++index)
        {
            addString(string_vector[index], index);
        }
    }

void Trie::find(const std::string &text)
    {
        int position = 0;
        std::vector<int> solver(text.length());

        for (int currentChar = 0; currentChar < text.length(); ++currentChar)
        {
            auto t = static_cast<int> (text[currentChar] - 'a');
            position = getDelta(position, t);

            int currentPosition = position;
            while (currentPosition != 0)
            {
                if (nodes[currentPosition].IsTerminal)
                {
                    for (int line : nodes[currentPosition].Lines)
                    {
                        if (currentChar - line + 1 >= 0)
                        {
                            solver[currentChar - line + 1]++;
                        }
                    }
                }
                currentPosition = getUpLink(currentPosition);
            }
        }

        for (int j = 0; j < solver.size() - patternSize + 1; ++j)
        {
            if (solver[j] == string_vector.size())
                answer.push_back(j);
        }
    }

void Trie::preprocessPattern(const std::string &pattern)
    {
        int position = 0;
        while (position < patternSize)
        {
            std::string current;
            while (pattern[position] == '?' && position < patternSize)
                ++position;
            if (position < pattern.length())
            {
                while (pattern[position] != '?' && position < patternSize)
                {
                    current += pattern[position];
                    position++;
                }
                string_vector.push_back(current);
                starts.push_back(position);
            }
        }
    }

void Trie::addString(const std::string &string, int index)
    {
        int state = 0;
        for (char character : string)
        {
            int temporary_state;
            temporary_state = static_cast<int>(character - 'a');
            if (nodes[state].NextStates[temporary_state] == -1)
            {
                BorNode node(alphabetSize);
                node.SuffixLink = -1;
                node.Parent = state;
                node.StateByChar = temporary_state;
                nodes[state].NextStates[temporary_state] = lastState;
                nodes.push_back(node);
                lastState++;
            }

            state = nodes[state].NextStates[temporary_state];
        }
        nodes[state].IsTerminal = true;
        nodes[state].Lines.push_back(starts[index]);
    }

int Trie::getSuffixLink(int state)
    {
        if (nodes[state].SuffixLink == -1)
        {
            int par = nodes[state].Parent, sbc = nodes[state].StateByChar;
            if (state == 0 || par == 0)
            {
                nodes[state].SuffixLink = 0;
            }
            else
            {
                nodes[state].SuffixLink = getDelta(getSuffixLink(par), sbc);
            }
        }
        return nodes[state].SuffixLink;
    }

int Trie::getDelta(int state, int stateByChar)
    {
        if (nodes[state].DeltaFunction[stateByChar] == -1)
            if (nodes[state].NextStates[stateByChar] != -1)
            {
                nodes[state].DeltaFunction[stateByChar] = nodes[state].NextStates[stateByChar];
            }
        else
            {
                nodes[state].DeltaFunction[stateByChar] = (state == 0) ? 0 : getDelta(getSuffixLink(state), stateByChar);
            }

        return nodes[state].DeltaFunction[stateByChar];
    }

int Trie::getUpLink(int state)
    {
        if (nodes[state].UpSuffixsLink == -1)
        {
            int currentState = getSuffixLink(state);
            if (nodes[currentState].IsTerminal)
            {
                nodes[state].UpSuffixsLink = currentState;
            }
            else
            {
                nodes[state].UpSuffixsLink = currentState == 0 ? 0 : getUpLink(currentState);
            }
        }

        return  nodes[state].UpSuffixsLink;
    }

std::vector<int> Trie::getAnswer()
    {
        return answer;
    }

int main()
    {
        Trie trie;
        std::string pattern;
        std::cin >> pattern;
        std::string text;
        std::cin >> text;

        if(pattern.size() > text.size())
        {
            return 0;
        }
        std::vector <int> result;
        trie.build(pattern);
        trie.find(text);
        result = trie.getAnswer();
        for (auto position: result)
        {
            std::cout << position << " ";
        }
        return 0;
    }