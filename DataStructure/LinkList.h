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
    LNode* head;   // ͷ���ָ��
    int length;    // �����ȣ��������

public:
    // ��ʼ��������ͷ���
    Status InitList() {
        head = new LNode();  // ͷ��㲻�������
        if (!head) exit(OVERFLOW);
        head->next = nullptr;
        length = 0;
        return OK;
    }

    // ��������
    void DestroyList() {
        if (!head) return;
        ClearList();
        delete head;
        head = nullptr;
        length = 0;
    }

    // �����������ͷ���
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

    // ��λ��ȡԪ��
    Status Get(int i, ElemType& e) const {
        if (i < 1 || i > length) return ERROR;
        LNode* p = head->next;
        for (int j = 1; j < i; j++) {
            p = p->next;
        }
        e = p->data;
        return OK;
    }

    // ��ֵ���ң�����λ��
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

    // ��ǰ��
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

    // �Һ��
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

    // ��λ�ò���
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

    // ��λ��ɾ��
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

    // ����
    void Traverse() const {
        LNode* p = head->next;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    // ����
    IList* UnionList(const IList& B) const {
        LinkList* C = new LinkList();
        ElemType e;

        // ���Ƶ�ǰ����
        LNode* p = head->next;
        while (p) {
            C->Insert(C->ListLength() + 1, p->data);
            p = p->next;
        }

        // ���� B �в��ظ���Ԫ��
        for (int i = 1; i <= B.ListLength(); i++) {
            B.Get(i, e);
            if (!C->LocateElem(e)) {
                C->Insert(C->ListLength() + 1, e);
            }
        }
        return C;
    }

    // ����
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

    // �
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
