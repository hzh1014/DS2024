#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

// 定义二叉树节点
struct BinTreeNode {
    char charValue;  // 节点代表的字符
    unsigned freq;  // 字符出现的频率
    BinTreeNode* left;
    BinTreeNode* right;

    BinTreeNode(char value, unsigned frequency)
        : charValue(value), freq(frequency), left(nullptr), right(nullptr) {}
};

// 比较函数，用于优先队列
struct Compare {
    bool operator()(BinTreeNode* l, BinTreeNode* r) {
        return l->freq > r->freq;
    }
};

// Huffman 编码类
class HuffmanCoding {
private:
    BinTreeNode* root;

    // 递归函数，用于分配 Huffman 编码
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

    // 构建 Huffman 树并生成编码
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

    // 析构函数，用于释放内存
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