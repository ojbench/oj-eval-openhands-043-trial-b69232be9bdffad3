#include <iostream>

using namespace std;

namespace LIST {

struct NODE {
    int value;
    NODE *prev;
    NODE *next;
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

NODE *move(int i) {
    if (i < 0 || i >= len) {
        return nullptr;
    }
    if (i < len / 2) {
        NODE *cur = head;
        for (int pos = 0; pos < i; ++pos) {
            cur = cur->next;
        }
        return cur;
    }
    NODE *cur = tail;
    for (int pos = len - 1; pos > i; --pos) {
        cur = cur->prev;
    }
    return cur;
}

void insert(int i, int x) {
    NODE *node = new NODE{x, nullptr, nullptr};
    if (len == 0) {
        head = node;
        tail = node;
    } else if (i == 0) {
        node->next = head;
        head->prev = node;
        head = node;
    } else if (i == len) {
        node->prev = tail;
        tail->next = node;
        tail = node;
    } else {
        NODE *cur = move(i);
        node->prev = cur->prev;
        node->next = cur;
        cur->prev->next = node;
        cur->prev = node;
    }
    ++len;
}

void remove(int i) {
    NODE *cur = move(i);
    if (cur == nullptr) {
        return;
    }
    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    } else {
        head = cur->next;
    }
    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    } else {
        tail = cur->prev;
    }
    delete cur;
    --len;
}

int Get_length() {
    return len;
}

int Query(int i) {
    NODE *cur = move(i);
    if (cur == nullptr) {
        return -1;
    }
    return cur->value;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE *cur = head;
    while (cur != nullptr) {
        cout << cur->value;
        if (cur->next != nullptr) {
            cout << ' ';
        }
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    NODE *cur = head;
    while (cur != nullptr) {
        NODE *next = cur->next;
        delete cur;
        cur = next;
    }
    head = nullptr;
    tail = nullptr;
    len = 0;
}

}  // namespace LIST

int n;

int main() {
    cin >> n;
    int op, x, p, ans;
    LIST::Pre();
    for (int step = 0; step < n; ++step) {
        cin >> op;
        switch (op) {
            case 0:
                ans = LIST::Get_length();
                cout << ans << '\n';
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << '\n';
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}
