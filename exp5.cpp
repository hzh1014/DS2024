#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
// 1. 起泡排序
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
// 2. 插入排序
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
// 3. 选择排序
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}
// 4. 归并排序辅助函数，合并两个已排序的子数组
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// 4. 归并排序
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
// 5. 快速排序辅助函数，划分操作
int partition(std::vector<int>& arr, int low, int high) {
    // 随机选取一个位置的元素作为基准
    int randomIndex = low + rand() % (high - low + 1);
    std::swap(arr[randomIndex], arr[high]);
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
// 5. 快速排序
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// 6. 堆排序辅助函数，维护最大堆性质
void maxHeapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}
// 6. 堆排序
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
    // 一个个取出元素进行排序
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}
// 生成顺序序列
std::vector<int> generateAscendingSequence(int size) {
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(i);
    }
    return result;
}
// 生成逆序序列
std::vector<int> generateDescendingSequence(int size) {
    std::vector<int> result;
    for (int i = size - 1; i >= 0; --i) {
        result.push_back(i);
    }
    return result;
}
// 生成随机序列
std::vector<int> generateRandomSequence(int size) {
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(rand() % 1000);  // 生成范围0到999的随机数，可按需调整范围
    }
    return result;
}
// 测试函数，传入排序函数指针和序列，返回排序花费的时间（毫秒）
long long testSort(void (*sortFunction)(std::vector<int>&), std::vector<int> sequence) {
    std::vector<int> arr = sequence;
    clock_t start = clock();
    sortFunction(arr);
    clock_t end = clock();
    return static_cast<long long>((end - start) * 1000.0 / CLOCKS_PER_SEC);
}
int main() {
    int sequenceSize = 10000;  // 可调整测试序列大小
    // 顺序序列测试
    std::vector<int> ascendingSequence = generateAscendingSequence(sequenceSize);
    std::cout << "顺序序列测试：" << std::endl;
    std::cout << "起泡排序时间：" << testSort(bubbleSort, ascendingSequence) << " 毫秒" << std::endl;
    std::cout << "插入排序时间：" << testSort(insertionSort, ascendingSequence) << " 毫秒" << std::endl;
    std::cout << "选择排序时间：" << testSort(selectionSort, ascendingSequence) << " 毫秒" << std::endl;
    std::vector<int> mergeSortAscending = ascendingSequence;
    std::cout << "归并排序时间：" << testSort([](std::vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, mergeSortAscending) << " 毫秒" << std::endl;
    std::vector<int> quickSortAscending = ascendingSequence;
    std::cout << "快速排序时间：" << testSort([](std::vector<int>& a) { quickSort(a, 0, a.size() - 1); }, quickSortAscending) << " 毫秒" << std::endl;
    std::vector<int> heapSortAscending = ascendingSequence;
    std::cout << "堆排序时间：" << testSort(heapSort, heapSortAscending) << " 毫秒" << std::endl;
    // 逆序序列测试
    std::vector<int> descendingSequence = generateDescendingSequence(sequenceSize);
    std::cout << "\n逆序序列测试：" << std::endl;
    std::cout << "起泡排序时间：" << testSort(bubbleSort, descendingSequence) << " 毫秒" << std::endl;
    std::cout << "插入排序时间：" << testSort(insertionSort, descendingSequence) << " 毫秒" << std::endl;
    std::cout << "选择排序时间：" << testSort(selectionSort, descendingSequence) << " 毫秒" << std::endl;
    std::vector<int> mergeSortDescending = descendingSequence;
    std::cout << "归并排序时间：" << testSort([](std::vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, mergeSortDescending) << " 毫秒" << std::endl;
    std::vector<int> quickSortDescending = descendingSequence;
    std::cout << "快速排序时间：" << testSort([](std::vector<int>& a) { quickSort(a, 0, a.size() - 1); }, quickSortDescending) << " 毫秒" << std::endl;
    std::vector<int> heapSortDescending = descendingSequence;
    std::cout << "堆排序时间：" << testSort(heapSort, heapSortDescending) << " 毫秒" << std::endl;
    // 随机序列测试
    std::vector<int> randomSequence = generateRandomSequence(sequenceSize);
    std::cout << "\n随机序列测试：" << std::endl;
    std::cout << "起泡排序时间：" << testSort(bubbleSort, randomSequence) << " 毫秒" << std::endl;
    std::cout << "插入排序时间：" << testSort(insertionSort, randomSequence) << " 毫秒" << std::endl;
    std::cout << "选择排序时间：" << testSort(selectionSort, randomSequence) << " 毫秒" << std::endl;
    std::vector<int> mergeSortRandom = randomSequence;
    std::cout << "归并排序时间：" << testSort([](std::vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, mergeSortRandom) << " 毫秒" << std::endl;
    std::vector<int> quickSortRandom = randomSequence;
    std::cout << "快速排序时间：" << testSort([](std::vector<int>& a) { quickSort(a, 0, a.size() - 1); }, quickSortRandom) << " 毫秒" << std::endl;
    std::vector<int> heapSortRandom = randomSequence;
    std::cout << "堆排序时间：" << testSort(heapSort, heapSortRandom) << " 毫秒" << std::endl;
    return 0;
}