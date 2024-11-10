#include <iostream>
#include <queue>
#include <memory>

using Rank = unsigned int;

template <typename T> using BinNodePosi = BinNode<T>*;

template <typename T> struct BinNode { // �������ڵ�ģ����
    T data; // ��ֵ
    BinNodePosi<T> parent, lc, rc; // ���ڵ㼰���Һ���
    Rank height; // �߶ȣ�ͨ�ã�
    Rank npl; // Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color; // ��ɫ���������

    // ���췽��
    BinNode(T e = T(), BinNodePosi<T> p = nullptr, BinNodePosi<T> l = nullptr,
        BinNodePosi<T> r = nullptr, int h = 0, int l = 1, RBColor c = RB_RED)
        : data(e), parent(p), lc(l), rc(r), height(h), npl(l), color(c) {}

    // �����ӿ�
    Rank size() {
        Rank leftSize = lc ? lc->size() : 0;
        Rank rightSize = rc ? rc->size() : 0;
        return 1 + leftSize + rightSize;
    }

    Rank updateHeight() {
        Rank leftHeight = stature(lc);
        Rank rightHeight = stature(rc);
        height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        return height;
    }

    void updateHeightAbove() {
        BinNodePosi<T> p = this;
        while (p) {
            p->updateHeight();
            p = p->parent;
        }
    }

    BinNodePosi<T> insertLc(T const& e) {
        lc = new BinNode<T>(e, this);
        updateHeightAbove();
        return lc;
    }

    BinNodePosi<T> insertRc(T const& e) {
        rc = new BinNode<T>(e, this);
        updateHeightAbove();
        return rc;
    }

    void attachLc(BinNodePosi<T> subtree) {
        if (lc) delete lc;
        lc = subtree;
        if (lc) lc->parent = this;
        updateHeightAbove();
    }

    void attachRc(BinNodePosi<T> subtree) {
        if (rc) delete rc;
        rc = subtree;
        if (rc) rc->parent = this;
        updateHeightAbove();
    }

    BinNodePosi<T> succ() {
        BinNodePosi<T> p = this;
        if (rc) {
            p = rc;
            while (p->lc) p = p->lc;
            return p;
        }
        else {
            while (p->parent && p == p->parent->rc) p = p->parent;
            return p->parent;
        }
    }

    template <typename VST>
    void travLevel(VST& visit) {
        std::queue<BinNodePosi<T>> q;
        q.push(this);
        while (!q.empty()) {
            BinNodePosi<T> p = q.front();
            q.pop();
            visit(p->data);
            if (p->lc) q.push(p->lc);
            if (p->rc) q.push(p->rc);
        }
    }

    template <typename VST>
    void travPre(VST& visit) {
        visit(this->data);
        if (lc) lc->travPre(visit);
        if (rc) rc->travPre(visit);
    }

    template <typename VST>
    void travIn(VST& visit) {
        if (lc) lc->travIn(visit);
        visit(this->data);
        if (rc) rc->travIn(visit);
    }

    template <typename VST>
    void travPost(VST& visit) {
        if (lc) lc->travPost(visit);
        if (rc) rc->travPost(visit);
        visit(this->data);
    }

    bool operator<(BinNode const& bn) { return data < bn.data; }
    bool operator==(BinNode const& bn) { return data == bn.data; }
};

// BinTree ��Ķ��屣�ֲ��䣬������Ҫȷ�����еĹ����ӿں͸�������������ȷ�ġ�

// ...��BinTree ��Ķ��壩