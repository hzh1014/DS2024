#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

// ����������ڵ�
struct BinTreeNode {
    char charValue;  // �ڵ������ַ�
    unsigned freq;  // �ַ����ֵ�Ƶ��
    BinTreeNode* left;
    BinTreeNode* right;

    BinTreeNode(char value, unsigned frequency)
        : charValue(value), freq(frequency), left(nullptr), right(nullptr) {}
};

// �ȽϺ������������ȶ���
struct Compare {
    bool operator()(BinTreeNode* l, BinTreeNode* r) {
        return l->freq > r->freq;
    }
};

// Huffman ������
class HuffmanCoding {
private:
    BinTreeNode* root;

    // �ݹ麯�������ڷ��� Huffman ����
    void assignCodes(BinTreeNode* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCode) {
        if (root == nullptr) return;
        if (root->charValue != '\0') {
            huffmanCode[root->charValue] = str;
        }
        assignCodes(root->left, str + "0", huffmanCode);
        assignCodes(root->right, str + "1", huffmanCode);
    }

public:
    HuffmanCoding() : root(nullptr) {}

    // ���� Huffman �������ɱ���
    std::unordered_map<char, std::string> encode(const std::string& text) {
        std::unordered_map<char, unsigned> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        std::priority_queue<BinTreeNode*, std::vector<BinTreeNode*>, Compare> pq;
        for (auto pair : freq) {
            pq.push(new BinTreeNode(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            BinTreeNode* left = pq.top(); pq.pop();
            BinTreeNode* right = pq.top(); pq.pop();

            BinTreeNode* sum = new BinTreeNode('\0', left->freq + right->freq);
            sum->left = left;
            sum->right = right;

            pq.push(sum);
        }

        root = pq.top();

        std::unordered_map<char, std::string> huffmanCode;
        assignCodes(root, "", huffmanCode);
        return huffmanCode;
    }

    // ���������������ͷ��ڴ�
    ~HuffmanCoding() {
        deleteTree(root);
    }

private:
    void deleteTree(BinTreeNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

int main() {
    std::string word1 = "dream";
    std::string word2 = "nation";
    HuffmanCoding huffmanCoding;

    auto huffmanCode1 = huffmanCoding.encode(word1);
    auto huffmanCode2 = huffmanCoding.encode(word2);

    std::cout << "Huffman Codes for 'dream':\n";
    for (auto pair : huffmanCode1) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    std::cout << "\nHuffman Codes for 'nation':\n";
    for (auto pair : huffmanCode2) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    return 0;
}