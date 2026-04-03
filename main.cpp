#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>
#include "solution.cpp"
#include "dp.cpp"
#include "learning/learning.cpp"
#include "learning/memcpyTest.cpp"
#include "learning/nameSpace.cpp"
#include "learning/operatorTest.cpp"
#include "learning/pointerTest.cpp"
#include "learning/stdTest.cpp"
#include "learning/templateTest.cpp"

using namespace std;


int main() {
    std::mutex raftLock_;
    std::lock_guard<std::mutex> g(raftLock_);

    Learning learning;
    learning.vecTest();
    learning.mapTest();
    learning.setTest();
    // learning.stringTest();
    learning.maxTest();
    learning.charTest();
    learning.mathsTest();
    learning.traverseTest();
    learning.maxIntTest();

    Solution solution;

    ListNode* node7 = new ListNode(7, nullptr);
    ListNode* node6 = new ListNode(6, node7);
    ListNode* node5 = new ListNode(5, node6);
    ListNode* node4 = new ListNode(4, node5);
    ListNode* node3 = new ListNode(3, node4);
    ListNode* node2 = new ListNode(2, node3);
    ListNode* node1 = new ListNode(1, node2);
    ListNode* node0 = new ListNode(0, node1);

    /*
     * 1
     * |\
     * 3 4
     * | |\
     * 2 6 5
     *   |  \
     *   8   7
     */
    TreeNode* tn7 = new TreeNode(7);
    TreeNode* tn5 = new TreeNode(5, NULL, tn7);
    TreeNode* tn8 = new TreeNode(8);
    TreeNode* tn6 = new TreeNode(6, tn8, NULL);
    TreeNode* tn2 = new TreeNode(2);
    TreeNode* tn4 = new TreeNode(4, tn6, tn5);
    TreeNode* tn3 = new TreeNode(3, tn2, NULL);
    TreeNode* tn1 = new TreeNode(1, tn3, tn4);

    // [[4,-16,1,-11],[6,18,-17,14],[16,-10,9,3],[-11,17,0,-11]]
    vector<vector<int>> matrix = {
        {7,2,9},
        {1,5,0},
        {2,6,6},
    };

    // [[0,1],[1,2],[1,3],[2,3],[3,4]]
    vector<vector<int>> grid = {
        {0,1},
        {1,2},
        {0,2},
    };

    vector<vector<char>> charMatrix = {
        {'#', '.', '*', '.'},
        {'#', '#', '*', '.'},
    };


    vector<string> start = {"ant", "act", "tack"};
    vector<string> target = {"tack", "act", "acti"};
    vector<int> vec = {4,8,5,3};
    vector<int> vec1 = {1,5,2,7};
    string s = "mokkori";


    size_t st = 10;
    cout << st << endl;

    string s1 = "siyolsdcjthwsiplccjbuceoxmpjgrauocx";
    string s2 = "siyolsdcjthwsiplccpbuceoxmjjgrauocx";

    int i = 10;
    int j = 9;
    j += i++;

    solution.countSubmatrices(matrix, 20);
    return 0;
}
