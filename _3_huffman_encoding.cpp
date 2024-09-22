#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset> // Include bitset for binary conversion

using namespace std;

// Huffman Tree Node
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) 
    {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }

    ~HuffmanNode() 
    {
        delete left;
        delete right;
    }
};

// Comparator for priority quese as we need min heap
struct compare
{
    bool operator()(HuffmanNode* left, HuffmanNode* right)
    {
        return (left->freq > right->freq);
    }
};

// printing Huffman codes
void printCode(HuffmanNode* root, string str, unordered_map<char, string> &huffmanCode)
{
    if(!root)
    {
        return;
    }

    if(!root->left && !root->right) // leaf node
    {
        huffmanCode[root->data] = str;
    }

    printCode(root->left , str+="0" , huffmanCode);
    printCode(root->right , str+="1" , huffmanCode);
}

// Building Huffman Tree
void buildHuffmanTree(string text)
{
    if (text.empty()) return; // Handle empty string

    // Calculate frequency of characters
    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    // Priority queue (min-heap) to store live nodes of Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;

    for(auto pair : freq)
    {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Merge nodes to build the Huffman Tree
    while(minHeap.size() != 1)
    {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* top = new HuffmanNode('$' , left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    HuffmanNode* root = minHeap.top();

    unordered_map<char, string> huffmanCode;
    printCode(root, "", huffmanCode);

    cout << "Huffman codes are: " << endl;
    for(auto pair : huffmanCode)
    {
        cout << pair.first << " => " << pair.second << endl;
    }

    cout << "-------------------------------------------------------------------" << endl;

    // compress the input string
    string compressedString = "";
    for(char ch : text)
    {
        compressedString += huffmanCode[ch];
    }

    cout << "Compressed String: " << compressedString << endl;

    // Free memory
    delete root; // Deletes the entire tree

}

// Print original string in binary
void printBinary(const string& text) {
    cout << "Original String in Binary: ";
    for (char ch : text) {
        cout << bitset<8>(ch); // Convert each character to binary
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    string text;
    cout << "Enter the String: " ;
    getline(cin, text);

    // cout << "-------------------------------------------------------------------" << endl;

    // printBinary(text);

    // cout << "-------------------------------------------------------------------" << endl;

    buildHuffmanTree(text);

    // cout << "-------------------------------------------------------------------" << endl;
    return 0;
}
