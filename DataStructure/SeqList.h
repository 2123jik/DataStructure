#ifndef SEQLIST_H
#define SEQLIST_H

#include "IList.h"
#include <iostream>

const int MAXSIZE = 100;

class SeqList : public IList {
private:
    ElemType* elem;
    int length;

public:
    SeqList();
    ~SeqList();

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
	//virtual void Sort();
};

#endif
