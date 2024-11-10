#include <iostream>
#include <cstring>
#include <cstdio>

typedef unsigned int Rank;

class Bitmap {
private:
    unsigned char* M;
    Rank N, _sz;

protected:
    void init(Rank n) {
        N = (n + 7) / 8;
        M = new unsigned char[N];
        std::memset(M, 0, N);
        _sz = 0;
    }

    void expand(Rank k) {
        if (k >= N * 8) {
            Rank oldN = N;
            unsigned char* oldM = M;

            N = (k + 7) / 8;
            M = new unsigned char[N];
            std::memcpy(M, oldM, oldN);
            delete[] oldM;
        }
    }

public:
    Bitmap(Rank n = 8) {
        init(n);
    }

    Bitmap(char* file, Rank n = 8) {
        init(n);

        FILE* fp = fopen(file, "r");
        if (fp == nullptr) {
            std::cerr << "无法打开文件: " << file << std::endl;
            return;
        }

        if (fread(M, sizeof(char), N, fp) != N) {
            std::cerr << "从文件读取位图数据时出错" << std::endl;
        }

        fclose(fp);

        for (Rank k = 0, _sz = 0; k < n; k++) {
            _sz += test(k);
        }
    }

    ~Bitmap() {
        delete[] M;
        M = nullptr;
        _sz = 0;
    }

    Rank size() {
        return _sz;
    }

    void set(Rank k) {
        expand(k);
        M[k >> 3] |= (0x80 >> (k & 0x07));
        _sz++;
    }

    void clear(Rank k) {
        expand(k);
        M[k >> 3] &= ~(0x80 >> (k & 0x07));
        _sz--;
    }

    bool test(Rank k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }

    void dump(char* file) {
        FILE* fp = fopen(file, "w");
        if (fp == nullptr) {
            std::cerr << "无法打开文件: " << file << std::endl;
            return;
        }

        if (fwrite(M, sizeof(char), N, fp) != N) {
            std::cerr << "将位图数据写入文件时出错" << std::endl;
        }

        fclose(fp);
    }

    char* bits2string(Rank n) {
        if (n > _sz) n = _sz;
        char* s = new char[n + 1];
        s[n] = '\0';

        for (Rank i = 0; i < n; i++) {
            s[i] = test(i) ? '1' : '0';
        }

        return s;
    }
};

class HuffCode {
public:
    HuffCode(const std::string& binaryCode) {
        for (size_t i = 0; i < binaryCode.size(); ++i) {
            bitmap.set(i, binaryCode[i] == '1');
        }
    }

    HuffCode() {}

    std::string toBinaryString() const {
        std::string result;
        for (int i = 0; i < bitmap.size(); ++i) {
            result += bitmap.test(i) ? '1' : '0';
        }
        return result;
    }

    const Bitmap& getBitmap() const {
        return bitmap;
    }

private:
    Bitmap bitmap;
};
