#include <iostream>
#include "SeqList.h"
#include "LinkList.h"
using namespace std;

void menu() {
    cout << "\n==== 线性表操作菜单 ====\n";
    cout << "1. 初始化。2.按位置插入。3.按位置删除。";
    cout << "4. 显示表。5. 判空。6. 求长度。";
    cout << "7. 按位置拿。8. 定位。9. 拿前驱。";
    cout << "10. 拿后继。11. 清空。12. 销毁。";
    cout << "13. 并集。14. 交集。15. 差集。";
    cout << "0. 退出\n========================\n";
}

void inputList(IList* B) {
    B->InitList();
    int n, val;
    cout << "请输入集合 B 的元素个数: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "请输入第 " << i << " 个元素: ";
        cin >> val;
        B->Insert(i, val);
    }
}

int main() {
    int implChoice;
    cout << "请选择表实现方式：1. 顺序表  2. 链表 : ";
    cin >> implChoice;

    IList* L = nullptr;
    switch (implChoice) {
    case 1:
        L = new SeqList();
        cout << "已选择：顺序表实现\n";
        break;
    case 2:
        L = new LinkList();
        cout << "已选择：链表实现\n";
        break;
    default:
        cout << "无效操作\n";
    }

    int choice, pos;
    ElemType e, pre, next;

    while (true) {
        menu();
        cout << "请选择操作: ";
        cin >> choice;
        switch (choice) {
        case 1:
            L->InitList(); cout << "表已初始化\n"; break;
        case 2:
            cout << "输入插入位置和元素: ";
            cin >> pos >> e;
            cout << (L->Insert(pos, e) ? "插入成功\n" : "插入失败\n");
            break;
        case 3:
            cout << "输入删除位置: ";
            cin >> pos;
            if (L->Delete(pos, e))
                cout << "删除成功，元素=" << e << endl;
            else
                cout << "删除失败\n";
            break;
        case 4:
            cout << "表: "; L->Traverse(); break;
        case 5:
            cout << (L->ListEmpty() ? "表为空\n" : "表非空\n"); break;
        case 6:
            cout << "表长度=" << L->ListLength() << endl; break;
        case 7:
            cout << "输入位置: "; cin >> pos;
            if (L->Get(pos, e)) cout << "元素=" << e << endl;
            else cout << "位置不合法\n";
            break;
        case 8:
            cout << "输入元素: "; cin >> e;
            pos = L->LocateElem(e);
            if (pos) cout << "位置=" << pos << endl;
            else cout << "元素不存在\n";
            break;
        case 9:
            cout << "输入元素: "; cin >> e;
            if (L->PriorElem(e, pre)) cout << "前驱=" << pre << endl;
            else cout << "无前驱\n";
            break;
        case 10:
            cout << "输入元素: "; cin >> e;
            if (L->NextElem(e, next)) cout << "后继=" << next << endl;
            else cout << "无后继\n";
            break;
        case 11:
            L->ClearList(); cout << "表已清空\n"; break;
        case 12:
            L->DestroyList(); cout << "表已销毁\n"; break;
        case 13: { // 并集
            IList* B = (implChoice == 1 ? (IList*)new SeqList() : (IList*)new LinkList());
            inputList(B);
            IList* C = L->UnionList(*B);
            cout << "并集: "; C->Traverse();
            delete B; delete C;
            break;
        }
        case 14: { // 交集
            IList* B = (implChoice == 1 ? (IList*)new SeqList() : (IList*)new LinkList());
            inputList(B);
            IList* C = L->IntersectList(*B);
            cout << "交集: "; C->Traverse();
            delete B; delete C;
            break;
        }
        case 15: { // 差集
            IList* B = (implChoice == 1 ? (IList*)new SeqList() : (IList*)new LinkList());
            inputList(B);
            IList* C = L->DifferenceList(*B);
            cout << "差集: "; C->Traverse();
            delete B; delete C;
            break;
        }
        case 0:
            delete L;
            return 0;
        default:
            cout << "无效操作\n";
        }
    }
}
