#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
// 1. ��������
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
// 2. ��������
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
// 3. ѡ������
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
// 4. �鲢�������������ϲ������������������
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
// 4. �鲢����
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
// 5. �������������������ֲ���
int partition(std::vector<int>& arr, int low, int high) {
    // ���ѡȡһ��λ�õ�Ԫ����Ϊ��׼
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
// 5. ��������
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// 6. ��������������ά����������
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
// 6. ������
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    // ��������
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
    // һ����ȡ��Ԫ�ؽ�������
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}
// ����˳������
std::vector<int> generateAscendingSequence(int size) {
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(i);
    }
    return result;
}
// ������������
std::vector<int> generateDescendingSequence(int size) {
    std::vector<int> result;
    for (int i = size - 1; i >= 0; --i) {
        result.push_back(i);
    }
    return result;
}
// �����������
std::vector<int> generateRandomSequence(int size) {
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(rand() % 1000);  // ���ɷ�Χ0��999����������ɰ��������Χ
    }
    return result;
}
// ���Ժ���������������ָ������У��������򻨷ѵ�ʱ�䣨���룩
long long testSort(void (*sortFunction)(std::vector<int>&), std::vector<int> sequence) {
    std::vector<int> arr = sequence;
    clock_t start = clock();
    sortFunction(arr);
    clock_t end = clock();
    return static_cast<long long>((end - start) * 1000.0 / CLOCKS_PER_SEC);
}
int main() {
    int sequenceSize = 10000;  // �ɵ����������д�С
    // ˳�����в���
    std::vector<int> ascendingSequence = generateAscendingSequence(sequenceSize);
    std::cout << "˳�����в��ԣ�" << std::endl;
    std::cout << "��������ʱ�䣺" << testSort(bubbleSort, ascendingSequence) << " ����" << std::endl;
    std::cout << "��������ʱ�䣺" << testSort(insertionSort, ascendingSequence) << " ����" << std::endl;
    std::cout << "ѡ������ʱ�䣺" << testSort(selectionSort, ascendingSequence) << " ����" << std::endl;
    std::vector<int> mergeSortAscending = ascendingSequence;
    std::cout << "�鲢����ʱ�䣺" << testSort([](std::vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, mergeSortAscending) << " ����" << std::endl;
    std::vector<int> quickSortAscending = ascendingSequence;
    std::cout << "��������ʱ�䣺" << testSort([](std::vector<int>& a) { quickSort(a, 0, a.size() - 1); }, quickSortAscending) << " ����" << std::endl;
    std::vector<int> heapSortAscending = ascendingSequence;
    std::cout << "������ʱ�䣺" << testSort(heapSort, heapSortAscending) << " ����" << std::endl;
    // �������в���
    std::vector<int> descendingSequence = generateDescendingSequence(sequenceSize);
    std::cout << "\n�������в��ԣ�" << std::endl;
    std::cout << "��������ʱ�䣺" << testSort(bubbleSort, descendingSequence) << " ����" << std::endl;
    std::cout << "��������ʱ�䣺" << testSort(insertionSort, descendingSequence) << " ����" << std::endl;
    std::cout << "ѡ������ʱ�䣺" << testSort(selectionSort, descendingSequence) << " ����" << std::endl;
    std::vector<int> mergeSortDescending = descendingSequence;
    std::cout << "�鲢����ʱ�䣺" << testSort([](std::vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, mergeSortDescending) << " ����" << std::endl;
    std::vector<int> quickSortDescending = descendingSequence;
    std::cout << "��������ʱ�䣺" << testSort([](std::vector<int>& a) { quickSort(a, 0, a.size() - 1); }, quickSortDescending) << " ����" << std::endl;
    std::vector<int> heapSortDescending = descendingSequence;
    std::cout << "������ʱ�䣺" << testSort(heapSort, heapSortDescending) << " ����" << std::endl;
    // ������в���
    std::vector<int> randomSequence = generateRandomSequence(sequenceSize);
    std::cout << "\n������в��ԣ�" << std::endl;
    std::cout << "��������ʱ�䣺" << testSort(bubbleSort, randomSequence) << " ����" << std::endl;
    std::cout << "��������ʱ�䣺" << testSort(insertionSort, randomSequence) << " ����" << std::endl;
    std::cout << "ѡ������ʱ�䣺" << testSort(selectionSort, randomSequence) << " ����" << std::endl;
    std::vector<int> mergeSortRandom = randomSequence;
    std::cout << "�鲢����ʱ�䣺" << testSort([](std::vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, mergeSortRandom) << " ����" << std::endl;
    std::vector<int> quickSortRandom = randomSequence;
    std::cout << "��������ʱ�䣺" << testSort([](std::vector<int>& a) { quickSort(a, 0, a.size() - 1); }, quickSortRandom) << " ����" << std::endl;
    std::vector<int> heapSortRandom = randomSequence;
    std::cout << "������ʱ�䣺" << testSort(heapSort, heapSortRandom) << " ����" << std::endl;
    return 0;
}