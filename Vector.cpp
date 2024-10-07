using Rank = unsigned int; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大） 
template <typename T> class Vector { //向量模板类
protected:
    Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
    void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble ( Rank lo, Rank hi ); //扫描交换
    void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
    Rank maxItem ( Rank lo, Rank hi ); //选取最大元素
    void selectionSort ( Rank lo, Rank hi ); //选择排序算法
    void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
    void mergeSort ( Rank lo, Rank hi ); //归并排序算法
    void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）
    Rank partition ( Rank lo, Rank hi ); //轴点构造算法
    void quickSort ( Rank lo, Rank hi ); //快速排序算法
    void shellSort ( Rank lo, Rank hi ); //希尔排序算法
public:
// 构造方法
    Vector ( Rank c = DEFAULT_CAPACITY ) //容量为c的空向量
    { _elem = new T[_capacity = c]; _size = 0; }
   Vector ( Rank c, Rank s, T v ) //容量为c、规模为s、所有元素初始为v；s<=c
    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); }
    Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
    Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
    Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
 // 析构方法
    ~Vector() { delete [] _elem; } //释放内部空间
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
    Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找
    Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //从无序向量中找到第k大的元素
    Rank search( T const& e ) const //有序向量整体查找
    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
    Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
 // 可写访问接口
    T& operator[] ( Rank r ); //重载下标操作符，可以类似于数组形式引用各元素
    const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本
    Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
    T remove ( Rank r ); //删除秩为r的元素
    Rank remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
    Rank insert ( Rank r, T const& e ); //插入元素
    Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
    void sort ( Rank lo, Rank hi ); //对[lo, hi)排序
    void sort() { sort ( 0, _size ); } //整体排序
    void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
    void unsort() { unsort ( 0, _size ); } //整体置乱
    Rank dedup(); //无序去重
   Rank uniquify(); //有序去重
 // 遍历
    void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
 }; //Vector
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

#define BEGINS(x) namespace x{
#define ENDS(x)}

template <typename T>
class Vector {
public:
    typedef T value_type;
    typedef T* iterator;

    Vector() : _start(nullptr), _finish(nullptr), _end(nullptr) {}

    size_t size() const {
        return _finish - _start;
    }

    size_t capacity() const {
        return _end - _start;
    }

    void push_back(const value_type &x) {
        if (capacity() == 0 || capacity() == size()) {
            reserve((capacity() == 0) ? 1 : capacity() * 2);
        }
        *_finish = x;
        ++_finish;
    }

    void pop_back() {
        if (!empty()) {
            --_finish;
            cout << "弹出元素: " << *_finish << endl;
        } else {
            cout << "容器为空，无法弹出元素." << endl;
        }
    }

    void insert(const value_type &x, const size_t &pos) {
        if (pos > size()) {
            cout << "越界: 无法在指定位置插入元素." << endl;
            return;
        }
        if (capacity() == 0) {
            reserve(1);
            *_finish = x;
            ++_finish;
        } else if (size() == capacity()) {
            size_t size1 = size();
            size_t cap = capacity();
            value_type* tmp = new value_type[2 * capacity()]();
            for (size_t i = 0; i < pos; i++) {
                tmp[i] = _start[i];
            }
            tmp[pos] = x;
            for (size_t i = pos; i < size1; i++) {
                tmp[i + 1] = _start[i];
            }
            delete[] _start;
            _start = tmp;
            _finish = _start + size1 + 1;
            _end = _start + 2 * cap;
        } else {
            for (int i = size(); i > pos; i--) {
                _start[i] = _start[i - 1];
            }
            _start[pos] = x;
            _finish = _start + size() + 1;
        }
    }

    void erase(const size_t &pos) {
        if (pos >= 0 && pos < size()) {
            iterator begin = _start + pos;
            while (begin != _finish) {
                *begin = *(begin + 1);
                ++begin;
            }
            --_finish;
            //--_end;
        } else {
            cout << "越界: 无法删除指定位置的元素" << endl;
        }
    }

    void Print() {
        if (empty()) {
            cout << "容器为空." << endl;
            return;
        }
        cout << "容器元素: ";
        for (size_t i = 0; i < size(); i++) {
            cout << _start[i] << "  ";
        }
        cout << endl;
    }

    void reserve(size_t newCapacity) {
        value_type* tmp = new value_type[newCapacity]();
        size_t size1 = size();
        if (_start) {
            for (size_t i = 0; i < size1; i++) {
                tmp[i] = _start[i];
            }
        }
        delete[] _start;
        _start = tmp;
        _finish = _start + size1;
        _end = _start + newCapacity;
    }

    bool empty() const {
        return _start == _finish;
    }

private:
    iterator _start;
    iterator _finish;
    iterator _end;
};


BEGINS(test3)

int main() {
  Vector<string> ve; //Vector<string> ve; 中的string是模板类型Vector中的元素类型
    cout << "按1压入数据" << endl;
    cout << "按2插入数据" << endl;
    cout << "按3弹出数据" << endl;
    cout << "按4删除数据" << endl;
    cout << "按5查看现有数据" << endl;
    cout << "按111结束" << endl;
    int a, y;
    string x;
    while (true) {
        cin >> a;
        if (a == 111) break;
        switch (a) {
            case 1:
                cout << "请输入要压入的元素: ";
                cin >> x;
                ve.push_back(x);
                break;
            case 2:
                cout << "请输入要插入的元素和位置 (元素 位置): ";
                cin >> x >> y;
                ve.insert(x, y);
                break;
            case 3:
                ve.pop_back();
                break;
            case 4:
                cout << "请输入要删除的位置: ";
                cin >> y;
                ve.erase(y);
                break;
            case 5:
                ve.Print();
                break;
        }
    }
    return 0;
}
ENDS(test3)


int main() {
    test3::main();
    return 0;
}

