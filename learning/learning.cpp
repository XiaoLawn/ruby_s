#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;

class Learning {
public:
    // const
    // inline
    // friend
    // template
    // namespace
    
    /*
     * vector
     * ->
     * push_back(),
     * pop_back(),
     * resize(),
     * clear(),
     * erase(begin() + i),
     * back(),
     * rbegin(),
     * reverse(begin(), end())
     *
     * set
     * ->
     * insert(),
     * erase(it / value),
     * if(st.count(1)),
     * if(st.find(1) == st.end()),
     * begin(),
     * end(),
     * rbegin(),
     * prev(st.end())
     *
     * map
     * ->
     * insert(pair<int, string>()),
     * if(mp.count(1)),
     * if(mp.find(1) == mp.end()),
     * erase(it / value),
     * clear()
     *
     * stack
     * ->
     * push(),
     * pop(),
     * top(),
     * empty()
     *
     * queue
     * -> push(),
     * pop(),
     * front(),
     * back(),
     * empty()
     */
    void vecTest() {
        // initialize
        vector<int> init; // {}
        vector<int> vec1(3); // {0, 0, 0}
        vector<int> vec2(3, 2); // {2, 2, 2}
        vector<int> vec3{3, 4, 5, 6};
        vector<int> vec4 = {3, 4, 5, 6};
        vector<int> vec5(vec1.begin(), vec1.end()); // same as vec1

        // Two-dimensional vector init
        vector<vector<int>> grid(2, vector<int>(10)); // initialize
        vector<vector<int>> grid1;
        grid1.resize(2); // now grid1 has two vector that size() == 0

        vector<int> a = {1, 2, 3, 4};
        vector<int> b = {5, 6, 7};

        // initialize two dimension vectors
        grid1 = {a, b};
        for (auto& x : grid1) {
            for (auto q : x) {
                cout << q << endl;
            }
        }

        // begin and end
        int bg = *vec4.begin(); // 3
        int ed = *vec4.end(); // 0
        int rb = *vec4.rbegin(); // 6

        // negative index not supported, will come up with random result
        int t = vec3[-1];

        // copy and reference
        vector<int> cpVec = vec3;
        vector<int>& rfVec = vec3; // now rfVec is a reference, an alias
        cpVec.push_back(4);
        rfVec.push_back(10);
        rfVec.push_back(11);
        rfVec.push_back(12);

        // use set to initialize vector
        set<int> st;
        st.insert(4);
        st.insert(4);
        st.insert(5);
        st.insert(6);
        vector<int> vec6(st.begin(), st.end()); // {4, 5, 6}


        init.resize(10); // init 里面 10 个 0
        init.push_back(1); // init.size() == 11
        init[20] = 90; // 并不会报错

        vector<int> left(10); // 定义大小为 10 的vector，初始值为 0
        vector<int> right(10, 20); // 定义大小为 10 的vector，初始值为 20

        iota(left.begin(), left.end(), 10); // left = [10, 11, 12, ... ,19]
        int sum = accumulate(left.begin(), left.end(), 0); // 将left中的元素累加，累加初始值为 0
        cout << sum << endl;

        left[100] = 100; // 不会报错，见下面 num[100] = 250
        for (vector<int>::iterator it = left.begin(); it != left.end(); it++) {
            cout << *it << endl;
        }

        int rightSize = right.size();
        right.push_back(10);
        int newRightSize = right.size();

        // get the last element
        int bk = right.back();
        right.pop_back(); // 弹出数组最后的元素，数组元素 - 1

        vector<int> num = {2, 4, 5, 1, 3, 6};
        // same thing
        cout << num.back() << endl;;
        cout << *num.rbegin() << endl;;


        vector<int> vk;
        for (int n : num) {
            update(vk, n);
        }
        num.insert(num.end(), 5, 4); // 在 num 的最后面添加 5 个 4

        num.insert(num.begin(), 1, -1);

        num.insert(num.begin() + 2, 1, -1);
        int t0 = num[100]; // t0 = 0, no error
        num[100] = 250; // do nothing
        int t1 = num[100]; // t1 = 250
        int t2 = num.size(); // t2 = 11 (5 + 6)

        // vec sort
        // sort ascending
        sort(num.begin(), num.end());

        // sort descending
        sort(num.begin(), num.end(), [](const int& a, const int& b) { return a > b; });

        // sort one based on another
        vector<int> vs1 = {7, 5, 4, 3, 2};
        vector<int> vs2 = {8, 3, 6, 2, 1};

        vector<int> idx(vs1.size());
        iota(idx.begin(), idx.end(), 0);

        sort(idx.begin(), idx.end(),
             [&](int i, int j) {
                 return vs1[i] < vs1[j];
             });

        vector<int> new_vs2;
        new_vs2.reserve(vs2.size());

        for (int i : idx)
            new_vs2.push_back(vs2[i]);

        vs2 = std::move(new_vs2);


        // sort Two-dimensional array
        vector<vector<int>> en = {{1, 2}, {4, 1}, {3, 5}, {3, 4}, {3, 7}};
        sort(en.begin(), en.end(), [](auto& a, auto& b) {
            if (a[0] != b[0]) return a[0] < b[0]; // a[0] from small to large
            return a[1] > b[1]; // a[1] from large to small
        });

        // sub vector
        vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7};
        vector<int> subVec(vec.begin() + 2, vec.begin() + 5);

        // vec erase
        vec.erase(vec.begin() + 3); // after this vec.size() go from 8 to 7

        // vec clear
        vec.clear();

        // reverse a vector
        reverse(vec.begin(), vec.end());
    }

    // update and maintain the order of vec
    // using binary search
    void update(vector<int>& items, int& item) {
        auto l = items.begin();
        auto r = items.end();
        while (l < r) {
            auto mid = l + (r - l >> 1);
            if (*mid > item) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        items.insert(l, 1, item);
    }

    void mapTest() {
        map<int, string> mp; // map ordered by Key ascending
        unordered_map<int, string> unmp; // unordered map

        // map insert
        mp[1] = "1";
        mp[2] = "2";
        mp[3] = "3";
        mp[4] = "4";
        mp.insert(pair<int, string>(5, "5")); // map is formed by pair<>
        mp[8] = "8";
        mp.erase(8);
        string t1 = mp[8]; // t1 will be "", and mp.count(8) will be > 0

        cout << mp.rbegin()->first << endl;
        cout << mp.rbegin()->second << endl;

        for (auto& p : mp) {
            cout << p.first << endl;
            cout << p.second << endl;
        }

        string t = mp[41];
        map<int, map<int, int>> mpm;
        auto& tmp = mpm[30]; // tmp is an empty map

        tmp[4] = 5;

        // map size
        int mpSize = mp.size();

        string s1 = mp[123];
        // return "" for key that doesn't exist, but once mp[123] it's called it inserts (123, "") into mp
        int cnt = mp.count(123);

        // map is sorted by key ascending
        map<int, string>::iterator iter1 = mp.lower_bound(5); // (5, "5")
        // 1, "2"   not less than(greater or equal to) the given value
        map<int, string>::iterator iter2 = mp.upper_bound(5); // (8, "8")

        map<int, string>::iterator iter3 = mp.find(1); // 1, "2"
        cout << iter1->second << endl;


        map<int, int> mp1;
        mp1[1]++; // mp1[1] = 1
        int u = mp1[9]; // return 0 for key that not exist

        int qoq = mp1[3];
        cout << "size:" << mp.size() << endl;

        // map erase
        bool b = mp.erase(1);
        if (b) {
            cout << "删除了" << endl;
        }

        // map clear 清空 map
        mp.clear();

        // map contain key
        if (mp.find(1) == mp.end()) {
            cout << "not contain that element" << endl;
        }
        if (!mp.count(1)) {
            cout << "contain that element" << endl;
        }
        if (mp.find(111) != mp.end()) {
            cout << "contain 111" << endl; // not contain 111, won't go here
        }
        if (mp.count(111)) {
            // the right way
            cout << "contain 111" << endl; // not contain 111, won't go here
        }
        if (mp.count(111)) {
            cout << "contain 111" << endl; // won't go here also
        }
        // the wrong way, bc once access mp[13], it inserts item mp[13] = "" into mp
        if (mp[13] == "") {
            cout << "not contain that element" << endl;
        }

        // map traverse
        for (auto& [k, v] : mp) {
            cout << k << endl;
            cout << v << endl;
        }

        // map traverse
        map<int, string>::iterator it;
        for (it = mp.begin(); it != mp.end(); it++) {
            cout << it->second << endl;
        }

        // Determine whether it is empty
        bool b1 = mp.empty();
        if (b1) {
            cout << "map 为空" << endl;
        }

        // lower_bound, upper_bound
        map<int, int> mp2;
        mp2[0] = 0;
        mp2[4] = 2;
        mp2[6] = 3;
        int lb = mp2.lower_bound(4)->first; // 4; First bigger than or equal to
        int ub = mp2.upper_bound(4)->first; // 6; First bigger than
        cout << lb << endl;
        cout << ub << endl;
    }

    void setTest() {
        // range initialization using iterators
        vector<int> nums = {1, 2, 3, 4, 5};
        vector<int> nums1(nums.begin(), nums.end());
        set<int> st1(nums.begin(), nums.end());
        set<int> st2(st1.begin(), st1.end());

        // insert
        set<int> st = {3,4,1,5,6,6};

        // access elements
        // access first
        auto it3 = st.begin();  // access first
        advance(it3, 2);   // move forward 2 positions
        it3 = next(it3);
        cout << *it3 << endl;

        // access last
        auto reverse_it = st.rbegin();  // a reverse_iterator, not support for erase()
        auto normal_it = prev(st.end());  // a normal it

        // erase
        // erase by iterator
        st.erase(normal_it);
        st.erase(st.begin());

        // erase by value
        st.erase(1);



        st.insert(3);
        st.insert(3);
        st.insert(5);
        // emplace is faster than insert
        st.emplace(8);
        st.emplace(9);

        cout << "size:" << st.size() << endl;
        cout << "3 count = " << st.count(3) << endl; // set.count(x) 只能返回0或1；可用来判断元素是否存在过

        // set contains
        if (st.count(2)) {
            // st.count() only returns 0 or 1, 1 means found, 0 means no
            // contains
        }

        // another
        if (st.find(2) == st.end()) {
        }

        // set traverse
        for (int u : st) {
            cout << u << endl;
        }

        // set traverse 1
        set<int>::iterator it1 = st.begin();
        set<int>::iterator it2 = st.end();
        for (; it1 != it2; it1++) {
            // 遍历；所有元素都会根据元素的键值自动排序
            cout << *it1;
        }
        cout << endl;

        // set traverse 2
        for (auto& u : st) {
            // ...
            cout << u << endl;
        }

        auto it = lower_bound(st.begin(), st.end(), 4); // ???

        // set clear
        st.clear();
    }

    /*
     * stack
     * .push()
     * .top()
     * .pop()
     */
    void stackTest() {
        stack<int> stack;
        stack.push(1);
        if (!stack.empty()) {
            int top = stack.top();
            cout << top << endl;
            stack.pop();
        }
    }

    /*
     * queue
     * .push()
     * .top()  return the first element
     * .pop()  return void
     * .empty()
     * .back()
     * .front()
     *
     * deque
     * .push_front()
     * .push_back()
     * .pop_front()
     * .pop_back()
     * .front()
     * .back()
     * .insert()
     */
    void queueTest() {
        queue<string> queue; // 定义queue
        queue.push("3"); // 添加元素
        if (!queue.empty()) {
            // 判空
            string front = queue.front(); // 取最前元素
            string back = queue.back();
            queue.pop();
        }

        deque<int> dq;

        // insert back
        dq.push_back(10); // [10]
        dq.push_back(20); // [10, 20]

        // insert front
        dq.push_front(5); // [5, 10, 20]

        if (dq.empty()) {
            cout << "empty" << endl;
        }

        // front(), back()
        cout << "Front: " << dq.front() << endl; // 5
        cout << "Back: " << dq.back() << endl; // 20
        cout << "Index 1: " << dq[1] << endl; // 10

        // pop_front(), pop_back()
        dq.pop_front(); // removes 5 → [10, 20]
        dq.pop_back(); // removes 20 → [10]

        // traverse deque
        cout << "Contents: ";
        for (int x : dq) {
            cout << x << " ";
        }
        cout << endl;
    }

    // priority_queue
    // .empty()
    // .push()
    // .pop()
    // .top()
    void priorityQueueTest() {
        // Descending by default
        // 默认大顶堆；等同于 priority_queue<int, vector<int>, less<int> > a;
        priority_queue<int> a; // descending
        priority_queue<int, vector<int>, greater<int>> c; // ascending, from small to large

        priority_queue<string> b;

        for (int i = 0; i < 5; i++) {
            a.push(i);
            c.push(i);
        }

        while (!a.empty()) {
            // 判空
            cout << a.top() << ' '; // 取顶
            a.pop(); // 后弹出
        }
        cout << endl;

        while (!c.empty()) {
            cout << c.top() << ' ';
            c.pop();
        }
        cout << endl;

        b.push("abc");
        b.push("abcd");
        b.push("cbd");
        while (!b.empty()) {
            cout << b.top() << ' ';
            b.pop();
        }
        cout << endl;
    }

    void dataStructureTest() {
        tuple<int, char, double> myTuple(10, 'a', 3.14);
        pair<int, string> p(0, "sss");
        pair<int, string> p1 = make_pair(9, "9");
        std::cout << "myTuple has ";
        std::cout << std::tuple_size<decltype(myTuple)>::value;
        std::cout << " elements." << '\n';
    }

    void memcpyTest() {
        vector<int> dist = {-1, 0, 1};
        vector<int> speed = {2, 2, 3, 3, 2, 4, 4, 4, 4, 4};

        vector<int> res;
        res.resize(10); // reset the length of vector to 10

        // res.data() + 1，这里的 1 是 一个 vector 元素，而不是一个字节
        // dist.data() 表示 vector<int> dist 的起始位置
        // dist.size() * sizeof(int) 表示字节长度
        memcpy(res.data() + 1, dist.data(), dist.size() * sizeof(int));
    }

    void maxTest() {
        int a1 = 0, a2 = 2, a3 = 1;
        int mx = max({a1, a2, a3});
    }

    void charTest() {
        char c = '1';
        if (isdigit(c)) {
            printf("is digit"); // is digit
        }
        if (isalpha(c)) {
            printf("is alpha");
        }

        char c1 = 'f';
        if (isdigit(c1)) {
            printf("is digit");
        }
        if (isalpha(c1)) {
            printf("is alpha"); // is alpha
        }
        if (isupper(c1)) {
            printf("is upper");
        }
        if (islower(c1)) {
            printf("is lower");
        }
    }

    void mathsTest() {
        int t = pow(2, 3); // 2 ^ 3 = 8
        int u = abs(-3);
        int a;
    }

    void maxIntTest() {
        // max int
        // int max
        int maxInt = INT_MAX; // 2,147,483,647
        long long ll = maxInt + (long long) 2789234234; // you must convert one of int to long long
        cout << ll << endl;

        // max long long
        // long long max
        long long maxLL = LONG_LONG_MAX;
    }

    void traverseTest() {
        unordered_map<int, vector<int>> mp;
        // map traverse 1
        for (auto& [k, v] : mp) {
        }
        for (auto& u : mp) {
            int k = u.first;
            vector<int> v = u.second;
        }
        // map traverse 2
        unordered_map<int, vector<int>>::iterator it;
        for (it = mp.begin(); it != mp.end(); it++) {
        }

        set<int> st;
        // set traverse 1
        for (int u : st) {
            cout << u << endl;
        }
        // set traverse 2
        set<int>::iterator its;
        for (its = st.begin(); its != st.end(); its++) {
        }

        // map contains
        // 1
        if (mp.find(1) != mp.end()) {
        }
        // 2
        if (mp.count(1)) {
        }

        // set contains
        // 1
        if (st.find(1) != st.end()) {
        }
        // 2
        if (st.count(1)) {
        }
    }
};
