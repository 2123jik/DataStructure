#include "LinkList.h"
using namespace std;

// �ڵ㹹�캯��
LNode::LNode(ElemType val, LNode* nxt)
    : data(val), next(nxt) {}

// ���� & ����
LinkList::LinkList() {
    InitList();
}

LinkList::~LinkList() {
    DestroyList();
}

// ��ʼ��������ͷ���
Status LinkList::InitList() {
    head = new LNode();  // ͷ��㲻�������
    if (!head) exit(OVERFLOW);
    head->next = nullptr;
    length = 0;
    return OK;
}

// ��������
void LinkList::DestroyList() {
    if (!head) return;
    ClearList();
    delete head;
    head = nullptr;
    length = 0;
}

// �����������ͷ���
void LinkList::ClearList() {
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

bool LinkList::ListEmpty() const {
    return length == 0;
}

int LinkList::ListLength() const {
    return length;
}

// ��λ��ȡԪ��
Status LinkList::Get(int i, ElemType& e) const {
    if (i < 1 || i > length) return ERROR;
    LNode* p = head->next;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }
    e = p->data;
    return OK;
}

// ��ֵ���ң�����λ��
int LinkList::LocateElem(ElemType e) const {
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
Status LinkList::PriorElem(ElemType cur_e, ElemType& pre_e) const {
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
Status LinkList::NextElem(ElemType cur_e, ElemType& next_e) const {
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
Status LinkList::Insert(int i, ElemType e) {
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
Status LinkList::Delete(int i, ElemType& e) {
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
void LinkList::Traverse() const {
    LNode* p = head->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// ����
IList* LinkList::UnionList(const IList& B) const {
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
IList* LinkList::IntersectList(const IList& B) const {
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
IList* LinkList::DifferenceList(const IList& B) const {
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
