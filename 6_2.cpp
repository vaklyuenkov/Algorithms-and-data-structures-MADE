/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 20.11.19

6_2. Обход дерева в порядке in-order

Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.

Выведите элементы в порядке in-order (слева направо).

Рекурсия запрещена.

Пример ввода-выода:

Ввод:
 10
9 10 4 3 2 7 8 5 1 6

Вывод:
1 2 3 4 5 6 7 8 9 10

*/
#include <iostream>
#include <vector>
#include <functional>


template <class T>
class BinaryTree
    {
        public:
            BinaryTree(){};
            ~BinaryTree();
            BinaryTree(const BinaryTree&) = delete; // five-rule
            BinaryTree(BinaryTree&&) = delete;
            BinaryTree& operator=(const BinaryTree&) = delete;
            BinaryTree& operator=(BinaryTree&&) = delete;

            void Add(T value);
            std::vector <T> GetAnswer();

        private:
            struct TreeNode
            {
                explicit TreeNode(T _value) : value(_value) {}

                int value = 0;
                TreeNode* Left = nullptr;
                TreeNode* Right = nullptr;
                TreeNode* Parent = nullptr; //need for in-order and post-order
            };
            std::vector <T> answer;

            TreeNode* root = nullptr;
            void InOrder(void (visit)(TreeNode*, std::vector<T>&));
    };


template <class T>
std::vector <T> BinaryTree<T>::GetAnswer()
{
    InOrder([](TreeNode* node, std::vector <T> &answer)
            {
                answer.push_back(node->value);
            });

    return answer;
}

template <class T>
BinaryTree<T>::~BinaryTree()
    {
        InOrder([](TreeNode* node, std::vector <T> &answer){delete node;});
    }

template <class T>
void BinaryTree<T>::InOrder(void (visit)(TreeNode*, std::vector<T>&))
    {
        // implementing in-order to print whole Binary Tree
        // almost hte same as in post-order in destructor, except we print in case 1 (went from left TreeNode)
        if (root == nullptr) return;
        TreeNode* currentNode = root;
        TreeNode* leftNode = nullptr;
        TreeNode* rightNode = nullptr;
        TreeNode* parentNode = nullptr;
        // we will use this variable to store state
        int state = 0;
        // 0 went down in child treeNode
        // 1 went from left TreeNode
        // 2 went from right TreeNode

        while (currentNode != root || state != 2)
        {
            switch (state)
            {
                case 0:
                {
                    leftNode = currentNode->Left;
                    if (leftNode != nullptr)
                    {
                        currentNode = leftNode;
                        state = 0;
                    }
                    else
                    {
                        state = 1;
                    }
                }
                break;

                case 1:
                 {
                     visit(currentNode, answer);
                     rightNode = currentNode->Right;
                    if (rightNode != nullptr)
                    {
                        currentNode = rightNode;
                        state = 0;
                    }
                    else
                    {
                        state = 2;
                    }
                }
                break;

                case 2:
                {
                    parentNode = currentNode->Parent;
                    if (currentNode == parentNode->Left)
                    {
                        state = 1;
                    }
                    else
                    {
                        state = 2;
                    }
                    currentNode = parentNode;
                }
                break;
            }
        }
    }

template <class T>
void BinaryTree<T>::Add(T value)
    {
        TreeNode* newTreeNode = new TreeNode(value);
        TreeNode* parentForValue = nullptr;
        TreeNode* parentCandidate = root;

        while (parentCandidate != nullptr) // go through binary tree to find parent for future TreeNode for value to add
        {
            parentForValue = parentCandidate;
            if (parentCandidate->value <= value) // according to our task conditions
            {
                parentCandidate = parentCandidate->Right;
            }
            else
            {
                parentCandidate = parentCandidate->Left;
            }
        }

        if (parentForValue == nullptr) // we have no root and need to create
        {
            root = newTreeNode;
        }
        else if (newTreeNode->value >= parentForValue->value) // add new node with value according to our task conditions
        {
            parentForValue->Right = newTreeNode;
            newTreeNode->Parent = parentForValue;
        }
        else
        {
            parentForValue->Left = newTreeNode;
            newTreeNode->Parent = parentForValue;
        }
    }


int main()
    {
        // read input and build BinaryTree
        int input_size = 0;
        std::cin >> input_size;

        std::vector <int> answer;
        BinaryTree<int> tree;

        for (int i = 0; i < input_size; i++)
        {
            int value;
            std::cin >> value;
            tree.Add(value);
        }

        answer = tree.GetAnswer();

        for (auto result: answer)
        {
            std::cout <<  result << " ";
        }


        return 0;
    }

