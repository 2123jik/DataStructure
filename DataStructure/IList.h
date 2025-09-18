#ifndef ILIST_H
#define ILIST_H
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;
typedef int ElemType;

class IList {
public:
    virtual ~IList() {}

    virtual Status InitList() = 0;
    virtual void DestroyList() = 0;
    virtual void ClearList() = 0;
    virtual bool ListEmpty() const = 0;
    virtual int ListLength() const = 0;
    virtual Status Get(int i, ElemType& e) const = 0;
    virtual int LocateElem(ElemType e) const = 0;
    virtual Status PriorElem(ElemType cur_e, ElemType& pre_e) const = 0;
    virtual Status NextElem(ElemType cur_e, ElemType& next_e) const = 0;
    virtual Status Insert(int i, ElemType e) = 0;
    virtual Status Delete(int i, ElemType& e) = 0;
    virtual void Traverse() const = 0;

    // 集合运算
    virtual IList* UnionList(const IList& B) const = 0;
    virtual IList* IntersectList(const IList& B) const = 0;
    virtual IList* DifferenceList(const IList& B) const = 0;
    //virtual void Sort() = 0;
};

#endif
