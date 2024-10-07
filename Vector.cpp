using Rank = unsigned int; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ���� 
template <typename T> class Vector { //����ģ����
protected:
    Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
    void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
    void expand(); //�ռ䲻��ʱ����
    void shrink(); //װ�����ӹ�Сʱѹ��
    bool bubble ( Rank lo, Rank hi ); //ɨ�轻��
    void bubbleSort ( Rank lo, Rank hi ); //���������㷨
    Rank maxItem ( Rank lo, Rank hi ); //ѡȡ���Ԫ��
    void selectionSort ( Rank lo, Rank hi ); //ѡ�������㷨
    void merge ( Rank lo, Rank mi, Rank hi ); //�鲢�㷨
    void mergeSort ( Rank lo, Rank hi ); //�鲢�����㷨
    void heapSort ( Rank lo, Rank hi ); //�������Ժ�����ȫ�ѽ��⣩
    Rank partition ( Rank lo, Rank hi ); //��㹹���㷨
    void quickSort ( Rank lo, Rank hi ); //���������㷨
    void shellSort ( Rank lo, Rank hi ); //ϣ�������㷨
public:
// ���췽��
    Vector ( Rank c = DEFAULT_CAPACITY ) //����Ϊc�Ŀ�����
    { _elem = new T[_capacity = c]; _size = 0; }
   Vector ( Rank c, Rank s, T v ) //����Ϊc����ģΪs������Ԫ�س�ʼΪv��s<=c
    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); }
    Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //�������帴��
    Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //����
    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //�������帴��
    Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //����
 // ��������
    ~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    Rank find ( T const& e ) const { return find ( e, 0, _size ); } //���������������
    Rank find ( T const& e, Rank lo, Rank hi ) const; //���������������
    Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //�������������ҵ���k���Ԫ��
    Rank search( T const& e ) const //���������������
    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
    Rank search ( T const& e, Rank lo, Rank hi ) const; //���������������
 // ��д���ʽӿ�
    T& operator[] ( Rank r ); //�����±������������������������ʽ���ø�Ԫ��
    const T& operator[] ( Rank r ) const; //����������ֵ�����ذ汾
    Vector<T> & operator= ( Vector<T> const& ); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    T remove ( Rank r ); //ɾ����Ϊr��Ԫ��
    Rank remove ( Rank lo, Rank hi ); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    Rank insert ( Rank r, T const& e ); //����Ԫ��
    Rank insert ( T const& e ) { return insert ( _size, e ); } //Ĭ����ΪĩԪ�ز���
    void sort ( Rank lo, Rank hi ); //��[lo, hi)����
    void sort() { sort ( 0, _size ); } //��������
    void unsort ( Rank lo, Rank hi ); //��[lo, hi)����
    void unsort() { unsort ( 0, _size ); } //��������
    Rank dedup(); //����ȥ��
   Rank uniquify(); //����ȥ��
 // ����
    void traverse ( void (* ) ( T& ) ); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> void traverse ( VST& ); //������ʹ�ú������󣬿�ȫ�����޸ģ�
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
            cout << "����Ԫ��: " << *_finish << endl;
        } else {
            cout << "����Ϊ�գ��޷�����Ԫ��." << endl;
        }
    }

    void insert(const value_type &x, const size_t &pos) {
        if (pos > size()) {
            cout << "Խ��: �޷���ָ��λ�ò���Ԫ��." << endl;
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
            cout << "Խ��: �޷�ɾ��ָ��λ�õ�Ԫ��" << endl;
        }
    }

    void Print() {
        if (empty()) {
            cout << "����Ϊ��." << endl;
            return;
        }
        cout << "����Ԫ��: ";
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
  Vector<string> ve; //Vector<string> ve; �е�string��ģ������Vector�е�Ԫ������
    cout << "��1ѹ������" << endl;
    cout << "��2��������" << endl;
    cout << "��3��������" << endl;
    cout << "��4ɾ������" << endl;
    cout << "��5�鿴��������" << endl;
    cout << "��111����" << endl;
    int a, y;
    string x;
    while (true) {
        cin >> a;
        if (a == 111) break;
        switch (a) {
            case 1:
                cout << "������Ҫѹ���Ԫ��: ";
                cin >> x;
                ve.push_back(x);
                break;
            case 2:
                cout << "������Ҫ�����Ԫ�غ�λ�� (Ԫ�� λ��): ";
                cin >> x >> y;
                ve.insert(x, y);
                break;
            case 3:
                ve.pop_back();
                break;
            case 4:
                cout << "������Ҫɾ����λ��: ";
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

