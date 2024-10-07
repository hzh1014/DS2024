#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
class Complex {
public:
    double real;
    double imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
};
// 随机生成一个无序的复数向量
std::vector<Complex> generateRandomComplexVector(int size) {
    std::vector<Complex> vec;
   
    for (int i = 0; i < size; ++i) {
        double realPart = static_cast<double>(rand()) / RAND_MAX * 10;
        double imagPart = static_cast<double>(rand()) / RAND_MAX * 10;
        vec.push_back(Complex(realPart, imagPart));
    }
    return vec;
}
// 查找复数
bool findComplex(const std::vector<Complex>& vec, const Complex& target) {
    return std::find(vec.begin(), vec.end(), target)!= vec.end();
}

// 比较函数用于排序
bool compareComplex(const Complex& a, const Complex& b) {
    double modB = b.modulus();
    if (modA!= modB) return modA < modB;
    return a.real < b.real;
}
// 起泡排序
void bubbleSort(std::vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compareComplex(vec[j], vec[j + 1])) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 归并函数
void merge(std::vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<Complex> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = vec[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = vec[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareComplex(L[i], R[j])) {
            vec[k] = L[i];
            ++i;
        } else {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        vec[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        vec[k] = R[j];
        ++j;
        ++k;
    }
}

// 归并排序
void mergeSort(std::vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// 区间查找
std::vector<Complex> rangeSearch(const std::vector<Complex>& vec, double m1, double m2) {
    std::vector<Complex> result;
    for (const Complex& c : vec) {
        double mod = c.modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    return result;
}
int main() {
    int vectorSize = 10;
    std::vector<Complex> complexVector = generateRandomComplexVector(vectorSize);

    // 置乱向量
    std::random_shuffle(complexVector.begin(), complexVector.end());
    std::cout << "After shuffling:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 查找复数
    Complex target(3, 4);
    bool found = findComplex(complexVector, target);
    std::cout << "Is " << target.real << " + " << target.imag << "i found? " << (found? "Yes" : "No") << "\n";

    // 插入复数
    complexVector.push_back(Complex(5, 6));
    std::cout << "After insertion:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 删除复数
    Complex toDelete(2, 3);
    complexVector.erase(std::remove(complexVector.begin(), complexVector.end(), toDelete), complexVector.end());
    std::cout << "After deletion:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 唯一化向量
    std::sort(complexVector.begin(), complexVector.end(), [](const Complex& a, const Complex& b) {
        if (a.real!= b.real) return a.real < b.real;
        return a.imag < b.imag;
    });
    auto it = std::unique(complexVector.begin(), complexVector.end());
    complexVector.erase(it, complexVector.end());
    std::cout << "After unique:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 排序效率比较
    std::vector<Complex> orderedVector = complexVector;
    std::vector<Complex> shuffledVector = complexVector;
    std::random_shuffle(shuffledVector.begin(), shuffledVector.end());
    std::vector<Complex> reversedVector = complexVector;
    std::reverse(reversedVector.begin(), reversedVector.end());

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    bubbleSort(orderedVector);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Bubble sort time for ordered vector: " << cpu_time_used << " seconds\n";

    start = clock();
    bubbleSort(shuffledVector);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Bubble sort time for shuffled vector: " << cpu_time_used << " seconds\n";

    start = clock();
    bubbleSort(reversedVector);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Bubble sort time for reversed vector: " << cpu_time_used << " seconds\n";

    orderedVector = complexVector;
    shuffledVector = complexVector;
    reversedVector = complexVector;

    start = clock();
    mergeSort(orderedVector, 0, orderedVector.size() - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Merge sort time for ordered vector: " << cpu_time_used << " seconds\n";

    start = clock();
    mergeSort(shuffledVector, 0, shuffledVector.size() - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Merge sort time for shuffled vector: " << cpu_time_used << " seconds\n";

    start = clock();
    mergeSort(reversedVector, 0, reversedVector.size() - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Merge sort time for reversed vector: " << cpu_time_used << " seconds\n";

    // 区间查找
    double m1 = 2.0, m2 = 5.0;
    std::vector<Complex> result = rangeSearch(orderedVector, m1, m2);
    std::cout << "Complex numbers with modulus between " << m1 << " and " << m2 << ":\n";
    for (const Complex& c : result) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    return 0;
}
