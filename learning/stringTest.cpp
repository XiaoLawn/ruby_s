#include "iostream"

using namespace std;

// std::variant

void stringTest() {
    // char has no initial value
    char c; // \0
    char ca;
    char cb;

    string s = "abc";
    string s1 = "hello";
    s1[1] = 'a'; // editable
    string s2 = "hello world";
    // string initial value is ""
    string s3; // ""

    string u = string(3, 'h'); // u = "hhh"
    cout << u << endl;

    // concatenation of string
    char c1 = 'a'; // 'a'
    char c2 = 'a' + 2; // 'c'
    s += s1 + s2;
    s3 += c1;
    s3 += c2;

    // s1 - s2
    int cmp = s1.compare(s2);

    // swap two strings
    s1.swap(s2);

    // find
    // s = "abchallohello world"
    int n = s.find("hel", 8); // find the first occasion of "hel" from position 8
    int n1 = s.rfind("hel"); // from back to rear, find the first occasion of "hel"

    int n2 = s.find("lef"); // -1 means not found

    string vowelList = "aeiouAEIOU";
    if (vowelList.find('d') != -1) {
        // not found
    }


    // Take a substring
    // From index 1 and takes a substring of length 2
    string sub = s.substr(1, 2);
    // Take a substring [m1, m2)
    int m1 = 3;
    int m2 = 6;
    string subm = s.substr(m1, m2 - m1);

    // erase
    // From index 1 and erase a substring of length 3
    s1.erase(1, 3); // 删除 从下标1开始，长度为3的子串

    // reverse
    reverse(s.begin(), s.end());

    // startWith
    if (s1.find(s2) == 0) {
    }

    // endWith
    if (s1.find(s2, s1.size() - s2.size()) != -1) {
    }

    // stoi() -> string to int
    string l = "120";
    int i = stoi(l);

    // to_string() -> int to string
    string t = to_string(i);
}
