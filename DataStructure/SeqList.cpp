#include "SeqList.h"
using namespace std;

SeqList::SeqList()
    : elem(nullptr), length(0) {
    // InitList()
}
SeqList::~SeqList() { DestroyList(); }

Status SeqList::InitList() {
    elem = new ElemType[MAXSIZE];
    if (!elem) exit(OVERFLOW);
    length = 0;
    return OK;
}
void SeqList::DestroyList() {
    if (elem) {
        delete[] elem;
        elem = nullptr;
        length = 0;
    }
}
void SeqList::ClearList() {
    if (elem) {
        length = 0;
    }
}
bool SeqList::ListEmpty() const { return elem == nullptr || length == 0;  }
int SeqList::ListLength() const { return length; }

Status SeqList::Get(int i, ElemType& e) const {
    if (i < 1 || i > length) return ERROR;  // 不合理下标
    e = elem[i - 1];  // 取第 i 个元素
    return OK;
}

int SeqList::LocateElem(ElemType e) const {
    for (int i = 0; i < length; i++) {
        if (elem[i] == e) return i + 1;  // 查找成功，返回位置
    }
    return 0;  // 查找失败
}

Status SeqList::PriorElem(ElemType cur_e, ElemType& pre_e) const {
    for (int i = 1; i < length; i++) {
        if (elem[i] == cur_e) {
            pre_e = elem[i - 1];  // 返回前驱
            return OK;
        }
    }
    return ERROR; // 没找到，或者 cur_e 是第一个元素
}

Status SeqList::NextElem(ElemType cur_e, ElemType& next_e) const {
    for (int i = 0; i < length - 1; i++) {
        if (elem[i] == cur_e) {
            next_e = elem[i + 1];  // 返回后继
            return OK;
        }
    }
    return ERROR; // 没找到或 cur_e 是最后一个元素
}

Status SeqList::Insert(int i, ElemType e) {
    if (i < 1 || i > length + 1) return ERROR;   // i 不合法
    if (length == MAXSIZE) return ERROR;         // 空间已满
    for (int j = length - 1; j >= i - 1; j--) {
        elem[j + 1] = elem[j];                   // 后移元素
    }
    elem[i - 1] = e;   // 插入新元素
    ++length;          // 长度+1
    return OK;
}

Status SeqList::Delete(int i, ElemType& e) {
    if (i < 1 || i > length) return ERROR;
    e = elem[i - 1];  // 保存删除的值
    for (int j = i; j <= length - 1; j++) {
        elem[j - 1] = elem[j];
    }
    --length;
    return OK;
}

void SeqList::Traverse() const {
    for (int i = 0; i < length; i++) {
        cout << elem[i] << " ";
    }
    cout << endl;
}

// 集合运算
IList* SeqList::UnionList(const IList& B) const {
    SeqList* C = new SeqList();  // 新建一个空表
    ElemType e;

    // 先复制当前表的元素
    for (int i = 1; i <= length; i++) {
        C->Insert(i, elem[i - 1]);
    }

    // 再把 B 中不重复的元素插入
    for (int i = 1; i <= B.ListLength(); i++) {
        B.Get(i, e);
        if (!C->LocateElem(e)) {
            C->Insert(C->ListLength() + 1, e);
        }
    }
    return C;
}


IList* SeqList::IntersectList(const IList& B) const {
    SeqList* C = new SeqList();  // 新建一个空表
    ElemType e;

    // 只有当前表和 B 都有的元素才插入
    for (int i = 1; i <= length; i++) {
        e = elem[i - 1];
        if (B.LocateElem(e)) {
            C->Insert(C->ListLength() + 1, e);
        }
    }
    return C;
}


IList* SeqList::DifferenceList(const IList& B) const {
    SeqList* C = new SeqList(); 
    ElemType e;

    // 只要当前表有、B 中没有，就插入
    for (int i = 1; i <= length; i++) {
        e = elem[i - 1];
        if (!B.LocateElem(e)) {
            C->Insert(C->ListLength() + 1, e);
        }
    }
    return C;
}

