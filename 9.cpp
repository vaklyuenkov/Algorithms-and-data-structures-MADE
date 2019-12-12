/*
Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 12.12.19

9. Алгоритм сжатия данных Хаффмана

Реализуйте алгоритм построения оптимального префиксного кода Хаффмана. При помощи алгоритма реализуйте две функции для создания архива из одного файла и извлечения файла из архива.


// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);
 где:
typedef unsigned char ourByteType;

struct IInputStream {
	// Возвращает false, если поток закончился
	bool Read(ourByteType& value) = 0;
};

struct IOutputStream {
	void Write(ourByteType value) = 0;
};

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode,
 а также включающий файл Huffman.h.
 Тестирующая программа выводит скоринг зависящий от соотношения размера сжатого файла и исходного.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <memory>

#include "Huffman.h"


// Create helpful data types
typedef unsigned char ourByteType; // Clion doesn`t allow to use "byte" overload

struct Node
    {
        ourByteType NodeValue = 0;
        int Frequency = 0;
        std::shared_ptr<Node> Left = nullptr;
        std::shared_ptr<Node> Right = nullptr;
        Node(ourByteType _nodeValue, int _frequency) : NodeValue(_nodeValue), Frequency(_frequency){}
    };

bool Comparator(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) //create comparator because it necessary practice. Instead compare right in methods as I did before
    {
        return a->Frequency > b->Frequency;
    }

void buildHuffmanTree(std::vector<std::shared_ptr<Node>>& heap, std::map<ourByteType, int> count)
    {

        for(auto iterator = count.begin(); iterator != count.end(); ++iterator)
        {
            heap.push_back(std::make_shared<Node>(iterator->first, iterator->second));
        }
        std::make_heap(heap.begin(), heap.end(), Comparator); // is it ok to use realisation of heap?

        while(heap.size() > 1) //repeat until get only one element - root of tree
        {
            pop_heap(heap.begin(), heap.end(), Comparator);
            std::shared_ptr<Node> leftTree = heap.back();
            heap.pop_back();

            pop_heap(heap.begin(), heap.end(), Comparator);
            std::shared_ptr<Node> rightTree = heap.back();
            heap.pop_back();

            std::shared_ptr<Node> treeNode = std::make_shared<Node>(0, leftTree->Frequency + rightTree->Frequency);
            treeNode->Left = leftTree;
            treeNode->Right = rightTree;

            heap.push_back(treeNode);
            push_heap(heap.begin(), heap.end(), Comparator);
        }
    }

void buildEncodeTable(std::map<ourByteType, std::string>& codeTable, std::shared_ptr<Node> root, std::string code = "")
    {
        if(root->Left == nullptr && root->Right == nullptr)
        {
            codeTable[root->NodeValue] = code;
        }
        if(root->Left != 0)
        {
            buildEncodeTable(codeTable, root->Left, code + "0");
        }
        if(root->Right != 0)
        {
            buildEncodeTable(codeTable, root->Right, code + "1");
        }
    }


void byteWritter(std::string& accumulator, ourByteType charToEncode)
    {
        int index = 0;
        std::string buffer = "";
        while(index < 8)
        {
            buffer = std::to_string(charToEncode % 2) + buffer;
            charToEncode /= 2;
            index++;
        }
        accumulator += buffer;
    }

void writeInteger(std::string& str, int x)  //write int to end of encoded message
    {
        int pos = 0;
        std::string tmp = "";
        while(pos < 32){
            tmp = std::to_string(x % 2) + tmp;
            x /= 2;
            pos++;
        }
        str += tmp;
    }

void EncodeAndWriteTree(std::shared_ptr<Node> root, std::string& encodedTree)
    {
        if(!root)
        {
            return;
        }
        if(root->Left == nullptr)
        {
            encodedTree += "0";
            byteWritter(encodedTree, root->NodeValue);
        } else {
            encodedTree += "1";
            EncodeAndWriteTree(root->Left, encodedTree);
            EncodeAndWriteTree(root->Right, encodedTree);
        }
    }


void EncodeText(std::string& compressed, std::string& original, std::map<ourByteType, std::string> encodeTable)
    {
        for(int i = 0; i < original.size(); ++i)
        {
            compressed += encodeTable[original[i]];
        }
    }


int fillStringToFullByte(std::string& original)
    {
        int num = 0;
        while(original.size() % 8 != 0)
        {
            original += "0";
            num++;
        }
        return num;
    }



void writeCompressed(IOutputStream& compressed, std::string str)
    {
        int index = 0;
        int indexByte = 0;
        ourByteType buffer = 0;

        while(index <= str.size())
        {
            if(indexByte < 8)
            {
                buffer *= 2;
                buffer += (str[index] - '0');
                index++;
                indexByte++;
            }
            else if(indexByte > 0)
            {
                compressed.Write(buffer);
                indexByte = 0;
            }
        }
    }


void writeEncodedToStream(IOutputStream& compressed, int codeTableSize, int filledBits, std::string textToEncode)
    {

        std::string dataToDecode = "";
        writeInteger(dataToDecode, codeTableSize);
        writeInteger(dataToDecode, filledBits);
        writeCompressed(compressed, dataToDecode);
        writeCompressed(compressed, textToEncode);
    }


int readIntegerFromStream(IInputStream& stream)
    {
        int decodeTableSize = 0;
        ourByteType tmp = 0;
        std::string tmpS = "";
        for(int i = 0; i < 4; ++i)
        {
            stream.Read(tmp);
            byteWritter(tmpS, tmp);
        }

        for (int i = 0; i < tmpS.size(); ++i)
        {
            decodeTableSize *= 2;
            decodeTableSize += tmpS[i] - '0';
        }

        return decodeTableSize;
    }

ourByteType readDecodeTableSize(std::string& str, int& pos)
    {
        ourByteType tmp = 0;
        int count = 0;
        while(count < 8){
            tmp *= 2;
            tmp += str[pos] - '0';
            pos++;
            count++;
        }
        return tmp;

    }


void readDecodeTable(std::string& input, std::map<std::string, ourByteType>& decodeTable, int decodeTableSize, int& index, std::string code = "")
    {
        if(index >= decodeTableSize)
        {
            return;
        }
        if(input[index] == '1')
        {
            index++;
            readDecodeTable(input, decodeTable, decodeTableSize, index, code + "0");
            readDecodeTable(input, decodeTable, decodeTableSize, index, code + "1");
        } else {
            index++;
            decodeTable[code] = readDecodeTableSize(input, index);
        }
    }



void readAndDecodeText(std::string& input, IOutputStream& decoded, std::map<std::string, ourByteType>& decodeTable, int index, int filledBits)
{
    std::string currentCode = "";
    while(index < input.size() - filledBits)
    {
        currentCode += input[index];
        if(decodeTable.find(currentCode) != decodeTable.end())
        {
            decoded.Write(decodeTable[currentCode]);
            currentCode = "";
        }
        index++;
    }

}

void Encode(IInputStream& original, IOutputStream& compressed)
    {
        std::string originalInput = "";

        std::map<ourByteType, int> frequencyDictionary;
        ourByteType buffer = 0;
        while(original.Read(buffer))
        {
            originalInput += buffer;
            frequencyDictionary[buffer]++;
        }
        std::vector<std::shared_ptr<Node>> heap;
        buildHuffmanTree(heap, frequencyDictionary);
        std::map<ourByteType, std::string> encodeTable;
        buildEncodeTable(encodeTable, heap[0]);
        std::string encoded;
        EncodeAndWriteTree(heap[0], encoded);
        int encodeTableSize = encoded.size();
        EncodeText(encoded, originalInput, encodeTable);
        int filledBits = fillStringToFullByte(encoded);
        writeEncodedToStream(compressed, encodeTableSize, filledBits, encoded);
    }

void Decode(IInputStream& compressed, IOutputStream& original)
    {

        int decodeTableSize = readIntegerFromStream(compressed);
        int filledBits = readIntegerFromStream(compressed);
        std::string compressedInput = "";
        ourByteType buffer = 0;
        while(compressed.Read(buffer))
        {
            byteWritter(compressedInput, buffer);
        }
        int index = 0;
        std::map<std::string, ourByteType> decodeTable;
        readDecodeTable(compressedInput, decodeTable, decodeTableSize, index);
        index = decodeTableSize;
        readAndDecodeText(compressedInput, original, decodeTable, index, filledBits);
    }