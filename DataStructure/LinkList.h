#ifndef LINKLIST_H
#define LINKLIST_H

#include "IList.h"
#include <iostream>

struct LNode {
    ElemType data;
    LNode* next;
};

class LinkList : public IList {
private:
    LNode* head;   // 头结点指针
    int length;    // 链表长度（结点数）

public:
    // 初始化：生成头结点
    Status InitList() {
        head = new LNode();  // 头结点不存放数据
        if (!head) exit(OVERFLOW);
        head->next = nullptr;
        length = 0;
        return OK;
    }

    // 销毁链表
    void DestroyList() {
        if (!head) return;
        ClearList();
        delete head;
        head = nullptr;
        length = 0;
    }

    // 清空链表但保留头结点
    void ClearList() {
        if (!head) return;
        LNode* p = head->next;
        while (p) {
            LNode* tmp = p->next;
            delete p;
            p = tmp;
        }
        head->next = nullptr;
        length = 0;
    }

    bool ListEmpty() const {
        return length == 0;
    }

    int ListLength() const {
        return length;
    }

    // 按位置取元素
    Status Get(int i, ElemType& e) const {
        if (i < 1 || i > length) return ERROR;
        LNode* p = head->next;
        for (int j = 1; j < i; j++) {
            p = p->next;
        }
        e = p->data;
        return OK;
    }

    // 按值查找，返回位置
    int LocateElem(ElemType e) const {
        LNode* p = head->next;
        int pos = 1;
        while (p) {
            if (p->data == e) return pos;
            p = p->next;
            pos++;
        }
        return 0;
    }

    // 找前驱
    Status PriorElem(ElemType cur_e, ElemType& pre_e) const {
        LNode* p = head->next;
        if (!p || !p->next) return ERROR;
        while (p->next) {
            if (p->next->data == cur_e) {
                pre_e = p->data;
                return OK;
            }
            p = p->next;
        }
        return ERROR;
    }

    // 找后继
    Status NextElem(ElemType cur_e, ElemType& next_e) const {
        LNode* p = head->next;
        while (p && p->next) {
            if (p->data == cur_e) {
                next_e = p->next->data;
                return OK;
            }
            p = p->next;
        }
        return ERROR;
    }

    // 按位置插入
    Status Insert(int i, ElemType e) {
        if (i < 1 || i > length + 1) return ERROR;
        LNode* p = head;
        for (int j = 1; j < i; j++) {
            p = p->next;
        }
        LNode* node = new LNode(e, p->next);
        p->next = node;
        ++length;
        return OK;
    }

    // 按位置删除
    Status Delete(int i, ElemType& e) {
        if (i < 1 || i > length) return ERROR;
        LNode* p = head;
        for (int j = 1; j < i; j++) {
            p = p->next;
        }
        LNode* q = p->next;
        e = q->data;
        p->next = q->next;
        delete q;
        --length;
        return OK;
    }

    // 遍历
    void Traverse() const {
        LNode* p = head->next;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    // 并集
    IList* UnionList(const IList& B) const {
        LinkList* C = new LinkList();
        ElemType e;

        // 复制当前链表
        LNode* p = head->next;
        while (p) {
            C->Insert(C->ListLength() + 1, p->data);
            p = p->next;
        }

        // 插入 B 中不重复的元素
        for (int i = 1; i <= B.ListLength(); i++) {
            B.Get(i, e);
            if (!C->LocateElem(e)) {
                C->Insert(C->ListLength() + 1, e);
            }
        }
        return C;
    }

    // 交集
    IList* IntersectList(const IList& B) const {
        LinkList* C = new LinkList();
        LNode* p = head->next;
        while (p) {
            if (B.LocateElem(p->data)) {
                C->Insert(C->ListLength() + 1, p->data);
            }
            p = p->next;
        }
        return C;
    }

    // 差集
    IList* DifferenceList(const IList& B) const {
        LinkList* C = new LinkList();
        LNode* p = head->next;
        while (p) {
            if (!B.LocateElem(p->data)) {
                C->Insert(C->ListLength() + 1, p->data);
            }
            p = p->next;
        }
        return C;
    }

};

#endif
