#ifndef LINKLIST_H
#define LINKLIST_H

#include "IList.h"
#include <iostream>

struct LNode {
    ElemType data;
    LNode* next;
    LNode(ElemType val = 0, LNode* nxt = nullptr);
};

class LinkList : public IList {
private:
    LNode* head;   // 头结点指针
    int length;    // 链表长度（结点数）

public:
    LinkList();
    ~LinkList();

    // 基本操作实现
    virtual Status InitList();
    virtual void DestroyList();
    virtual void ClearList();
    virtual bool ListEmpty() const;
    virtual int ListLength() const;
    virtual Status Get(int i, ElemType& e) const;
    virtual int LocateElem(ElemType e) const;
    virtual Status PriorElem(ElemType cur_e, ElemType& pre_e) const;
    virtual Status NextElem(ElemType cur_e, ElemType& next_e) const;
    virtual Status Insert(int i, ElemType e);
    virtual Status Delete(int i, ElemType& e);
    virtual void Traverse() const;

    // 集合运算
    virtual IList* UnionList(const IList& B) const;
    virtual IList* IntersectList(const IList& B) const;
    virtual IList* DifferenceList(const IList& B) const;
};

#endif
