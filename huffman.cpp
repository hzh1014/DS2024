#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Huffman树节点结构体
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// 比较函数结构体，用于优先队列的排序
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// 生成Huffman树
HuffmanNode* buildHuffmanTree(const string& data) {
    // 统计字符频率
    unordered_map<char, int> freqMap;
    for (char c : data) {
        freqMap[c]++;
    }

    // 创建优先队列（最小堆）
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // 将每个字符及其频率作为节点放入优先队列
    for (auto& it : freqMap) {
        pq.push(new HuffmanNode(it.first, it.second));
    }

    // 构建Huffman树
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.empty() ? nullptr : pq.top();
}

// 生成Huffman编码
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        codes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", codes);
    generateHuffmanCodes(root->right, code + "1", codes);
}

// 对数据进行Huffman编码
string huffmanEncode(const string& data) {
    HuffmanNode* root = buildHuffmanTree(data);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    string encodedData;
    for (char c : data) {
        encodedData += codes[c];
    }

    // 释放Huffman树占用的内存
    deleteHuffmanTree(root);

    return encodedData;
}

// 释放Huffman树占用的内存
void deleteHuffmanTree(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteHuffmanTree(node->left);
    deleteHuffmanTree(node->right);
    delete node;
}

int main() {
    string data = "hello world";
    string encodedData = huffmanEncode(data);

    cout << "原始数据: " << data << endl;
    cout << "编码后数据: " << encodedData << endl;

    // 释放编码字符串占用的内存
    // 注意：这里实际上并不需要释放，因为encodedData是一个局部变量，其生命周期结束时会自动释放内存。

    return 0;
}