#include <iostream>
#include <queue>
#include <stack>

using Rank = unsigned int;

#if defined(DSA_REDBLACK) //在红黑树中
#define stature(p) ((p)? (p)->height : 0) //外部节点（黑）高度为0，以上递推
#else //其余BST中
#define stature(p) ((int)((p)? (p)->height : -1)) //外部节点高度为-1，以上递推
#endif

typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色

template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //节点位置

template <typename T> struct BinNode { //二叉树节点模板类
    // 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
    T data; //数值
    BinNodePosi<T> parent, lc, rc; //父节点及左、右孩子
    Rank height; //高度（通用）
    Rank npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）

    // 构造方法
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
        BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED)
        : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)
    {
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }

    // 操作接口

    // 统计当前节点后代总数，亦即以其为根的子树的规模
    Rank size()
    {
        Rank leftSize = lc ? lc->size() : 0;
        Rank rightSize = rc ? rc->size() : 0;
        return 1 + leftSize + rightSize;
    }

    // 更新当前节点高度
    Rank updateHeight()
    {
        Rank leftHeight = stature(lc);
        Rank rightHeight = stature(rc);
        height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        return height;
    }

    // 更新当前节点及其祖先的高度
    void updateHeightAbove()
    {
        BinNodePosi<T> p = this;
        while (p) {
            p->updateHeight();
            p = p->parent;
        }
    }

    // 插入左孩子
    BinNodePosi<T> insertLc(T const& e)
    {
        lc = new BinNode<T>(e, this);
        return lc;
    }

    // 插入右孩子
    BinNodePosi<T> insertRc(T const& e)
    {
        rc = new BinNode<T>(e, this);
        return rc;
    }

    // 接入左子树
    void attachLc(BinNodePosi<T> subtree)
    {
        if (lc) delete lc;
        lc = subtree;
        if (lc) lc->parent = this;
    }

    // 接入右子树
    void attachRc(BinNodePosi<T> subtree)
    {
        if (rc) delete rc;
        rc = subtree;
        if (rc) rc->parent = this;
    }

    // 取当前节点的直接后继
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

    // 子树层次遍历
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

    // 子树先序遍历
    template <typename VST>
    void travPre(VST& visit)
    {
        visit(this->data);
        if (lc) lc->travPre(visit);
        if (rc) rc->travPre(visit);
    }

    // 子树中序遍历
    template <typename VST>
    void travIn(VST& visit)
    {
        if (lc) lc->travIn(visit);
        visit(this->data);
        if (rc) rc->travIn(visit);
    }

    // 子树后序遍历
    template <typename VST>
    void travPost(VST& visit)
    {
        if (lc) lc->travPost(visit);
        if (rc) rc->travPost(visit);
        visit(this->data);
    }

    // 比较器、判等器（各列其一，其余自行补充）
    bool operator<(BinNode const& bn) { return data < bn.data; } //小于
    bool operator==(BinNode const& bn) { return data == bn.data; } //等于
};