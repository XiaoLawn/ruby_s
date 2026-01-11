#include "iostream"

using namespace std;

void pointerTest() {
    vector<int>* p; // p is a pointer of an object
    p = new vector<int>(5, 0);
    vector<int>& obj = *p; // obj is a reference/alias of that object
    vector<int> cpobj = *p; // cpobj is a copy of that object
    p->push_back(2);
    p = nullptr; // p can be nullptr


    // & means reference
    vector<int> vec(5, 0); // vec is an object
    vector<int>& a = vec; // a is an alias/reference, type of a is same as vec, which is vector<int>
    vector<int>& b = vec; // also b
    vector<int> c = vec; // c is a copy of
    // a = nullptr; // No viable operator= matches arguments of type vector<int> and nullptr_t.

    // vec, a, b is the same object with 3 alias, so all their element [3] = 1, [2]v=v3
    b[0] = 1;
    vec[2] = 3;
}

void pointerTest1() {
    // &
    // 取变量地址 &a
    // 表引用 void pointerTest(vector<int>& vec) {...}
    //
    // *
    // 代表指针 int*
    // 取指针变量指向的值 *pt
    int a = 8;
    int *pt = &a;
    int b = *pt;

    *pt = 9;

    cout << a << endl;  // 9
    cout << b << endl;  // 8
}