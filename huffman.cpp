#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Huffman���ڵ�ṹ��
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// �ȽϺ����ṹ�壬�������ȶ��е�����
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// ����Huffman��
HuffmanNode* buildHuffmanTree(const string& data) {
    // ͳ���ַ�Ƶ��
    unordered_map<char, int> freqMap;
    for (char c : data) {
        freqMap[c]++;
    }

    // �������ȶ��У���С�ѣ�
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // ��ÿ���ַ�����Ƶ����Ϊ�ڵ�������ȶ���
    for (auto& it : freqMap) {
        pq.push(new HuffmanNode(it.first, it.second));
    }

    // ����Huffman��
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

// ����Huffman����
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

// �����ݽ���Huffman����
string huffmanEncode(const string& data) {
    HuffmanNode* root = buildHuffmanTree(data);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    string encodedData;
    for (char c : data) {
        encodedData += codes[c];
    }

    // �ͷ�Huffman��ռ�õ��ڴ�
    deleteHuffmanTree(root);

    return encodedData;
}

// �ͷ�Huffman��ռ�õ��ڴ�
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

    cout << "ԭʼ����: " << data << endl;
    cout << "���������: " << encodedData << endl;

    // �ͷű����ַ���ռ�õ��ڴ�
    // ע�⣺����ʵ���ϲ�����Ҫ�ͷţ���ΪencodedData��һ���ֲ����������������ڽ���ʱ���Զ��ͷ��ڴ档

    return 0;
}