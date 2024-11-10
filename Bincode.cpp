#include <iostream>
#include <queue>
#include <stack>

using Rank = unsigned int;

#if defined(DSA_REDBLACK) //�ں������
#define stature(p) ((p)? (p)->height : 0) //�ⲿ�ڵ㣨�ڣ��߶�Ϊ0�����ϵ���
#else //����BST��
#define stature(p) ((int)((p)? (p)->height : -1)) //�ⲿ�ڵ�߶�Ϊ-1�����ϵ���
#endif

typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ

template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��

template <typename T> struct BinNode { //�������ڵ�ģ����
    // ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
    T data; //��ֵ
    BinNodePosi<T> parent, lc, rc; //���ڵ㼰���Һ���
    Rank height; //�߶ȣ�ͨ�ã�
    Rank npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color; //��ɫ���������

    // ���췽��
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
        BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED)
        : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)
    {
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }

    // �����ӿ�

    // ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
    Rank size()
    {
        Rank leftSize = lc ? lc->size() : 0;
        Rank rightSize = rc ? rc->size() : 0;
        return 1 + leftSize + rightSize;
    }

    // ���µ�ǰ�ڵ�߶�
    Rank updateHeight()
    {
        Rank leftHeight = stature(lc);
        Rank rightHeight = stature(rc);
        height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        return height;
    }

    // ���µ�ǰ�ڵ㼰�����ȵĸ߶�
    void updateHeightAbove()
    {
        BinNodePosi<T> p = this;
        while (p) {
            p->updateHeight();
            p = p->parent;
        }
    }

    // ��������
    BinNodePosi<T> insertLc(T const& e)
    {
        lc = new BinNode<T>(e, this);
        return lc;
    }

    // �����Һ���
    BinNodePosi<T> insertRc(T const& e)
    {
        rc = new BinNode<T>(e, this);
        return rc;
    }

    // ����������
    void attachLc(BinNodePosi<T> subtree)
    {
        if (lc) delete lc;
        lc = subtree;
        if (lc) lc->parent = this;
    }

    // ����������
    void attachRc(BinNodePosi<T> subtree)
    {
        if (rc) delete rc;
        rc = subtree;
        if (rc) rc->parent = this;
    }

    // ȡ��ǰ�ڵ��ֱ�Ӻ��
    BinNodePosi<T> succ()
    {
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

    // ������α���
    template <typename VST>
    void travLevel(VST& visit)
    {
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

    // �����������
    template <typename VST>
    void travPre(VST& visit)
    {
        visit(this->data);
        if (lc) lc->travPre(visit);
        if (rc) rc->travPre(visit);
    }

    // �����������
    template <typename VST>
    void travIn(VST& visit)
    {
        if (lc) lc->travIn(visit);
        visit(this->data);
        if (rc) rc->travIn(visit);
    }

    // �����������
    template <typename VST>
    void travPost(VST& visit)
    {
        if (lc) lc->travPost(visit);
        if (rc) rc->travPost(visit);
        visit(this->data);
    }

    // �Ƚ������е�����������һ���������в��䣩
    bool operator<(BinNode const& bn) { return data < bn.data; } //С��
    bool operator==(BinNode const& bn) { return data == bn.data; } //����
};