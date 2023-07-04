#define _USE_MATH_DEFINES
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <functional>
#include <thread>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;


/* 秘制代码
int a[50001];

int init = [] {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ofstream out("user.out");
	for (string s; getline(cin, s);) {
		if (s.length() == 2) {
			out << "[]\n";
			continue;
		}
		int n = 0;
		for (int _i = 1, _n = s.length(); _i < _n; ++_i) {
			bool _neg = false;
			if (s[_i] == '-') ++_i, _neg = true;
			int v = s[_i++] & 15;
			while ((s[_i] & 15) < 10) v = v * 10 + (s[_i++] & 15);
			if (_neg) v = -v;
			a[n++] = v;
		}
		sort(a, a + n);
		out << '[' << a[0];
		for (int i = 1; i < n; ++i) out << ',' << a[i];
		out << "]\n";
	}
	out.flush();
	exit(0);
	return 0;
}();

class Solution {
public:
	ListNode *sortList(ListNode *) { return 0; }
};
*/

struct Point2D
{
	double x;
	double y;
	Point2D(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
};
struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	ListNode(vector<int>& vec)
	{
		vector<ListNode*> Nodes(vec.size());
		for (int i = 0; i < vec.size(); i++)
		{
			Nodes[i] = new ListNode();
		}
		for (int i = 0; i < vec.size(); i++)
		{
			Nodes[i]->val = vec[i];
			if (i != vec.size() - 1)
			{
				Nodes[i]->next = Nodes[i + 1];
			}
		}
		if (vec.size() != 0)
		{
			val = vec[0];
			next = Nodes[0]->next;
		}
	}
};
class MyQueue
{
public:
	stack<int> s1, s2;
	int CurSize = 0;
	MyQueue() {}

	void push(int x)
	{
		if (s2.size() == 0)
		{
			s1.push(x);
			CurSize++;
		}
		else
		{
			for (int i = 0; i < CurSize; i++)
			{
				s1.push(s2.top());
				s2.pop();
			}
			s1.push(x);
			CurSize++;
		}
	}
	int pop() //从队列的开头移除并返回元素
	{
		if (s2.size() == 0)
		{
			for (int i = 0; i < CurSize - 1; i++)
			{
				s2.push(s1.top());
				s1.pop();
			}
			int re = s1.top();
			s1.pop();
			CurSize--;
			return re;
		}
		else
		{
			int re = s2.top();
			s2.pop();
			CurSize--;
			return re;
		}
	}
	int peek() //返回队列开头的元素
	{
		if (s2.size() == 0)
		{
			for (int i = 0; i < CurSize; i++)
			{
				s2.push(s1.top());
				s1.pop();
			}
			return s2.top();
		}
		else
		{
			return s2.top();
		}
	}

	bool empty()
	{
		return CurSize == 0;
	}
};
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, int LeftVal, int RightVal) : val(x), left(new TreeNode(LeftVal)), right(new TreeNode(RightVal)) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	TreeNode(vector<int>& vec)
	{
		vector<TreeNode*> Nodes(vec.size(), nullptr);
		for (int i = 0; i < vec.size(); i++)
		{
			TreeNode* node = nullptr;
			if (vec[i] != -1)
			{
				node = new TreeNode(vec[i]);
			}
			Nodes[i] = node;
		}
		for (int i = 0; 2 * i + 2 < vec.size(); i++)
		{
			if (Nodes[i])
			{
				Nodes[i]->left = Nodes[2 * i + 1];
				Nodes[i]->right = Nodes[2 * i + 2];
			}
		}
		val = Nodes[0]->val;
		left = Nodes[0]->left;
		right = Nodes[0]->right;
	}
	TreeNode(vector<vector<int>>& nums)
	{
		int n = nums.size();
		vector<TreeNode*> Nodes(n);
		for (int i = 0; i < n; i++)
		{
			Nodes[i] = new TreeNode(i + 1, nullptr, nullptr);
		}
		TreeNode* root = Nodes[0];
		for (int i = 0; i < n; i++)
		{
			int LeftNode = nums[i][0];
			int RightNode = nums[i][1];
			if (LeftNode != -1)
			{
				Nodes[i]->left = Nodes[LeftNode - 1];
				if (LeftNode == 1)
				{
					root = Nodes[i];
				}
			}
			if (RightNode != -1)
			{
				Nodes[i]->right = Nodes[RightNode - 1];
				if (RightNode == 1)
				{
					root = Nodes[i];
				}
			}
		}
		val = root->val;
		left = root->left;
		right = root->right;
	}

};
class MyCircularDeque
{
	struct Node
	{
		int val;
		Node* next;
		Node() : val(0), next(nullptr) {}
		Node(int x) : val(x), next(nullptr) {}
		Node(int x, Node* next) : val(x), next(next) {}
	};
public:
	Node* head;
	Node* tail;
	int size, Maxsize;
	MyCircularDeque(int k)//构造函数,双端队列最大为 k 
	{
		head = new Node(INT_MIN);
		tail = head;
		size = 0;
		Maxsize = k;
	}
	bool insertFront(int value)//将一个元素添加到双端队列头部。 如果操作成功返回 true ，否则返回 false
	{
		if (size == Maxsize)return false;
		Node* NewNode = new Node(value, head->next);
		head->next = NewNode;
		if (size == 1)
		{
			tail = tail->next;
		}
		size++;
		return true;
	}
	bool insertLast(int value)//将一个元素添加到双端队列尾部。如果操作成功返回 true ，否则返回 false 
	{
		if (size == Maxsize)return false;
		if (size == 0)return insertFront(value);
		Node* NewNode = new Node(value);
		tail->next->next = NewNode;
		if (size > 0)
		{
			tail = tail->next;
		}
		size++;
		return true;
	}
	bool deleteFront()//从双端队列头部删除一个元素。 如果操作成功返回 true ，否则返回 false
	{
		if (size == 0)return false;
		head->next = head->next->next;
		if (size == 2)tail = head;
		size--;
		return true;
	}
	bool deleteLast()//从双端队列尾部删除一个元素。如果操作成功返回 true ，否则返回 false
	{
		if (size == 0)return false;
		tail->next = nullptr;
		if (size == 2)tail = head;
		else if (size >= 3)
		{
			tail = head;
			while (tail->next->next)tail = tail->next;
		}
		size--;
		return true;
	}
	int getFront()//从双端队列头部获得一个元素。如果双端队列为空，返回 -1
	{
		if (size == 0)return -1;
		return head->next->val;
	}
	int getRear()//获得双端队列的最后一个元素。 如果双端队列为空，返回 -1
	{
		if (size == 0)return -1;
		return tail->next->val;
	}
	bool isEmpty()//若双端队列为空，则返回 true ，否则返回 false
	{
		return size == 0;
	}
	bool isFull()//若双端队列满了，则返回 true ，否则返回 false
	{
		return size == Maxsize;
	}
};
class MyHashMap
{
public:
	vector<int> data;
	MyHashMap()
	{
		data.resize(0);
	}

	void put(int key, int value)
	{
		if (key >= data.size())data.resize(key + 1, INT_MIN);
		data[key] = value;
	}

	int get(int key)
	{
		if (key < data.size() && data[key] != INT_MIN)return data[key];
		return -1;
	}

	void remove(int key)
	{
		if (key < data.size())data[key] = INT_MIN;
	}

};
class Interval
{
public:
	int l;
	int r;
	Interval() : l(0), r(0) {}
	Interval(vector<int>& vec) : l(vec[0]), r(vec[1]) {}
	//按区间的右端点的升序排列
	bool operator<(const Interval& other) const
	{
		return r < other.r;
	}
};
class MyLinkedList
{
	//双向链表
public:
	int val;
	MyLinkedList* next;
	MyLinkedList* prev;
	int Num;
	MyLinkedList()
	{
		val = INT_MIN;
		next = nullptr;
		prev = nullptr;
		Num = 0;
	}
	//取链表中第 index 个节点的值。如果索引无效，则返回-1
	int get(int index)
	{
		if (index < 0 || index >= Num)return -1;
		int Sum = 0;
		MyLinkedList* p = this->next;
		while (Sum != index)
		{
			p = p->next;
			Sum++;
		}
		return p->val;
	}
	//在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点
	void addAtHead(int val)
	{
		MyLinkedList* Cur = new MyLinkedList();
		Cur->val = val;
		Cur->next = this->next;
		if (this->next)this->next->prev = Cur;
		this->next = Cur;
		Cur->prev = this;
		Num++;
	}
	//将值为 val 的节点追加到链表的最后一个元素。
	void addAtTail(int val)
	{
		MyLinkedList* Cur = new MyLinkedList();
		Cur->val = val;
		MyLinkedList* p = this;
		while (p->next)
		{
			p = p->next;
		}
		p->next = Cur;
		Cur->prev = p;
		Num++;
	}
	//在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。
	//如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点
	void addAtIndex(int index, int val)
	{
		if (index > Num)return;
		if (index <= 0)
		{
			addAtHead(val);
			return;
		}
		if (index == Num)
		{
			addAtTail(val);
			return;
		}
		int Sum = 0;
		MyLinkedList* Cur = new MyLinkedList();
		Cur->val = val;
		MyLinkedList* p = this->next;
		while (Sum != index)
		{
			p = p->next;
			Sum++;
		}
		Cur->next = p;
		Cur->prev = p->prev;
		p->prev->next = Cur;
		p->prev = Cur;
		Num++;
	}
	//如果索引 index 有效，则删除链表中的第 index 个节点
	void deleteAtIndex(int index)
	{
		if (index < 0 || index >= Num)return;
		int Sum = 0;
		MyLinkedList* p = this->next;
		while (Sum != index)
		{
			p = p->next;
			Sum++;
		}
		p->prev->next = p->next;
		if (p->next)p->next->prev = p->prev;
		Num--;
	}
};
class MinStack
{
public:
	stack<long long>* DiffData;
	long long Min;
	// 初始化堆栈对象。
	MinStack()
	{
		DiffData = new stack<long long>();
		Min = LLONG_MIN;
	}
	//将元素val推入堆栈。
	void push(int val)
	{
		if (DiffData->empty())
		{
			DiffData->emplace(0);
			Min = val;
		}
		else
		{
			DiffData->emplace((long long)val - Min);
			if (val < Min)Min = val;
		}
	}
	//删除堆栈顶部的元素。
	void pop()
	{
		if (DiffData->top() >= 0)DiffData->pop();
		else
		{
			Min = Min - DiffData->top();
			DiffData->pop();
		}
		if (DiffData->empty())Min = LLONG_MIN;
	}
	//获取堆栈顶部的元素。
	int top()
	{
		long long Top = DiffData->top();
		if (Top <= 0)return Min;
		else return Min + Top;
	}
	// 获取堆栈中的最小元素。
	int getMin()
	{
		return Min;
	}
};
class LRUCache
{
public:
	struct DoubleLinkNode
	{
		int val;
		DoubleLinkNode* pre;
		DoubleLinkNode* next;
		DoubleLinkNode()
		{
			val = 0;
			pre = nullptr;
			next = nullptr;
		}
		DoubleLinkNode(int x)
		{
			val = x;
			pre = nullptr;
			next = nullptr;
		}
		DoubleLinkNode(int x, DoubleLinkNode* p, DoubleLinkNode* n)
		{
			val = x;
			pre = p;
			next = n;
		}
	};
	LRUCache(int capacity)
	{
		Cache = new DoubleLinkNode(INT_MIN);
		CurrentNum = 0;
		MaxNum = capacity;
		tail = Cache;
	}

	int get(int key)
	{
		auto it = map.find(key);
		if (it == map.end())
		{
			return -1;
		}
		else if (it->second->val == INT_MAX)
		{
			return -1;
		}
		if (it->second->next)
		{
			it->second->pre->next = it->second->next;
			it->second->next->pre = it->second->pre;
			tail->next = it->second;
			it->second->pre = tail;
			it->second->next = nullptr;
			tail = it->second;
		}
		return tail->val;
	}

	void put(int key, int value)
	{
		auto it = map.find(key);
		if (it == map.end() || it->second->val == INT_MAX) //当前没有，要创建新的
		{
			DoubleLinkNode* Node = new DoubleLinkNode(value, tail, nullptr); //新创建的放在尾部
			tail->next = Node;
			tail = Node;
			map[key] = Node;
			if (CurrentNum < MaxNum)
			{
				CurrentNum++;
			}
			else
			{
				Cache->next->val = INT_MAX;
				Cache->next = Cache->next->next;
				if (Cache->next)
				{
					Cache->next->pre = Cache;
				}
			}
		}
		else //覆盖
		{
			DoubleLinkNode* Node = it->second;
			Node->val = value;
			if (Node->next)
			{
				Node->next->pre = Node->pre;
				Node->pre->next = Node->next;
				tail->next = Node;
				Node->pre = tail;
				Node->next = nullptr;
				tail = Node;
			}
		}
	}
private:
	int CurrentNum;
	int MaxNum;
	DoubleLinkNode* tail;
	DoubleLinkNode* Cache;
	unordered_map<int, DoubleLinkNode*> map;
};
//图
class Node
{
public:
	int val;
	vector<Node*> neighbors;
	Node()
	{
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val)
	{
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors)
	{
		val = _val;
		neighbors = _neighbors;
	}
};
//并查集
class DisjointSet
{
public:
	DisjointSet()
	{
		FindFather.clear();
		Size.clear();
		SetNum = 0;
	}
	DisjointSet(vector<int>& nums)
	{
		FindFather.clear();
		Size.clear();
		for (int num : nums)
		{
			FindFather[num] = num;
			Size[num] = 1;
			SetNum++;
		}
	}
	void Insert(int num)
	{
		if (FindFather.find(num) != FindFather.end())return;
		FindFather[num] = num;
		Size[num] = 1;
		SetNum++;
	}
	void Insert(int num, int father)
	{
		if (num == father)
		{
			Insert(num);
			return;
		}
		FindFather[num] = FindFather[father];
		Size[num] = 1;
	}
	void Union(int a, int b)
	{
		int Father1 = Find(a), Father2 = Find(b);
		if (Father1 == Father2)return;
		if (Size[Father1] > Size[Father2])
		{
			FindFather[Father2] = Father1;
			Size[Father1] += Size[Father2];
		}
		else
		{
			FindFather[Father1] = Father2;
			Size[Father2] += Size[Father1];
		}
		SetNum--;
	}
	int Find(int num)
	{
		int Father = FindFather[num];
		if (Father == num)
		{
			return num;
		}
		FindFather[num] = Find(Father);
		return FindFather[num];
	}
	bool IsInSameSet(int a, int b)
	{
		return FindFather[a] == FindFather[b];
	}
	int GetSetNum()
	{
		return SetNum;
	}

private:
	map<int, int> FindFather;
	map<int, unsigned int> Size;
	unsigned int SetNum;
};

//树状数组. 初始化时间复杂度O(n), 修改时间复杂度O(logn), 求和时间复杂度O(logn). 空间复杂度O(n)
// https://zhuanlan.zhihu.com/p/93795692
// https://www.bilibili.com/video/BV1ce411u7qP
class FenwickTree
{
private:
	vector<int> bit;
public:
	static int lowbit(int x)
	{
		return x & (-x);
	}
	FenwickTree(unsigned int size)
	{
		bit.resize(size);
	}
	FenwickTree(vector<int>& nums) //从普通数组构建树状数组
	{
		int n = nums.size();
		bit.resize(n);
		for (int i = 0; i < n; i++)
		{
			Add(i, nums[i]);
		}
	}
	void Add(unsigned int p, int x) //给数组的第p(从0开始)个数加上x
	{
		while (p < bit.size())
		{
			bit[p] += x;
			p += lowbit(p + 1);
		}
	}
	long long Sum(unsigned int p) //求数组的[0,p]范围内的和
	{
		long long re = 0;
		for (int i = p; i >= 0; i -= lowbit(i + 1))
		{
			re += bit[i];
		}
		return re;
	}
	int Get(unsigned int p) //返回当前数组的第p位
	{
		if (p % 2 == 0)return bit[p];
		return Sum(p) - Sum(p - 1);
	}
};
typedef FenwickTree TreeVector;
typedef FenwickTree BinaryIndexedTree;

//(小写英文字母)字典树. 初始化O(n*len), 查询插入删除O(len), 空间复杂度26^len, 查询公共前缀单词O(len), 词频统计O(n*len)
class TrieTree
{
public:
	struct Node
	{
		char c; //节点存储的字符数据
		unsigned int freq;
		unordered_map<char, Node*> map;
		Node(char c, unsigned int freq)
		{
			this->c = c;
			this->freq = freq;
		}
		~Node()
		{
			map.clear();
		}

	};
	Node* root;
	TrieTree()
	{
		root = new Node('\0', 0);
	}
	~TrieTree()
	{
		queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node* Cur = q.front();
			q.pop();
			for (auto it = Cur->map.begin(); it != Cur->map.end(); it++)
			{
				q.push(it->second);
			}
			delete[] Cur;
		}
	}
	void Insert(const string& word)
	{
		Node* Cur = root;
		for (const char& c : word)
		{
			auto it = Cur->map.find(c);
			if (it == Cur->map.end())
			{
				Node* NewNode = new Node(c, 0);
				Cur->map[c] = NewNode;
				Cur = NewNode;
			}
			else
			{
				Cur = it->second;
			}
		}
		Cur->freq++;
	}
	void Remove(const string& word)
	{
		Node* Cur = root;
		Node* Pre = root;
		for (const char& c : word)
		{
			auto it = Cur->map.find(c);
			if (it == Cur->map.end())
			{
				return;
			}
			Pre = Cur;
			Cur = it->second;
		}
		if (!Cur->map.empty())
		{
			Cur->freq = 0;
		}
		else
		{
			Pre->map.erase(Cur->c);
			delete Cur;
		}
	}
	unsigned int Count(const string& word)
	{
		Node* Cur = root;
		for (const char& c : word)
		{
			auto it = Cur->map.find(c);
			if (it == Cur->map.end())
			{
				return 0;
			}
			else
			{
				Cur = it->second;
			}
		}
		return Cur->freq;
	}
	void PreOrder(vector<string>& words, Node* cur = nullptr, string CurWord = "")
	{
		if (!cur)
		{
			cur = root;
		}
		if (cur != root)
		{
			CurWord.push_back(cur->c);
			if (cur->freq > 0)
			{
				words.push_back(CurWord);
			}
		}
		for (auto it = cur->map.begin(); it != cur->map.end(); it++)
		{
			PreOrder(words, it->second, CurWord);
		}
	}
	void SearchPrefix(const string& prefix, vector<string>& words)
	{
		Node* Cur = root;
		for (const char& c : prefix)
		{
			auto it = Cur->map.find(c);
			if (it == Cur->map.end())
			{
				return;
			}
			Cur = it->second;
		}
		PreOrder(words, Cur, prefix.substr(0, prefix.length() - 1));
	}

};

void PrintVector(vector<int>& nums)
{
	for (int i = 0; i < nums.size() - 1; i++)
	{
		cout << nums[i] << " ";
	}
	cout << nums.back() << endl;
}

class ACM
{
public:
	//读取固定大小一维数组, 以空格分隔
	/*
	3
	1 2 3
	*/
	static void ReadFixedVec(vector<int>& nums)
	{
		int n;
		cin >> n;
		nums = vector<int>(n);
		for (int i = 0; i < n; i++)
		{
			cin >> nums[i];
		}
	}
	//读取固定大小一维数组, 以非空格分隔
	/*
	3
	1,2,3
	*/
	static void ReadFixedVec_NonSpace(vector<int>& nums)
	{
		int n;
		cin >> n;
		nums = vector<int>(n);
		char c;
		for (int i = 0; i < n - 1; i++)
		{
			cin >> nums[i] >> c;
		}
		cin >> nums[n - 1];
	}
	//读取非固定大小一维数组, 以空格分隔
	/*
	1 2 3
	*/
	static void ReadNonFixedVec(vector<int>& nums)
	{
		nums.resize(0);
		int num;
		while (cin >> num)
		{
			nums.push_back(num);
			if (getchar() == '\n')
			{
				break;
			}
		}
	}
	//读取非固定大小一维数组, 以非空格分隔
	/*
	1,2;3'4
	*/
	static void ReadNonFixedVec_NonSpace(vector<int>& nums)
	{
		nums.resize(0);
		int num;
		while (cin >> num)
		{
			nums.push_back(num);
			char c = getchar();
			if (c == '\n')
			{
				break;
			}
		}
	}


	//读取固定大小二维数组, 以空格分隔
	/*
	2 3
	1 2 3
	4 5 6
	*/
	static void ReadFixedVec(vector<vector<int>>& nums)
	{
		int m, n;
		cin >> m >> n;
		nums = vector<vector<int>>(m, vector<int>(n));
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> nums[i][j];
			}
		}
	}
	//读取固定大小二维数组, 以非空格分隔
	/*
	2 3
	1,2*3
	4'5;6
	*/
	static void ReadFixedVec_NonSpace(vector<vector<int>>& nums)
	{
		int m, n;
		cin >> m >> n;
		nums = vector<vector<int>>(m, vector<int>(n));
		for (int i = 0; i < m; i++)
		{
			char c;
			for (int j = 0; j < n - 1; j++)
			{
				cin >> nums[i][j] >> c;
			}
			cin >> nums[i][n - 1];
		}
	}
	//读取非固定大小二维数组, 以任意字符(空格分隔也适用)分隔
	/*
	1,2#3
	4'5;6
	*/
	static void ReadNonFixedVec(vector<vector<int>>& nums)
	{
		while (true)
		{
			vector<int> temp;
			int num;
			char c;
			while ((c = getchar()) != '\n')
			{
				ungetc(c, stdin);
				cin >> num;
				temp.push_back(num);
				c = getchar();
				if (c == '\n')
				{
					break;
				}
			}
			if (temp.size() == 0)
			{
				break;
			}
			nums.push_back(temp);
		}
	}


	//读取字符串数组, 都写在同一行, 以空格分隔
	/*
	wo ai peipei
	*/
	static void ReadString(vector<string>& vec)
	{
		vec.resize(0);
		string str;
		while (cin >> str)
		{
			vec.push_back(str);
			if (getchar() == '\n')
			{
				break;
			}
		}
	}
	//读取字符串数组, 都写在同一行, 以指定字符分隔
	/*
	wo#ai#peipei
	*/
	static void ReadString(vector<string>& vec, char sep)
	{
		string AllInput;
		getline(cin, AllInput);
		vec.resize(0);
		string str;
		int p = 0;
		for (int q = 0; q < AllInput.size(); q++)
		{
			p = q;
			while (AllInput[p] != sep && p < AllInput.size())
			{
				p++;
			}
			vec.push_back(AllInput.substr(q, p - q));
			q = p;
		}
	}
	//读取字符串数组, 写在不同行
	/*
	wo ai
	peipei
	*/
	static void ReadStringLines(vector<string>& vec)
	{
		vec.resize(0);
		string str;
		while (getline(cin, str))
		{
			if (str.size() == 0)
			{
				break;
			}
			vec.push_back(str);
		}
	}

	//读取二叉树
	/*
	5
	2 3
	4 5
	-1 -1
	-1 -1
	-1 -1
	*/
	static void ReadTree(TreeNode** tree)
	{
		int n;
		cin >> n;
		vector<vector<int>> nums(n, vector<int>(2, -1));
		for (int i = 0; i < n; i++)
		{
			cin >> nums[i][0] >> nums[i][1];
		}
		vector<TreeNode*> Nodes(n);
		for (int i = 0; i < n; i++)
		{
			Nodes[i] = new TreeNode(i + 1, nullptr, nullptr);
		}
		*tree = Nodes[0];
		for (int i = 0; i < n; i++)
		{
			int LeftNode = nums[i][0];
			int RightNode = nums[i][1];
			if (LeftNode != -1)
			{
				Nodes[i]->left = Nodes[LeftNode - 1];
				if (LeftNode == 1)
				{
					*tree = Nodes[i];
				}
			}
			if (RightNode != -1)
			{
				Nodes[i]->right = Nodes[RightNode - 1];
				if (RightNode == 1)
				{
					*tree = Nodes[i];
				}
			}
		}
	}

};
class Sort
{
public:
	//冒泡排序. 平均时间O(n^2), 最好时间O(n^2), 最坏时间O(n^2), 空间复杂度O(1), 内部排序, 稳定
	static void BubbleSort(vector<int>& nums)
	{
		int n = nums.size();
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (nums[j] > nums[j + 1])swap(nums[j], nums[j + 1]);
			}
		}
	}
	//选择排序. 平均时间O(n^2), 最好时间O(n^2), 最坏时间O(n^2), 空间复杂度O(1), 内部排序, 不稳定
	static void SelectionSort(vector<int>& nums)
	{
		int n = nums.size();
		for (int i = 0; i < n - 1; i++)
		{
			int MinIndex = i;
			for (int j = i + 1; j < n; j++)
			{
				if (nums[j] < nums[MinIndex])
				{
					MinIndex = j;
				}
			}
			swap(nums[MinIndex], nums[i]);
		}
	}
	//插入排序. 平均时间O(n^2), 最好时间O(n), 最坏时间O(n^2), 空间复杂度O(1), 内部排序, 稳定
	static void InsertSort(vector<int>& nums)
	{
		int n = nums.size();
		for (int i = 1; i < n; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (nums[j] >= nums[j - 1])break;
				swap(nums[j], nums[j - 1]);
			}
		}
	}
	//希尔排序(缩小增量排序). 平均时间O(nlogn), 最好时间O(n(logn)^2), 最坏时间O(n(logn)^2), 空间复杂度O(1), 内部排序, 不稳定
	static void ShellSort(vector<int>& nums)
	{
		int n = nums.size();
		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; i++)
			{
				int temp = nums[i], j;
				for (j = i; j >= gap && nums[j - gap] > temp; j -= gap)
				{
					nums[j] = nums[j - gap];
				}
				nums[j] = temp;
			}
		}
	}
	//归并排序. 平均时间O(nlogn), 最好时间O(nlogn), 最坏时间O(nlogn), 空间复杂度O(n), 外部排序, 稳定
	static void MergeSort(vector<int>& nums, bool UseRecursive = true)
	{
		int n = nums.size();
		if (UseRecursive)
		{
			MergeSort_Recursive(nums, 0, n - 1);
		}
		else
		{
			MergeSort_NonRecursive(nums);
		}
	}
	//快速排序. 平均时间O(nlogn), 最好时间O(nlogn), 最坏时间O(n^2), 空间复杂度O(logn), 内部排序, 不稳定
	static void QuickSort(vector<int>& nums, bool UseRecursive = true)
	{
		int n = nums.size();
		if (UseRecursive)
		{
			QuickSort_Recursive(nums, 0, n - 1);
		}
		else
		{
			QuickSort_NonRecursive(nums);
		}
	}
	//堆排序. 平均时间O(nlogn), 最好时间O(nlogn), 最坏时间O(nlogn), 空间复杂度O(1), 内部排序, 不稳定
	static void HeapSort(vector<int>& nums, bool UseRecursive = true)
	{
		int n = nums.size();
		if (UseRecursive)
		{
			for (int i = n / 2 - 1; i >= 0; i--)
			{
				MakeHeap_Recursive(nums, n, i);
			}
			for (int i = n - 1; i >= 1; i--)
			{
				swap(nums[0], nums[i]);           // 将当前最大的放置到数组末尾
				MakeHeap_Recursive(nums, i, 0);               // 将未完成排序的部分继续进行堆排序
			}
		}
		else
		{
			for (int i = n / 2 - 1; i >= 0; i--)
			{
				MakeHeap_NonRecursive(nums, n, i);
			}
			for (int i = n - 1; i >= 1; i--)
			{
				swap(nums[0], nums[i]);           // 将当前最大的放置到数组末尾
				MakeHeap_NonRecursive(nums, i, 0);               // 将未完成排序的部分继续进行堆排序
			}
		}
	}
	//桶排序. 平均时间O(n+k), 最好时间O(n+k), 最坏时间O(n^2), 空间复杂度O(n+k), 外部排序, 稳定
	static void BucketSort(vector<int>& nums)
	{
		int n = nums.size();
		int MinValue = *min_element(nums.begin(), nums.end());
		int MaxValue = *max_element(nums.begin(), nums.end());
		int range = MaxValue - MinValue;
		vector<vector<int>> buckets(n);
		for (int i = 0; i < n; i++)
		{
			int index = (n - 1) * (nums[i] - MinValue) / range;
			buckets[index].push_back(nums[i]);
		}
		for (int i = 0; i < n; i++)
		{
			sort(buckets[i].begin(), buckets[i].end());
		}
		int CurIndex = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < buckets[i].size(); j++)
			{
				nums[CurIndex++] = buckets[i][j];
			}
		}
	}
	//计数排序. 平均时间O(n+k), 最好时间O(n+k), 最坏时间O(n+k), 空间复杂度O(k), 外部排序, 稳定
	//当nums全为整数时, 采用这个方法最快, 但是比较占内存.
	static void CountingSort(vector<int>& nums, bool IsMustStable = true)
	{
		int n = nums.size();
		int MinValue = *min_element(nums.begin(), nums.end());
		int MaxValue = *max_element(nums.begin(), nums.end());
		int k = MaxValue - MinValue + 1;
		vector<int> Count(k);
		for (int i = 0; i < n; i++)
		{
			Count[nums[i] - MinValue]++;
		}
		if (IsMustStable)
		{
			for (int i = 1; i < k; i++)
			{
				Count[i] += Count[i - 1];
			}
			vector<int> temp(n);
			for (int i = n - 1; i >= 0; i--)
			{
				temp[Count[nums[i] - MinValue] - 1] = nums[i];
				Count[nums[i] - MinValue]--;
			}
			nums = temp;
		}
		else
		{
			int CurIndex = 0;
			for (int i = 0; i < k; i++)
			{
				while (Count[i] > 0)
				{
					nums[CurIndex++] = i + MinValue;
					Count[i]--;
				}
			}
		}
	}
	//基数排序. 平均时间O(nk), 最好时间O(nk), 最坏时间O(nk), 空间复杂度O(n+k), 外部排序, 稳定
	static void RadixSort(vector<int>& nums)
	{
		int n = nums.size();
		int MinValue = *min_element(nums.begin(), nums.end());
		int MaxValue = *max_element(nums.begin(), nums.end());
		int k = MaxValue - MinValue + 1;
		int MaxDigit = log10(k) + 1;
		vector<int> Count(19), temp(n);
		for (int exp = 0; exp < MaxDigit; exp++)
		{
			fill(Count.begin(), Count.end(), 0);
			for (int i = 0; i < n; i++)
			{
				int index = 9 + (nums[i] - MinValue) / int(pow(10, exp)) % 10;
				Count[index]++;
			}
			for (int i = 1; i < 19; i++)
			{
				Count[i] += Count[i - 1];
			}
			for (int i = n - 1; i >= 0; i--)
			{
				int index = 9 + (nums[i] - MinValue) / int(pow(10, exp)) % 10;
				temp[Count[index] - 1] = nums[i];
				Count[index]--;
			}
			nums = temp;
		}
	}

private:
	static void MergeSort_Recursive(vector<int>& nums, int left, int right)
	{
		if (left >= right)return;
		int mid = left + (right - left) / 2;
		MergeSort_Recursive(nums, left, mid);
		MergeSort_Recursive(nums, mid + 1, right);
		if (nums[mid] <= nums[mid + 1])return;
		vector<int> temp = nums;
		int index = left, i = left, j = mid + 1;
		while (i <= mid && j <= right)
		{
			if (nums[i] < nums[j])
			{
				temp[index++] = nums[i++];
			}
			else
			{
				temp[index++] = nums[j++];
			}
		}
		while (i <= mid)
		{
			temp[index++] = nums[i++];
		}
		while (j <= right)
		{
			temp[index++] = nums[j++];
		}
		nums = temp;
	}
	static void MergeSort_NonRecursive(vector<int>& nums)
	{
		int n = nums.size();
		vector<int> temp(n);
		for (int gap = 1; gap < n; gap *= 2)
		{
			for (int i = 0; i < n; i += 2 * gap)
			{
				//[i,i+gap-1] [i+gap, i+2*gap-1]
				if (i + gap >= n)break;
				if (nums[i + gap - 1] <= nums[i + gap])continue;
				int left = i, right = min(i + 2 * gap - 1, n - 1);
				int m = left, n = i + gap, index = left;
				while (m <= i + gap - 1 && n <= right)
				{
					if (nums[m] < nums[n])
					{
						temp[index++] = nums[m++];
					}
					else
					{
						temp[index++] = nums[n++];
					}
				}
				while (m <= i + gap - 1)
				{
					temp[index++] = nums[m++];
				}
				while (n <= right)
				{
					temp[index++] = nums[n++];
				}
				for (int k = left; k <= right; k++)
				{
					nums[k] = temp[k];
				}
			}
		}

	}
	static void QuickSort_Recursive(vector<int>& nums, int left, int right)
	{
		if (left >= right)return;
		int i = left, j = right;
		srand(time(0));
		int RandomIndex = rand() % (right - left + 1) + left;
		swap(nums[left], nums[RandomIndex]);
		int pivot = nums[left];
		while (i < j)
		{
			while (i < j && pivot <= nums[j]) j--;
			if (i < j) nums[i++] = nums[j];
			while (i < j && pivot >= nums[i]) i++;
			if (i < j) nums[j--] = nums[i];
		}
		nums[i] = pivot;
		QuickSort_Recursive(nums, left, i - 1);
		QuickSort_Recursive(nums, i + 1, right);
	}
	static void QuickSort_NonRecursive(vector<int>& nums)
	{
		int n = nums.size();
		stack<int> s;
		s.push(0);
		s.push(n - 1);
		while (!s.empty())
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			int i = left, j = right;
			srand(time(0));
			int RandomIndex = rand() % (right - left + 1) + left;
			swap(nums[left], nums[RandomIndex]);
			int pivot = nums[left];
			while (i < j)
			{
				while (i < j && pivot <= nums[j]) j--;
				if (i < j) nums[i++] = nums[j];
				while (i < j && pivot >= nums[i]) i++;
				if (i < j) nums[j--] = nums[i];
			}
			nums[i] = pivot;
			if (i - 1 > left)
			{
				s.push(left);
				s.push(i - 1);
			}
			if (i + 1 < right)
			{
				s.push(i + 1);
				s.push(right);
			}
		}
	}
	static void MakeHeap_Recursive(vector<int>& nums, int len, int index)
	{
		int left = 2 * index + 1; // index的左子节点
		int right = 2 * index + 2;// index的右子节点

		int maxIdx = index;
		if (left < len && nums[left] > nums[maxIdx])maxIdx = left;
		if (right < len && nums[right] > nums[maxIdx])maxIdx = right;
		if (maxIdx != index)
		{
			swap(nums[maxIdx], nums[index]);
			MakeHeap_Recursive(nums, len, maxIdx);
		}
	}
	static void MakeHeap_NonRecursive(vector<int>& nums, int len, int index)
	{
		int temp = nums[index];
		for (int i = 2 * index + 1; i < len; i = 2 * i + 1)
		{
			if (i + 1 < len && nums[i] < nums[i + 1])
			{
				i++;
			}
			if (nums[i] <= temp)break;
			nums[index] = nums[i];
			index = i;
		}
		nums[index] = temp;
	}
};
class Random
{
public:
	//生成单个随机整数, 范围为[min, max]
	int static GenerateSingleRandomInt(int min, int max)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}
	//生成单个随机小数, 范围为[min, max]
	int static GenerateSingleRandomDouble(double min, double max)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(min, max);
		return dis(gen);
	}
	//生成n个随机整数, 范围为[min, max], 是否允许重复
	void static GenerateRandomInt(int n, int min, int max, vector<int>& result, bool IsAllowDuplicate = true)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(min, max);
		if (IsAllowDuplicate)
		{
			for (int i = 0; i < n; i++)
			{
				result.push_back(dis(gen));
			}
			return;
		}
		unordered_set<int> set;
		while (set.size() < n)
		{
			int num = dis(gen);
			if (set.find(num) == set.end())
			{
				set.insert(num);
				result.push_back(num);
			}
		}
	}
	//生成n个随机小数, 范围为[min, max], 是否允许重复
	void static GenerateRandomDouble(int n, double min, double max, vector<double>& result, bool IsAllowDuplicate = true)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(min, max);
		if (IsAllowDuplicate)
		{
			for (int i = 0; i < n; i++)
			{
				result.push_back(dis(gen));
			}
			return;
		}
		unordered_set<double> set;
		while (set.size() < n)
		{
			double num = dis(gen);
			if (set.find(num) == set.end())
			{
				set.insert(num);
				result.push_back(num);
			}
		}
	}
	//随机打乱一个数组
	void static ShuffleVector(vector<int>& nums)
	{
		random_device rd;
		mt19937 rng(rd());
		shuffle(nums.begin(), nums.end(), rng);
	}
};

class Solution
{
private:
	double Radius, CenterX, CenterY; //在圆内随机生成点
public:
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
	void ios() { ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); }
	Solution() { ios(); }
	//478.在圆内随机生成点
	Solution(double radius, double x_center, double y_center)
	{
		Radius = radius;
		CenterX = x_center;
		CenterY = y_center;
	}
	//217.存在重复元素
	bool containsDuplicate(vector<int>& nums)
	{
		/* //84~116ms, 50.9MB
		set<int> nums_set;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums_set.find(nums[i]) != nums_set.end())
				return true;
			nums_set.insert(nums[i]);
		}
		return false;
		*/

		//60~80ms, 50.1MB
		unordered_set<int> nums_set;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums_set.find(nums[i]) != nums_set.end())
				return true;
			nums_set.insert(nums[i]);
		}
		return false;

		/* //68~84ms, 53.8MB
		unordered_set<int> nums_set(nums.begin(), nums.end());
		if (nums_set.size() != nums.size())return true;
		return false;
		*/

	}
	//53.求最大子数组和
	int maxSubArray(vector<int>& nums)
	{
		//贪心算法
		int Num = 0, MaxNum = nums[0];
		for (int element : nums)
		{
			Num += element;
			if (Num > MaxNum)
			{
				MaxNum = Num;
			}
			if (Num < 0)
			{
				Num = 0;
			}
		}
		return MaxNum;


		/* //动态规划算法
		int* SubMax = new int[nums.size()];
		SubMax[0] = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			int Temp = SubMax[i - 1] + nums[i];
			if (Temp <= nums[i])
			{
				SubMax[i] = nums[i];
			}
			else
			{
				SubMax[i] = Temp;
			}
		}
		int Max = SubMax[0];
		for (int i = 0; i < nums.size(); i++)
		{
			Max = max(SubMax[i], Max);
		}
		delete[] SubMax;
		return Max;
		*/

	}
	//1.两数之和
	vector<int> twoSum(vector<int>& nums, int target)
	{
		unordered_map<int, int> Sub;  // <补数, index>
		for (int i = 0; i < nums.size(); i++)
		{
			auto It = Sub.find(nums[i]);
			if (It == Sub.end())
			{
				Sub[target - nums[i]] = i;
			}
			else
			{
				return { It->second,i };
			}
		}
	}
	//88.合并两个有序数组
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		int p1 = m - 1, p2 = n - 1, p3 = m + n - 1;
		while (p1 != -1 && p2 != -1 && p3 != -1)
		{
			int n1 = nums1[p1], n2 = nums2[p2];
			if (n1 > n2)
			{
				nums1[p3] = n1;
				p1--;
			}
			else
			{
				nums1[p3] = n2;
				p2--;
			}
			p3--;
		}
		if (p1 == -1)
		{
			while (p3 >= 0)
			{
				nums1[p3] = nums2[p2];
				p2--;
				p3--;
			}
		}
	}
	//350.两个数组的交集 II
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
	{
		/* //使用multiset
		unordered_multiset<int> a(nums1.begin(), nums1.end());
		unordered_multiset<int> b(nums2.begin(), nums2.end());
		nums1.resize(0);
		for (auto It = a.begin(); It != a.end(); It++)
		{
			int Num2 = b.count(*It);
			if (Num2 == 0)
			{
				continue;
			}
			else
			{
				int Num1 = a.count(*It);
				for (int i = 0; i < min(Num1, Num2); i++)
				{
					nums1.push_back(*It);
				}
				while (Num1 != 1)
				{
					It++;
					Num1--;
				}
			}
		}
		return nums1;
		*/

		unordered_map<int, int> b;
		for (int e2 : nums2)
		{
			b[e2]++;
		}
		int k = 0;
		for (int e1 : nums1)
		{
			auto It = b.find(e1);
			if (It != b.end() && It->second > 0)
			{
				nums1[k++] = It->first;
				It->second--;
			}
		}
		return vector<int>(nums1.begin(), nums1.begin() + k);
	}
	//121.买卖股票的最佳时机
	int maxProfit(vector<int>& prices)
	{
		int Buy = prices[0], Profit = 0;
		for (int price : prices)
		{
			if (price > Buy)
			{
				Profit = max(price - Buy, Profit);
			}
			else
			{
				Buy = price;
			}
		}
		return Profit;
	}
	//566.重塑矩阵
	vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c)
	{
		/* //先展开成一维向量
		if (r*c != mat.size()*mat[0].size())
			return mat;
		vector<vector<int>> Re(r, vector<int>(c, 0));
		vector<int> flattened = accumulate(mat.begin(), mat.end(), vector<int>(),
			[](vector<int>& x, vector<int>& y) {
			x.insert(x.end(), y.begin(), y.end());
			return x;
		});
		for (int i = 0; i < r; i++)
		{
			Re[i].assign(flattened.begin() + c*i, flattened.begin() + c*i + c);
		}
		return Re;
		*/

		// 找出重塑前后，下标之间的对应关系
	   /* 从一维数组下标，找二维数组的下标:
	   原矩阵{{0,1,2},{3,4,5}},2行3列 → {{0,1},{2,3},{4,5}},3行2列
	   0 → (0,0) → (0,1)     1 → (0,1) → (0,1)     2 → (0,2) → (1,0)
	   3 → (1,0) → (1,1)     4 → (1,1) → (2,0)     5 → (1,2) → (2,1)
	   i → (i/n,i%n) → (i/n2,i%n2)
	   */
		int c0 = mat[0].size();
		int Num = mat.size() * c0;
		if (r * c != Num)
		{
			return mat;
		}
		vector<vector<int>> Re(r, vector<int>(c, 0));
		for (int i = 0; i < Num; i++)
		{
			Re[i / c][i % c] = mat[i / c0][i % c0];
		}
		return Re;
	}
	//118.杨辉三角
	vector<vector<int>> generate(int numRows)
	{
		vector<vector<int>> Re(numRows);
		for (int i = 0; i < numRows; i++)
		{
			Re[i] = vector<int>(i + 1, 1);
			for (int j = 1; j <= i / 2; j++)
			{
				Re[i][i - j] = Re[i][j] = Re[i - 1][j - 1] + Re[i - 1][j];
			}
		}
		return Re;
	}
	//36.有效的数独
	bool isValidSudoku(vector<vector<char>>& board)
	{
		for (int i = 0; i < 9; i++)
		{
			vector<int> Temp1(9, 0), Temp2(9, 0);
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] != '.')
				{
					int Num1 = board[i][j] - 48;
					if (Temp1[Num1 - 1] != 0)
					{
						return false;
					}
					Temp1[Num1 - 1] = 1;
				}
				if (board[j][i] != '.')
				{
					int Num2 = board[j][i] - 48;
					if (Temp2[Num2 - 1] != 0)
					{
						return false;
					}
					Temp2[Num2 - 1] = 1;
				}

			}
		}
		for (int block = 0; block < 9; block++)
		{
			vector<int> Temp3(9, 0);
			int Imin = 3 * (block / 3), Jmin = 3 * (block % 3);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					char e = board[Imin + i][Jmin + j];
					if (e != '.')
					{
						int Num = e - 48;
						if (Temp3[Num - 1] != 0)
						{
							return false;
						}
						Temp3[Num - 1] = 1;
					}
				}
			}
		}
		return true;
	}
	//73.矩阵置零
	void setZeroes(vector<vector<int>>& matrix)
	{
		//额外设置一个标志位(Col0Flag)表示第0列是否存在0(存在则为0)
		int Col0Flag = 1, row = matrix.size(), col = matrix[0].size();
		for (int i = 0; i < row; i++)
		{
			if (matrix[i][0] == 0)
			{
				Col0Flag = 0;
				break;
			}
		}
		//然后不管第0列，从第1列开始，如果某处为0，则把其所在行和所在列的第0个元素都变成0
		for (int i = 0; i < row; i++)
		{
			for (int j = 1; j < col; j++)
			{
				if (matrix[i][j] == 0)
				{
					matrix[i][0] = matrix[0][j] = 0;
				}
			}
		}
		//此时，如果[i][0]为0，表示第i行有0
		//如果[0][j]为0，表示第j(j!=0)列有0
		// i从row-1到0(倒序)，j从1到col-1(排除第0列)
		for (int i = row - 1; i >= 0; i--)
		{
			for (int j = 1; j < col; j++)
			{
				if (matrix[i][0] == 0 || matrix[0][j] == 0)
				{
					matrix[i][j] = 0;
				}
			}
		}
		//最后判断第0列是否应该全为0
		if (Col0Flag == 0)
		{
			for (int i = 0; i < row; i++)
			{
				matrix[i][0] = 0;
			}
		}
	}
	//387.字符串中的第一个唯一字符
	int firstUniqChar(string s)
	{
		unordered_map<char, int> map;
		for (int i = 0; i < s.size(); i++)
		{
			auto it = map.find(s[i]);
			if (it == map.end())
			{
				map[s[i]] = i;
			}
			else
			{
				it->second = -1;
			}
		}
		int MinIndex = INT_MAX;
		for (auto it = map.begin(); it != map.end(); it++)
		{
			int Num = it->second;
			if (Num != -1 && Num < MinIndex)
			{
				MinIndex = Num;
			}
		}
		return (MinIndex == INT_MAX ? -1 : MinIndex);
	}
	//383.赎金信
	bool canConstruct(string ransomNote, string magazine)
	{
		if (magazine.size() < ransomNote.size())
		{
			return false;
		}
		unordered_map<char, int> MagazineMap;
		for (char c : magazine)
		{
			MagazineMap[c]++;
		}
		for (char c : ransomNote)
		{
			auto It = MagazineMap.find(c);
			if (It == MagazineMap.end() || It->second == 0)
			{
				return false;
			}
			else
			{
				MagazineMap[c]--;
			}
		}
		return true;
	}
	//242.有效的字母异位词
	bool isAnagram(string s, string t)
	{
		if (s.size() != t.size())
		{
			return false;
		}
		unordered_map<char, int> map;
		for (char c : s)
		{
			map[c]++;
		}
		for (char c : t)
		{
			if (map[c] == 0)
			{
				return false;
			}
			else
			{
				map[c]--;
			}
		}
		return true;
	}
	//141.环形链表
	bool hasCycle(ListNode* head)
	{
		/* 改val值来标志是否已经走过
		if (head == NULL)
		{
			return false;
		}
		ListNode* Node = head->next;
		while (Node != NULL)
		{
			if (Node->val == INT_MIN)
			{
				return true;
			}
			Node->val = INT_MIN;
			Node = Node->next;
		}
		return false;
		*/

		//Floyd判圈算法(龟兔赛跑算法)
		//快指针和慢指针。快指针初始位于head->next，慢指针初始位于head，快指针每次移动2步，慢指针每次移动1步。
		//如果两指针相遇，则有循环
		if (head == nullptr)
		{
			return false;
		}
		ListNode* Fast = head->next;
		ListNode* Slow = head;
		while (Fast != nullptr && Slow != nullptr)
		{
			if (Fast == Slow)
			{
				return true;
			}
			if (Fast->next == nullptr)
			{
				return false;
			}
			Fast = Fast->next->next;

			Slow = Slow->next;
		}
		return false;

	}
	//21.合并两个有序链表
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
	{
		ListNode* re = new ListNode(-1, nullptr);
		ListNode* cur = re;
		while (list1 && list2)
		{
			if (list1->val < list2->val)
			{
				cur->next = list1;
				list1 = list1->next;
			}
			else
			{
				cur->next = list2;
				list2 = list2->next;
			}
			cur = cur->next;
		}
		cur->next = (list1 != nullptr ? list1 : list2);
		return re->next;
	}
	//203.移除链表元素
	ListNode* removeElements(ListNode* head, int val)
	{
		/*if (!head)
		{
			return head;
		}
		ListNode* p = head;
		while (p->next)
		{
			if (p->val == val)
			{
				ListNode* Temp = p;
				p = p->next;
				delete[] Temp;
			}
			else
			{
				break;
			}
		}
		head = p->val == val ? nullptr : p;
		while (true)
		{
			if (!p->next)
			{
				break;
			}
			if (p->next->val == val)
			{
				ListNode* temp = p->next;
				p->next = p->next->next;
				delete[] temp;
			}
			else
			{
				p = p->next;
			}
		}
		return head;*/
		if (!head)
			return head;
		head->next = removeElements(head->next, val);
		return head->val == val ? head->next : head;
	}
	//206.反转链表
	ListNode* reverseList(ListNode* head)
	{
		/*
		if (!head || !head->next)
		{
			return head;
		}
		ListNode* List = reverseList(head->next);
		ListNode* p = List;
		while (p->next)
		{
			p = p->next;
		}
		head->next = nullptr;
		p->next = head;
		return List;
		*/

		if (!head || !head->next)
		{
			return head;
		}
		ListNode* Cur = head->next;
		ListNode* Fo = head;
		ListNode* Next = Cur->next;
		while (true)
		{
			if (Fo->next == Cur)
			{
				Fo->next = nullptr;
			}
			Cur->next = Fo;
			Fo = Cur;
			Cur = Next;
			if (Next)
			{
				Next = Next->next;
			}
			else
			{
				return Fo;
			}

		}


	}
	//83.删除排序链表中的重复元素
	ListNode* deleteDuplicates(ListNode* head)
	{
		if (!head || !head->next)
		{
			return head;
		}
		ListNode* Start = head;
		ListNode* End = Start->next;
		int CurNum = Start->val;
		while (End)
		{
			while (End && End->val == Start->val)
			{
				End = End->next;
			}
			Start->next = End;
			Start = End;
		}
		return head;
	}
	//20.有效的括号
	bool isValid(string s)
	{
		stack<char> stack;
		if (s.size() % 2 != 0)
		{
			return false;
		}
		for (char c : s)
		{
			if (c == '(' || c == '{' || c == '[')
			{
				stack.push(c);
			}
			else if ((c == ')' && (stack.size() == 0 || stack.top() != '(')) ||
				(c == '}' && (stack.size() == 0 || stack.top() != '{')) ||
				(c == ']' && (stack.size() == 0 || stack.top() != '[')))
			{
				return false;
			}
			else
			{
				stack.pop();
			}
		}
		if (stack.size() != 0)
		{
			return false;
		}
		return true;
	}
	//Morris遍历
	vector<int> MorrisTraversal(TreeNode* root)
	{
		vector<int> Re;
		TreeNode* Cur = root;
		while (Cur)
		{
			Re.emplace_back(Cur->val);
			if (!Cur->left)
			{
				Cur = Cur->right;
				continue;
			}
			TreeNode* MostRight = Cur->left;
			while (true)
			{
				if (!MostRight->right)
				{
					MostRight->right = Cur;
					Cur = Cur->left;
					break;
				}
				else if (MostRight->right == Cur)
				{
					MostRight->right = nullptr;
					Cur = Cur->right;
					break;
				}
				MostRight = MostRight->right;
			}
		}
		return Re;
	}
	//144.二叉树的前序遍历
	vector<int> preorderTraversal(TreeNode* root)
	{
		/*//Morris遍历方式, 只打印第一次遍历到的节点
		vector<int> Re;
		TreeNode* Cur = root;
		while (Cur)
		{
			if (!Cur->left)
			{
				Re.emplace_back(Cur->val);
				Cur = Cur->right;
				continue;
			}
			TreeNode* MostRight = Cur->left;
			while (true)
			{
				if (!MostRight->right)
				{
					MostRight->right = Cur;
					Re.emplace_back(Cur->val);
					Cur = Cur->left;
					break;
				}
				else if (MostRight->right == Cur)
				{
					MostRight->right = nullptr;
					Cur = Cur->right;
					break;
				}
				MostRight = MostRight->right;
			}
		}
		return Re;

		*/

		/* 迭代方法, 人为地维护一个栈
		stack<TreeNode*> s;
		TreeNode* Cur = root;
		vector<int> Re;
		while (Cur || !s.empty())
		{
			while (Cur)
			{
				Re.emplace_back(Cur->val);
				s.emplace(Cur);
				Cur = Cur->left;
			}
			Cur = s.top();
			s.pop();
			Cur = Cur->right;
		}
		return Re;
		*/

		//递归方式
		if (!root)
		{
			return{};
		}
		if (!root->left && !root->right)
		{
			return{ root->val };
		}
		vector<int> Re, Left, Right;
		Re.push_back(root->val);
		Left = preorderTraversal(root->left);
		Right = preorderTraversal(root->right);
		Re.insert(Re.end(), Left.begin(), Left.end());
		Re.insert(Re.end(), Right.begin(), Right.end());
		return Re;

	}
	//94.二叉树的中序遍历
	vector<int> inorderTraversal(TreeNode* root)
	{
		//Morris遍历
		vector<int> Re;
		TreeNode* Cur = root;
		while (Cur)
		{
			if (!Cur->left)
			{
				Re.emplace_back(Cur->val);
				Cur = Cur->right;
				continue;
			}
			TreeNode* MostRight = Cur->left;
			while (true)
			{
				if (!MostRight->right)
				{
					MostRight->right = Cur;
					Cur = Cur->left;
					break;
				}
				else if (MostRight->right == Cur)
				{
					MostRight->right = nullptr;
					Re.emplace_back(Cur->val);
					Cur = Cur->right;
					break;
				}
				MostRight = MostRight->right;
			}
		}
		return Re;

		/*迭代
		TreeNode* Cur = root;
		stack<TreeNode*> s;
		vector<int> Re;
		while (!s.empty() || Cur)
		{
		while (Cur)
		{
		s.emplace(Cur);
		Cur = Cur->left;
		}
		Cur = s.top();
		s.pop();
		Re.emplace_back(Cur->val);
		Cur = Cur->right;
		}
		return Re;
		*/
	}
	//145.二叉树的后序遍历
	void RightPathReverse(TreeNode* root, TreeNode* t, vector<int>& vec)//逆序输出以root为根的子树的最右路径
	{
		TreeNode* p = root;
		vector<int> Temp{ p->val };
		while (p != t)
		{
			p = p->right;
			Temp.emplace_back(p->val);
		}
		for (int i = Temp.size() - 1; i >= 0; i--)
		{
			vec.emplace_back(Temp[i]);
		}
	}
	vector<int> postorderTraversal(TreeNode* root)
	{
		//Morris遍历
		TreeNode* NewTree = new TreeNode(0, root, nullptr);
		TreeNode* Cur = NewTree;
		vector<int> Re;
		while (Cur)
		{
			if (!Cur->left)
			{
				Cur = Cur->right;
				continue;
			}
			TreeNode* MostRight = Cur->left;
			while (true)
			{
				if (!MostRight->right)
				{
					MostRight->right = Cur;
					Cur = Cur->left;
					break;
				}
				else if (MostRight->right == Cur)
				{
					MostRight->right = nullptr;
					RightPathReverse(Cur->left, MostRight, Re);
					Cur = Cur->right;
					break;
				}
				MostRight = MostRight->right;

			}
		}
		return Re;


		/* 迭代方法
		if (!root) return{};
		vector<int> vec;
		stack<TreeNode*> stk;
		TreeNode* prev = nullptr;
		auto node = root;
		while (!stk.empty() || node)
		{
		// 1.遍历到最左子节点
		while (node)
		{
		stk.emplace(node);
		node = node->left;
		}
		node = stk.top(); stk.pop();
		// 2.遍历最左子节点的右子树(右子树存在 && 未访问过)
		if (node->right && node->right != prev)
		{
		// 重复压栈以记录当前路径分叉节点
		stk.emplace(node);
		node = node->right;
		}
		else
		{
		// 后序：填充vec在node->left和node->right后面
		// 注意：此时node的左右子树应均已完成访问
		vec.emplace_back(node->val);
		// 避免重复访问右子树[记录当前节点便于下一步对比]
		prev = node;
		// 避免重复访问左子树[设空节点]
		node = nullptr;
		}
		}
		return vec;
		*/
	}
	//102.二叉树的层序遍历
	vector<TreeNode*> GetLevel(vector<TreeNode*> Parents, vector<vector<int>>& Val)
	{
		vector<TreeNode*> Re;
		vector<int> Val_Re;
		for (TreeNode* p : Parents)
		{
			if (p && p->left)
			{
				Re.emplace_back(p->left);
				Val_Re.emplace_back(p->left->val);
			}
			if (p && p->right)
			{
				Re.emplace_back(p->right);
				Val_Re.emplace_back(p->right->val);
			}

		}
		if (Val_Re.size() != 0)Val.emplace_back(Val_Re);
		return Re;
	}
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		/*
		vector<vector<int>> Re;
		vector<TreeNode*> Temp{ root };
		if (root)Re.emplace_back(1, root->val);
		while (true)
		{
			Temp = GetLevel(Temp, Re);
			if (Temp.size() == 0)
			{
				break;
			}
		}
		return Re;

		vector <vector <int>> ret;
		if (!root) {
			return ret;
		}
		*/

		queue<TreeNode*> q;
		vector<vector<int>> Re{};
		if (root)
		{
			q.emplace(root);
		}
		while (!q.empty())
		{
			int size = q.size();
			vector<int> Cur;
			for (int i = 0; i < size; i++)
			{
				TreeNode* Temp = q.front();
				Cur.push_back(Temp->val);
				q.pop();
				if (Temp->left)
				{
					q.emplace(Temp->left);
				}
				if (Temp->right)
				{
					q.emplace(Temp->right);
				}
			}
			Re.push_back(Cur);
		}
		return Re;
	}
	//104.二叉树的最大深度
	int maxDepth(TreeNode* root)
	{
		if (!root)return 0;
		if (!root->left && !root->right)return 1;
		int LeftDepth = maxDepth(root->left) + 1;
		int RightDepth = maxDepth(root->right) + 1;
		return max(LeftDepth, RightDepth);
	}
	//101.对称二叉树
	bool isSymmetric(TreeNode* root)
	{
		if (!root->left && !root->right)return true;
		TreeNode* p1 = root->left, * p2 = root->right;
		if ((p1 && !p2) || (!p1 && p2))return false;
		if (p1->val != p2->val)return false;
		if (!isSymmetric(new TreeNode(0, p1->left, p2->right)))return false;
		if (!isSymmetric(new TreeNode(0, p1->right, p2->left)))return false;
		return true;

	}
	//226.翻转二叉树
	TreeNode* invertTree(TreeNode* root)
	{
		if (!root)return root;
		TreeNode* Temp;
		Temp = root->left;
		root->left = root->right;
		root->right = Temp;
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
	//112.路径总和
	bool hasPathSum(TreeNode* root, int targetSum)
	{
		if (!root)return false;
		if (!root->left && !root->right)
		{
			if (root->val == targetSum)return true;
			return false;
		}
		if (hasPathSum(root->left, targetSum - root->val))return true;
		if (hasPathSum(root->right, targetSum - root->val))return true;
		return false;
	}
	//768.最多能完成排序的块 II
	int maxChunksToSorted(vector<int>& arr)
	{
		/*
		// 排序+哈希表
		vector<int> sort_arr(arr.begin(), arr.end());
		sort(sort_arr.begin(), sort_arr.end());
		int p = 0;
		int NumBlock = 0;
		unordered_map<int, int>map;
		while (p != arr.size())
		{
			map[sort_arr[p]]++;
			if (map[sort_arr[p]] == 0)map.erase(sort_arr[p]);
			map[arr[p]]--;
			if (map[arr[p]] == 0)map.erase(arr[p]);
			if (map.size() == 0)NumBlock++;
			p++;
		}
		return NumBlock;
		*/
		//单调栈
		stack<int> s;
		for (int num : arr)
		{
			if (s.empty() || num >= s.top())
			{
				s.emplace(num);
			}
			else
			{
				int Top = s.top();
				s.pop();
				while (!s.empty() && num < s.top())
				{
					s.pop();
				}
				s.emplace(Top);
			}
		}
		return s.size();
	}
	//700.二叉搜索树中的搜索
	TreeNode* searchBST(TreeNode* root, int val)
	{
		/*
		//递归算法
		if (!root)return nullptr;
		if (root->val == val)return root;
		if (!root->left && !root->right)
		{
			if (root->val == val)return root;
			return nullptr;
		}
		if (val < root->val)return searchBST(root->left, val);
		return searchBST(root->right, val);
		*/
		//迭代算法
		while (root)
		{
			if (root->val == val)return root;
			if (val < root->val)root = root->left;
			else if (val > root->val)root = root->right;
		}
		return nullptr;
	}
	//701.二叉搜索树中的插入操作
	TreeNode* insertIntoBST(TreeNode* root, int val)
	{
		TreeNode* Cur = root;
		if (!root)return new TreeNode(val);
		while (Cur)
		{
			if (val < Cur->val)
			{
				if (!Cur->left)
				{
					Cur->left = new TreeNode(val);
					return root;
				}
				Cur = Cur->left;
			}
			else
			{
				if (!Cur->right)
				{
					Cur->right = new TreeNode(val);
					return root;
				}
				Cur = Cur->right;
			}
		}
	}
	//1422.分割字符串的最大得分
	int maxScore(string s)
	{
		int Max = -1;
		int Total1 = count(s.begin(), s.end(), '1');
		int Cur0 = 0, Cur1 = 0;
		for (int i = 0; i < s.size() - 1; i++)
		{
			if (s[i] == '0')Cur0++;
			else Cur1++;
			int CurScore = Cur0 + Total1 - Cur1;
			if (CurScore > Max)Max = CurScore;
		}
		return Max;

	}
	//98.验证二叉搜索树
	bool isValid(TreeNode* root, long long Min, long long Max)
	{
		if (root->val <= Min || root->val >= Max)return false;
		if (root->left && !isValid(root->left, Min, root->val))return false;
		if (root->right && !isValid(root->right, root->val, Max))return false;
		return true;
	}
	bool isValidBST(TreeNode* root)
	{
		/*
		//Morris中序遍历，判断是否递增
		TreeNode* Cur = root;
		auto LastCur = -INFINITY;
		while (Cur)
		{
		if (!Cur->left)
		{
		if (Cur->val <= LastCur)return false;
		LastCur = Cur->val;
		Cur = Cur->right;
		continue;
		}
		TreeNode* p = Cur->left;
		while (true)
		{
		if (!p->right)
		{
		p->right = Cur;
		Cur = Cur->left;
		break;
		}
		if (p->right == Cur)
		{
		p->right = nullptr;
		if (Cur->val <= LastCur)return false;
		LastCur = Cur->val;
		Cur = Cur->right;
		break;
		}
		p = p->right;
		}
		}
		return true;
		*/

		/* //迭代中序遍历方法
		stack<TreeNode*> s;
		TreeNode* Cur = root;
		long long Last = LLONG_MIN;
		while (!s.empty() || Cur)
		{
			while (Cur)
			{
				s.emplace(Cur);
				Cur = Cur->left;
			}
			Cur = s.top();
			s.pop();
			if (Cur->val <= Last)return false;
			Last = Cur->val;
			Cur = Cur->right;
		}
		return true;
		*/

		bool a = isValid(root, LLONG_MIN, LLONG_MAX);
		return a;
	}
	//653.两数之和 IV - 输入二叉搜索树
	bool findTarget(TreeNode* root, int k)
	{
		/*
		//使用栈的中序遍历+哈希表
		stack<TreeNode*> s;
		unordered_set<int> set;
		TreeNode* Cur = root;
		while (!s.empty() || Cur)
		{
			while (Cur)
			{
				s.emplace(Cur);
				Cur = Cur->left;
			}
			Cur = s.top();
			s.pop();
			if (set.find(k - Cur->val) != set.end())return true;
			set.emplace(Cur->val);
			Cur = Cur->right;
		}
		return false;
		*/

		//Morris中序遍历，得到一个升序序列，用双指针的方法在升序序列中查找是否有和为目标值的两个值
		vector<int> vec;
		TreeNode* Cur = root;
		while (Cur)
		{
			if (!Cur->left)
			{
				vec.emplace_back(Cur->val);
				Cur = Cur->right;
				continue;
			}
			TreeNode* MostRight = Cur->left;
			while (MostRight)
			{
				if (!MostRight->right)
				{
					MostRight->right = Cur;
					Cur = Cur->left;
					break;
				}
				if (MostRight->right == Cur)
				{
					MostRight->right = nullptr;
					vec.emplace_back(Cur->val);
					Cur = Cur->right;
					break;
				}
				MostRight = MostRight->right;
			}
		}
		int p1 = 0, p2 = vec.size() - 1;
		while (p1 != p2)
		{
			if (vec[p1] + vec[p2] == k)return true;
			if (vec[p1] + vec[p2] > k)p2--;
			else p1++;
		}
		return false;
	}
	//235.二叉搜索树的最近公共祖先
	queue<TreeNode*> FindPath(TreeNode* root, TreeNode* p)
	{
		TreeNode* Cur = root;
		queue<TreeNode*> re;
		while (Cur->val != p->val)
		{
			re.emplace(Cur);
			if (p->val > Cur->val)Cur = Cur->right;
			else Cur = Cur->left;
		}
		re.emplace(Cur);
		return re;
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		/* 得到两个目标分别的路径
		queue<TreeNode*> path1 = FindPath(root, p);
		queue<TreeNode*> path2 = FindPath(root, q);
		TreeNode* re = nullptr;
		while (true)
		{
			if (path1.empty() || path2.empty() || path1.front() != path2.front())
			{
				return re;
			}
			re = path1.front();
			path1.pop();
			path2.pop();
		}
		return nullptr;
		*/
		TreeNode* re = root;
		while (true)
		{
			if (p->val > re->val && q->val > re->val)
			{
				re = re->right;
			}
			else if (p->val < re->val && q->val < re->val)
			{
				re = re->left;
			}
			else
			{
				return re;
			}
		}
		return nullptr;
	}
	//136.只出现一次的数字
	int singleNumber(vector<int>& nums)
	{
		/*
		//先排序，再判断
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); i = i + 2)
		{
			if (i == nums.size() - 1)return nums[i];
			if (nums[i] != nums[i + 1])return nums[i];
		}
		return INT_MIN;
		*/

		//使用异或运算
		/*
		任何数和 0 做异或运算，结果仍然是原来的数，即 a ⊕ 0 = a。
		任何数和其自身做异或运算，结果是 0，即 a ⊕ a = 0
		异或运算满足交换律和结合律，即 a ⊕ a ⊕ b = b ⊕ a ⊕ a = b ⊕ (a ⊕ a) = b ⊕ 0 = b
		*/
		int re = 0;
		for (int n : nums)
		{
			re ^= n;
		}
		return re;
	}
	//堆排序
	void adjust(vector<int>& arr, int len, int index)//递归方式构建大根堆(len是arr的长度, index是第一个非叶子节点的下标)
	{
		int left = 2 * index + 1; // index的左子节点
		int right = 2 * index + 2;// index的右子节点

		int maxIdx = index;
		if (left<len && arr[left] > arr[maxIdx])maxIdx = left;
		if (right<len && arr[right] > arr[maxIdx])maxIdx = right;

		if (maxIdx != index)
		{
			swap(arr[maxIdx], arr[index]);
			adjust(arr, len, maxIdx);
		}
	}
	vector<int> HeapSort(vector<int>& nums)
	{
		/*  //STL堆排序(升序)
		make_heap(nums.begin(), nums.end());//默认是大根堆
		sort_heap(nums.begin(), nums.end(), less<int>());
		return nums;
		*/

		/*  //STL堆排序(降序)
		make_heap(nums.begin(), nums.end(), greater<int>());//小根堆
		sort_heap(nums.begin(), nums.end(), greater<int>());
		return nums;
		*/

		// 构建大根堆（从最后一个非叶子节点向上）
		for (int i = nums.size() / 2 - 1; i >= 0; i--)
		{
			adjust(nums, nums.size(), i);
		}

		// 调整大根堆
		for (int i = nums.size() - 1; i >= 1; i--)
		{
			swap(nums[0], nums[i]);           // 将当前最大的放置到数组末尾
			adjust(nums, i, 0);               // 将未完成排序的部分继续进行堆排序
		}
		return nums;
	}
	//169.多数元素(不是求众数!!本函数是求nums中某个超过了一半的元素)
	int majorityElement(vector<int>& nums)
	{
		/*
		  //先进行堆排序，然后返回排序后的中间值
		make_heap(nums.begin(), nums.end());//默认是大根堆
		sort_heap(nums.begin(), nums.end(), less<int>());
		return nums[nums.size() / 2];
		*/

		/* //分治思想。如果数 a 是数组 nums 的众数，如果我们将 nums 分成两部分，那么 a 必定是至少一部分的众数。
		if (nums.size() == 1)return nums[0];
		int Left = majorityElement(vector<int>(nums.begin(), nums.begin() + nums.size() / 2));
		int Right = majorityElement(vector<int>(nums.begin() + nums.size() / 2, nums.end()));
		int Count1 = count(nums.begin(), nums.end(), Left);
		int Count2 = count(nums.begin(), nums.end(), Right);
		return (Count1 > Count2 ? Left : Right);
		*/

		// Boyer - Moore 投票算法
		/*
		核心就是对拼消耗。
		玩一个游戏，假设某一国的人口超过全世界总人口一半以上，并且能保证每个人口出去打仗都能跟其他国家的人一对一同归于尽。
		最后就只有这个国家的人口能活下来，就是胜利。
		最差的情况就是所有人都联合起来对付你（对应你每次选择作为计数器的数都是众数），但是只要不要内斗，最后肯定你赢。
		最后能剩下的必定是自己人。
		*/
		int Re = nums[0], count = 0;
		for (int n : nums)
		{
			if (n == Re)count++;
			else count--;
			if (count < 0)
			{
				count = 0;
				Re = n;
			}
		}
		return Re;

		/*
		先随机挑选一个数，再统计这个数出现的次数
		*/
		/*while (true)
		{
			int CurNum = nums[rand() % nums.size()];
			int Count = count(nums.begin(), nums.end(), CurNum);
			if (Count > floor(nums.size() / 2.0))return CurNum;
		}
		return INT_MIN;*/
	}
	//15.三数之和
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		if (nums.size() <= 2)return{};
		if (nums.size() == 3)
		{
			if (nums[0] + nums[1] + nums[2] == 0)return { {nums[0],nums[1],nums[2]} };
			else return {};
		}
		vector<vector<int>> re;
		make_heap(nums.begin(), nums.end());
		sort_heap(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 2;)
		{
			int p = i + 1, q = nums.size() - 1;
			int NumI = nums[i];
			while (p != q)
			{
				int NumP = nums[p], NumQ = nums[q];
				if (NumI + NumP + NumQ == 0)
				{
					re.push_back({ nums[i],NumP,NumQ });
					p++;
					while (p != q && NumP == nums[p])p++; //跳过重复值
				}
				else if (NumI + NumP + NumQ > 0)
				{
					q--;
					while (p != q && NumQ == nums[q])q--; //跳过重复值
				}
				else
				{
					p++;
					while (p != q && NumP == nums[p])p++; //跳过重复值
				}
			}
			while (i < nums.size() - 2 && NumI == nums[i])i++;
		}
		return re;
	}
	//75.颜色分类(荷兰国旗问题, 由Dijkstra提出)
	void sortColors(vector<int>& nums)
	{
		/*不止遍历一次
		int Num1 = 0;
		int p = 0, q = 0;
		while (p != nums.size())
		{
			if (nums[p] == 0)
			{
				nums[q] = 0;
				q++;
			}
			else if (nums[p] == 1)
			{
				Num1++;
			}
			p++;
		}
		p = q;
		while (Num1 != 0)
		{
			nums[p] = 1;
			Num1--;
			p++;
		}
		while (p != nums.size())
		{
			nums[p] = 2;
			p++;
		}
		*/
		//双指针解法
		/*
		[0,p0)都为0
		[p0,i)都为1
		[i,p2]未知
		(p2,end]都为2
		*/
		int p0 = 0, i = 0, p2 = nums.size() - 1;
		while (i <= p2)
		{
			if (nums[i] == 0)
			{
				swap(nums[p0], nums[i]);
				p0++;
				i++; //不用检查p0换过来的是什么，因为一定是1，nums[p0]为1
			}
			else if (nums[i] == 1)
			{
				i++;
			}
			else //nums[i] == 2
			{
				swap(nums[p2], nums[i]);
				p2--;
				//这里要检查从p2换过来的数，因为不确定nums[p2]的值，所以要进入下一个循环判断换过来的值
			}
		}
	}
	//56.合并区间
	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		make_heap(intervals.begin(), intervals.end());
		sort_heap(intervals.begin(), intervals.end());
		vector<vector<int>> re = { intervals[0] };
		for (vector<int> vec : intervals)
		{
			if (vec[0] > re.back()[1])re.emplace_back(vec);
			else if (vec[1] > re.back()[1])re.back()[1] = vec[1];
		}
		return re;
	}
	//119.杨辉三角 II
	vector<int> getRow(int rowIndex)
	{
		/*
		Cnm=Cn(m-1)*(n-m+1)/m;递推
		*/
		vector<int> re(rowIndex + 1, 1);
		for (int i = 1; i <= rowIndex / 2; i++)
		{
			re[i] = 1LL * re[i - 1] * (rowIndex - i + 1) / i;
		}
		for (int i = rowIndex / 2 + 1; i <= rowIndex - 1; i++)
		{
			re[i] = re[rowIndex - i];
		}
		return re;
	}
	//48.旋转图像
	void GetIndex(int i, int j, int n, int& NewI, int& NewJ)
	{
		//原(i,j)->新(j,n-i-1)
		NewI = j;
		NewJ = n - i - 1;
	}
	void rotate(vector<vector<int>>& matrix)
	{
		int n = matrix.size();
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = i; j < n - 1 - i; j++)
			{
				int NewI = 0, NewJ = 0;
				GetIndex(i, j, n, NewI, NewJ);
				swap(matrix[i][j], matrix[NewI][NewJ]);
				GetIndex(NewI, NewJ, n, NewI, NewJ);
				swap(matrix[i][j], matrix[NewI][NewJ]);
				GetIndex(NewI, NewJ, n, NewI, NewJ);
				swap(matrix[i][j], matrix[NewI][NewJ]);
			}
		}
	}
	//59.螺旋矩阵 II
	vector<vector<int>> generateMatrix(int n)
	{
		int Num = 1, Direction = 4;//1:上,2:下,3:左,4:右
		int X = -1, Y = 0;
		vector<vector<int>> re(n, vector<int>(n, -1));
		while (Num <= n * n)
		{
			if (Direction == 1)
			{
				Y--;
				while (true)
				{
					if (Y < 0 || re[Y][X] != -1)break;
					re[Y][X] = Num;
					Num++; Y--;
				}
				Y++;
				Direction = 4;
			}
			else if (Direction == 2)
			{
				Y++;
				while (true)
				{
					if (Y >= n || re[Y][X] != -1)break;
					re[Y][X] = Num;
					Num++; Y++;
				}
				Y--;
				Direction = 3;
			}
			else if (Direction == 3)
			{
				X--;
				while (true)
				{
					if (X < 0 || re[Y][X] != -1)break;
					re[Y][X] = Num;
					Num++; X--;
				}
				X++;
				Direction = 1;
			}
			else if (Direction == 4)
			{
				X++;
				while (true)
				{
					if (X >= n || re[Y][X] != -1)break;
					re[Y][X] = Num;
					Num++; X++;
				}
				X--;
				Direction = 2;
			}
		}
		return re;
	}
	//240.搜索二维矩阵 II
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		//从左上角看，矩阵就是一个二叉搜索树，左边都小于节点，右边都大于节点
		//Z字形搜索
		//if (matrix[0][0] > target)return false;
		//if (matrix[matrix.size() - 1][matrix[0].size() - 1] < target)return false;
		int m = 0, n = matrix[0].size() - 1;
		while (true)
		{
			if (m == matrix.size() || n == -1)return false;
			if (matrix[m][n] == target)return true;
			if (matrix[m][n] > target) //左移
			{
				n--;
			}
			else //下移
			{
				m++;
			}
		}
		return false;
	}
	//435.无重叠区间
	int eraseOverlapIntervals(vector<vector<int>>& intervals)
	{
		//把问题转化成：选出最多数量的区间，使得它们互不重叠
		/* 动态规划思想
		//把问题转化成：选出最多数量的区间，使得它们互不重叠
		make_heap(intervals.begin(), intervals.end());
		sort_heap(intervals.begin(), intervals.end());
		int n = intervals.size();
		vector<int> dp(n, 1);
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (intervals[j][1] <= intervals[i][0]) //不重合
				{
					//方案A：当前已知的以i结尾的最佳选取方法(最开始的时候，这种方案是“只选取自身”)
					//方案B：以j结尾的最佳选取后面跟上第i区段的方法
					//比较以上两种方案哪种更优
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		return n - *max_element(dp.begin(), dp.end());
		*/

		/*
		//贪心算法
		//按右边界排序，然后从左往右遍历，右边界结束的越早，留给后面的区间的空间就越大，不重合的区间个数就越多，intervals的长度减去最多的不重复的区间 就是最少删除区间的个数
		//
		// 堆排序，实际测试会慢于直接排序!
		make_heap(intervals.begin(), intervals.end(),[](vector<int>& a, vector<int>& b)
		{
			return a[1] < b[1];
		});
		sort_heap(intervals.begin(), intervals.end(),[](vector<int>& a, vector<int>& b)
		{
			return a[1] < b[1];
		});
		//传入的参数最好加上引用，更快
		sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b)
		{
			return a[1] < b[1];
		});
		int CurRight = intervals[0][1];
		int Num = 1;
		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[i][0] >= CurRight)
			{
				Num++;
				CurRight = intervals[i][1];
			}
		}
		return intervals.size() - Num;
		*/

		//按右边界排序，然后从左往右遍历，右边界结束的越早，留给后面的区间的空间就越大，不重合的区间个数就越多，intervals的长度减去最多的不重复的区间 就是最少删除区间的个数
		int count = 0;
		vector<Interval> inter(intervals.begin(), intervals.end());
		sort(inter.begin(), inter.end());
		int tem = INT_MIN;
		for (int i = 0; i < inter.size(); i++)
		{
			if (inter[i].l >= tem) tem = inter[i].r;
			else count++;
		}
		return count;
	}
	//334.递增的三元子序列
	bool increasingTriplet(vector<int>& nums)
	{
		if (nums.size() < 3)return false;
		int Num1 = INT_MAX, Num2 = INT_MAX;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] < Num1)
			{
				Num1 = nums[i];
				continue;
			}
			if (nums[i] > Num2)return true;
			if (nums[i] > Num1)
			{
				Num2 = nums[i];
			}
		}
		return false;
	}
	//238.除自身以外数组的乘积
	vector<int> productExceptSelf(vector<int>& nums)
	{
		int n = nums.size();
		vector<int> re(n, 1);
		for (int i = 1; i < n; i++)
		{
			re[i] = re[i - 1] * nums[i - 1];
		}
		int Num = nums[n - 1];
		for (int i = n - 2; i >= 0; i--)
		{
			re[i] = re[i] * Num;
			Num = Num * nums[i];
		}
		return re;
	}
	//560.和为 K 的子数组
	int subarraySum(vector<int>& nums, int k)
	{
		/* //前缀和，超时
		int n = nums.size(), re = 0;
		vector<int> Sum(n + 1, 0);
		for (int i = 0; i < n; i++)
		{
			Sum[i + 1] = Sum[i] + nums[i];
		}
		for (int i = 0; i < n + 1; i++)
		{
			for (int j = i + 1; j < n + 1; j++)
			{
				if (Sum[j] - Sum[i] == k)re++;
			}
		}
		return re;
		*/
		//前缀和+哈希表，map[i]=j表示：当前，前缀和为i的项有j个
		int n = nums.size(), re = 0, Sum = 0;
		unordered_map<int, int> map;
		map[0] = 1;
		for (int& n : nums)
		{
			Sum += n;
			auto it = map.find(Sum - k);
			if (it != map.end())re += it->second;
			map[Sum]++;
		}
		return re;
	}
	//415.字符串相加
	string addStrings(string num1, string num2)
	{
		string re(max(num1.size(), num2.size()) + 1, '0');
		int i = 1;
		bool Carry = false;
		while (true)
		{
			int Num1, Num2;
			if (num1.size() < i)Num1 = 0;
			else Num1 = num1[num1.size() - i] - '0';
			if (num2.size() < i)Num2 = 0;
			else Num2 = num2[num2.size() - i] - '0';
			int Sum = Num1 + Num2;
			if (Carry)
			{
				Sum++;
				Carry = false;
			}
			if (Sum >= 10)
			{
				Carry = true;
				Sum = Sum - 10;
			}
			re[re.size() - i] = Sum + '0';
			if (i > num1.size() && i > num2.size())break;
			i++;
		}
		if (re[0] == '0')re.erase(re.begin());
		return re;

	}
	//409.最长回文串
	int longestPalindrome1(string s)
	{
		int Num[52] = { 0 }, re = 0;
		bool Exist = false;
		for (char& c : s)
		{
			if (c > 90)Num[c - 'a' + 26]++;
			else Num[c - 'A']++;
		}
		for (int i = 0; i < 52; i++)
		{
			if (Num[i] % 2 == 0)re += Num[i];
			else
			{
				re += Num[i] - 1;
				Exist = true;
			}
		}
		if (Exist)re++;
		return re;
	}
	//43.字符串相乘
	string multiply(string num1, string num2)
	{
		/* //普通竖式
		int n1 = num1.size(), n2 = num2.size();
		string re(n1 + n2, '0');
		for (int i = n2 - 1; i >= 0; i--)
		{
			int Num = num2[i] - '0';
			string temp = num1;
			for (int j = 0; j < n2 - 1 - i; j++)temp.push_back('0');
			for (int j = 0; j < Num; j++)
			{
				re = addStrings(re, temp);
			}
		}
		while (re.size() > 1 && re[0] == '0')re.erase(re.begin());
		return re;
		*/

		//优化竖式
		//num1[i] x num2[j] 的结果记为 tmp(位数为两位，"0x","xy"的形式)，tmp的第一位位于 re[i+j]，第二位位于 re[i+j+1]
		if (num1 == "0" || num2 == "0")return "0";
		int n1 = num1.size(), n2 = num2.size();
		vector<int> re_Num(n1 + n2, 0);
		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < n2; j++)
			{
				int Mul = (num1[i] - '0') * (num2[j] - '0');
				re_Num[i + j] += Mul / 10;
				re_Num[i + j + 1] += Mul % 10;
			}
		}
		string re(n1 + n2, '0');
		for (int i = n1 + n2 - 1; i >= 0; i--)
		{
			while (re_Num[i] >= 10 && i != 0)
			{
				re_Num[i] -= 10;
				re_Num[i - 1]++;
			}
			re[i] = re_Num[i] + '0';
		}
		if (re[0] == '0')re.erase(re.begin());
		return re;
	}
	//290.单词规律
	bool wordPattern(string pattern, string s)
	{
		unordered_map<string, char> s2p;
		unordered_map<char, string> p2s;
		int Start = 0, WordNum = 0;
		while (Start < s.size())
		{
			int End = Start;
			while (End < s.size())
			{
				if (s[End] == ' ')break;
				End++;
			}
			if (WordNum >= pattern.size())return false;
			string word = s.substr(Start, End - Start);

			auto it = s2p.find(word);
			if (it == s2p.end())s2p[word] = pattern[WordNum];
			else if (it->second != pattern[WordNum])return false;

			auto it2 = p2s.find(pattern[WordNum]);
			if (it2 == p2s.end())p2s[pattern[WordNum]] = word;
			else if (it2->second != word)return false;

			WordNum++;
			Start = End + 1;
		}
		if (WordNum != pattern.size())return false;
		return true;
	}
	//763.划分字母区间
	vector<int> partitionLabels(string s)
	{
		int Hash[26];
		vector<int> re;
		int Start = 0, End = 0;
		for (int i = 0; i < s.size(); i++)Hash[s[i] - 'a'] = i;
		while (true)
		{
			if (Start >= s.size())break;
			End = Hash[s[Start] - 'a'];
			int i = Start + 1;
			while (true)
			{
				if (i >= End)break;
				End = max(End, Hash[s[i] - 'a']);
				i++;
			}
			re.emplace_back(End - Start + 1);
			Start = End + 1;
		}
		return re;
	}
	//49.字母异位词分组
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		/*
		vector<pair<string, int>> tmp;
		for (int i = 0; i < strs.size(); i++)
		{
			tmp.emplace_back(make_pair(strs[i], i));
		}
		for (pair<string, int>& p : tmp)
		{
			sort(p.first.begin(), p.first.end());
		}
		sort(tmp.begin(), tmp.end(), [](pair<string, int>& a, pair<string, int>& b)
		{
			return a.first < b.first;
		});
		vector<vector<string>> re;
		int i = 0;
		string Cur;
		while (true)
		{
			if (i == tmp.size())break;
			vector<string> Cur_str;
			Cur = tmp[i].first;
			Cur_str.emplace_back(strs[tmp[i].second]);
			i++;
			while (i < tmp.size() && tmp[i].first == Cur)
			{
				Cur_str.emplace_back(strs[tmp[i].second]);
				i++;
			}
			re.emplace_back(Cur_str);
		}
		return re;
		*/

		unordered_map<string, vector<string>> map;
		for (string& s : strs)
		{
			string temp = s;
			sort(s.begin(), s.end());
			map[s].push_back(temp);
		}
		vector<vector<string>> re;
		for (auto& it : map)
		{
			re.push_back(it.second);
		}
		return re;
	}
	//187.重复的DNA序列
	vector<string> findRepeatedDnaSequences(string s)
	{
		/*
		if (s.size() <= 10)return{};
		unordered_map<string, bool> set;
		vector<string> re;
		int Start = 0;
		while (Start + 9 < s.size())
		{
			string Cur = s.substr(Start, 10);
			auto it = set.find(Cur);
			if (it != set.end())
			{
				if (!it->second)
				{
					re.emplace_back(Cur);
					it->second = true;
				}
			}
			else set[Cur] = false;
			Start++;

		}
		return re;
		*/

		if (s.size() <= 10)return{};
		vector<string> re;
		unordered_map<unsigned int, bool> map;
		unsigned int Cur = 0;
		for (int i = 0; i < 10; i++)
		{
			switch (s[i])
			{
			case 'T':
				Cur += 1 * pow(10, 9 - i); break;
			case 'C':
				Cur += 2 * pow(10, 9 - i); break;
			case 'G':
				Cur += 3 * pow(10, 9 - i); break;
			default:
				break;
			}
		}
		map[Cur] = false;
		for (int Start = 1; Start + 9 < s.size(); Start++)
		{
			int Next = 0;
			switch (s[Start + 9])
			{
			case 'T':
				Next = 1; break;
			case 'C':
				Next = 2; break;
			case 'G':
				Next = 3; break;
			default:
				break;
			}
			Cur = 10 * (Cur % 1000000000) + Next;
			auto it = map.find(Cur);
			if (it == map.end())map[Cur] = false;
			else if (!it->second)
			{
				re.emplace_back(s.substr(Start, 10));
				it->second = true;
			}
		}
		return re;
	}
	//5.最长回文子串
	int expand(const string& s, int left, int right)
	{
		while (left >= 0 && right < s.size() && s[left] == s[right])
		{
			--left;
			++right;
		}
		return (right - left - 2) / 2;
	}
	string longestPalindrome(string s)
	{

		/* //中心开花算法
		if (s.size() == 1)return s;
		int MaxLen = 1;
		string re;
		for (int i = 0; i < s.size(); i++)
		{
			int j = 1;
			//奇数长度的回文子串
			while (true)
			{
				if (i - j < 0 || i + j >= s.size())break;
				if (s[i - j] != s[i + j])break;
				j++;
			}
			if (2 * j - 1 > MaxLen)
			{
				MaxLen = 2 * j - 1;
				re = s.substr(i - j + 1, 2 * j - 1);
			}
			j = 0;
			//偶数长度的回文子串
			while (true)
			{
				if (i - j < 0 || i + j + 1 >= s.size())break;
				if (s[i - j] != s[i + j + 1])break;
				j++;
			}
			if (2 * j > MaxLen)
			{
				MaxLen = 2 * j;
				re = s.substr(i - j + 1, 2 * j);
			}

		}
		if (re.size() == 0)re = s[0];
		return re;
		*/

		//马拉车算法(Manacher's Algorithm)
		int start = 0, end = -1;
		string t = "#";
		for (char c : s) {
			t += c;
			t += '#';
		}
		t += '#';
		s = t;

		vector<int> arm_len;
		int right = -1, j = -1;
		for (int i = 0; i < s.size(); ++i)
		{
			int cur_arm_len;
			if (right >= i)
			{
				int i_sym = j * 2 - i;
				int min_arm_len = min(arm_len[i_sym], right - i);
				cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
			}
			else
			{
				cur_arm_len = expand(s, i, i);
			}
			arm_len.push_back(cur_arm_len);
			if (i + cur_arm_len > right)
			{
				j = i;
				right = i + cur_arm_len;
			}
			if (cur_arm_len * 2 + 1 > end - start)
			{
				start = i - cur_arm_len;
				end = i + cur_arm_len;
			}
		}

		string ans;
		for (int i = start; i <= end; ++i)
		{
			if (s[i] != '#')
			{
				ans += s[i];
			}
		}
		return ans;
	}
	//2.两数相加
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		bool Carry = false;
		ListNode* p1 = l1, * p2 = l2;
		ListNode* re = new ListNode(INT_MIN, nullptr);
		ListNode* Cur = re;
		ListNode* pre = Cur;
		while (p1 != nullptr && p2 != nullptr)
		{
			int Sum = p1->val + p2->val;
			if (Carry)
			{
				Sum++;
				Carry = false;
			}
			if (Sum >= 10)
			{
				Sum -= 10;
				Carry = true;
			}
			Cur->val = Sum;
			Cur->next = new ListNode(INT_MIN, nullptr);
			pre = Cur;
			Cur = Cur->next;
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p2 != nullptr)
		{
			int Sum = p2->val;
			if (Carry)
			{
				Sum++;
				Carry = false;
			}
			if (Sum >= 10)
			{
				Sum -= 10;
				Carry = true;
			}
			Cur->val = Sum;
			Cur->next = new ListNode(INT_MIN, nullptr);
			pre = Cur;
			Cur = Cur->next;
			p2 = p2->next;
		}
		while (p1 != nullptr)
		{
			int Sum = p1->val;
			if (Carry)
			{
				Sum++;
				Carry = false;
			}
			if (Sum >= 10)
			{
				Sum -= 10;
				Carry = true;
			}
			Cur->val = Sum;
			Cur->next = new ListNode(INT_MIN, nullptr);
			pre = Cur;
			Cur = Cur->next;
			p1 = p1->next;
		}
		if (Carry)pre->next->val = 1;
		else pre->next = nullptr;
		return re;
	}
	//142.环形链表 II
	ListNode* detectCycle(ListNode* head)
	{
		ListNode* fast = head, * slow = head;
		while (true)
		{
			if (!fast || !slow || !fast->next || !slow->next)return nullptr;
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)break;
		}
		ListNode* re = head;
		while (re != slow)
		{
			re = re->next;
			slow = slow->next;
		}
		return re;
	}
	//160.相交链表
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
	{
		//我来到你的城市, 走过你来时的路
		//你们之所以相遇, 正是因为你走了ta走过的路, 而ta也刚好走了你走过的路
		if (!headA || !headB)return nullptr;
		ListNode* p1 = headA, * p2 = headB;
		while (true)
		{
			if (p1 == p2)return p1;
			if (p1)p1 = p1->next;
			else p1 = headB;
			if (p2)p2 = p2->next;
			else p2 = headA;
		}
		return nullptr;
	}
	//82.删除排序链表中的重复元素 II
	ListNode* deleteDuplicates2(ListNode* head)
	{
		if (!head)return nullptr;
		while (head->next && head->next->val == head->val)
		{
			int LastNum = head->val;
			if (head->next && head->next->val == LastNum)
			{
				ListNode* p = head->next->next;
				while (p && p->val == LastNum)
				{
					p = p->next;
				}
				head = p;
			}
			if (!head)return nullptr;
		}
		ListNode* p = head->next, * pre = head;
		while (p)
		{
			int LastNum = p->val;
			if (p->next && p->next->val == LastNum)
			{
				while (p->next && p->next->val == LastNum)
				{
					p = p->next;
				}
				pre->next = p->next;
				p = pre->next;
			}
			else
			{
				pre = p;
				p = p->next;
			}
		}
		return head;
	}
	//24.两两交换链表中的节点
	ListNode* swapPairs(ListNode* head)
	{
		if (!head)return nullptr;
		if (!head->next)return head;
		if (!head->next->next)
		{
			head->next->next = head;
			head = head->next;
			head->next->next = nullptr;
			return head;
		}
		if (!head->next->next->next)
		{
			ListNode* p1 = head, * p2 = head->next, * p3 = head->next->next;
			p2->next = p1;
			p1->next = p3;
			return p2;
		}
		ListNode* p1 = head, * p2 = p1->next, * p3 = p2->next, * p4 = p3->next;
		p1->next = p3;
		p2->next = p1;
		head = p2;

		p1 = head->next;
		p2 = p1->next;
		p3 = p2->next;
		p4 = p3->next;
		while (true)
		{
			if (!p3)break;
			p1->next = p3;
			p3->next = p2;
			p2->next = p4;
			p1 = p2;
			p2 = p2->next;
			if (!p2)
			{
				p3 = p4 = nullptr;
				break;
			}
			else
			{
				p3 = p2->next;
				if (!p3)p4 = nullptr;
				else p4 = p3->next;
			}
		}
		return head;
	}
	//25.K 个一组翻转链表
	ListNode* reverseKGroup(ListNode* head, int k)
	{
		if (!head)return nullptr;
		if (k <= 1)return head;
		ListNode* NewHead = new ListNode(INT_MIN, head);
		ListNode* pre = NewHead;
		ListNode* Start = NewHead->next;
		ListNode* End = NewHead, * Next = NewHead->next;
		while (true)
		{
			pre = End;
			Start = Next;
			End = Start;
			int CurSum = 1;
			while (true)
			{
				if (CurSum == k)break;
				if (!End || !End->next)return NewHead->next;
				End = End->next;
				CurSum++;
			}
			Next = End->next;
			ListNode* p1 = Start, * p2 = p1->next, * p3 = p2->next;
			while (p1 != End)
			{
				p2->next = p1;
				p1 = p2;
				p2 = p3;
				if (p2)p3 = p2->next;
			}
			pre->next = End;
			Start->next = Next;
			End = Start;
			Start = p1;
		}
		return nullptr;
	}
	//143.重排链表
	void reorderList(ListNode* head)
	{
		int n = 0;
		ListNode* tail = head, * medium = head;
		while (tail)
		{
			n++;
			tail = tail->next;
		}
		tail = head;
		for (int i = n / 2; i > 0; i--)
		{
			medium = tail;
			tail = tail->next;
		}
		medium->next = nullptr;
		ListNode* q = tail->next;
		tail->next = nullptr;
		while (true)
		{
			if (!q)break;
			ListNode* r = q->next;
			q->next = tail;
			tail = q;
			q = r;
		}
		ListNode* p = head;
		q = tail;
		while (true)
		{
			ListNode* p_next = nullptr, * q_next = nullptr;
			if (p->next)p_next = p->next;
			if (q->next)q_next = q->next;
			p->next = q;
			q->next = p_next ? p_next : q_next;
			p = p_next;
			q = q_next;
			if (!p_next || !q_next)break;
		}
	}
	//1249.移除无效的括号
	string minRemoveToMakeValid(string s)
	{
		stack<pair<bool, unsigned int>> st;// 0为'(', 1为')'
		bool* mask = new bool[s.size()];
		for (unsigned int i = 0; i < s.size(); i++)
		{
			if (s[i] == '(')
			{
				mask[i] = true;
				st.emplace(0, i);
			}
			else if (s[i] == ')')
			{
				if (st.empty())
				{
					mask[i] = false;
				}
				else if (st.top().first == 0)
				{
					st.pop();
					mask[i] = true;
				}
			}
			else mask[i] = true;
		}
		while (!st.empty())
		{
			mask[st.top().second] = false;
			st.pop();
		}
		string re;
		for (unsigned int i = 0; i < s.size(); i++)
		{
			if (mask[i])re += s[i];
		}
		return re;
	}
	//3.无重复字符的最长子串
	int lengthOfLongestSubstring(string s)
	{
		//滑动窗口法
		int pos[128] = { 0 }; //保证每个字符都有一个位置
		int left = 0, re = 0;
		for (int i = 0; i < s.size(); i++)
		{
			int OriginPos = pos[s[i]]; //这个字符上一次出现的位置的下一位
			left = max(left, OriginPos); //只关心在当前left的右侧的区间([left,i])
			pos[s[i]] = i + 1;
			re = max(re, i - left + 1);
		}
		return re;
	}
	//215.数组中的第K个最大元素
	void MakeMaxHeap(vector<int>& nums, int start, int end)
	{
		int root = start;//获取父节点的下标 
		int Child = root * 2 + 1;//左节点，因为下标0开始所以需要+1
		while (Child <= end)  //子节点不能超出范围，就是判断若无子节点直接退出 
		{
			if (Child + 1 <= end && nums[Child] < nums[Child + 1]) //先比较两个子节点大小，选择最大的
			{
				Child++;//指向右节点 
			}
			if (nums[root] > nums[Child]) //如果父节点大于子节点代表调整完毕，直接跳出函数
			{
				return;
			}
			else  //否则交换父子节点再继续子节点和孙节点比较
			{
				swap(nums[root], nums[Child]);
				root = Child;//父节点指向子节点 
				Child = Child * 2 + 1;//子节点指向孙节点 ，也就是这个点还需要跟孙节点进行比较
			}
		}
	}
	int QuickSort_FindK(vector<int>& nums, int start, int end, int k)
	{
		//-------    一趟快速排序    -------//
		srand(time(0));
		int left = start, right = end;
		int RandomIndex = rand() % (right - left + 1) + left;
		swap(nums[start], nums[RandomIndex]);
		int pivot = nums[start];
		while (left < right)
		{
			while (left < right && nums[right] >= pivot)
			{
				right--;
			}
			while (left < right && nums[left] <= pivot)
			{
				left++;
			}
			swap(nums[left], nums[right]);
		}
		swap(nums[start], nums[left]);
		//--------------------------------//
		if (nums.size() - left == k)
		{
			return nums[left];
		}
		if (nums.size() - left > k)return QuickSort_FindK(nums, left + 1, end, k);
		else return QuickSort_FindK(nums, start, left - 1, k);
	}
	int findKthLargest(vector<int>& nums, int k)
	{
		////基于堆排序 O(nlogn)
		//for (int i = nums.size() / 2 - 1; i >= 0; i--)
		//{
		//	MakeHeap(nums, i, nums.size() - 1);
		//}
		//int Current = 1;
		//for (int i = nums.size() - 1; i > 0 && Current < k; i--)
		//{
		//	swap(nums[0], nums[i]);
		//	MakeHeap(nums, 0, i - 1);
		//	Current++;
		//}
		//return nums[0];

		//基于快速排序 O(n)
		return QuickSort_FindK(nums, 0, nums.size() - 1, k);

	}
	//25.K 个一组翻转链表2
	ListNode* reverseKGroup2(ListNode* head, int k)
	{
		if (k == 1)return head;
		ListNode* pre = head;
		ListNode* start = head;
		ListNode* end = start;
		bool IsFirst = true;
		while (true)
		{
			if (!start)return head;
			int Curr = 1;
			while (Curr < k)
			{
				end = end->next;
				if (!end)return head;
				Curr++;
			}
			ListNode* next = end->next;

			ListNode* temp = start->next;
			pre->next = end;

			start->next = next;
			while (true)
			{
				ListNode* temp_next = temp->next;
				temp->next = start;
				start = temp;
				if (start == end)break;
				temp = temp_next;
			}
			if (IsFirst)
			{
				head = end;
				IsFirst = false;
			}
			else
			{
				Curr = 0;
				while (Curr < k)
				{
					pre = pre->next;
					Curr++;
				}
			}
			start = next;
			end = start;


		}
	}
	//15.三数之和
	vector<vector<int>> threeSum2(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		vector<vector<int>> re;
		unordered_set<int> TwoSum;
		int BaseNum = nums[0], SecondNum = nums[0];
		for (unsigned int i = 0; i < nums.size();)
		{
			BaseNum = nums[i];
			TwoSum.clear();
			for (unsigned int j = i + 1; j < nums.size(); )
			{
				SecondNum = nums[j];
				if (TwoSum.find(SecondNum) != TwoSum.end())
				{
					re.push_back({ BaseNum, SecondNum, -BaseNum - SecondNum });
					do
					{
						j++;
					} while (j < nums.size() && nums[j] == SecondNum);
					continue;
				}
				TwoSum.emplace(-BaseNum - SecondNum);
				j++;
			}
			do
			{
				i++;
			} while (i < nums.size() && nums[i] == BaseNum);
		}
		return re;
	}
	//236.二叉树的最近公共祖先
	TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		/*
			公司出了两个内鬼，每个人下面负责两个人，要找出这两个内鬼的共同指使者
		*/
		if (!root || root == p || root == q)return root; //root这个人是内鬼，则向上传递这个内鬼的信息，表明：此处找到一个内鬼
		TreeNode* Left = lowestCommonAncestor2(root->left, p, q);//如果Left非空，则表明root这个人负责的所有人中，至少有一个内鬼
		TreeNode* Right = lowestCommonAncestor2(root->right, p, q);//如果Right非空，则表明root这个人负责的所有人中，至少有一个内鬼
		if (Left && Right)return root;// 如果root这个人的Left和Right都非空，则表明root这个人就是两个内鬼的共同指使者
		return Left ? Left : Right; //如果root这个人下面只有一个内鬼，那么说明他还不是“两个内鬼的共同指使者”，那么继续向上传递这个内鬼的信息，表明：此处找到一个内鬼
	}
	//124.二叉树中的最大路径和
	int maxPathSum(TreeNode* root, int& re)
	{
		if (!root)return 0;
		int LeftMax = maxPathSum(root->left, re);
		int RightMax = maxPathSum(root->right, re);
		int LeftMediumRight = max(LeftMax, 0) + root->val + max(RightMax, 0); //LeftMediumRight表示: "左+中+右"的值，这个值不能继续向上传递
		int LeftMediumOrRightMedium = root->val + max(max(LeftMax, RightMax), 0); //LeftMediumOrRightMedium表示: "左+中"或"右+中"可以达到的最大值，这个最大值需要往上传递（可以连接）
		re = max({ re,LeftMediumRight,LeftMediumOrRightMedium }); //更新当前的"全局最大值"
		return LeftMediumOrRightMedium; //该层求得的"左+中"或"右+中"最大值需要向上层传递（可以和上层节点一起构成路径）
	}
	int maxPathSum(TreeNode* root)
	{
		int re = INT_MIN;
		maxPathSum(root, re);
		return re;
	}
	//227.基本计算器II
	int calculate(string s)
	{
		//以+-号为界限分割字符串，计算每一部分的结果存入frag数组
		vector<int> frag; //每一部分的结果
		frag.reserve(s.size() / 2);
		s += '+'; //因为只有s[i]为运算符的时候才会执行计算，为了把s的最后一个数也纳入计算，所以在最后面加一个+
		char PreOperator = '+'; // 当s[i]为运算符的时候，需要把frag的尾元素与当前的CurNum做运算，所以需要记录s[i]之前的一个运算，而s[i]当前的运算会在下次读取一个数之后再计算
		int CurNum = 0; //计算多位数的值
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == ' ')
			{
				continue;
			}
			if (isdigit(s[i]))
			{
				CurNum = s[i] - '0' + CurNum * 10; //计算多位数的值
			}
			else //当前是一个运算符，那么此时CurNum就读取完了上一个数
			{
				if (PreOperator == '*')
				{
					frag.back() *= CurNum; //把上一个元素的尾元素与当前最新的CurNum相乘，然后重新放入
				}
				else if (PreOperator == '/')
				{
					frag.back() /= CurNum;
				}
				else if (PreOperator == '+')
				{
					frag.emplace_back(CurNum);
				}
				else
				{
					frag.emplace_back(-CurNum);
				}
				PreOperator = s[i];
				CurNum = 0;
			}
		}
		return accumulate(frag.begin(), frag.end(), 0); //frag求和

		/* 思路与上面一样，只是不使用数组，把“最后才累加数组”改为“在for循环中就一个一个地加起来”
		s += '+';
		char prevSign = '+';
		int prev = 0, cur = 0, res = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == ' ') continue;
			if (s[i] >= '0' && s[i] <= '9')
			{
				cur = s[i] - '0' + 10 * cur;
			}
			else
			{
				if (prevSign == '+' || prevSign == '-')
				{
					res += prev;
					prev = (prevSign == '+' ? cur : -cur);
				}
				else if (prevSign == '*')
				{
					prev = prev * cur;
				}
				else
				{
					prev = prev / cur;
				}
				prevSign = s[i];
				cur = 0;
			}
		}
		return res + prev;  //最后再做一次运算。因为最后一个字符必为数字，那么for循环里面就不会做运算，所以需要再在最后做一次运算。
		*/
	}
	//739.每日温度
	vector<int> dailyTemperatures(vector<int>& temperatures)
	{
		//后序遍历解法, 从后往前看
		int n = temperatures.size();
		vector<int> re(n);
		re[n - 1] = 0; //最后一位一定是0
		for (int i = n - 2; i >= 0; i--)
		{
			int found = i + 1; //确保temperatures[found]是大于temperatures[i]中最靠近的位置. 先看它的后一位
			while (true)
			{
				if (temperatures[i] < temperatures[found]) //顺利找到
				{
					re[i] = found - i;
					break;
				}
				else if (re[found] == 0) //i处比found处还大(或等于)，而且found处的后面没人比found处还大(即re[found] == 0)，那么i处的后面肯定也没有比他大的
				{
					re[i] = 0;
					break;
				}
				found += re[found];//i处比found处还大(或等于), 但是found处后面有人比found处还大, 所以需要找到那个人, 把它再跟i处的比(更新found, 继续迭代)
			}
		}
		return re;

		////单调栈解法
		//stack<unsigned int> s; //栈里面记录的是下标
		//vector<int> re(temperatures.size(), 0);
		//for (int i = 0; i < temperatures.size(); i++)
		//{
		//	while (!s.empty() && temperatures[i] > temperatures[s.top()]) //当前数字比栈顶下标对应数字大, 则依次出栈并计算下标差值
		//	{
		//		re[s.top()] = i - s.top();
		//		s.pop();
		//	}
		//	s.emplace(i);
		//}
		//return re;
	}
	//554.砖墙
	int leastBricks(vector<vector<int>>& wall)
	{
		//把问题转化为: 穿过最多的缝隙
		unordered_map<int, int> Gaps; //key为宽度坐标(缝隙位置), value为在这个位置下有多少个缝隙
		int CurMaxGap = 0;
		for (vector<int>& line : wall)
		{
			int CurTotalWidth = 0;
			for (int i = 0; i < line.size() - 1; i++) //每一行最后一个砖块不用记
			{
				CurTotalWidth += line[i];
				Gaps[CurTotalWidth]++;
				CurMaxGap = max(Gaps[CurTotalWidth], CurMaxGap);
			}
		}
		return wall.size() - CurMaxGap; //穿过砖块数 = 行数 - 穿过的缝隙数
	}
	//438.找到字符串中所有字母异位词
	vector<int> findAnagrams(string s, string p)
	{
		//滑动窗口法
		vector<int> re;
		re.reserve(s.size());
		if (p.size() > s.size())return re;
		int Target[26] = { 0 }; //p里面, 每个字母出现的次数
		for (char& c : p)
		{
			Target[c - 'a']++;
		}
		int Temp[26] = { 0 }; //当前的窗口里面, 每个字母出现的次数
		for (int i = 0; i < p.size(); i++)
		{
			Temp[s[i] - 'a']++;
		}
		int CurStart = 0;
		while (true)
		{
			//Temp是否等于Target
			bool IsOK = true;
			for (int i = 0; i < 26; i++)
			{
				if (Temp[i] != Target[i])
				{
					IsOK = false;
					break;
				}
			}
			if (IsOK)
			{
				re.emplace_back(CurStart);
			}

			//滑动窗口往右走
			CurStart++;
			if (CurStart + p.size() > s.size())
			{
				break;
			}
			Temp[s[CurStart - 1] - 'a']--;
			Temp[s[CurStart + p.size() - 1] - 'a']++;
		}
		return re;
	}
	//791.自定义字符串排序
	string customSortString(string order, string s)
	{
		vector<int> Freq(26, 0);//先遍历s, 统计每个字母出现的次数放入Freq中
		for (char& c : s)
		{
			Freq[c - 'a']++;
		}
		string re(s.size(), '+'); //初始化为全为+的字符串
		int CurIndex = 0; //当前位置
		for (char& c : order) //再遍历order, 看当前字母c是否在s中出现过, 次数为x, 那么就把re的当前位置后添加x个c
		{
			while (Freq[c - 'a'] > 0)
			{
				re[CurIndex] = c;
				CurIndex++;
				Freq[c - 'a']--;
			} //循环退出时, Freq中该字母出现的次数归零了
		}
		for (int i = 0; i < 26; i++) //处理s中有但order中没有的字母, 从a~z遍历
		{
			while (Freq[i] > 0) //如果当前字母的Freq不为0, 说明它是s中有但order中没有的
			{
				re[CurIndex] = char(i + 'a'); //填入当前位置
				CurIndex++;
				Freq[i]--;
			} //循环退出时, Freq中该字母出现的次数归零了
		}
		return re;
	}
	//47.全排列 II:给定一个可包含重复数字的序列 nums ，按任意顺序返回所有不重复的全排列。
	void Do(vector<vector<int>>& re, vector<int>& nums, int CurDepth, string& used)
	{
		//used为01字符串, 第i位为1则说明nums[i]已经被使用过, CurDepth为当前这一层填入一个数之后的数列长度 
		if (CurDepth == nums.size()) //当前只差最后一位
		{
			re.push_back(re.back());//把当前结果的最后, 拷贝一个(此时, 最后一位就是上一层的根结果)
			int Index = used.find('0');//最后一层, 只需要找当前还有哪个位置没有被使用过
			re[re.size() - 2].push_back(nums[Index]);//补上倒数第二个结果的最后一位
			return;
		}
		int Index = -1;
		while (true)
		{
			int NextIndex = used.find('0'); //找当前第一个还没被使用过的
			if (Index != -1) //如果当前节点不是该层的第一个节点
			{
				used[Index] = '0'; //上一节点(兄弟节点)最后填的数字现在不使用了
				while (NextIndex <= Index || nums[NextIndex] == nums[Index] || used[NextIndex] == '1')
				{
					//当前节点的最后一位需要填的数的id(NextIndex)必须满足: 在Index的右边、与上一次(兄弟节点)填的数不同、该数还没被使用过
					NextIndex++; //依次往后寻找NextIndex
					if (NextIndex == nums.size()) //如果找到最后了还没找到, 那么这一层已经迭代完了
					{
						//此时, re.back()还是上一个兄弟节点(该层最后的一个节点)的值, re.back().back()是上一个兄弟节点(该层最后的一个节点)填的值
						re.back().pop_back(); //去掉上一个兄弟节点的填的值, 执行之后, re.back()就等于父节点的值
						used[Index] = '0'; //上一层数最后填的数字现在不使用了
						return; // 返回上一层父节点, 返回之后的re.back()就等于父节点的值, re.back().back()是父节点填的值
					}
				}
				Index = NextIndex; //找到了, 那么当前节点就填入NextIndex处的数, 此时re.back().back()还是上一个兄弟节点填的值
				re.back().back() = nums[Index];//把re.back().back()替换成当前节点需要填入的数
			}
			else //该节点是该层的第一个节点(只会执行一次)
			{
				Index = NextIndex;
				re.back().push_back(nums[Index]);//把上一层传下来的结果的末尾加上第一个还没使用的数
			}
			used[Index] = '1';//该数标记为"被使用过"
			Do(re, nums, CurDepth + 1, used); //在该节点进行深度递归, 往下继续找, 层数+1
			if (Index == nums.size() - 1) //当前节点填的数已是nums的最后一个数, 表明该层已经搜索完
			{
				re.back().pop_back(); //执行前, re.back()是当前节点的值, 执行后, re.back()是当前节点的父节点的值
				used[Index] = '0'; //当前节点填入的数标记为"没有被使用过"
				return; //返回上一层父节点, 返回之后的re.back()就等于父节点的值, re.back().back()是父节点填的值
			}
			//虽然当前节点填的数不是nums的最后一个数, 但有可能后面的数都是不能使用的
			bool IsFinished = true;
			for (int i = Index; i < nums.size(); i++)
			{
				//如果后面的数存在没有被使用过, 而且与当前节点填入的数不一样, 那么则表明: 当前节点填的数并不是最后一个可行数
				//那么就表明该层还要扩展新的节点
				if (used[i] == '0' && nums[i] != nums[Index])
				{
					IsFinished = false;
					break;
				}
			}
			if (IsFinished)
			{
				//当前节点填的数之后没有其他可以填入的数了(当前节点填的数已经是最后一个可行数了)
				re.back().pop_back(); //执行前, re.back()是当前节点的值, 执行后, re.back()是当前节点的父节点的值
				used[Index] = '0'; //当前节点填入的数标记为"没有被使用过"
				return; // 返回上一层父节点, 返回之后的re.back()就等于父节点的值, re.back().back()是父节点填的值
			}
		}
	}
	vector<vector<int>> permuteUnique2(vector<int>& nums)
	{
		make_heap(nums.begin(), nums.end());
		sort_heap(nums.begin(), nums.end()); //堆排序(升序)
		vector<vector<int>> re;
		re.push_back(vector<int>()); //初始时需要填入一个空vector
		string used(nums.size(), '0'); //used全部初始化为0 (避免使用vector<bool>)
		Do(re, nums, 1, used); //CurDepth为1, 因为下一层只尝试填入一个数, 填入后长度为1
		re.pop_back(); //结尾会有一个空vector
		return re;
	}
	//300.最长递增子序列
	int lengthOfLIS(vector<int>& nums)
	{
		//动态规划, O(n2)
		/*
		int N = nums.size();
		if (N < 2)
		{
			return N;
		}
		vector<int> MaxLen(N, 0); //MaxLen[i]表示以nums[i]结尾(必须取到nums[i])的最长递增子序列长度
		MaxLen[0] = 1;
		int re = 1; //最终结果就是MaxLen中的最大值
		for (int i = 1; i < N; i++)
		{
			int TempMax = 0;
			for (int j = i - 1; j >= 0; j--) //求MaxLen[i]
			{
				//在0 ~ i-1范围内, 找出所有的j满足nums[j]必须小于nums[i], 再在所有的MaxLen[j]中找最大值TempMax
				if (nums[j]<nums[i] && MaxLen[j]>TempMax)
				{
					TempMax = MaxLen[j];
				}
			}
			MaxLen[i] = TempMax + 1; //求MaxLen[i]就等于TempMax+1
			if (MaxLen[i] > re)
			{
				re = MaxLen[i];
			}
		}
		return re;
		*/

		//贪心+二分查找, O(nlogn)
		//如果我们要使上升子序列尽可能的长，则需要让序列上升得尽可能慢，因此希望每次在上升子序列最后加上的那个数尽可能的小
		//一个新员工一个老员工价值相当，老员工就可以走了，因为新员工被榨取的剩余空间更多。
		int N = nums.size();
		if (N < 2)
		{
			return N;
		}
		//Path[i]表示长度为i的所有可能的最长上升子序列的最后一个元素的最小值, Path[i]是递增的
		vector<int> Path(1, nums[0]); //Path的第一个元素为nums的第一个元素
		Path.reserve(N);
		for (int i = 1; i < N; i++)
		{   //如果nums[i]比当前Path的最后一个元素还大, 那么说明当前最长上升子序列长度+1
			if (nums[i] > Path.back())
			{
				Path.push_back(nums[i]);
			}
			else
			{//需要找到一个下标j, 使得Path[j-1]<nums[i]且Path[j]>nums[i]
				//使用二分法找到这个j, 再把Path[j]替换成nums[i]
				int MinIndex = 0, MaxIndex = Path.size() - 1;
				int Middle = (MinIndex + MaxIndex) / 2;
				while (Middle != MinIndex && Middle != MaxIndex)
				{
					if (Path[Middle] < nums[i])
					{
						MinIndex = Middle;
					}
					else
					{
						MaxIndex = Middle;
					}
					Middle = (MinIndex + MaxIndex) / 2;
				}
				//j有时候是Middle, 有时候可能是Middle+1, 需要判断
				if (Path[Middle] < nums[i])
				{
					Path[Middle + 1] = nums[i]; //替换
				}
				else if (Path[Middle] > nums[i])
				{
					Path[Middle] = nums[i]; //替换
				}
			}
		}
		return Path.size();
	}
	//234.回文链表
	bool isPalindrome(ListNode* head)
	{
		ListNode* p1 = head;
		ListNode* Fast = head;
		while (Fast && Fast->next)
		{
			p1 = p1->next;
			Fast = Fast->next->next;
		}
		ListNode* p2 = p1->next;
		p1->next = nullptr;
		while (p2)
		{
			ListNode* p3 = p2->next;
			p2->next = p1;
			p1 = p2;
			p2 = p3;
		}
		while (p1)
		{
			if (p1->val != head->val)
			{
				return false;
			}
			p1 = p1->next;
			head = head->next;
		}
		return true;
	}
	//26.删除有序数组中的重复项
	int removeDuplicates(vector<int>& nums)
	{
		int re = 1;
		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] == nums[re - 1])
			{
				continue;
			}
			nums[re] = nums[i];
			re++;
		}
		return re;
	}
	//35.搜索插入位置
	int searchInsert(vector<int>& nums, int target)
	{
		int Len = nums.size();
		int Low = 0, High = Len - 1;
		while (Low <= High)
		{
			int Mid = (Low + High) / 2;
			if (nums[Mid] == target)
			{
				return Mid;
			}
			if (nums[Mid] < target)
			{
				Low = Mid + 1;
			}
			else
			{
				High = Mid - 1;
			}
		}
		return Low;

	}
	//34.在排序数组中查找元素的第一个和最后一个位置
	int SearchPos(vector<int>& nums, int target, int MinIndex, int MaxIndex, bool Right)
	{
		int Low = MinIndex, High = MaxIndex;
		while (Low <= High)
		{
			int Mid = (Low + High) / 2;
			if (nums[Mid] == target)
			{
				if (Right)
				{
					Low = Mid + 1;
				}
				else
				{
					High = Mid - 1;
				}
				continue;
			}
			if (nums[Mid] > target)
			{
				High = Mid - 1;
			}
			else
			{
				Low = Mid + 1;
			}
		}
		if (Right)return High;
		return Low;
	}
	vector<int> searchRange(vector<int>& nums, int target)
	{
		int Low = 0, High = nums.size() - 1;
		int ReLow = -1, ReHigh = -1;
		while (Low <= High)
		{
			int Mid = (Low + High) / 2;
			if (nums[Mid] < target)
			{
				Low = Mid + 1;
			}
			else if (nums[Mid] > target)
			{
				High = Mid - 1;
			}
			else
			{
				ReHigh = SearchPos(nums, target, Mid, nums.size() - 1, true);
				ReLow = SearchPos(nums, target, 0, Mid, false);
				return { ReLow ,ReHigh };
			}
		}
		return { -1,-1 };
	}
	//阿里3.15笔试1
	void Calculate(TreeNode* root, int& Height, int& Num, int& re)
	{
		if (!root)return;
		Num++;
		Height++;
		int LeftHeight = 0, RightHeight = 0;
		int LeftNum = 0, RightNum = 0;
		Calculate(root->left, LeftHeight, LeftNum, re);
		Calculate(root->right, RightHeight, RightNum, re);
		if (abs(LeftNum + RightNum + 2 - pow(2, 1 + max(LeftHeight, RightHeight))) < 1e-5)
		{
			re++;
		}
		Num += LeftNum + RightNum;
		Height += max(LeftHeight, RightHeight);
	}
	int FullTreeNum(TreeNode* root)
	{
		if (!root)return 0;
		int re = 0;
		int Height = 0, Num = 0;
		Calculate(root, Height, Num, re);
		return re;
	}
	//阿里3.15笔试2
	int FindTriplet(vector<int>& nums)
	{
		map<int, int> map;
		for (int i = 0; i < nums.size(); i++)
		{
			map[nums[i]]++;
		}
		int re = 0;
		auto Cur = map.begin();
		auto Pre = Cur;
		Cur++;
		for (; Cur != map.end(); Cur++)
		{
			if (Cur->first - Pre->first == 1)
			{
				int m = Cur->second;
				int n = Pre->second;
				re += m * n * (m + n - 2) / 2;
			}
			Pre = Cur;
		}
		return re;
	}
	//阿里3.15笔试3
	int MinRange(vector<int>& nums, int k)
	{
		int n = nums.size();
		if (n < 2)
		{
			return 0;
		}
		PrintVector(nums);
		make_heap(nums.begin(), nums.end());
		sort_heap(nums.begin(), nums.end());
		PrintVector(nums);
		unordered_set<int> UsedIndex;
		while (k > 0)
		{
			if (UsedIndex.count(0) && UsedIndex.count(n - 1)) //【首位末位都不能动】
			{
				break;
			}
			if (UsedIndex.count(0)) //【首位不能动】（末位一定可以动）
			{
				nums.back() /= 2;
				int NewIndex = n - 1;
				while (NewIndex > 0 && nums[NewIndex - 1] > nums[NewIndex])
				{
					swap(nums[NewIndex - 1], nums[NewIndex]);
					NewIndex--;
				}
				for (int i = n - 1; i >= NewIndex; i--)
				{
					if (UsedIndex.count(i))
					{
						UsedIndex.erase(i);
						UsedIndex.insert(i + 1);
					}
				}
				UsedIndex.insert(NewIndex);
				k--;
				PrintVector(nums);
				continue;
			}
			if (UsedIndex.count(n - 1)) //【末位不能动】（首位一定可以动）
			{
				nums[0] *= 2;
				int NewIndex = 0;
				while (NewIndex < n - 1 && nums[NewIndex + 1] < nums[NewIndex])
				{
					swap(nums[NewIndex + 1], nums[NewIndex]);
					NewIndex++;
				}
				for (int i = 0; i <= NewIndex; i++)
				{
					if (UsedIndex.count(i))
					{
						UsedIndex.erase(i);
						UsedIndex.insert(i - 1);
					}
				}
				UsedIndex.insert(NewIndex);
				k--;
				PrintVector(nums);
				continue;
			}
			//【首位末位都可以动】
			int NewMin = min(nums[0] * 2, nums[1]);
			int NewMax = max(nums.back() / 2, nums[n - 2]);
			if (max(nums.back(), nums[0] * 2) - NewMin < NewMax - min(nums[0], nums.back() / 2)) // 动首位更划算
			{
				nums[0] *= 2;
				int NewIndex = 0;
				while (NewIndex < n - 1 && nums[NewIndex + 1] < nums[NewIndex])
				{
					swap(nums[NewIndex + 1], nums[NewIndex]);
					NewIndex++;
				}
				for (int i = 0; i <= NewIndex; i++)
				{
					if (UsedIndex.count(i))
					{
						UsedIndex.erase(i);
						UsedIndex.insert(i - 1);
					}
				}
				UsedIndex.insert(NewIndex);
				k--;
				PrintVector(nums);
				continue;
			}
			else //动末位更划算
			{
				nums.back() /= 2;
				int NewIndex = n - 1;
				while (NewIndex > 0 && nums[NewIndex - 1] > nums[NewIndex])
				{
					swap(nums[NewIndex - 1], nums[NewIndex]);
					NewIndex--;
				}
				for (int i = n - 1; i >= NewIndex; i--)
				{
					if (UsedIndex.count(i))
					{
						UsedIndex.erase(i);
						UsedIndex.insert(i + 1);
					}
				}
				UsedIndex.insert(NewIndex);
				k--;
				PrintVector(nums);
				continue;
			}
		}
		return nums.back() - nums.front();
	}
	//美团3.18笔试1
	int CaptureEnemiesMaxNum(vector<vector<int>>& Enemies, int MaxDX, int MaxDY)
	{
		sort(Enemies.begin(), Enemies.end(), [](vector<int>& e1, vector<int>& e2)
			{
				if (e1[0] != e2[0])
				{
					return e1[0] < e2[0];
				}
				else
				{
					return e1[1] < e2[1];
				}
			});
		int n = Enemies.size();
		int re = INT_MIN;
		for (int i = 0; i < n; i++)
		{
			int CurNum = 0;
			for (int j = 0; j < n; j++)
			{
				if (Enemies[j][0] >= Enemies[i][0] && Enemies[j][0] - Enemies[i][0] <= MaxDX && Enemies[i][1] >= Enemies[j][1] && Enemies[i][1] - Enemies[j][1] <= MaxDY)
				{
					CurNum++;
				}
			}
			re = max(re, CurNum);
		}
		return re;
	}
	//美团3.18笔试2
	int RibbonMaxLen(vector<int>& Ribbon, int K)
	{
		int n = Ribbon.size();
		if (K >= n)
		{
			return n;
		}
		int p = 0, q = 0;
		int re = 0;
		unordered_map<int, int> map;
		while (q < n)
		{
			if (map.find(Ribbon[q]) != map.end()) //已存在
			{
				map[Ribbon[q]]++;
			}
			else //不存在
			{
				map[Ribbon[q]] = 1;
				while (map.size() > K)
				{
					map[Ribbon[p]]--;
					if (map[Ribbon[p]] == 0)
					{
						map.erase(Ribbon[p]);
					}
					p++;
				}
			}
			re = max(re, q - p + 1);
			q++;
		}
		return re;

	}
	//美团3.18笔试3
	string MinPalindromeString(string str)
	{
		int n = str.size();
		int p = 0, q = n - 1;
		int Use = 0;
		while (p <= q)
		{
			if (str[p] < str[q])
			{
				str[q] = str[p];
				Use++;
			}
			else if (str[p] > str[q])
			{
				str[p] = str[q];
				Use++;
			}
			p++;
			q--;
		}
		p = 0; q = n - 1;
		if (Use == 1 && n % 2 == 1)
		{
			str[n / 2] = 'a';
			Use++;
		}
		else if (Use == 0)
		{
			for (int i = 0; i <= (n - 1) / 2; i++)
			{
				if (str[i] != 'a')
				{
					str[i] = str[n - 1 - i] = 'a';
					Use = Use + (i == n - 1 - i ? 1 : 2);
					break;
				}
			}
		}
		return str;
	}
	//百度3.13笔试1
	void CanRearrange()
	{
		int n;
		cin >> n;
		vector<string> strs(n);
		for (int i = 0; i < n; i++)
		{
			cin >> strs[i];
		}
		vector<char> re(n);
		string pattern = "Baidu";
		sort(pattern.begin(), pattern.end());
		for (int i = 0; i < n; i++)
		{
			if (strs[i].size() != 5)
			{
				re[i] = 0;
				continue;
			}
			sort(strs[i].begin(), strs[i].end());
			re[i] = (strs[i] == pattern ? 1 : 0);
		}
		for (int i = 0; i < n - 1; i++)
		{
			cout << (re[i] == 1 ? "Yes" : "No") << endl;
		}
		cout << (re.back() == 1 ? "Yes" : "No");
	}
	//133.克隆图
	Node* cloneGraph(Node* node)
	{
		//先克隆节点(的值), 再克隆节点之间的边
		if (!node)return nullptr;
		unordered_map<int, Node*> NewNodes; //节点的值 → 新的节点
		queue<Node*> q;
		q.emplace(node);
		while (!q.empty()) //广度优先遍历
		{
			Node* Cur = q.front(); //原节点
			q.pop();
			Node* NewNode = new Node(Cur->val, Cur->neighbors);  //新节点, 但新节点的邻居节点的地址先暂时保持原图的地址
			NewNodes[Cur->val] = NewNode;
			for (Node* Neighbor : Cur->neighbors) //遍历该节点的邻居节点, 如果之前没有访问过, 就入队
			{
				if (NewNodes.find(Neighbor->val) == NewNodes.end())
				{
					Node* NewNeighbor = new Node(Neighbor->val, Neighbor->neighbors);
					NewNodes[Neighbor->val] = NewNeighbor;
					q.emplace(Neighbor);
				}
			}
		}
		for (auto it = NewNodes.begin(); it != NewNodes.end(); it++) //修复边的关系, 将邻居节点的地址改成新创建的节点的地址
		{
			for (int i = 0; i < it->second->neighbors.size(); i++)
			{
				int NeighborID = it->second->neighbors[i]->val;
				it->second->neighbors[i] = NewNodes[NeighborID];
			}
		}
		return NewNodes[node->val];
	}
	//16.最接近的三数之和
	int threeSumClosest(vector<int>& nums, int target)
	{
		//先排序, 然后固定一个指针, 浮动left和right两个指针
		make_heap(nums.begin(), nums.end());
		sort_heap(nums.begin(), nums.end());
		int n = nums.size();
		int re = nums[0] + nums[1] + nums[2]; //初始值, 不能设置成INT_MIN或INT_MAX, 因为下面还要对它做加减法
		for (int i = 0; i < n - 2; i++) //按顺序固定一个指针
		{
			int TempSum = nums[i] + nums[n - 2] + nums[n - 1]; //TempSum已经是固定指针为i时候的最大可能和了
			if (TempSum < target) //这个最大可能和的TempSum如果还是小于target, 那么不用做浮动指针了, 直接i++
			{
				re = abs(TempSum - target) < abs(re - target) ? TempSum : re;
				continue;
			}
			TempSum = nums[i] + nums[i + 1] + nums[i + 2]; //TempSum已经是固定指针为i时候的最小可能和了
			if (TempSum > target) //这个最小可能和的TempSum如果还是大于target, 那么不用做浮动指针了, 直接i++
			{
				re = abs(TempSum - target) < abs(re - target) ? TempSum : re;
				continue;
			}
			int left = i + 1, right = n - 1; //浮动指针
			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];
				if (sum == target)
				{
					return target;
				}
				if (sum < target) //如果当前和太小, 那么left右移
				{
					re = abs(sum - target) < abs(re - target) ? sum : re;
					left++;
					while (left + 1 < right && nums[left + 1] == nums[left]) //跳过相同的数
					{
						left++;
					}
				}
				else //如果当前和太大, 那么right左移
				{
					re = abs(sum - target) < abs(re - target) ? sum : re;
					right--;
					while (right - 1 > left && nums[right - 1] == nums[right]) //跳过相同的数
					{
						right--;
					}
				}
			}
		}
		return re;
	}
	//54.螺旋矩阵
	vector<int> spiralOrder(vector<vector<int>>& matrix)
	{
		int row = matrix.size(), col = matrix[0].size();
		vector<int> re(row * col);

		int CurX = 0, CurY = 0;
		int CurIndex = 0;
		vector<int> Diff(4, 0);

		while (CurIndex < row * col)
		{
			int CurDirection = 2; //向右
			while (CurIndex < row * col && CurX <= col - (Diff[CurDirection - 1] + 1))
			{
				re[CurIndex] = matrix[CurY][CurX];
				CurX++;
				CurIndex++;
			}
			Diff[CurDirection - 1]++;
			CurX--;
			CurDirection = 3; //向下
			CurY++;
			while (CurIndex < row * col && CurY <= row - (Diff[CurDirection - 1] + 1))
			{
				re[CurIndex] = matrix[CurY][CurX];
				CurY++;
				CurIndex++;
			}
			Diff[CurDirection - 1]++;
			CurY--;
			CurDirection = 4; //向左
			CurX--;
			while (CurIndex < row * col && CurX >= Diff[CurDirection - 1])
			{
				re[CurIndex] = matrix[CurY][CurX];
				CurX--;
				CurIndex++;
			}
			Diff[CurDirection - 1]++;
			CurX++;
			CurDirection = 1; //向上
			CurY--;
			while (CurIndex < row * col && CurY >= Diff[CurDirection - 1] + 1)
			{
				re[CurIndex] = matrix[CurY][CurX];
				CurY--;
				CurIndex++;
			}
			Diff[CurDirection - 1]++;
			CurY++;
			CurX++;
		}
		return re;

	}
	//剑指 Offer 40:最小的k个数
	void MakeMinHeap(vector<int>& arr, int start, int end) //构建小根堆
	{
		int root = start, child = 2 * root + 1;
		while (child <= end)
		{
			if (child + 1 <= end && arr[child + 1] < arr[child]) //看root的哪个孩子更小
			{
				child++;
			}
			if (arr[root] > arr[child])
			{
				swap(arr[child], arr[root]);
				root = child;
				child = 2 * root + 1;
			}
			else
			{
				return;
			}
		}
	}
	int Partition(vector<int>& arr, int start, int end) //随机在start和end中选择一个数作为Pivot, 然后把他与end处交换, 最后将数组交换为: [start,i)的元素都小于等于Pivot, (i,end]处的元素都大于等于Pivot, arr[i]==Pivot, 返回i
	{
		srand((unsigned)time(NULL));
		int PivotIndex = rand() % (end - start + 1) + start;
		swap(arr[PivotIndex], arr[end]);
		int i = start - 1, Pivot = arr[end];
		for (int j = start; j <= end - 1; j++)
		{
			if (arr[j] <= Pivot) //直到找到一个数小于或等于Pivot(即: 应该放在Pivot左边)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		i++;
		swap(arr[i], arr[end]);
		return i;
	}
	void PartitionK(vector<int>& arr, int start, int end, int k) //递归函数
	{
		if (start >= end)return;
		int PivotIndex = Partition(arr, start, end);
		int CurK = PivotIndex - start + 1;
		//此时: [start, PivotIndex]一定是前CurK小的数, [PivotIndex,end]一定是前CurK大的数
		if (CurK == k)
		{
			return;
		}
		if (CurK > k) //前k小的数一定在[start, PivotIndex-1]里面
		{
			PartitionK(arr, start, PivotIndex - 1, k);
		}
		else //前CurK小的数已经得到了, 还需要剩下的(k-CurK)小的数, 它们一定在[PivotIndex+1,end]区间内
		{
			PartitionK(arr, PivotIndex + 1, end, k - CurK);
		}
	}
	vector<int> getLeastNumbers(vector<int>& arr, int k)
	{
		//基于快速选择算法(快速排序的变形), 时间复杂度平均为O(n)最坏为O(n^2), 空间复杂度平均为O(logn)最坏为O(n)
		if (k == arr.size())return arr;
		if (k == 0)return vector<int>();
		int n = arr.size();
		PartitionK(arr, 0, n - 1, k);
		//此时: arr的前k个一定是最小的k个数
		return vector<int>(arr.begin(), arr.begin() + k);

		//基于优先队列(底层实现是堆), 时间复杂度O(nlogk), 空间复杂度O(k)
		//相比快速选择算法的优点: 1.不会对原数组做修改. 2.数字可以一个一个地输入, 适合数据量非常大的情况
		/*
		if (k == arr.size())return arr;
		if (k == 0)return vector<int>();
		int n = arr.size();
		//priority_queue<int, vector<int>, greater<int>> q; //小根堆
		//priority_queue<int, vector<int>, less<int>> q;//大根堆
		priority_queue<int> q; //默认是大根堆
		int i = 0;
		while (q.size() < k)
		{
			q.push(arr[i]);
			i++;
		}
		while (i < n)
		{
			q.push(arr[i]);
			q.pop();
			i++;
		}
		vector<int> re(k);
		for (i = 0; i < k; i++)
		{
			re[i] = q.top();
			q.pop();
		}
		return re;
		*/

		//基于数组排序, 非常快, 但是空间复杂度很大, 而且arr中必须都为非负整数!
		/*
		int MaxSpace = 10001; //MaxSpace必须大于arr中可能出现的最大值
		int MaxNum = INT_MIN; //arr中的最大值
		vector<int> count(MaxSpace, 0); // count[i]表示: arr中数i出现了多少次
		for (int& num : arr)
		{
			count[num]++;
			MaxNum = max(MaxNum, num);
		}
		count.resize(MaxNum + 1); //及时降低空间占用
		vector<int> re(k);
		int CurK = 0, CurIndex = 0;
		while (CurK < k)
		{
			while (CurK < k && count[CurIndex] > 0)
			{
				re[CurK] = CurIndex;
				CurK++;
				count[CurIndex]--;
			}
			CurIndex++;
		}
		return re;
		*/

		//基于小根堆的全数组排序【超时!】
		/*if (k == arr.size())return arr;
		if (k == 0)return vector<int>();
		int n = arr.size();
		vector<int> re(k);
		int CurNum = 0;
		while (CurNum < k)
		{
			for (int i = (n - 2 - CurNum) / 2; i >= 0; i--)
			{
				MakeMinHeap(arr, i, n - 1 - CurNum);
			}
			re[CurNum] = arr[0];
			swap(arr[0], arr[n - 1 - CurNum]);
			CurNum++;
		}
		return re;*/
	}
	//22.括号生成
	vector<string> generateParenthesis(int n)
	{
		//递归, 用最基本的单位"()"进行组装
		if (n == 1)
		{
			return { "()" };
		}
		vector<string> LastResult = generateParenthesis(n - 1);
		unordered_set<string> set; //去重
		for (string& s : LastResult)
		{
			for (int i = 0; i < s.size(); i++) //s[0:i-1]+"()"+s[i:end]
			{
				set.insert(s.substr(0, i) + "()" + s.substr(i));
			}
		}
		return { set.begin(),set.end() };
	}
	//46.全排列: 给定一个不含重复数字的数组nums, 返回其所有可能的全排列。
	void DoPermute(vector<int>& nums, vector<int>& path, vector<vector<int>>& re, string& use)
	{
		if (path.size() == nums.size()) //当前已经是一个完整的path, 已经是一个全排列
		{
			re.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); i++) //遍历这一层递归中, use为0的所有位置
		{
			if (use[i] == '1')continue;
			use[i] = '1';
			path.push_back(nums[i]);
			DoPermute(nums, path, re, use);
			path.pop_back();
			use[i] = '0';
		}
	}
	vector<vector<int>> permute(vector<int>& nums)
	{
		//采用"递归-回溯"的思想: 不撞南墙不回头. 时间复杂度O(n*n!), 空间复杂度O(n)
		if (nums.size() == 1)
		{
			return { nums };
		}
		int n = nums.size();
		unsigned long long ReCount = 1; //求n!
		for (int i = 1; i <= n; i++)
		{
			ReCount *= i;
		}
		vector<vector<int>> re;
		re.reserve(ReCount);
		string use(n, '0'); //use[i]表示nums[i]当前是否已被使用过, 避免使用vector<bool>
		vector<int> path;
		path.reserve(n);
		DoPermute(nums, path, re, use);
		return re;
	}
	//1004.最大连续1的个数 III: 给定一个二进制数组nums和一个整数k, 如果可以翻转最多k个0, 则返回数组中连续 1 的最大个数
	int longestOnes(vector<int>& nums, int k)
	{
		//问题转化为: 窗口内0的数量不超过k
		//滑动窗口法, 将right不断地右移直到窗口中0的数量超过k, 再把left不断右移知道窗口中0的数量等于k
		int n = nums.size();
		if (k == n)return n;
		int num0 = 0, re = 0; //num0表示窗口中0的数量
		for (int left = 0, right = 0; right < n; right++)
		{
			//每次运行到这里时, nums[right]还没有经过判断, 即nums[left:right-1]内的0的数量一定不超过k, 而nums[left:right]内的0的数量则目前还不一定
			if (nums[right] == 1) //如果当前right值为1, 那么肯定是可以的(不影响窗口内0的数量), 计算长度之后right++
			{
				re = max(re, right - left + 1);
				continue;
			}
			num0++; //运行到这里说明nums[right]为0, 所以num0++
			if (num0 > k) //如果nums[left:right]内0的数量已经超了, 那么把left往右移, 直到移除一个0
			{
				while (nums[left] == 1) //只要nums[left]当前为1, 那么就可以放心大胆的往右移, 因为不影响窗口内0的数量
				{
					left++;
				}
				left++; //运行到这里说明当前nums[left]=0, 所以需要再把left++来移除当前的0
				num0--;
			}
			re = max(re, right - left + 1);
		}
		return re;
	}
	//316.去除重复字母: 去除字符串中重复的字母，使得每个字母只出现一次。需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）
	string removeDuplicateLetters(string s)
	{
		//单调栈的思想: 让字典序小的字符尽可能出现在靠前(靠近栈底)的位置, 时间复杂度O(n), 空间复杂度O(Σ)
		int n = s.size();
		vector<int> count(26, 0); //每个字符出现的次数
		for (char& c : s)
		{
			count[c - 'a']++;
		}
		string re = ""; //用string代表单调栈, re.back()就是栈顶, 之后的步骤会确保栈:【"尽可能地"递增, 除非某个字符在此之后不会再碰到】
		vector<char> IsExist(26, '0'); //栈里面是否已经存在这个字符了
		for (char& c : s) //遍历这个字符串
		{
			if (re.empty()) //如果栈为空(只会执行一次), 直接把当前字符压入栈中
			{
				re.push_back(c);
				IsExist[c - 'a'] = '1';
				count[c - 'a']--; //该字符后面剩下的次数要减一
				continue;
			}
			if (IsExist[c - 'a'] == '1') //如果栈里面已经有这个字符了, 那么直接跳过
			{
				count[c - 'a']--;
				continue;
			}
			while (!re.empty() && re.back() > c && count[re.back() - 'a'] > 0) //只要【当前字符比栈顶字符要小, 而且栈顶字符在这之后还会碰到】, 那么目前就可以把栈顶字符弹出, 反正之后还会遇到
			{
				IsExist[re.back() - 'a'] = '0';
				re.pop_back();
			}
			re.push_back(c); //运行到这里, 说明【当前字符比栈顶字符要大】或者【之后没有栈顶字符了】, 那么直接把当前字符压入栈
			IsExist[c - 'a'] = '1';
			count[c - 'a']--;
		}
		return re;
	}
	//200.岛屿数量
	void Expand(vector<vector<char>>& grid, int row, int col)
	{
		if (grid[row][col] != '1')return;
		grid[row][col] = '2';
		if (col + 1 < grid[0].size() && grid[row][col + 1] == '1')
		{
			Expand(grid, row, col + 1);
		}
		if (row + 1 < grid.size() && grid[row + 1][col] == '1')
		{
			Expand(grid, row + 1, col);
		}
		if (col - 1 >= 0 && grid[row][col - 1] == '1')
		{
			Expand(grid, row, col - 1);
		}
		if (row - 1 >= 0 && grid[row - 1][col] == '1')
		{
			Expand(grid, row - 1, col);
		}
	}
	int numIslands(vector<vector<char>>& grid)
	{
		int row = grid.size(), col = grid[0].size(), re = 0;
		//广度优先搜索. 时间复杂度O(mn), 空间复杂度O(min(m,n))
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (grid[i][j] != '1')continue;
				re++;
				queue<pair<int, int>> q;
				q.emplace(i, j);
				while (!q.empty())
				{
					int CurI = q.front().first, CurJ = q.front().second;
					q.pop();
					if (grid[CurI][CurJ] != '1')continue;
					grid[CurI][CurJ] = '2'; //【已经访问过的且已经扩展过的】位置都变成2
					if (CurJ + 1 < col && grid[CurI][CurJ + 1] == '1')
					{
						q.emplace(CurI, CurJ + 1);
					}
					if (CurJ - 1 >= 0 && grid[CurI][CurJ - 1] == '1')
					{
						q.emplace(CurI, CurJ - 1);
					}
					if (CurI + 1 < row && grid[CurI + 1][CurJ] == '1')
					{
						q.emplace(CurI + 1, CurJ);
					}
					if (CurI - 1 >= 0 && grid[CurI - 1][CurJ] == '1')
					{
						q.emplace(CurI - 1, CurJ);
					}
				}
			}
		}
		return re;

		//深度优先搜索. 时间复杂度O(mn), 空间复杂度O(mn)
		/*for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (grid[i][j] != '1')continue;
				re++;
				Expand(grid, i, j);
			}
		}
		return re;*/

		//并查集. 时间复杂度O(mn*α(MN)), 空间复杂度O(mn), α(MN)为反阿克曼函数, 最慢
		/*DisjointSet set;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (grid[i][j] != '1')continue;
				grid[i][j] = '2';
				set.Insert(i * col + j);
				if (j + 1 < col && grid[i][j + 1] == '1')
				{
					set.Insert(i * col + j + 1);
					set.Union(i * col + j + 1, i * col + j);
				}
				if (j - 1 >= 0 && grid[i][j - 1] == '1')
				{
					set.Insert(i * col + j - 1);
					set.Union(i * col + j - 1, i * col + j);
				}
				if (i + 1 < row && grid[i + 1][j] == '1')
				{
					set.Insert((i + 1) * col + j);
					set.Union((i + 1) * col + j, i * col + j);
				}
				if (i - 1 >= 0 && grid[i - 1][j] == '1')
				{
					set.Insert((i - 1) * col + j);
					set.Union((i - 1) * col + j, i * col + j);
				}
			}
		}
		return set.GetSetNum();*/

	}
	//45.跳跃游戏 II: 给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。返回到达 nums[n - 1] 的最小跳跃次数
	int jump(vector<int>& nums)
	{
		//贪心思想. 时间复杂度O(n), 空间复杂度O(1)
		int n = nums.size(), begin = 0, end = 0; //[begin, end]初始起跳点的范围
		int re = 0;
		while (end < n - 1)
		{
			int ThisJumpMaxIndex = INT_MIN; //当前[begin,end]的所有可能起跳点中, 能跳到的最远位置
			for (int i = begin; i <= end; i++) //在当前[begin,end]的所有可能起跳点中找出能跳到的最远位置
			{
				ThisJumpMaxIndex = max(ThisJumpMaxIndex, i + nums[i]); //当前位置为i, 从当前位置起跳, 最大能跳nums[i]格
			}
			begin = end + 1; //下一次循环(下一次起跳点)所在的范围[begin,end]
			end = ThisJumpMaxIndex;
			re++; //跳跃次数+1
		}
		return re;

		//动态规划. 比较慢. 时间复杂度O(n*max(nums))
		/*int n = nums.size();
		vector<int> re(n, INT_MAX);
		re[0] = 0;
		for (int i = 0; i < n - 1; i++)
		{
			int CurJumpMax = nums[i], j = i + 1, MaxJ = min(i + CurJumpMax, n - 1);
			while (j <= MaxJ)
			{
				re[j] = min(re[j], re[i] + 1);
				j++;
			}
		}
		return re.back();*/
	}
	//735.行星碰撞
	vector<int> asteroidCollision(vector<int>& asteroids)
	{
		//栈模拟. 时间复杂度O(n), 空间复杂度O(1)
		vector<int> re;
		re.reserve(asteroids.size());
		for (int& cur : asteroids) //遍历所有行星
		{   //当前栈顶行星(re.back())一定在当前行星(cur)的左边位置
			if (re.empty() || cur > 0) //如果当前栈为空或者当前行星向右走(只要是向右走的行星一定可以入栈, 不管当前栈顶行星是向左走的还是向右走的, 都不会撞到)
			{
				re.push_back(cur);
				continue;
			}
			//运行到这里, 说明当前栈一定非空, 而且当前行星一定向左走
			while (!re.empty() && re.back() > 0 && re.back() < -cur) //只要栈顶行星向右走而且他的质量比当前行星(向左走)小, 那么说明栈顶行星会爆炸
			{
				re.pop_back(); //栈顶行星移出栈
			}
			if (re.empty() || re.back() < 0) //如果【栈里面的行星都碰撞完了, 或者栈顶行星也是向左走的】, 那么当前行星(向左走)就可以直接入栈
			{
				re.push_back(cur);
			}
			else if (re.back() == -cur) //运行到这里, 说明栈顶行星是向右走的而且他的质量不小于当前行星(向左走), 进一步地, 如果【栈顶行星(向右走)的质量和当前行星质量相等】, 那么当前行星和栈顶行星都会爆炸
			{
				re.pop_back(); //【栈顶行星(向右走)爆炸: 栈顶行星移出栈】, 【当前行星(向左走)爆炸: 什么都不用做, 直接开始判断下一个行星】
			}
			//运行到这里, 说明栈顶行星(向右走)的质量比当前行星(向左走)大, 那么当前行星会爆炸(什么都不用做, 直接开始判断下一个行星)
		}
		return re;
	}
	//394.字符串解码: "3[a2[c]]" -> "accaccacc"
	string decodeString(string s)
	{
		int n = s.size();
		string re;
		//start和end表示当前[AAA]中"AAA"的起始位置和终止位置, "AAA"中可能也包含[...]
		int i = 0, start = -1, end = -1, num = 0; //num表示"AAA"的重复次数
		while (i < n)
		{
			if (s[i] == '[')
			{
				int Left = 1, Right = 0; //当前遇到的左括号和右括号的数量(应对括号嵌套)
				start = i + 1; //括号里的内容是从i+1开始的
				i++;
				while (i < n) //这个while循环是用来找当前左括号对应的右括号
				{
					if (s[i] == '[') //左括号数量加一
					{
						Left++;
					}
					else if (s[i] == ']') //右括号数量加一
					{
						Right++;
						if (Right == Left) //如果当前左右括号数量相等, 则表明当前i处的右括号, 是与start-1处的左括号对应的
						{
							break;
						}
					}
					i++;
				}
				end = i - 1; //括号里的内容是到i-1结束的
				string temp = decodeString(s.substr(start, end - start + 1)); //把括号里的内容再次递归调用
				for (int j = 0; j < num; j++) //重复num次
				{
					re += temp;
				}
				num = 0;//num重新变回0
			}
			else if (isdigit(s[i])) //是括号前的重复次数
			{
				num = num * 10 + (s[i] - '0');
			}
			else //是正常的普通的字母
			{
				re.push_back(s[i]);
			}
			i++;
		}
		return re;
	}
	//400.第N位数字: 1234567891011121314151617181920...
	int findNthDigit(int n)
	{
		//直接计算. 时间复杂度O(log10 n), 空间复杂度O(1)
		int CurNumLength = 0, SubNum = -1; //CurNumLength(99)=2, CurNumLength(100)=3. 
		unsigned long long CurMaxIndex = 0; //CurNumLength长度的所有数字涉及到的最大的n为CurMaxIndex, 例如CurNumLength为1那么CurMaxIndex为9, CurNumLength为2那么CurMaxIndex为189
		while (CurMaxIndex < n)
		{
			//当数字k属于当前CurNumLength范围内时, 数字k里面的一共CurNumLength个数字所在的(全局)序号为[CurNumLength*k-SubNum, CurNumLength*k-SubNum+CurNumLength-1]
			//例如, 当CurNumLength为2时, 数字k的(全局)序号为[2k-10, 2k-9]
			CurNumLength++; //初始->[0,9]->[10,99]->[100,999]...
			SubNum = pow(10, CurNumLength - 1) + SubNum; //SubNum需要迭代着求
			CurMaxIndex = CurNumLength * (pow(10, CurNumLength) - 1) - SubNum + CurNumLength - 1; //当 k=(10^CurNumLength)-1时其(全局)序号的最后一位
		}
		//运行到这里, 说明第n位所属的数字(TargetNum)长度一定是当前的CurNumLength
		unsigned long long BaseNum = pow(10, CurNumLength - 1); //数字长度为CurNumLength时的最小数字(例如CurNumLength为2时, BaseNum为10)
		unsigned long long NumOffset = (n - (CurNumLength * BaseNum - SubNum)) / CurNumLength; //第n位所属的数字(TargetNum)相对于BaseNum的偏移(单位: 数字), 即TargetNum = BaseNum + NumOffset
		unsigned long long TargetNum = BaseNum + NumOffset; //第n位所属的数字
		unsigned long long OffsetInNum = n - (CurNumLength * TargetNum - SubNum); //第n位在当前数字中的偏移(单位: 位), 从数字的左边开始数
		//通用: 如果要提取数字(num)的第k位(从个位数开始数, k最小取1)上的数字, 公式为: num % (10^k) / (10^(k-1)). 例如1234提取十位(k=2)上的数字: 1234 % 100 / 10 = 3
		unsigned long long DivNum = pow(10, CurNumLength - OffsetInNum); //OffsetInNum是从左边开始数的, 要转换成从个位数(右边)开始数
		return TargetNum % DivNum / (DivNum / 10);

		//基于模拟的方法. 很慢!
		/*int CurN = 0, CurNum = 1, CurExp = 10, CurNumLen = 1;
		while (CurN < n)
		{
			int DivNum, ExpTemp = 1;
			if (CurN >= n - CurNumLen)
			{
				for (int i = 1; i <= CurNumLen; i++)
				{
					if (CurN == n - 1)
					{
						DivNum = CurExp / ExpTemp;
						return CurNum % DivNum / (DivNum / 10);
					}
					ExpTemp *= 10;
					CurN++;
				}
			}
			else
			{
				CurN += CurNumLen;
			}
			CurNum++;
			if (CurNum == CurExp)
			{
				CurExp *= 10;
				CurNumLen++;
			}
		}
		return -1;*/

	}
	//55.跳跃游戏: 能否跳到最后一位
	bool canJump(vector<int>& nums)
	{
		//贪心思想. 时间复杂度O(n), 空间复杂度O(1)
		int CurMaxIndex = 0; //当前所能到达的最远处
		for (int i = 0; i < nums.size(); i++)
		{
			if (CurMaxIndex < i) //如果当前位置i是CurMaxIndex所不能达到的, 那么表明无法跳到这里
			{
				return false;
			}
			CurMaxIndex = max(CurMaxIndex, i + nums[i]);
		}
		return true;

		//贪心思想. 但是基于[begin, end]区间, 算法与"跳跃游戏 II"相同, 略微要慢一些
		/*int begin = 0, end = 0, n = nums.size();
		while (end < n - 1)
		{
			int CurMaxIndex = INT_MIN;
			for (int i = begin; i <= end; i++)
			{
				CurMaxIndex = max(CurMaxIndex, nums[i] + i);
			}
			if (CurMaxIndex <= end)
			{
				return false;
			}
			begin = end + 1;
			end = CurMaxIndex;
		}
		return true;*/
	}
	//239.滑动窗口最大值: 有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧, 返回滑动窗口中每次的最大值 
	vector<int> maxSlidingWindow(vector<int>& nums, int k)
	{
		//基于分组的思想. 时间复杂度O(n), 空间复杂度O(n). 实际运行起来比双端队列更快, 但是占用内存比双端队列稍微大一些
		//将nums分组, 使每个组大小为k(如果n%k!=0的话, 最后一个组除外), 计算[0,n-1]内每个位置的组内前缀最大值、组内后缀最大值
		int n = nums.size();
		vector<int> GroupFrontMax(n); //GroupFrontMax[i]表示第i个元素在其所属组(设组下标范围为[start,end])内[start,i]范围的最大值: 组内前缀最大值
		vector<int> GroupBackMax(n); //GroupBackMax[i]表示第i个元素在其所属组(设组下标范围为[start,end])内[i,end]范围的最大值: 组内后缀最大值
		for (int i = 0, IndexInGroup = 0; i < n; i++)
		{
			//每次运行到这里, 如果IndexInGroup为0则表示当前的i是其所属组的最开头的元素
			GroupFrontMax[i] = (IndexInGroup == 0 ? nums[i] : max(GroupFrontMax[i - 1], nums[i]));
			IndexInGroup++;
			if (IndexInGroup == k)
			{
				IndexInGroup = 0;
			}
		}
		int Extra = n % k; //假如n为8, k为3, 那么会被分成3个组:[0,2]、[3,5]、[6,7]. Extra就是最后不能被分成长度为k的那个组的大小. 
		//下面是计算最后那个不能被分成长度为k的那个组的GroupBackMax
		GroupBackMax[n - 1] = nums[n - 1];
		for (int i = n - 2; i >= n - Extra; i--)
		{
			GroupBackMax[i] = max(GroupBackMax[i + 1], nums[i]);
		}
		//上面是计算最后那个不能被分成长度为k的那个组的GroupBackMax
		for (int i = n - Extra - 1, IndexInGroup = k - 1; i >= 0; i--)
		{
			//每次运行到这里, 如果IndexInGroup为k-1则表示当前的i是其所属组的最后的元素
			GroupBackMax[i] = (IndexInGroup == k - 1 ? nums[i] : max(GroupBackMax[i + 1], nums[i]));
			IndexInGroup--;
			if (IndexInGroup == -1)
			{
				IndexInGroup = k - 1;
			}
		}
		vector<int> re(n - k + 1);
		for (int i = 0; i <= n - k; i++)
		{
			//每次运行到这里, 说明当前窗口的下标范围是[i, i+k-1]
			if (i % k == 0) //说明当前窗口范围正好是某一个组的范围
			{
				re[i] = GroupFrontMax[i + k - 1];//那么就取当前窗口(组)的最后一个元素的GroupFrontMax
				continue;
			}
			//运行到这里, 说明当前窗口横跨了两个组(设为第p组[startp, endp]和第q组[startq, endq]), 那么就需要判断[i, endp]内的最大值PreGroupPartMax和[startq, i+k-1]内的最大值NextGroupPartMax哪个大
			int PreGroupPartMax = GroupBackMax[i];  //[i, endp]内的最大值就是i处的组内后缀最大值
			int NextGroupPartMax = GroupFrontMax[i + k - 1]; //[startq, i+k-1]内的最大值就是i+k-1处的组内前缀最大值
			re[i] = max(PreGroupPartMax, NextGroupPartMax);
		}
		return re;

		//使用双端队列, 队列里面存的是数的下标(所以队列中的元素是递增的), 而后续操作会确保队列中下标对应的元素是非递增的(递减或有相等)
		//确保队列中下标对应的元素是非递增: 当需要往队尾插入一个新下标时, 只要当前队尾下标对应的元素值小于新下标对应的元素值(说明【只要有这个新元素在, 那么队尾下标的元素就永远不可能成为最大值】), 那么就把当前队尾的下标弹出
		//确保队列中下标对应的元素都在窗口范围内: 每次移动窗口后, 判断队头下标是否在窗口范围内
		//时间复杂度O(n), 空间复杂度O(k)
		/*
		int n = nums.size();
		vector<int> re;
		re.reserve(n - k + 1);
		deque<unsigned int> q; //双端队列, 队列中存的是元素下标(为了在窗口移动时主动移出那些不在窗口内的元素, 所以队列中的元素是递增的), 后续操作会确保这个双端队列中下标对应的元素是非递增的(递减或有相等)
		for (int i = 0; i < k; i++)
		{
			while (!q.empty() && nums[q.back()] < nums[i]) //只要队尾下标对应的元素比当前元素小, 说明【只要有当前元素在, 那么队尾下标的元素就永远不可能成为最大值】, 所以就可以把队尾移出, 这样就保证了这个双端队列中下标对应的元素是非递增的
			{
				q.pop_back();
			}
			q.push_back(i);
		}
		re.push_back(nums[q.front()]);
		for (int end = k; end < n; end++)
		{
			if (q.front() < end - k + 1) //如果当前双端队列的队头下标不在窗口范围内了, 那么就要移出这个下标, 这就是为什么双端队列中存的是下标而不是数的原因.
			{
				q.pop_front();
			}
			while (!q.empty() && nums[q.back()] < nums[end])
			{
				q.pop_back();
			}
			q.push_back(end);
			re.push_back(nums[q.front()]);
		}
		return re;*/

		//使用优先队列, 队列里面存的是pair<数, 数的下标>. 滑动窗口每次移动时, 只要当前最大值的下标不在窗口范围内, 就移出
		//每次窗口移动时不用主动检测哪些数需要移出, 只要被动检测当前优先队列里的最大值是否在窗口内就可以了
		//时间复杂度O(nlogn), 空间复杂度O(n)
		/*
		int n = nums.size();
		priority_queue<pair<int, unsigned int>> q; //优先队列(大根堆)里面存数和该数的位置
		vector<int> re;
		re.reserve(n - k + 1);
		for (int i = 0; i < k; i++)
		{
			q.emplace(nums[i], i);
		}
		re.push_back(q.top().first);

		for (int end = k; end < n; end++) //此时, 滑动窗口从[1,k]开始
		{
			q.emplace(nums[end], end);
			while (q.top().second < end - k + 1) //只要当前最大值(堆顶)所在的位置不在滑动窗口范围内, 就弹出
			{
				q.pop();
			}
			re.push_back(q.top().first);
		}
		return re;*/

		//使用std::map, 维护当前窗口内各个元素的数量, 依次取出map里的最后一个元素. 很慢
		/*int n = nums.size();
		map<int, int> map;
		vector<int> re;
		re.reserve(n - k + 1);
		int start = 0, end = k - 1;
		for (int i = start; i <= end; i++)
		{
			map[nums[i]]++;
		}
		re.push_back(map.rbegin()->first);

		map[nums[start]]--;
		if (map[nums[start]] == 0)
		{
			map.erase(nums[start]);
		}
		start++; end++;
		while (start < n - k + 1)
		{
			map[nums[end]]++;
			re.push_back(map.rbegin()->first);
			map[nums[start]]--;
			if (map[nums[start]] == 0)map.erase(nums[start]);
			start++; end++;
		}
		return re;*/
	}
	//64.最小路径和: 找出一条从左上角到右下角的路径，使得路径上的数字总和为最小
	int minPathSum(vector<vector<int>>& grid)
	{
		//动态规划思想. 对于上边界和左边界的位置, 到达他们的路径只有唯一一条, 累加就行. 对于中间的位置, 可以从上面的位置到达和左边的位置到达, 判断哪种最小
		//时间复杂度O(mn), 空间复杂度O(1)
		int row = grid.size(), col = grid[0].size();
		int CurSum = 0;
		for (int i = 0; i < col; i++) //处理上边界
		{
			CurSum += grid[0][i];
			grid[0][i] = CurSum;
		}
		CurSum = 0;
		for (int i = 0; i < row; i++) //处理左边界
		{
			CurSum += grid[i][0];
			grid[i][0] = CurSum;
		}
		for (int i = 1; i < row; i++)
		{
			for (int j = 1; j < col; j++)
			{
				grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]); //第(i,j)的位置要看第(i,j-1)和第(i-1,j)的位置哪个小
			}
		}
		return grid[row - 1][col - 1];
	}
	//322.零钱兑换: 计算并返回可以凑成总金额所需的最少的硬币个数
	int coinChange(vector<int>& coins, int amount)
	{
		//动态规划思想. 时间复杂度为O(amount*size(coins)), 空间复杂度为O(amount)
		if (amount == 0)return 0;
		int n = coins.size();
		bool IsAllEven = true; //面值是否全为偶数
		for (int& coin : coins)
		{
			if (coin % 2 == 1)
			{
				IsAllEven = false;
				break;
			}
		}
		if (IsAllEven && amount % 2 == 1) //如果面值全为偶数, 而且金额为奇数, 那么肯定不能组成这个金额, 直接返回-1
		{
			return -1;
		}
		int MinCoin = *min_element(coins.begin(), coins.end()); //最小的面额值
		if (amount < MinCoin)return -1;
		if (amount == MinCoin)return 1;
		vector<int> re(amount + 1, -1); //re[i]表示: 组成总金额为i最少需要多少个硬币
		re[0] = 0;
		for (int i = MinCoin; i <= amount; i++) //总金额为i时
		{
			int ThisRe = INT_MAX;
			for (int& coin : coins) //遍历所有的硬币
			{
				if (i - coin < 0 || re[i - coin] == -1)continue; //假如当前取coin元硬币, 那么剩下的i-coin元最少需要多少硬币
				ThisRe = min(ThisRe, re[i - coin]);
			}
			re[i] = (ThisRe == INT_MAX ? -1 : ThisRe + 1);
		}
		return re[amount];
	}
	//93.复原IP地址: 返回所有可能的有效 IP 地址
	bool IsRightIP(string& s, int start, int end) //s的[start,end]区间是否是一个合法的IP节
	{
		if (start >= s.size() || end >= s.size() || start < 0 || end < 0)return false;
		if (s[start] == '0') //如果以0开头, 那么当且仅当该区间长度为1(只有这个O)的时候才合法
		{
			return start == end;
		}
		int num = 0; //计算当前区间的数字是否超过了255
		for (int i = start; i <= end; i++)
		{
			num = num * 10 + (s[i] - '0');
		}
		return num <= 255;
	}
	void Do(string& s, vector<string>& re, string& Cur, int CurNum, int StartPos) //Cur为当前尝试的IP地址, CurNum为这一层递归的IP节(1~4), StartPos为当前这一层从s的哪里开始尝试
	{
		if (CurNum == 4) //当前已经是最后一节了
		{
			if (IsRightIP(s, StartPos, s.size() - 1)) //如果s的剩余部分是合法的, 那么直接加入结果
			{
				Cur += s.substr(StartPos);
				re.push_back(Cur);
			}
			return;
		}
		string Temp;
		for (int length = 1; length <= 3; length++) //每一节最多进行3次尝试, 取字符串长度分别为1、2、3
		{
			if (!IsRightIP(s, StartPos, StartPos + length - 1))continue;
			Temp = Cur + s.substr(StartPos, length) + ".";
			Do(s, re, Temp, CurNum + 1, StartPos + length);
		}
	}
	vector<string> restoreIpAddresses(string s)
	{
		int n = s.size();
		if (n < 4 || n > 12)return {};
		vector<string> re;
		string Cur = "";
		Do(s, re, Cur, 1, 0);
		return re;
	}
	//剑指 Offer 10-II. 青蛙跳台阶问题: 斐波拉切数列
	int numWays(int n)
	{
		if (n == 0 || n == 1)return 1;
		unsigned int PrePre = 0, Pre = 1;
		for (int i = 2; i <= n; i++)
		{
			unsigned int temp = Pre;
			Pre = (Pre + PrePre) % 1000000007;
			PrePre = temp;
		}
		return (Pre + PrePre) % 1000000007;
	}
	//1109.航班预订统计: bookings[i] = [firsti, lasti, seatsi], 求每个航班预定的座位总数
	vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n)
	{
		//差分的方法. 时间复杂度O(m+n), 空间复杂度O(1).
		//假如一个booking为{3,5,10}.抽象成: 从左到右(从1~n)的过程中, 3号(index为2)开始需要增加10, 6号开始(index为5)需要减少10(注意: 并不是5号)
		vector<int> re(n + 1, 0); //差分数组
		for (vector<int>& booking : bookings)
		{
			re[booking[0] - 1] += booking[2]; //booking[0]==3, 也就是说index为2处应该增加10
			re[booking[1]] -= booking[2];     //booking[1]==5, 也就是说6号(index为5)处应该减少10
		}
		re.pop_back(); //求完差分数组之后, 最后一位是没用的
		for (int i = 1; i < n; i++) //最后根据差分数组求出每一个的结果
		{
			re[i] += re[i - 1]; //第i处的结果应该是前一处的结果加上当前处的差分值
		}
		return re;
	}
	//1235.规划兼职工作: 根据startTime、endTime和profit计算并返回可以获得的最大报酬。
	int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit)
	{
		//动态规划+二分查找. 时间复杂度O(nlogn), 空间复杂度O(n)
		int n = startTime.size();
		vector<vector<int>> jobs(n); //每个vector的格式为{startTime, endTime, profit}
		for (int i = 0; i < n; i++)
		{
			jobs[i] = { startTime[i] ,endTime[i] ,profit[i] };
		}
		sort(jobs.begin(), jobs.end(), [](vector<int>& a, vector<int>& b) //把endTime按照升序排序
			{
				return a[1] < b[1];
			});
		vector<int> re(n, 0); //re[i]表示: 前i个job可以获得的最大报酬
		re[0] = jobs[0][2]; //re[0]是第0个工作的报酬

		//假如运行到这里时, jobs为: [1,2,5], [2,6,1], [3,6,2], [4,7,5], [6,7,2], [4,9,1]
		//例如, 当i为4时([6,7,2]), 表示当前工作从6开始, 到7结束, 那么, 需要在它之前(i=0~3)找出结束时间小于等于6的最靠后的位置(j==2, 即[3,6,2])
		//那么, 就有两种情况: 1. 做job[i], 而且也做job[i]之前的能获得最大报酬的一系列工作(re[j]), re[i]就等于profit[i]+re[j]. 2.不做job[i], 那么re[i]就等于re[i-1]. 所以就要判断哪种情况的收益更大
		//对于第一种情况, 假如没找到符合条件的j(此时j==-1), 那么这时候re[i]就等于profit[i]
		for (int i = 1; i < n; i++)
		{
			int j = upper_bound(jobs.begin(), jobs.begin() + i, jobs[i][0], [](int val, vector<int>& a) //查找满足a[j]>jobs[i][0]的第一个j, 查找范围:[jobs.begin(), jobs.begin() + i)
				{
					return val < a[1];
				}) - jobs.begin() - 1;  //对于上面的例子来说, 当i==4([6,7,2])时, upper_bound函数返回3([4,7,5])处的迭代器(因为7>6), 减去jobs.begin()后得到3, 再减一就得到2([3,6,2])
				//此时, [3,6,2]就是i==4([6,7,2])前面的、结束时间小于或等于i处开始时间的、最靠后的job
				if (j < 0) //如果j<0, 说明没找到这样的j
				{
					re[i] = max(re[i - 1], jobs[i][2]); //max(不做该工作, 做该工作)
				}
				else
				{
					re[i] = max(re[i - 1], re[j] + jobs[i][2]); //max(不做该工作, 做该工作)
				}
		}
		return re[n - 1];
		/* upper_bound和lower_bound: 仅适用于已排序的数组, 底层实现是二分查找
		   upper_bound: 在指定范围内查找(严格)大于目标值的第一个元素.
		   lower_bound: 在指定范围内查找大于或等于目标值的第一个元素.
		*/

	}
	//539.最小时间差: 给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示
	int findMinDifference(vector<string>& timePoints)
	{
		//排序+鸽巢原理. 时间复杂度O(nlogn)
		//最小的时间差只可能有两种情况: 1.排序之后相邻数之间. 2.第0个和最后一个之间(例如"00:00"(0)和"23:59"(1439)只相差1)
		int n = timePoints.size();
		if (n > 1440)return 0; //鸽巢原理, 一共只有1440种可能(24小时=1440分钟), 如果给的数组比这还多, 那么肯定至少有两个是重复的
		vector<int> nums(n);
		for (int i = 0; i < n; i++) //字符串转分钟数
		{
			nums[i] = ((timePoints[i][0] - '0') * 10 + (timePoints[i][1] - '0')) * 60 + (timePoints[i][3] - '0') * 10 + (timePoints[i][4] - '0');
		}
		sort(nums.begin(), nums.end());
		int re = INT_MAX;
		for (int i = 0; i < n - 1; i++) //相邻之间比较
		{
			re = min(re, nums[i + 1] - nums[i]);
			if (re == 0)return 0;
		}
		re = min(re, nums[0] + 1440 - nums[n - 1]); //第0个和最后一个比较
		return re;
	}
	//1160.拼写单词: 假如可以用chars中的字符拼写出words中的某个字符串，那么我们就认为你掌握了这个单词。返回词汇表 words 中你掌握的所有单词的长度之和
	int countCharacters(vector<string>& words, string chars)
	{
		//时间复杂度O(n), n为所有字符串长度之和. 空间复杂度O(S). S为字符集大小(26)
		vector<int> nums(26, 0); //chars中每个字母出现的次数
		for (char& c : chars)
		{
			nums[c - 'a']++;
		}
		vector<int> nums_copy = nums; //备份一下nums, 免得每次都要还原
		int re = 0;
		for (string& s : words)
		{
			if (s.size() > chars.size())continue; //如果某个单词的长度比chars还长, 那么这个单词肯定不能被掌握, 直接看下一个单词
			bool IsSuccess = true; //是否被掌握
			for (char& c : s)
			{
				nums[c - 'a']--;
				if (nums[c - 'a'] < 0) //如果某个字符超了, 那么当前单词一定不能被掌握, 后序字符不用看了
				{
					IsSuccess = false;
					break;
				}
			}
			if (IsSuccess)
			{
				re += s.size();
			}
			nums = nums_copy; //还原nums
		}
		return re;
	}
	//475.供暖器: 给出位于一条水平线上的房屋houses和供暖器heaters的位置，找出并返回可以覆盖所有房屋的最小加热半径
	int findRadius(vector<int>& houses, vector<int>& heaters)
	{
		//双排序+双指针. 时间复杂度O(mlogm+nlogn), 空间复杂度O(logm+logn)
		//对于每个房屋house, 找到距离它最近的heater, 设house和这个heater之间的距离为Dis. 求所有house对应的Dis的最大值
		//问题的关键: 如何找到距离某个house最近的heater. 两种算法: 1. 对house和heater都排序, 使用双指针(本方法). 2.只对heater排序, 使用lower_bound二分查找最近的heater(下面的方法)
		int m = houses.size(), n = heaters.size();
		sort(houses.begin(), houses.end());
		sort(heaters.begin(), heaters.end());
		int j = 0, re = INT_MIN;
		for (int house : houses)
		{
			if (house <= heaters[0]) //如果house比heaters[0]还小, 说明最近的heater一定就是heaters[0]了
			{
				re = max(re, heaters[0] - house);
				continue;
			}
			if (house >= heaters[n - 1]) //如果house比heaters[n-1](最后的一个heater)还小, 说明最近的heater一定就是heaters[n-1](最后的一个heater)了
			{
				re = max(re, house - heaters[n - 1]);
				continue;
			}
			while (heaters[j] < house) //找到某个大于等于house的位置的heater, 找到之后, 因为houses也排过序, 所以下一次house对应的最近的heater一定等于当前heater或者在当前heater的右边(j继续往右移动)
			{
				j++;
			}
			re = max(re, min(abs(house - heaters[j]), abs(house - heaters[j - 1]))); //因为当前找的是位置大于或等于house的heater为heaters[j], 所以距离最近的heater可能是heaters[j]或者heaters[j-1]
		}
		return re;

		//排序heaters+lower_bound二分查找. 时间复杂度O((m+n)logn), 空间复杂度O(logn). 比上面的方法略慢
		/*sort(heaters.begin(), heaters.end());
		int n = heaters.size();
		int re = INT_MIN;
		for (int house : houses)
		{
			if (house <= heaters[0])
			{
				re = max(re, abs(house - heaters[0]));
				continue;
			}
			if (house >= heaters[n - 1])
			{
				re = max(re, abs(house - heaters[n - 1]));
				continue;
			}
			int j = lower_bound(heaters.begin(), heaters.end(), house) - heaters.begin();
			int ThisMinDis = min(abs(house - heaters[j]), abs(house - heaters[j - 1])); //同样地, 要看heaters[j-1]和heaters[j]哪个更近一些
			re = max(re, ThisMinDis);
		}
		return re;*/
	}
	//451.根据字符出现频率排序: 根据字符在s中出现的次数, 对其进行s降序排序
	string frequencySort(string s)
	{
		//按照出现频率排序. 时间复杂度O(n+klogk), n为s的长度, k为s中字符的种类数. 空间复杂度O(n+k)
		vector<pair<int, int>> nums(75); //因为s中只可能出现大小写字母和数字, 在ASCII表中, '0'对应48, 'z'对应122, 所以需要(122-48+1)长度的vector, 不过, 中间有一些不可能使用到(比如';'对应的59)
		for (int i = 0; i < 75; i++) //nums[i]表示字符('0'+i)出现了多少次
		{
			nums[i].first = i;  //记录下相对于'0'的偏移量
			nums[i].second = 0; //次数初始化为0
		}
		for (char& c : s) //遍历s
		{
			int index = c - '0';
			nums[index].second = nums[index].second + 1;
		}
		sort(nums.begin(), nums.end(), [](pair<int, int>& a, pair<int, int>& b) //按照出现次数的倒序排序
			{
				return a.second > b.second;
			});
		string re = "";
		for (int i = 0; i < 75; i++) //遍历排序之后的nums
		{
			if (nums[i].second == 0)break; //如果当前的nums[i]对应的次数为0, 那么说明从i开始, 之后的次数都为0, 所以可以直接退出这个循环
			int num = nums[i].second; //出现次数
			char c = '0' + nums[i].first; //对应的字符
			for (int j = 0; j < num; j++)
			{
				re.push_back(c);
			}
		}
		return re;


		//基于桶排序, 时间复杂度O(n+k), n为s的长度, k为s中字符的种类数. 空间复杂度O(n+k)
		//但是实际运行起来是没有上面方法快的
		/*unordered_map<char, int> map; //每个字符出现的次数
		int MaxFreq = 0; //最高的出现频率
		for (char& c : s)
		{
			map[c]++;
			MaxFreq = max(MaxFreq, map[c]);
		}
		vector<string> Freq2Char(MaxFreq); //Freq2Char[i]表示: 出现频率为(i+1)的字符有哪些(桶排序)
		for (auto it = map.begin(); it != map.end(); it++)
		{
			Freq2Char[it->second - 1].push_back(it->first); //构建Freq2Char
		}
		string re = "";
		for (int i = MaxFreq - 1; i >= 0; i--) //按频率从大到小
		{
			int n = Freq2Char[i].size(); //出现频率为(i+1)的字符种类数
			if (n == 0)continue;
			for (int j = 0; j < n; j++)
			{
				char c = Freq2Char[i][j];
				for (int k = 0; k < i + 1; k++) //重复i+1次
				{
					re.push_back(c);
				}
			}
		}
		return re;*/

	}
	//42.接雨水: 给定n个非负整数表示每个宽度为1的柱子的高度图，计算按此排列的柱子, 下雨之后能接多少雨水
	int trap(vector<int>& height)
	{
		//使用双指针. 从i从左往右, j从右往左遍历. 时间复杂度O(n), 空间复杂度O(1)
		//对于第i个位置, 假设在[0,i]范围(左侧并包括自身)内最高的方块高度是LeftMax, 在[i,n-1]范围(右侧并包括自身)内最高的方块高度是RightMax, 于是, 该位置上的TargetHeight就等于min(LeftMax,RightMax)
		//可以知道, TargetHeight一定大于或等于height[i], 当等于height[i]时, 则表明这个位置不能接到水; 如果大于height[i]就表明这个位置可以接到TargetHeight-height[i]的水
		//已知: j左>=i左, 所以如果i左(ILeftMax)>j右(JRightMax), 那么j左>j右, 即对于j来说, 其TargetHeight(==min(LeftMax,RightMax))就等于j右(JRightMax)
		//同样地, 已知i右>=j右, 所以如果i左(ILeftMax)<j右(JRightMax), 那么i左<i右, 即对于i来说, 其TargetHeight(==min(LeftMax,RightMax))就等于i左(ILeftMax)
		int n = height.size(), re = 0;
		//ILeftMax表示[0,i]范围内的最大高度, JRightMax表示[j, n-1]范围内的最大高度
		int ILeftMax = height[0], JRightMax = height[n - 1], i = 0, j = n - 1;
		while (i < j)
		{
			int TargetHeight;
			if (JRightMax >= ILeftMax) //j右>=i左, 那么TargetHeight就等于i左
			{
				TargetHeight = ILeftMax;
				re += TargetHeight - height[i]; //不必担心(TargetHeight - height[i])为负数, 因为TargetHeight永远大于或等于height[i], 当且仅当【该处不能接到水】的时候相等
				i++; //i左移
			}
			else
			{
				TargetHeight = JRightMax;
				re += TargetHeight - height[j];
				j--; //j右移
			}
			ILeftMax = max(ILeftMax, height[i]); //更新i左
			JRightMax = max(JRightMax, height[j]);//更新j右
		}
		return re;

		//动态规划思想. 从左到右遍历. 时间复杂度O(n), 空间复杂度O(n).
		//对于第i个位置, 假设在[0,i-1]范围(左侧)内最高的方块高度是LeftMax, 在[i+1,n-1]范围(右侧)内最高的方块高度是RightMax
		//只有当height[i]严格小于min(LeftMax,RightMax)时, 第i个位置上才会接到水, 会接到min(LeftMax,RightMax)-height[i]的水
		//使用动态规划的思想求LeftMax和RightMax
		/*int n = height.size(), re = 0;
		vector<int> LeftMax(n, -1), RightMax(n, -1); //最左边/最右边的位置处的LeftMax/RightMax默认置为-1
		for (int i = 1; i < n; i++)
		{
			LeftMax[i] = max(height[i - 1], LeftMax[i - 1]);
			RightMax[n - 1 - i] = max(height[n - i], RightMax[n - i]);
		}
		for (int i = 0; i < n; i++)
		{
			int TargetHeight = min(LeftMax[i], RightMax[i]);
			re += max(TargetHeight - height[i], 0); //当且仅当TargetHeight大于height[i]时才会接到水
		}
		return re;
		*/

		//基于栈模拟. 时间复杂度O(n), 空间复杂度O(n).
		/*
		int n = height.size(), re = 0;
		stack<int> s; //栈里面存储的是下标
		for (int i = 0; i < n; i++) //从右往左逐个遍历
		{
			while (!s.empty() && height[s.top()] < height[i]) //只要栈顶对应的高度比当前高度小, 说明i位置的左边若干格可以接水
			{
				int ThisHeight = height[s.top()]; //栈顶的高度需要留下来
				s.pop();
				if (s.empty())break; //如果出栈之前只有一个元素, 那么表明虽然当前位置的高度比栈顶对应高度高, 但是也没办法接到水, 因为会流到边缘外
				int TargetHeight = min(height[i], height[s.top()]); //min(当前位置高度, 出栈之后下一个元素的高度)
				int Width = i - s.top() - 1; //可以接到水的宽度
				re += (TargetHeight - ThisHeight) * Width;
			}
			s.push(i); //不管怎么样, 当前位置要入栈
		}
		return re;
		*/

		//依次求每一层高度可以接多少雨水. 时间复杂度O(mn), m为height中的最大值. 空间复杂度O(1). 会超时
		/*
		int n = height.size(), re = 0;
		int CurHeight = 1; //当前高度
		bool IsContinue = false; //当前高度结束后, 是否有必要继续把高度+1. 如果当前高度至少能找到一个方块的高度不低于CurHeight, 那么就应该继续把CurHeight+1
		do
		{
			IsContinue = false; //每次循环时, 都置为false
			int i = 0, CurRe = 0; //CurRe为当前高度下的当前区域能接多少雨水
			while (i < n && height[i] < CurHeight) //跳过最开始的很低的部分, 这部分虽然高度比CurRe低, 但是在最左边, 接不到水(流到旁边去了)
			{
				i++;
			}
			//运行到这里, 说明当前height[i]已经是高度大于或等于CurHeight的最靠左的方块了, 从这个方块开始, 后面的方块如果高度再比CurHeight小, 就可以接到水了(不会流到旁边, 会被挡住)
			while (i < n)
			{
				if (height[i] >= CurHeight) //当前方块的高度大于或等于当前高度, 那么"当前区域"结束, 把CurRe("当前区域"接了多少水)加到re中, 然后开始一个新的"区域"
				{
					IsContinue = true; //至少找到了大于等于"当前高度"的方块, CurHeight还会+1
					re += CurRe; //"当前区域"结束, 把CurRe("当前区域"接了多少水)加到re中
					CurRe = 0; //然后开始一个新的"区域", CurRe归零重新计数
				}
				else //如果当前方块的高度小于CurHeight, 说明在这一层(高度), 这里的方块会接到水
				{
					CurRe++;
				}
				i++;
			}
			//如果担心在序列右边也出现左边那样的情况:【虽然该方块的高度小于CurHeight, 但是不会接到水, 因为会流到边界外面去】
			//这个担心是多余的, 因为假如最右侧的方块高度都小于CurHeight, 那么"区域"的CurRe确实会加一, 但是这一"区域"的CurRe并不会加到最后结果re里, 因为这一"区域"没有哪个方块的高度大于或等于CurHeight
			CurHeight++;
		} while (IsContinue);
		return re;
		*/
	}
	//315.计算右侧小于当前元素的个数:给你一个整数数组nums, 按要求返回一个新数组 counts 。数组 counts 有该性质:counts[i]的值是 nums[i] 右侧小于 nums[i] 的元素的数量
	void Merge(vector<int>& nums, vector<int>& Index, vector<int>& re, vector<int>& MergeReTemp, int LBegin, int LEnd, int REnd)
	{
		//做一次归并排序. nums为原数组. Index为排序结果(存的是下标). re为问题的结果. MergeReTemp为在一次归并排序过程中的临时结果数组.
		//左区间的范围: [LBegin, LEnd-1], 右区间的范围: [LEnd, REnd-1]
		int i = LBegin, j = LEnd, CurPos = 0; //CurPos为当前是MergeReTemp的第几位
		while (i < LEnd)
		{
			if (j < REnd && nums[Index[i]] > nums[Index[j]]) //左区间的i处大于右区间的j处
			{
				MergeReTemp[CurPos] = Index[j];
				j++;
			}
			else //在右区间中终于找到了当前的j处, 它比左区间的i处大, 说明右区间的[LEnd, j-1](全局下标)都比左区间的i处要小
			{
				MergeReTemp[CurPos] = Index[i];
				re[Index[i]] += j - LEnd;
				i++;
			}
			CurPos++;
		}
		copy(MergeReTemp.begin(), MergeReTemp.begin() + CurPos, Index.begin() + LBegin); //把临时结果数组拷贝到排序结果数组上
	}
	vector<int> countSmaller(vector<int>& nums)
	{
		//基于归并排序. 时间复杂度O(nlogn), 空间复杂度O(n).
		//在归并排序的"并"的过程中, 对左右两个区间(L和R)的左右两个指针i、j: 假设当前L[i]>R[j], 那么就把j++, 并且把R[j]放到合并结果的临时数组MergeReTemp中;
		//否则(L[i]<R[j]), 则表明右区间的[0, j-1]范围内的数都比L[i]要小, 而且这些数也肯定都在L[i]的右侧, 所以L[i]右侧小于它的数量可以加上j, 最后也要i++, 且把R[i]放到合并结果的临时数组MergeReTemp中
		int n = nums.size();
		vector<int> Index(n); //待排序的数组(存下标), 初始为[0, n-1]
		for (int i = 0; i < n; i++)
		{
			Index[i] = i;
		}
		vector<int> re(n, 0);
		vector<int> MergeReTemp(n, 0);
		for (int len = 1; len < n; len *= 2) //区间长度依次乘以2
		{
			for (int i = 0; i + len < n; i += 2 * len) //i为每个区间的起始下标
			{
				Merge(nums, Index, re, MergeReTemp, i, i + len, min(i + 2 * len, n)); //右区间的右边界可能超过n, 所以要取min
			}
		}
		return re;

		//基于离散化数组构造树状数组. 时间复杂度O(nlogn), 空间复杂度O(n).
		/*
		int n = nums.size();
		vector<int> Freq = nums; //nums备份一份为Freq, 后序过程中, Freq[i]表示Freq[i]这个数在遍历中当前已经出现了多少次
		sort(Freq.begin(), Freq.end());
		Freq.erase(unique(Freq.begin(), Freq.end()), Freq.end()); //对Freq排序后, 删除重复元素. 注意:unique之前必须排序, 而且会改变Freq

		//假设 a = {3,1,1,5,6,9,0,3,6}, 排序后, a就是{0,1,1,3,3,5,6,6,9}.
		//auto it = unique(a.begin(),a.end()); 之后, a就是{0,1,3,5,6,9,x,x,x}, 并且it指向第一个x(有效部分的end())
		//再执行 a.erase(it,a.end()); 之后, a就是{0,1,3,5,6,9}, 即删除了后面无效(重复数字)的部分

		//运行到这里, 假设原nums为{3,1,1,5,6,9,0,3,6}, 那么Freq就是{0,1,3,5,6,9}, 即把nums中所有不重复的数按升序排列
		FenwickTree tree(Freq.size()); //构造一个全为0的树状数组, 长度为nums中所有不重复的数的种类
		vector<int> re(n, 0);
		for (int i = n - 1; i >= 0; i--) //从右往左遍历nums, 先找到nums[i]在Freq中的序号(index):FreqIndex, 然后求Freq中index范围为[0, FreqIndex-1](因为题目要求严格小于nums[i], 所以不能取到FreqIndex)内的和(即Freq的FreqIndex-1下标的前缀和)
		{
			if (nums[i] == Freq[0]) //假如当前的数是Freq的最开头的数(即当前nums[i]是nums中的最小值), 那么当前位置的右侧肯定没有比它更小的数, 所以当前位置的re为0, 同时要把树状数组中, 当前数出现的次数加一
			{
				re[i] = 0;
				tree.Add(0, 1);
				continue;
			}
			int FreqIndex = lower_bound(Freq.begin(), Freq.end(), nums[i]) - Freq.begin(); //nums[i]在Freq中的序号(index)
			re[i] = tree.Sum(FreqIndex - 1);//利用树状数组求[0, FreqIndex-1]范围内的和(即FreqIndex-1的前缀和)
			tree.Add(FreqIndex, 1);//当前数出现的次数加一
		}
		return re;
		*/
	}
	//518.零钱兑换 II: 计算并返回可以凑成总金额的硬币组合数
	int change(int amount, vector<int>& coins)
	{
		//动态规划. 时间复杂度O(amount*coins.size()), 空间复杂度O(amount)
		//为了避免出现【3=1+2, 3=2+1】的重复, 设定【amount = ... + coins[i] + coins[j]+ ...】中, 确保i一定大于或等于j. 所以先遍历coins再遍历money
		//这样的话, 假设coins={3,7,4,9}, amount=11的情况下, 只会出现【11=4+7】而不会出现【11=7+4】
		int n = coins.size();
		int MinCoin = *min_element(coins.begin(), coins.end()); //最小的硬币面值
		if (amount == MinCoin || amount == 0)return 1;
		if (amount < MinCoin)return 0;
		bool IsAllEven = true; //硬币面值是否全为偶数, 如果面值全为偶数但是amount为奇数, 那么不管怎么组合一定得不到amount
		for (int i = 0; i < n; i++)
		{
			if (coins[i] % 2 == 1)
			{
				IsAllEven = false;
				break;
			}
		}
		if (IsAllEven && amount % 2 == 1)return 0;

		vector<int> re(amount, 0); //re[i]表示: 组成i+1金额有多少种方法
		for (int i = 0; i < n; i++) //为了确保组合方法不会有重复, 所以先遍历coins, 这样的话, 一定确保了【顺序越靠后的硬币出现在组合的越靠前的位置】
		{
			for (int money = coins[i]; money <= amount; money++)
			{
				if (money == coins[i])
				{
					re[money - 1]++;
					continue;
				}
				re[money - 1] += re[money - coins[i] - 1]; // money = coins[i] + A. 组成A的硬币中, 一定不会出现coins[i]右边的硬币
				// 假设coins={3,7,4,9}, 当i=1(coins[i]=7), money=11, 即【11=7+?】时, re[4-1]为0, 因为此时只靠{3,7}两种硬币无法形成4元金额
				// 但当i=2(coins[i]=4), money=11, 即【11=4+?】时, re[7-1]为2(7=7, 7=4+3), 所以这个时候re[11-1]就可以加2(11=4+7, 11=4+4+3)
			}
		}
		return re[amount - 1];
	}
	//207.课程表\有向图是否存在环路: 判断是否可能完成所有课程的学习, 是否会出现冲突(循环依赖)
	bool Dfs(vector<vector<int>>& table, vector<char>& visited, int Cur) //深度优先搜索遍历. 当前遍历到了Cur(在进入这个函数之前, visited[Cur]已被设置为'1')
	{
		for (int next : table[Cur]) //对Cur的每一个邻接节点做深度遍历
		{
			if (visited[next] == '1')return false; //如果Cur的某个邻接节点当前状态为"正在搜索中", 说明找到了环, 直接返回false
			if (visited[next] == '2')continue; //如果Cur的某个邻接节点"已经搜索过了", 那么不用再对这个邻接节点做深度遍历了
			//运行到这里, 说明Cur的这个邻接节点还没被搜索过, 即visited[Cur]==0
			visited[next] = '1'; //将这个邻接节点也设置为"正在搜索中"
			if (!Dfs(table, visited, next)) //对这个邻接节点也做深度遍历, 如果中途发现了环路, 那么也返回false
			{
				return false;
			}
			visited[next] = '2'; //这个邻接节点设置为"已被遍历过"
		}
		return true; //当前路径没有找到环路
	}
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
	{
		//基于入度的广度优先遍历. 时间复杂度O(numCourses + prerequisites.size()), 空间复杂度O(numCourses + prerequisites.size()).
		//将prerequisites中的每个依赖关系p看成图的一条边, p[0]为起点, p[1]为终点. 问题就转化为: 如果这个有向图中存在环路, 那么就会出现冲突, 返回false.
		//广度遍历思想: 首先把所有入度为0的节点加入队列, 然后对队列中的每个元素q, 找到q的所有邻接节点, 将这些邻接节点的入度都减一(即: 删掉q与该邻接节点之间的边), 如果入度减一之后为0, 把这个邻接节点加入队列
		//记录从队列中遍历到的节点数n, 如果n等于总节点数, 则表明不存在环
		vector<int> Node2InDegree(numCourses, 0); //每个节点的入度
		vector<vector<int>> table(numCourses);    //邻接表. table[i]表示第i个课程需要先上哪些课程
		for (vector<int>& p : prerequisites)
		{
			table[p[0]].push_back(p[1]);
			Node2InDegree[p[1]]++; //p[0]为起点, p[1]为终点, 所以p[1]的入度加一
		}
		queue<int> q;
		for (int i = 0; i < numCourses; i++)
		{
			if (Node2InDegree[i] == 0) //把初始的时候入度为0的节点加入队列
			{
				q.push(i);
			}
		}
		int VisitedCount = 0; // 从队列中遍历到的节点数量
		while (!q.empty())
		{
			int Cur = q.front();
			VisitedCount++;
			for (int next : table[Cur]) //遍历该节点的所有邻接节点
			{
				Node2InDegree[next]--; //邻接节点的入度都要减一(删除Cur节点到该邻接节点之间的边)
				if (Node2InDegree[next] == 0) //如果删除后, 该邻接节点的入度为0了, 就把它加入队列
				{
					q.push(next);
				}
			}
			q.pop();
		}
		return VisitedCount == numCourses; //当且仅当"从队列中遍历到的节点数量"等于"总节点数"时, 该有向图中不存在环, 也就是说课程表不冲突, 返回true

		//深度优先搜索遍历. 时间复杂度O(numCourses + prerequisites.size()), 空间复杂度O(numCourses + prerequisites.size()).
		/*
		vector<vector<int>> table(numCourses); //邻接表. table[i]表示第i个课程需要先上哪些课程
		for (vector<int>& p : prerequisites)
		{
			table[p[0]].push_back(p[1]);
		}
		vector<char> visited(numCourses, '0'); //'0'表示没被搜索过, '1'表示正在搜索中, '2'表示已经搜索完
		for (int i = 0; i < numCourses; i++)
		{
			if (visited[i] != '0')continue; //只遍历当前还没有遍历过的节点
			visited[i] = '1'; //将当前节点设置为"正在遍历中"
			if (!Dfs(table, visited, i)) //如果找到环, 直接返回false
			{
				return false;
			}
			visited[i] = '2'; //运行到这里, 说明以当前节点的深度优先搜索没有找到环, 那么将这个节点设置为"已经搜索完", 再看下一个节点
		}
		return true; //如果以所有节点开头的路径都没找到环路, 那么说明这个图都没有环路
		*/

	}
	//820.单词的压缩编码: 后缀子字符串, 以#结尾
	int minimumLengthEncoding(vector<string>& words)
	{
		//将字符串按反序排序, 再迭代式判断前一个word是否是后一个word的"后缀子串"
		sort(words.begin(), words.end(), [](string& a, string& b)
			{
				int Len1 = a.size(), Len2 = b.size(), i = 0;
				while (true) //从a和b的最后一位开始往前看
				{
					if (Len1 - i < 0)return true; //a字符串要短一些, 而且从后往前看, a字符串完全就是b的子串
					if (Len2 - i < 0)return false;
					if (a[Len1 - i] != b[Len2 - i])
					{
						return a[Len1 - i] < b[Len2 - i];
					}
					i++;
				}
			}); //将每个字符串反序排序, 但是排序之后的words里面的字符串还是正序, 因为上面的Lambda表达式是传值
		// 假如原words为{"abell","me","ll","ime","bell","time"}. 那么运行到这里, words为{"me","ime","time","ll","bell","abell"}
		int n = words.size(), re = 0;
		words.push_back("!"); //因为下面的循环, 需要将words[i]和words[i+1]做对比, 为了避免在words最后一位出现溢出的繁琐操作, 所以将随后再加一个"!"这个绝对不可能出现的word
		for (int i = 0; i < n; i++)
		{
			int ThisLen = words[i].size(), NextLen = words[i + 1].size();
			if (NextLen < ThisLen) //如果下一个word的长度比当前word长度还短, 那么当前word肯定不是下一个word的"后缀子串"
			{
				re += ThisLen + 1; //所以当前字符串需要单独编码. +1是指后面的#号
				continue;
			}
			bool IsSameTail = true; //当前word是否是下一个word的后缀子串
			for (int j = 0; j < ThisLen; j++) //分别从当前word和下一个word的最后一位开始判断, 如果出现了一个n, 使得当前word的倒数第n位和下一个word的倒数第n位不同, 那么当前word肯定就不是下一个word的后缀子串
			{
				if (words[i][ThisLen - j - 1] != words[i + 1][NextLen - j - 1])
				{
					IsSameTail = false;
					break;
				}
			}
			if (!IsSameTail) //如果当前word不是下一个word的后缀子串, 说明当前word需要单独编码
			{
				re += ThisLen + 1;
			}
			//运行到这里, 说明当前word是下一个word的后缀子串, 那么当前word不用单独编码, 因为完全可以使用下一个word的编码. 所以继续看再下面的word.
		}
		return re;


		//将字符串倒序之后插入字典树, 最后将树中所有叶子节点的深度(这个叶子节点本来对应的word的长度为深度-1, 但因为要在word后面加#号, 所以还要+1)之后求和.
		//实际运行很慢
		/*
		TrieTree tree; //字典树
		for (string& word : words) //把每个字符串倒序之后插入字典树
		{
			reverse(word.begin(), word.end());
			tree.Insert(word);
		}
		queue<TrieTree::Node*> q; //按层次遍历字典树的节点
		q.push(tree.root);

		int CurDepth = 1, CurDepthLen = 1, re = 0; //CurDepth为当前深度(根节点的深度为1), CurDepthLen为当前层有多少个节点
		while (!q.empty())
		{
			while (CurDepthLen > 0) //只要当前层的节点还没遍历完...
			{
				TrieTree::Node* Cur = q.front();
				for (auto it = Cur->map.begin(); it != Cur->map.end(); it++) //遍历当前节点的所有子节点
				{
					if (it->second->map.empty()) //如果这个子节点(it->second)没有孩子(map为空), 说明这个子节点(it->second)是叶子节点
					{
						re += CurDepth + 1; //因为CurDepth为Cur节点的深度, 所以it->second(是Cur的孩子节点)的深度就是CurDepth+1
					}
					q.push(it->second); //当前子节点加入队列
				}
				CurDepthLen--; //当前层(Cur所在的层)已经遍历完一个了
				q.pop();
			}
			CurDepthLen = q.size(); //当前层已经全部遍历完, 目前队列中的元素都是下一层的节点, 所以就获取下一层的节点数
			CurDepth++; //深度+1
		}
		return re;
		*/

	}
	//994.腐烂的橘子: 经过多少分钟后就没有新鲜橘子了
	int orangesRotting(vector<vector<int>>& grid)
	{
		//多源广度优先遍历. 时间复杂度O(mn), 空间复杂度O(mn)
		int m = grid.size(), n = grid[0].size();
		queue<pair<unsigned int, unsigned int>> q; //q中存放还没搜索过的腐烂橘子
		int Num1 = 0, re = 0; //Num1为最开始的时候有多少个新鲜橘子
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (grid[i][j] == 2)
				{
					q.emplace(i, j);
				}
				else if (grid[i][j] == 1)
				{
					Num1++;
				}
			}
		}
		while (!q.empty() && Num1 > 0)
		{
			unsigned int CurNum2 = q.size(); //当前队列里有多少腐烂的橘子
			while (CurNum2 > 0)
			{
				unsigned int row = q.front().first;
				unsigned int col = q.front().second;
				if (col < n - 1 && grid[row][col + 1] == 1) //右边找
				{
					q.emplace(row, col + 1);
					grid[row][col + 1] = 2;
					Num1--;
				}
				if (col > 0 && grid[row][col - 1] == 1) //左边找
				{
					q.emplace(row, col - 1);
					grid[row][col - 1] = 2;
					Num1--;
				}
				if (row > 0 && grid[row - 1][col] == 1) //上边找
				{
					q.emplace(row - 1, col);
					grid[row - 1][col] = 2;
					Num1--;
				}
				if (row < m - 1 && grid[row + 1][col] == 1) //下边找
				{
					q.emplace(row + 1, col);
					grid[row + 1][col] = 2;
					Num1--;
				}
				q.pop(); //当前腐烂橘子搜索完毕, 移出队列
				CurNum2--; //与"当前腐烂橘子"同一级别的还没被搜索的橘子数减一
			}
			re++; //已经过了一代
		}
		if (Num1 > 0)return -1; //有新鲜橘子无法腐烂
		return re;
	}
	//19.删除链表的倒数第 N 个结点
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		//快慢指针+dummy指针. 时间复杂度O(L), 空间复杂度O(1).
		ListNode* Target = head;
		ListNode* Tail = head;
		ListNode* pre = new ListNode(INT_MIN, head);
		while (n > 1)
		{
			Tail = Tail->next;
			n--;
		}
		while (Tail->next)
		{
			Tail = Tail->next;
			Target = Target->next;
			pre = pre->next;
		}
		pre->next = Target->next;
		return Target == head ? pre->next : head;
	}
	//165.比较版本号: 1.01 == 1.001, 1.0 < 1.0.5
	int compareVersion(string version1, string version2)
	{
		int CurVersion1 = 0, CurVersion2 = 0;
		int n1 = version1.size(), n2 = version2.size(), i = 0, j = 0;
		while (true)
		{
			bool IsJumpFrontZero = false;
			CurVersion1 = CurVersion2 = 0;
			for (; i < n1; i++)
			{
				if (version1[i] == '0' && !IsJumpFrontZero)continue;
				if (version1[i] == '.')break;
				IsJumpFrontZero = true;
				CurVersion1 = CurVersion1 * 10 + (version1[i] - '0');
			}
			i++;
			IsJumpFrontZero = false;
			for (; j < n2; j++)
			{
				if (version2[j] == '0' && !IsJumpFrontZero)continue;
				if (version2[j] == '.')break;
				IsJumpFrontZero = true;
				CurVersion2 = CurVersion2 * 10 + (version2[j] - '0');
			}
			j++;
			if (CurVersion1 > CurVersion2)return 1;
			if (CurVersion1 < CurVersion2)return -1;
			if (i >= n1 && j >= n2)return 0;
		}
	}
	//103.二叉树的锯齿形层序遍历: 第一层从左往右, 第二层从右往左, 第三层从左往右, 第四层从右往左...
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		//使用双端队列. 时间复杂度O(n), 空间复杂度O(n)
		//用IsNormal来标志当前层是否是"从左往右"的次序. 假如是"从左往右", 那么就从队头取节点, 然后先把左孩子插入队尾, 再把右孩子插入队尾.
		//假如是"从右往左", 那么就从队尾取节点, 然后先把右孩子插入队头, 再把左孩子插入队头
		if (!root)return {};
		vector<vector<int>> re;
		bool IsNormal = true;
		deque<TreeNode*> q;
		q.push_back(root);
		while (!q.empty())
		{
			int CurNum = q.size();
			vector<int> temp; temp.reserve(CurNum);
			while (CurNum > 0)
			{
				if (IsNormal)
				{
					TreeNode* Cur = q.front();
					temp.push_back(Cur->val);
					q.pop_front();
					if (Cur->left)q.push_back(Cur->left);
					if (Cur->right)q.push_back(Cur->right);
				}
				else
				{
					TreeNode* Cur = q.back();
					temp.push_back(Cur->val);
					q.pop_back();
					if (Cur->right)q.push_front(Cur->right);
					if (Cur->left)q.push_front(Cur->left);
				}
				CurNum--;
			}
			re.push_back(temp);
			IsNormal = !IsNormal;
		}
		return re;
	}
	//912.排序数组. 把数组按升序排列
	vector<int> sortArray(vector<int>& nums)
	{
		Sort::QuickSort(nums);
		return nums;
	}
	//222.完全二叉树的节点个数. 完全二叉树中有多少个节点
	int countNodes(TreeNode* root)
	{
		//利用完全二叉树的性质 + 二分查找 + 位运算. 时间复杂度O((logn)^2), 空间复杂度O(1)
		//首先, 一路往左, 得到完全二叉树的深度(当只有根节点时深度为1)depth. 所以该完全二叉树的节点个数只可能在[2^(depth-1), 2^depth-1]范围内. 
		//设根节点为1号节点, 那么最后一层的最右边的节点(最后一个节点)的节点号就等于该树的总节点数. 所以问题就转化为: 求最后一层的最右边的节点
		//在[2^(depth-1), 2^depth-1]范围使用二分查找. 当节点号为i时, 将其转换成二进制就必有depth位, 而且最高位必定为1. 
		//对i的二进制表示从第1位(第二高位)到第depth-1位(最低位)遍历, 如果当前位为0, 则表示该节点在当前Cur节点的左子树上; 为1则表示在右子树上
		if (!root)return 0;
		int depth = 1; //完全二叉树的深度
		TreeNode* Cur = root;
		while (Cur->left)
		{
			Cur = Cur->left;
			depth++;
		}

		int left = 1 << (depth - 1), right = (1 << depth) - 1; //为了加快运算. 2^(depth-1)就等于1<<(depth-1), 2^depth-1就等于(1<<depth)-1. left和right是该二叉树的节点个数的边界值
		while (left <= right) //二分查找
		{
			int mid = left + (right - left) / 2;
			Cur = root; //每次二分查找都要把Cur指针还原到root根节点, 以便从根往下查找mid号节点是否存在
			bool IsExist = true;
			for (int CurBit = depth - 2; CurBit >= 0; CurBit--) // CurBit为从最低位到最高位的序号(0表示最低位)
			{
				// 假如mid为11(二进制为1011), 那么从第二高位到低位的"011"表明, 从根节点(1号节点)到mid号节点的路径为: 左->右->右
				// mid转成二进制后第CurBit位(从右往左数, 最低位为第0位)为: mid & (1 << CurBit)
				if (mid & (1 << CurBit)) //右孩子
				{
					if (Cur->right) //如果右孩子存在, 那么就把Cur设置为右孩子
					{
						Cur = Cur->right;
					}
					else //右孩子不存在, 那么说明mid号节点肯定不在这个完全二叉树中
					{
						IsExist = false;
						break;
					}
				}
				else //左孩子
				{
					if (Cur->left)
					{
						Cur = Cur->left;
					}
					else
					{
						IsExist = false;
						break;
					}
				}
			}
			if (IsExist) //如果mid号节点在这个完全二叉树中...
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		return right;

		//递归. 时间复杂度O(n), 空间复杂度O(n).
		/*if (!root)return 0;
		int re = 1;
		if (root->left)
		{
			re += countNodes(root->left);
		}
		if (root->right)
		{
			re += countNodes(root->right);
		}
		return re;*/
	}
	//对于包含许多个pair的nums, 其中first表示索引(或者位置), second表示值. 需要找出一个范围[left, right], 使得nums[left]和nums[right]之间的距离不超过MaxRange, 并且范围内的所有pair的second最大
	int MaxPairValue(vector<pair<int, int>>& nums, int MaxRange)
	{
		int left = 0, right = 0, n = nums.size();
		int CurVal = nums[right].second;
		int re = CurVal;
		while (right < n - 1)
		{
			right++;
			CurVal += nums[right].second;
			while (nums[right].first - nums[left].first + 1 > MaxRange)
			{
				CurVal -= nums[left].second;
				left++;
			}
			re = max(re, CurVal);
		}
		return re;
	}
	//1052.爱生气的书店老板
	int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes)
	{
		//滑动窗口法 + 动态规划. 时间复杂度O(n), 空间复杂度O(n). 实际运行时, 比下面的方法二要快一些.
		int n = customers.size();
		vector<int> prefix(n); //prefix[i]表示[0, i]时间段来的customers之和. 前缀和
		vector<int> CalmCustomerNum(n); //CalmCustomerNum[i]表示[0, i]时间段来的因为"没有生气"而获得的顾客数量之和. 不生气的前缀和
		prefix[0] = customers[0];
		CalmCustomerNum[0] = (grumpy[0] ? 0 : customers[0]);
		for (int i = 1; i < n; i++)
		{
			prefix[i] = prefix[i - 1] + customers[i];
			CalmCustomerNum[i] = CalmCustomerNum[i - 1] + (grumpy[i] ? 0 : customers[i]);
		}
		int re = 0;
		for (int i = 0; i <= n - minutes; i++) //窗口区间: [i, i+minutes-1]
		{
			//窗口会将整个[0, n-1]区间分成三段: [0, i-1], 窗口, [i+minutes, n-1].
			int WindowAllCalm = prefix[i + minutes - 1] - (i == 0 ? 0 : prefix[i - 1]); //窗口内的时段, 全部"不生气", 期间可以获得的顾客数为: prefix[窗口右端点] - prefix[i-1](如果i为0, 那么就不减)

			//窗口左侧[0,i-1]和右侧[i+minutes,n-1]区间内, "不生气"可以获得的顾客数. 左侧区间计算: CalmCustomerNum[i-1](如果i为0, 那么就取0). 右侧区间计算: CalmCustomerNum[n-1]-CalmCustomerNum[窗口右端点]
			int OutsideCalm = (i == 0 ? 0 : CalmCustomerNum[i - 1]) + (CalmCustomerNum[n - 1] - CalmCustomerNum[i + minutes - 1]);
			re = max(re, WindowAllCalm + OutsideCalm);
		}
		return re;

		//滑动窗口法. 时间复杂度O(n), 空间复杂度O(1). 首先计算所有"不生气"时可以获得的顾客数量之和. 之后使用滑动窗口, 窗口长度为minutes, 看窗口处在什么位置时, 窗口内的"生气时的顾客数量之和"最多.
		/*
		int n = customers.size(), re = 0;
		for (int i = 0; i < n; i++)
		{
			if (!grumpy[i])
			{
				re += customers[i];
			}
		}
		//这里的re就是所有"不生气"时候可以获得的总顾客数.
		int Extra = 0, left = 0, right = 0; //Extra就是当前窗口内"生气时"获得的顾客数之和
		for (; right < minutes; right++) //创建初始窗口[0, minutes-1]
		{
			Extra += grumpy[right] * customers[right];
		}
		int MaxExtra = Extra; //窗口内的"生气时的顾客数量之和"的最大值
		for (left = 1, right = minutes; right < n; left++, right++) // 窗口从[1, minutes]开始往右滑动.
		{
			Extra -= grumpy[left - 1] * customers[left - 1];
			Extra += grumpy[right] * customers[right];
			MaxExtra = max(MaxExtra, Extra);
		}
		return re + MaxExtra;
		*/

		//动态可变窗口. 比较慢而且占内存.
		/*
		int n = customers.size(), re = 0;
		vector<pair<int, int>> AngryLostNum; //第AngryLostNum[i].first时间会因生气而离开AngryLostNum[i].second个顾客
		AngryLostNum.reserve(n);
		for (int i = 0; i < n; i++)
		{
			if (!grumpy[i])
			{
				re += customers[i];
			}
			else if (customers[i] > 0)
			{
				AngryLostNum.emplace_back(i, customers[i]);
			}
		}
		int MaxLostNum = 0;
		if (AngryLostNum.size() > 0)
		{
			MaxLostNum = MaxPairValue(AngryLostNum, minutes);
		}
		re += MaxLostNum;
		return re;
		*/
	}
	//4.寻找两个正序数组的中位数: 找出并返回这两个正序数组的中位数
	int GetKthMinNum_Recursive(vector<int>& nums1, int i, vector<int>& nums2, int j, int k)
	{
		//求第k(k最小为1)小的数(递归写法!!!!). 1.比较nums1[k/2-1]和nums2[k/2-1], 如果前者小一些(nums1[k/2-1]<nums2[k/2-1]), 那么对于nums1来说, 最多最多只可能有nums1[0:k/2-2]和nums2[0:k/2-2]共k-2个数比nums1[k/2-1]小, 所以nums1的[0, k/2-1]一定不会是第k个数, 就可以排除掉
		//2. 上面的步骤可以排除掉k/2个数, 那么现在只需要在新的(排除了k/2个数之后的)两个数组再查找第k/2个小的数.
		int n1 = nums1.size(), n2 = nums2.size(), len1 = n1 - i, len2 = n2 - j; //len1和len2为nums1和nums2有效区间的长度. [0,i-1]是nums1已经排除的区间, [i,n1-1]是nums1剩下考虑的区间
		if (len1 == 0)return nums2[j + k - 1]; //nums1整个数组已经被全部排除了, 那么当前第k(这个k通常和传进来的k不一样)个最小元素就直接是nums2[j+k-1]
		if (len2 == 0)return nums1[i + k - 1];
		if (k == 1)return min(nums1[i], nums2[j]); //如果当前k等于1了, 表示: 要在nums1和nums2的有效区间(nums1[i:n1-1]和nums2[j:n2-1])内找最小的一个数, 又因为nums1和nums2都是升序, 所以直接比较nums1[i]和nums2[j]

		int TargetIndex1 = min(i + k / 2 - 1, n1 - 1); //在"有效区间内"的第"k/2-1"个数, min是为了防止越界
		int TargetIndex2 = min(j + k / 2 - 1, n2 - 1);
		if (nums1[TargetIndex1] < nums2[TargetIndex2]) //如果nums1的这个位置小, 那么需要把当前的[i, TargetIndex1]这个区间排除掉
		{
			k -= TargetIndex1 - i + 1; //排除掉了TargetIndex1-i+1这么多个元素, 当前k还剩多少
			return GetKthMinNum_Recursive(nums1, TargetIndex1 + 1, nums2, j, k); //更新i值, 进入下一层递归
		}
		else
		{
			k -= TargetIndex2 - j + 1;
			return GetKthMinNum_Recursive(nums1, i, nums2, TargetIndex2 + 1, k);
		}
	}
	int GetKthMinNum(vector<int>& nums1, vector<int>& nums2, int k)
	{
		//求第k(k最小为1)小的数. 1.比较nums1[k/2-1]和nums2[k/2-1], 如果前者小一些(nums1[k/2-1]<nums2[k/2-1]), 那么对于nums1来说, 最多最多只可能有nums1[0:k/2-2]和nums2[0:k/2-2]共k-2个数比nums1[k/2-1]小, 所以nums1的[0, k/2-1]一定不会是第k个数, 就可以排除掉
		//2. 上面的步骤可以排除掉k/2个数, 那么现在只需要在新的(排除了k/2个数之后的)两个数组再查找第k/2个小的数.
		int n1 = nums1.size(), n2 = nums2.size();
		int i = 0, j = 0; //[0,i-1]是nums1已经排除的区间, [i,n1-1]是nums1剩下考虑的区间
		while (true)
		{
			if (i == n1)return nums2[j + k - 1]; //nums1整个数组已经被全部排除了, 那么当前第k(这个k通常和传进来的k不一样)个最小元素就直接是nums2[j+k-1]
			if (j == n2)return nums1[i + k - 1];
			if (k == 1)return min(nums1[i], nums2[j]); //如果当前k等于1了, 表示: 要在nums1和nums2的有效区间(nums1[i:n1-1]和nums2[j:n2-1])内找最小的一个数, 又因为nums1和nums2都是升序, 所以直接比较nums1[i]和nums2[j]

			int TargetIndex1 = min(i + k / 2 - 1, n1 - 1); //在"有效区间内"的第"k/2-1"个数, min是为了防止越界
			int TargetIndex2 = min(j + k / 2 - 1, n2 - 1);
			if (nums1[TargetIndex1] < nums2[TargetIndex2]) //如果nums1的这个位置小, 那么需要把当前的[i, TargetIndex1]这个区间排除掉
			{
				k -= TargetIndex1 - i + 1; //排除掉了TargetIndex1-i+1这么多个元素, 当前k还剩多少
				i = TargetIndex1 + 1;  //更新i值, 即有效区间的左边界
			}
			else
			{
				k -= TargetIndex2 - j + 1;
				j = TargetIndex2 + 1;
			}
		}
	}
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		//二分查找. 时间复杂度O(log(m+n)). 空间复杂度O(1). 把求中位数的问题转化成: 求两个有序数组第k(k从1开始)小的数. 比如当n为5时, 那么k为3. n为6时, k为3和4.
		int n = nums1.size() + nums2.size();
		int k1 = (n + 1) / 2, k2 = (n + 2) / 2; //小技巧: 假设某个升序数组nums长度为n, 那么不管n是奇数还是偶数, 他的中位数都等于nums的第k1个数和第k2个数的平均值. (k1和k2都从1开始!!!)
		//例如升序数组nums长度为5, 那么k1和k2都为3, 即nums的中位数就是nums第3个数(nums[2])和nums第3个数(nums[2])的平均值, 就等于第3个数(nums[2])
		return GetKthMinNum(nums1, nums2, k1) / 2.0 + GetKthMinNum(nums1, nums2, k2) / 2.0; //非递归版本
		//return GetKthMinNum_Recursive(nums1, 0, nums2, 0, k1) / 2.0 + GetKthMinNum_Recursive(nums1, 0, nums2, 0, k2) / 2.0; 调用递归版本的函数


		//基于数组的划分 + 二分查找. 时间复杂度O(log(min(m,n))), 空间复杂度O(1). 思想比较复杂
		/*
		int n1 = nums1.size(), n2 = nums2.size();
		if (n1 > n2)return findMedianSortedArrays(nums2, nums1); //确保nums1总是比nums2短
		int left = 0, right = n1; //对nums1做划分, 使用二分查找搜索合适的划分线, 对nums1的每一次二分搜索都可以得到nums2的划分线
		int LeftPartMax = 0, RightPartMin = 0; //左边部分(nums1的左边和nums2的左边)的最大值. 右边部分(nums1的右边和nums2的右边)的最小值
		while (left <= right) //对nums1的划分线做二分查找
		{
			int SegPos1 = left + (right - left) / 2;  //nums1划分成[0, SegPos1-1]和[SegPos1, n1-1]两部分
			int SegPos2 = (n1 + n2 + 1) / 2 - SegPos1; //nums2划分成[0, SegPos2-1]和[SegPos2, n2-1]两部分, SegPos2的位置要使得左边部分和右边部分的数一样多
			//运行到这里, 就确保了"nums1的左边长度+nums2的左边长度"等于"nums1的右边长度+nums2的右边长度".
			int LeftMax1 = (SegPos1 == 0 ? INT_MIN : nums1[SegPos1 - 1]); //通常情况下等于nums1[SegPos1 - 1]. 即"nums1左边部分的最大值(最右侧值)"
			int RightMin1 = (SegPos1 == n1 ? INT_MAX : nums1[SegPos1]);   //通常情况下等于nums1[SegPos1]. 即"nums1右边部分的最小值(最左侧值)"
			int LeftMax2 = (SegPos2 == 0 ? INT_MIN : nums2[SegPos2 - 1]); //通常情况下等于nums2[SegPos2 - 1]. 即"nums2左边部分的最大值(最右侧值)"
			int RightMin2 = (SegPos2 == n2 ? INT_MAX : nums2[SegPos2]);   //通常情况下等于nums2[SegPos2]. 即"nums2右边部分的最小值(最左侧值)"
			if (LeftMax1 <= RightMin2)
			{
				LeftPartMax = max(LeftMax1, LeftMax2); //更新左边部分的最大值
				RightPartMin = min(RightMin1, RightMin2);//更新右边部分的最小值
				left = SegPos1 + 1;
			}
			else
			{
				right = SegPos1 - 1;
			}
		}
		if ((n1 + n2) % 2 == 0)
		{
			return LeftPartMax / 2.0 + RightPartMin / 2.0;
		}
		else
		{
			return LeftPartMax;
		}
		*/

		//并不进行真正的合并, 只是根据num1和num2的长度之和计算出合并后数组的中位数的两个目标下标.时间复杂度O(m+n). 空间复杂度O(1).
		/*
		int n1 = nums1.size(), n2 = nums2.size();
		int TargetIndex1 = (n1 + n2 - 1) / 2, TargetIndex2 = (n1 + n2) / 2; //假设合并后数组为nums, 那么需要计算nums[TargetIndex1]/2.0+nums[TargetIndex2]/2.0就可以了.
		double re = 0; //结果
		int i = 0, j = 0, CurIndex = 0; //CurIndex为当前是nums的第几位
		while (i < n1 && j < n2 && CurIndex <= TargetIndex2)
		{
			if (nums1[i] > nums2[j])
			{
				if (CurIndex == TargetIndex1)re += nums2[j] / 2.0;
				if (CurIndex == TargetIndex2)re += nums2[j] / 2.0;
				j++;
			}
			else
			{
				if (CurIndex == TargetIndex1)re += nums1[i] / 2.0;
				if (CurIndex == TargetIndex2)re += nums1[i] / 2.0;
				i++;
			}
			CurIndex++;
		}
		while (CurIndex <= TargetIndex2 && i >= n1 && j < n2)
		{
			if (CurIndex == TargetIndex1)re += nums2[j] / 2.0;
			if (CurIndex == TargetIndex2)re += nums2[j] / 2.0;
			j++;
			CurIndex++;
		}
		while (CurIndex <= TargetIndex2 && j >= n2 && i < n1)
		{
			if (CurIndex == TargetIndex1)re += nums1[i] / 2.0;
			if (CurIndex == TargetIndex2)re += nums1[i] / 2.0;
			i++;
			CurIndex++;
		}
		return re;
		*/

		//先把两个数组合并, 然后求合并后数组的中位数. 时间复杂度O(m+n), 空间复杂度O(m+n).
		/*
		int n1 = nums1.size(), n2 = nums2.size();
		vector<int> nums;
		nums.reserve(n1 + n2);
		int i = 0, j = 0;
		while (i < n1 && j < n2)
		{
			if (nums1[i] > nums2[j])
			{
				nums.push_back(nums2[j]);
				j++;
			}
			else
			{
				nums.push_back(nums1[i]);
				i++;
			}
		}
		if (i >= n1)
		{
			while (j < n2)
			{
				nums.push_back(nums2[j]);
				j++;
			}
		}
		if (j >= n2)
		{
			while (i < n1)
			{
				nums.push_back(nums1[i]);
				i++;
			}
		}
		return nums[(n1 + n2 - 1) / 2] / 2.0 + nums[(n1 + n2) / 2] / 2.0;
		*/
	}
	//115.不同的子序列: "babgbag"中有5个"bag", "rabbbit"中有3个"rabbit"
	void Do(unordered_map<char, vector<int>>& map, string& t, int CurPosT, int CurPosS, unsigned long long& re)
	{   //在s的CurPosS位置之后(不包含)查找t的CurPosT处字符
		int n = t.size();
		if (CurPosT == n - 1) //如果当前已经是t的最后一位
		{
			auto it = map.find(t[CurPosT]);
			if (it != map.end() && it->second.back() > CurPosS)
			{
				int Pos = upper_bound(it->second.begin(), it->second.end(), CurPosS) - it->second.begin(); //因为map[i]的vector都是按升序排列的, 所以可以这样二分查找大于CurPosS的第一个元素出现的位置
				re += it->second.size() - Pos;
			}
			return;
		}
		auto it = map.find(t[CurPosT]);
		if (it != map.end())
		{
			int Pos = upper_bound(it->second.begin(), it->second.end(), CurPosS) - it->second.begin();
			int m = it->second.size();
			for (int i = Pos; i < m; i++)
			{
				Do(map, t, CurPosT + 1, it->second[i], re);
			}
		}
	}
	int numDistinct(string s, string t)
	{
		//二维动态规划. 时间复杂度O(mn), 空间复杂度O(mn). 下面的注释假设s为"babgbag", t为"bag". m为7, n为3.
		//使用dp[i][j]表示: 在s[i:end]中有多少个t[j:end]子序列. 其中i在[0,m]范围, j在[0,n]范围. 当i为m(7)时, s[i:end]就是空字符串"". 当j为n(3)时, t[j:end]就是空字符串""
		//1. 对所有的j==n, dp[i][j]都等于1. 因为此时t[j:end]是空字符串, 所以无论s[i:end]是什么, 其肯定有且只有一个t[j:end](空字符串).
		//2. 对所有的i==m, 只要j!=n, dp[i][j]都等于0. 因为此时s[i:end]是空字符串, 所以只要t[j:end]不为空, 那么在s[i:end](空字符串)中肯定找不到t[j:end].
		//3. 对于一般情况的i和j.  (1) 不管s[i]和t[j]是不是一样的, 都可以先考虑"在s[i:end]中, 不让s[i]与t[j]配对, 让后面的s[i+1:end]与t[j:end]配对", 对应dp矩阵是"dp[i][j]的值等于它下面的值dp[i+1][j]", 这就有dp[i+1][j]种;
		//                       (2) 如果s[i]和t[j]是一样的, 在(1)之后就还可以"让s[i]与t[j]配对, 再让后面的s[i+1:end]与t[j+1:end]配对, 对应dp矩阵是"dp[i][j]的值再加上它右下方的值dp[i+1][j+1]", 这就有dp[i+1][j+1]种.
		//从右下角开始往左上角计算, 最左上角的dp[0][0]就是要求的. 为了减少无关的计算量, 可以从dp[0][0]画一条经过dp[1][1]、dp[2][2]、dp[3][3]的斜线, 在斜线上方的部分不用计算, 因为不会影响到dp[0][0]的值.
		int m = s.size(), n = t.size();
		if (m < n)return 0; //如果s的长度比t的长度还小, 那么s根本不可能包含t, 所以直接返回0
		vector<vector<unsigned int>> dp(m + 1, vector<unsigned int>(n + 1));
		for (int i = m; i >= 0; i--) //第1点
		{
			dp[i][n] = 1;
		}
		for (int j = n - 1; j >= 0; j--)//第2点
		{
			dp[m][j] = 0;
		}
		for (int j = n - 1; j >= 0; j--) //第三点.
		{
			for (int i = m - 1; i >= j; i--) //为了减少计算量, 所以斜线上方的就不计算.
			{
				dp[i][j] = dp[i + 1][j] + (s[i] == t[j] ? dp[i + 1][j + 1] : 0); //首先, dp[i][j]肯定可以等于它下面的值(3.(1)情况), 如果s[i]和t[j]相等的话, 还要加上他右下角的值(3.(2)情况)
			}
		}
		return dp[0][0]; //返回左上角的值

		//递归. 很慢
		/*
		unordered_map<char, vector<int>> map; //每个字母会出现在哪些位置
		for (int i = 0; i < s.size(); i++)
		{
			map[s[i]].push_back(i);
		}
		int CurPosT = 0, CurPosS = -1; //当前处在t的哪个位置.  寻找t当前位置的字母必须在s字符串的CurPosS之后(不能包含)
		unsigned long long re = 0;
		Do(map, t, CurPosT, CurPosS, re);
		return re;
		*/
	}
	//23.合并 K 个升序链表: {1->4->5, 1->3->4, 2->6}合并成1->1->2->3->4->4->5->6
	ListNode* MergeTwoLists(ListNode* a, ListNode* b) //合并两个有序链表
	{
		if ((!a) || (!b))return a ? a : b;
		ListNode* re = new ListNode(INT_MAX);
		ListNode* p = a, * q = b, * Cur = re;
		while (p && q)
		{
			if (p->val < q->val)
			{
				ListNode* Next = p;
				Cur->next = Next;
				Cur = Next;
				p = p->next;
			}
			else
			{
				ListNode* Next = q;
				Cur->next = Next;
				Cur = Next;
				q = q->next;
			}
		}
		Cur->next = (p ? p : q);
		return re->next;
	}
	ListNode* Merge(vector<ListNode*>& lists, int left, int right) //基于二分的递归调用
	{
		if (left == right) return lists[left];
		if (left > right)return nullptr;
		int mid = left + (right - left) / 2;
		return MergeTwoLists(Merge(lists, left, mid), Merge(lists, mid + 1, right));
	}
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		//基于分治 + 递归的思想, 每次合并两个链表. 时间复杂度O(kn*log(k)), 空间复杂度O(logk).
		//假如lists中共有5个链表, 那么先合并[lists[0], lists[1]]->re0, 再合并[re0, lists[2]]->re1, 再合并[lists[3], lists[4]]->re2, 最后合并[re1, re2]->re
		return Merge(lists, 0, lists.size() - 1);

		//使用优先队列. 时间复杂度O(kn*log(k)), 空间复杂度O(k).
		/*
		int n = lists.size();
		if (n == 0)return nullptr;
		auto ListNodeCompareFunc = [](const ListNode* a, const ListNode* b) {return a->val > b->val; }; //将优先队列设置为按ListNode的val值升序排列
		priority_queue<ListNode*, vector<ListNode*>, decltype(ListNodeCompareFunc)> q(ListNodeCompareFunc);
		for (int i = 0; i < n; i++)
		{
			if (lists[i])q.push(lists[i]); //将每个"头节点非空的链表"加入优先队列
		}
		ListNode* re = new ListNode(INT_MAX); //初始的哑节点, 避免第一次操作时要re=Node, 后面几次操作都是re->next=Node
		ListNode* Cur = re; //当前结果链表的尾节点
		while (!q.empty())
		{
			ListNode* top = q.top(); //当前值最小的链表
			q.pop();
			Cur->next = top; //连接到后面
			Cur = top; //更新Cur
			if (top->next) //如果当前链表的下一个节点不为空, 就将其加入队列
			{
				top = top->next;
				q.push(top);
			}
		}
		return re->next;
		*/
	}
	//478.在圆内随机生成点
	vector<double> randPoint()
	{
		// 拒绝采样. 在以原点为中心的边长为2的正方形中生成随机点, 然后拒绝掉不在"以原点为圆心的单位圆"中, 然后做一个坐标变换. 时间复杂度O(1), 空间复杂度O(1).
		mt19937 gen(random_device{}());
		uniform_real_distribution<double> dis(-1, 1); // [-1,1]内的均匀分布
		double x = dis(gen), y = dis(gen); //x从[-1,1], y从[-1,1]内的正方形的均匀分布
		while (x * x + y * y > 1) //如果不在单位圆(圆心在原点)里面, 就重新生成.
		{
			x = dis(gen);
			y = dis(gen);
		}
		return { x * Radius + CenterX , y * Radius + CenterY }; //计算坐标

		// 生成随机的θ和r, 再根据x=r*cos(θ), y=r*sin(θ)得到坐标. 时间复杂度O(1), 空间复杂度O(1).
		// 注意: 不能直接生成随机数r, 应该先生成随机数n, 再让r=sqrt(n). 因为是面积微分的随机, 不是半径微分的随机.
		/*
		mt19937 gen(random_device{}());
		uniform_real_distribution<double> dis(0, 1); // [0,1]内的均匀分布
		double Angle = dis(gen) * 2 * M_PI; //Angle为[0, 2pi]内的均匀分布
		double R1 = sqrt(dis(gen)); //首先要生成单位圆(R=1)内的半径. 生成方法: 先生成[0,1]内的随机数n, 然后R=sqrt(n), 此时这个R才是均匀分布. 注意: 这个R是单位圆上的
		return { R1*cos(Angle)*Radius + CenterX, R1*sin(Angle)*Radius + CenterY }; //计算坐标
		*/

	}
	//129.求根节点到叶节点数字之和: 每条从根节点到叶节点的路径都代表一个数字, 计算从根节点到叶节点生成的所有数字之和
	void Do(TreeNode* root, int& re, int CurPath)
	{   //因为CurPath只能由上一层传给下一层, 而不能由下一层返回给上一层, 所以CurPath不能传引用.
		if (!root)return;
		CurPath = CurPath * 10 + root->val;
		if (!root->left && !root->right)
		{
			re += CurPath;
			return;
		}
		Do(root->left, re, CurPath);
		Do(root->right, re, CurPath);
	}
	int sumNumbers(TreeNode* root)
	{
		//递归解法(深度优先搜索). 时间复杂度O(n), 空间复杂度O(n)
		int re = 0, CurPath = 0;
		Do(root, re, CurPath);
		return re;

		//广度优先搜索. 时间复杂度O(n), 空间复杂度O(n). 但是会比深度优先搜索慢一些.
		/*
		if (!root)return 0;
		int re = 0;
		queue<TreeNode*> q;
		queue<int> CurPath; //CurPath与q是一一对应的, CurPath[i]表示从根节点到q[i]节点的路径数字
		q.push(root);
		CurPath.push(root->val);
		while (!q.empty())
		{
			TreeNode* Cur = q.front();
			if (!Cur->left && !Cur->right)
			{
				re += CurPath.front();
				q.pop();
				CurPath.pop();
				continue;
			}
			if (Cur->left)
			{
				q.push(Cur->left);
				CurPath.push(CurPath.front() * 10 + Cur->left->val);
			}
			if (Cur->right)
			{
				q.push(Cur->right);
				CurPath.push(CurPath.front() * 10 + Cur->right->val);
			}
			q.pop();
			CurPath.pop();
		}
		return re;
		*/
	}
	//41.缺失的第一个正数. 例如[-3, 1, 0, -1, 2, 9, 4]缺失的第一个正数就是3
	int firstMissingPositive(vector<int>& nums)
	{
		//基于置换的原地哈希. 时间复杂度O(n), 空间复杂度O(1). 要求nums允许修改!
		//置换的目标是让第i处的数nums[i]出现在他应该出现的地方(第nums[i]-1位), 即要让nums的第k位放k+1. 置换完成后遍历nums, 如果某个位置i处的值不为i+1, 就表明原数组中缺失i+1这个数, 所以就返回i+1.
		//如果最后遍历完了还没找到, 那么说明原数组里的数是1~n都有, 所以就应该返回n+1.
		int n = nums.size();
		for (int i = 0; i < n; i++)
		{
			//如果第i处的值是合理的(应该被放在对应位置), 而且对应位置的数跟现在的数不一样(如果不加这个限定条件的话, 假如交换的两个地方的数本来是相等的, 那么会出现死循环), 那么就应该把第i处和第nums[i]-1处的值交换
			//用while循环是因为, 交换到第i处的值(也就是原第nums[i]-1)处的值可能也是合理的, 也应该放到对应位置.
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
			{
				swap(nums[nums[i] - 1], nums[i]);
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (nums[i] != i + 1)return i + 1;
		}
		return n + 1;

		//基于打标记的原地哈希. 时间复杂度O(n), 空间复杂度O(1). 要求nums允许修改! 先验知识: 缺失的第一个(最小)正数一定是在[1, n+1]的范围内!
		//将数组中所有小于等于0的数都改成INT_MAX. 再遍历这个数组, 对每个数求他的绝对值num, 如果nums[num-1]还是正数, 就把它改成负数(相当于做标记, 表示num这个数出现过). 所以如果nums[i]为负数, 就表明i+1是在原数组中存在的
		//最后遍历一次数组, 如果nums[i]还是正数, 也就是说i这个位置还没被标记, 所以就表明i+1在原数组中是不存在的, 就返回i+1. 如果遍历完了还没找到负数, 就说明原数组中的正数都是连续的从1~n都有, 那么就返回n+1.
		/*
		int n = nums.size();
		for (int& num : nums) //将数组中所有小于等于0的数都改成INT_MAX
		{
			if (num <= 0)
			{
				num = INT_MAX;
			}
		}
		for (int i = 0; i < n; i++)
		{
			int num = abs(nums[i]);
			if (num <= n && nums[num - 1] > 0)
			{
				nums[num - 1] = -nums[num - 1]; //把第num-1处置为负数, 表明原数组中存在num这个数
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (nums[i] > 0)return i + 1; //原数组中不存在i+1这个数
		}
		return n + 1;
		*/

		//先排序, 然后从正数部分开始找缺失哪个数. 时间复杂度O(nlogn), 空间复杂度O(nlogn).
		/*
		int n = nums.size();
		sort(nums.begin(), nums.end()); //升序排列
		if (nums[n - 1] <= 0)return 1;
		int left = upper_bound(nums.begin(), nums.end(), 0) - nums.begin(); //第一个正数的位置
		if (nums[left] != 1)return 1; //如果第一个正数不为1, 说明1肯定没有, 就直接返回1
		nums.push_back(-1); //在最后插一个-1, 如果不插的话, 假如是[1, 2, 3, 4]这种缺最后一个元素的情况, return CurTarget;之后还得单独判断
		int CurTarget = 1, i = left;
		while (i < n + 1)
		{
			while (i < n + 1 && nums[i] == CurTarget)
			{
				i++;
			}
			CurTarget++;
			if (i < n + 1 && nums[i] != CurTarget)
			{
				return CurTarget;
			}
		}
		*/
	}
	//31.下一个排列: 返回下一个字典序更大的排列, 如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列. 如何[1,2,3]返回[1,3,2]; [3,2,1]返回[1,2,3]
	void nextPermutation(vector<int>& nums)
	{
		//原地算法. 时间复杂度O(n), 空间复杂度O(1). 假设原输入数组为[1,9,1,9,8,1,0], 首先从右往左遍历, 直到当前的nums[i]比nums[i+1]小, 即i为2(nums[i]为1)时. 此时, nums的[i+1:end](9,8,1,0)肯定是降序的
		//然后, 因为i后面的序列是有序数列, 所以用二分查找在[i+1:end]范围内, 大于nums[1]的最小的数, 即j为4(nums[j]为8), 再把nums[i]和nums[j]交换, 就变成了[1,9,8,9,1,1,0], 那么这时候, nums的[i+1:end](9,1,1,0)肯定也是降序的
		//最后再把nums的[i+1:end]反转成升序(变成0,1,1,9)就可以了.最后就得到了[1,9,8,0,1,1,9]
		int n = nums.size();
		for (int i = n - 2; i >= 0; i--)
		{
			if (nums[i] >= nums[i + 1])continue; //当前元素本来就比后一个元素大, 就不用管
			int TargetIndex = n - 1 - (upper_bound(nums.rbegin(), nums.rbegin() + (n - i - 1), nums[i]) - nums.rbegin()); //二分查找, 从右往左做二分查找
			swap(nums[TargetIndex], nums[i]);
			reverse(nums.begin() + i + 1, nums.end());
			return;
		}
		reverse(nums.begin(), nums.end()); //如果最后都没找到某个元素比它后面的元素小, 说明这个排列本来就是降序排列, 那么直接反转成升序就可以了
	}
	//76.最小覆盖子串. 例如在字符串"ADOBECODEBANC"中, 覆盖了"ABC"的所有字符的最小子串是"BANC"
	string minWindow(string s, string t)
	{
		//滑动窗口. 时间复杂度O(n), 空间复杂度O(C), C为字符集. 
		int m = s.size(), n = t.size();
		if (m < n)return "";
		vector<int> nums(128, 0); //'A'的ASCII码为65, 'a'的ASCII码为122, 所以大小为128够用
		for (char& c : t) //统计t中每个字符出现的次数
		{
			nums[c]++;
		}
		string re = "";
		//对s做循环
		for (int left = 0, right = 0, MatchedCount = 0; right < m; right++) //MatchedCount表示当前窗口内包含多少个t中的字符, 假设t为"ABBC", 那么MatchedCount最大就是4
		{
			nums[s[right]]--; //nums中消耗一个right处字符
			if (nums[s[right]] >= 0) //如果消耗完之后, nums中right这里的字符数还是大于等于0的, 说明s[right]肯定在t中, 表明找到了t中的一个字符
			{
				MatchedCount++;
			}
			//判断左边界是否可以左移
			while (MatchedCount == n && nums[s[left]] < 0) //如果当前已经找齐了t中的所有字符, 而且【左边界处的字符[原本就不属于t中]或者[属于t中, 但是窗口内有不止一个这个字符], 这两个情况都是nums[s[left]]<0】
			{
				nums[s[left]]++; //左边界左移之前, 归还左边界处的字符
				left++; //左边界左移
			}
			//更新结果
			if (MatchedCount == n && (re.size() == 0 || right - left + 1 < re.size())) //如果当前已经找齐了t中的所有字符, 而且【re还没被赋值过, 或者说re之前被赋值过, 但是当前的窗口长度更短】, 那么就要更新结果
			{
				re = s.substr(left, right - left + 1);
			}
		}
		return re;
	}
	//33.搜索旋转排序数组: 把一个升序数组变成两段, 如[1,2,3,4,5,6]变成[5,6,1,2,3,4], 再查找对应位置
	int search(vector<int>& nums, int target)
	{
		//二分法. 时间复杂度O(logn), 空间复杂度O(1).
		//升序数组旋转之后, 分成了两段(设为A段和B段), 每一段分别都是递增的, 而且【B段的最大值(最后一个值nums[n-1])或者说B段的所有值】肯定都小于【A段的最小值(第一个值nums[0])或者说A段的所有值】
		int n = nums.size(), left = 0, right = n - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (nums[mid] == target)return mid;
			//运行到这里, 说明nums[mid]肯定不等于target
			if (nums[mid] >= nums[0])  //表明当前mid处在A段中
			{   //target就有三种可能: 
				// 1.在[0, mid-1]内, 则target >= nums[0] && target < nums[mid]. 此时直接把right设置为mid-1就可以了
				// 2.在[mid+1, Aend]内, 则要在mid的右边找
				// 3.在B段[Bstart, n-1]中, 则要在mid的右边找
				if (target >= nums[0] && target < nums[mid])
				{
					right = mid - 1;
				}
				else
				{
					left = mid + 1;
				}
			}
			else //表明当前mid处在B段中
			{
				//target就有三种可能: 
				// 1.在[Bstart, mid-1]内, 则要在mid的左边找
				// 2.在[mid+1, n-1]内, 则target > nums[mid] && target <= nums[n - 1]. 此时直接把left设置为mid+1就可以了
				// 3.在A段[0, Aend]中, 则要在mid的左边找
				if (target > nums[mid] && target <= nums[n - 1])
				{
					left = mid + 1;
				}
				else
				{
					right = mid - 1;
				}
			}
		}
		return -1; //没找到
	}
	//92.反转链表 II. 假设链表为: [1->2->3->4->5->6], left为2, right为5, 那么结果应该是[1->5->4->3->2->6]
	ListNode* reverseBetween(ListNode* head, int left, int right)
	{
		//头插法. 最多一次遍历. 时间复杂度O(n), 空间复杂度O(1). 经典的"穿针引线": 右、左、右.
		ListNode* dummy = new ListNode(INT_MIN, head); //设置dummy节点, 防止left为1而不好处理
		ListNode* pre = dummy; // pre在固定之后就不会动了, 永远指向left的前一个节点(1)
		for (int i = 0; i < left - 1; i++)
		{
			pre = pre->next;
		} //此时, pre指向left的前一个节点
		ListNode* cur = pre->next; //cur永远指向left对应的节点, 不会动, 但是他在链表中的次序会变
		for (int i = left; i < right; i++) // 每次直行到这一行时, i一定都等于cur节点(left节点)在链表中的次序
		{   //循环里面不用担心next为nullptr而导致next->next报错的情况! 因为i为cur当前在链表中的次序, i是小于right的, 而right一定是小于或等于链表中节点个数的
			ListNode* next = cur->next; //next指向cur当前的下一个节点, 这一次循环结束之后, 会变成pre的next节点(变到最开头去了)
			cur->next = next->next; // 右. left节点的next设置为next->next
			next->next = pre->next; // 左. next节点的next设置为pre->next
			pre->next = next;       // 右. pre(left的前一个节点)的next设置为next
		}
		return dummy->next;
	}
	//72.编辑距离. 将 word1 转换成 word2 所使用的最少操作数. 例如将"horse"变成"ros"最少需要3步
	int minDistance(string word1, string word2)
	{
		//二维动态规划. 时间复杂度O(mn), 空间复杂度O(mn). 使用一个二维数组dp. dp[i][j]表示: word1[0:i]变为word2[0:j]最少需要多少步. 增: dp[i][j]=dp[i][j-1]+1. 删:dp[i][j]=dp[i-1][j]+1. 改:dp[i][j]=dp[i-1][j-1]+1
		int m = word1.size(), n = word2.size();
		if (m * n == 0)return m + n; //1. 如果m和n都为0(都为空字符串), 那么最少需要0步. 2.如果m为0(""变成"ros"), 那么就最少需要n步. 3. 如果n为0("ros"变成""), 那么最少需要m步
		vector<vector<int>> dp(m, vector<int>(n)); //m行n列
		dp[0][0] = (word1[0] == word2[0] ? 0 : 1); //将word1[0]变成word2[0]最少需要多少步. 如果他们相等就肯定只需要0步.
		for (int j = 1; j < n; j++) //将word1[0]变成word2[0:j]. 如果word1[0]等于word2[j](从"a"变到"cba"), 那么就只需要j步(添加word2前面的j个); 否则(从"a"变到"abc"), 就需要dp[0][j-1]+1步(从"a"变到"ab"的步数+1)
		{
			dp[0][j] = (word1[0] == word2[j] ? j : dp[0][j - 1] + 1);
		}
		for (int i = 1; i < m; i++)//将word1[0:i]变成word2[0]. 如果word1[i]等于word2[0](从"cba"变到"a"), 那么就只需要i步(删除word1前面的i个); 否则(从"cba"变到"b"), 就需要dp[i-1][0]+1步(从"cb"变到"b"的步数+1)
		{
			dp[i][0] = (word1[i] == word2[0] ? i : dp[i - 1][0] + 1);
		}
		for (int i = 1; i < m; i++) //一般的情况: 将word1[0:i]变成word2[0:j]
		{
			for (int j = 1; j < n; j++)
			{
				if (word1[i] == word2[j]) //如果word1[i]等于word2[j](从"hors"变到"ros"), 那么步数就直接等于从dp[i-1][j-1](从"hor"变到"ro")
				{
					dp[i][j] = dp[i - 1][j - 1];
				}
				else //否则(从"hor"变到"ros"), 那么步数就需要从dp[i-1][j](从"ho"变到"ros", 2步), dp[i][j-1](从"hor"变到"ro", 2步), dp[i-1][j-1](从"ho"变到"ro", 1步)这三者中找出最小值再加一
				{
					dp[i][j] = min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
				}
			}
		}
		return dp[m - 1][n - 1]; //dp[m-1][n-1]就是word1[0:m-1](全部的word1)变到word2[0:n-1](全部的word2)所需的最少步数
	}
	//704.二分查找. 在升序数组nums中查找target
	int search704(vector<int>& nums, int target)
	{
		//时间复杂度O(logn), 空间复杂度O(1).
		int n = nums.size();
		int left = 0, right = n - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (nums[mid] == target)
			{
				return mid;
			}
			if (nums[mid] < target)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		return -1;
	}
	//199.二叉树的右视图
	void Dfs(TreeNode* root, vector<int>& re, int CurDepth) //CurDepth为当前root所在的深度
	{
		if (!root)return;
		if (CurDepth > re.size()) //如果re的大小比CurDepth小, 说明当前深度还没有加入任何一个节点, 又因为是先访问的右孩子再访问的左孩子(下面的代码), 说明当前节点是当前层的最右节点, 右视图能看到
		{
			re.push_back(root->val);
		}
		Dfs(root->right, re, CurDepth + 1); //先访问右孩子, 再访问左孩子
		Dfs(root->left, re, CurDepth + 1);
	}
	vector<int> rightSideView(TreeNode* root)
	{
		//层次遍历(广度优先搜索). 时间复杂度O(n), 空间复杂度O(n).
		vector<int> re;
		if (!root)return re;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int n = q.size();
			re.push_back(q.back()->val); //上一层的最右侧节点
			for (int i = 0; i < n; i++)
			{
				TreeNode* Cur = q.front();
				q.pop();
				if (Cur->left)q.push(Cur->left);
				if (Cur->right)q.push(Cur->right);
			}
		}
		return re;

		//递归(深度优先搜索). 时间复杂度O(n), 空间复杂度O(n).
		/*
		vector<int> re;
		if (!root)return re;
		Dfs(root, re, 1);
		return re;
		*/

		//基于Morris遍历. 时间复杂度O(n), 空间复杂度O(1).
		/*
		vector<int> re;
		if (!root)return re;
		int CurDepth = 1;
		TreeNode* pre = nullptr;
		while (root)
		{
			pre = root->right;
			if (pre)
			{
				int n = 1;
				while (pre->left && pre->left != root)
				{
					pre = pre->left;
					n++;
				}
				if (pre->left)
				{
					pre->left = nullptr;
					root = root->left;
					CurDepth -= n;
				}
				else
				{
					if (CurDepth > re.size())
					{
						re.push_back(root->val);
					}
					pre->left = root;
					root = root->right;
					CurDepth++;
				}
			}
			else
			{
				if (CurDepth > re.size())
				{
					re.push_back(root->val);
				}
				root = root->left;
				CurDepth++;
			}
		}
		return re;
		*/

	}
	//1143.最长公共子序列. 例如"abcde"和"afce"之间的最长公共子序列是"ace", 长度为3
	int longestCommonSubsequence(string text1, string text2)
	{
		//二维动态规划 + 空间压缩. 时间复杂度O(mn), 空间复杂度O(n). dp数组长为n+1, 而且是随着遍历text1的过程动态变化的, dp[i+1]表示在当前text1的子串下, text2[0:i]的最长公共子序列长度
		int n = text2.size();
		vector<int> dp(n + 1);
		for (char x : text1) //遍历text1, 相当于每次都是从text1[0]到x之间的子串
		{
			int pre = 0; //pre表示: 对每个i, 因为要算dp[i+1], 所以需要dp[i]的值, pre存储的就是上一次i循环的dp[i+1]的值
			for (int i = 0; i < n; i++)
			{
				int temp = dp[i + 1];
				dp[i + 1] = (x == text2[i] ? pre + 1 : max(dp[i + 1], dp[i]));
				pre = temp;
			}
		}
		return dp[n];

		//二维动态规划. 时间复杂度O(mn), 空间复杂度O(mn). 使用一个二维数组dp. dp[i][j]表示text1[0:i]与text2[0:j]的最长公共子序列长度
		/*
		int m = text1.size(), n = text2.size();
		if (m == 0 || n == 0)return 0; //如果text1和text2存在空字符串, 那么最长公共子序列肯定也是空字符串, 长度为0
		vector<vector<int>> dp(m, vector<int>(n)); //m行n列的二维数组
		dp[0][0] = (text1[0] == text2[0] ? 1 : 0); //dp[0][0]表示text1[0]和text2[0]之间的最长公共子序列长度, 所以显然需要看它们是否相同
		for (int j = 1; j < n; j++) //text1[0]和text2[0:j]之间的最长公共子序列长度. 假如text1[0]与text2[j]相等("a"与"cba"), 那么显然它们的最长公共子序列("a")长度就为1; 否则("a"与"cbd")就为0.
		{
			dp[0][j] = ((dp[0][j - 1] == 1 || text2[j] == text1[0])? 1 : 0);
		}
		for (int i = 1; i < m; i++) //text1[0:i]和text2[0]之间的最长公共子序列长度. 假如text1[i]与text2[0]相等("cba"与"a"), 那么显然它们的最长公共子序列("a")长度就为1; 否则("cbd"与"a")就为0.
		{
			dp[i][0] = ((dp[i - 1][0] == 1 || text1[i] == text2[0]) ? 1 : 0);
		}
		for (int i = 1; i < m; i++) //更一般的情况.
		{ //假如text1[i]与text2[j]相等("abcd"与"bamd"), 那么dp[i][j]就等于dp[i-1][j-1]("abc"与"bam")加一(加上最后的"d"). 否则("abm"与"bamc"), 就要看dp[i-1][j]("ab"与"bamc")和dp[i][j-1]("abm"与"bam")哪个大
			for (int j = 1; j < n; j++)
			{
				dp[i][j] = (text1[i] == text2[j] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]));
			}
		}
		return dp[m - 1][n - 1];
		*/
	}
	//70.爬楼梯(斐波拉切数列)
	unsigned long long** Multiple(unsigned long long** a, unsigned long long** b) //普通的2x2的矩阵乘法
	{
		unsigned long long** re = new unsigned long long* [2];
		re[0] = new unsigned long long[2];
		re[1] = new unsigned long long[2];
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				re[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
			}
		}
		return re;
	}
	unsigned long long** MatrixQuickPow(unsigned long long** a, int n) //矩阵快速幂
	{
		unsigned long long** re = new unsigned long long* [2];
		re[0] = new unsigned long long[2] { 1, 0 };
		re[1] = new unsigned long long[2] { 0, 1 };
		while (n > 0)
		{
			if (n & 1) //是奇数
			{
				unsigned long long** temp = Multiple(re, a);
				delete[] re;
				re = temp;
			}
			n >>= 1; // n除以2取整
			unsigned long long** temp = Multiple(a, a);
			delete[] a;
			a = temp;
		}
		return re;
	}
	int climbStairs(int n)
	{
		//基于通项公式. 
		double Sqrt5 = sqrt(5);
		double re = (pow((1 + Sqrt5) / 2, n + 1) - pow((1 - Sqrt5) / 2, n + 1)) / Sqrt5;
		return round(re);

		//基于矩阵快速幂: 其实就是[1,1;1,0]这个2x2矩阵的n次幂的左上角数. 时间复杂度O(logn), 空间复杂度O(1)
		/*
		unsigned long long** re = new unsigned long long*[2];
		re[0] = new unsigned long long[2]{ 1,1 };
		re[1] = new unsigned long long[2]{ 1,0 };
		unsigned long long** temp = MatrixQuickPow(re, n);
		re = temp;
		return re[0][0];
		*/

		//基于迭代式动态规划. 时间复杂度O(n), 空间复杂度O(1).
		/*
		if (n <= 3)return n;
		int Pre2 = 2, Pre1 = 3, re;
		for (int i = 4; i <= n; i++)
		{
			re = Pre2 + Pre1;
			Pre2 = Pre1;
			Pre1 = re;
		}
		return re;
		*/
	}
	//148.排序链表
	ListNode* FindMid(ListNode* head) //找到链表的中间节点
	{
		if (!head)return nullptr;
		ListNode* mid = head, * tail = head;
		while (tail->next && tail->next->next)
		{
			tail = tail->next->next;
			mid = mid->next;
		}
		return mid;
	}
	ListNode* CutList(ListNode* head, int Len) //从head开始, 截取出长度为Len的子链表(会把子链表的最后一个元素的next置为nullptr)返回
	{
		Len--;
		while (head && Len > 0)
		{
			head = head->next;
			Len--;
		}
		if (!head)return nullptr;
		ListNode* re = head->next;
		head->next = nullptr;
		return re;
	}
	ListNode* partition(ListNode*& head, ListNode* end) //一趟快速排序. 注意: 这个函数会修改head指针指向的节点, 所以head指针需要传引用
	{
		ListNode* target_pre = head; //实际目标节点的前驱
		ListNode* pivot = head; //pivot节点设置为第一个节点
		while (target_pre != end) //依次往后遍历target_pre, 实际要找的是
		{   //因为pivot为第一个节点, 而target_pre是从第一个节点往后遍历的, 所以只要target_pre->next(目标节点)大于或等于pivot的值(本就应该放在pivot的右边), 所以就不需要动
			while (target_pre->next && target_pre->next->val >= pivot->val)
			{
				target_pre = target_pre->next;
			}
			if (!target_pre->next) //当前已经遍历完了
			{
				return pivot;
			}
			ListNode* temp = target_pre->next; //让head指向目标节点(target_pre->next), 并且把pivot节点移到目标节点的后面一个节点(因为目标节点的值比pivot要小)
			target_pre->next = temp->next;
			temp->next = head;
			head = temp;
		}
		return pivot;
	}
	ListNode* QuickSort_Recur_List(ListNode* head, ListNode* end) //基于递归的链表快速排序
	{
		ListNode* dummy = new ListNode(-1, head);
		if (head != end && head->next != end)
		{
			ListNode* pivot = partition(dummy->next, end);
			dummy->next = QuickSort_Recur_List(dummy->next, pivot); //dummy->next指向的节点会改变
			pivot->next = QuickSort_Recur_List(pivot->next, end);
		}
		return dummy->next;
	}
	ListNode* sortList(ListNode* head)
	{
		//自底向上(迭代)的链表归并排序. 时间复杂度O(nlogn), 空间复杂度O(1).
		if (!head || !head->next)return head;
		int TotalLen = 0; //计算链表的长度
		ListNode* cur = head;
		while (cur)
		{
			TotalLen++;
			cur = cur->next;
		}
		ListNode* dummy = new ListNode(-1, head);
		for (int SubLen = 1; SubLen < TotalLen; SubLen <<= 1) //每次都将前后两个SubLen长度的子链表(A和B)合并
		{
			ListNode* pre = dummy; //第一次合并前, 先指定子链表A的前驱节点
			cur = dummy->next; //cur在这里表示: 子链表A的头节点
			while (cur) //开始逐个合并
			{
				ListNode* FrontHead = cur; //当前子链表A的头节点
				ListNode* BackHead = CutList(FrontHead, SubLen); //将子链表A切出来, 也会得到子链表B的头节点. 执行完这一步后, 子链表A的尾节点的next会被置为nullptr
				cur = CutList(BackHead, SubLen); //再将子链表B切出来, 同时得到下一次循环时下一个子链表A的头节点. 执行完这一步后, 子链表B的尾节点的next会被置为nullptr
				pre->next = mergeTwoLists(FrontHead, BackHead); //合并AB两个子链表, 将当前的前驱节点的next指向合并后的链表的头节点
				while (pre->next) //因为在合并之前把子链表B的尾节点的next置为nullptr了, 所以需要依次往后遍历合并之后的整个链表的尾节点作为下一次合并的前驱结点pre
				{
					pre = pre->next;
				}
			}
		}
		return dummy->next;


		//基于递归的链表快速排序. 平均时间复杂度O(nlogn), 空间复杂度O(logn). 会超时.
		/*
		return QuickSort_Recur_List(head, nullptr);
		*/

		//自顶向下(递归)的链表归并排序. 时间复杂度O(nlogn), 空间复杂度O(logn).
		/*
		if (!head || !head->next)return head; //如果当前head已经是空或者只有head这一个节点, 那么直接返回
		ListNode* mid = FindMid(head); //找到head的中点mid
		ListNode* next = mid->next; //在mid处断开之前, 先得到mid的下一个节点
		mid->next = nullptr; //mid处断开
		ListNode* Front = sortList(head); //前半段递归调用
		ListNode* Back = sortList(next);  //后半段递归调用
		return mergeTwoLists(Front, Back); //合并前半段和后半段这两个有序链表
		*/
	}
	//69.x的平方根(结果取整)
	int mySqrt(int x)
	{
		//牛顿迭代法. 时间复杂度O(logx), 空间复杂度O(1).
		//实际上是求解Y=X^2-x的零点, 首先令X的初值为x0, 函数在x处的点坐标就是(x0, x0^2-x), 在该点处的切线方程为: Y=2*x0*X-x0^2-x, 该切线方程与X轴的交点为((x0+x/x0)/2, 0).
		if (x == 0)return 0;
		double x0 = x;
		while (true)
		{
			double xi = 0.5 * (x0 + x / x0);
			if (fabs(xi - x0) < 1e-7)
			{
				return int(xi);
			}
			x0 = xi;
		}

		// 二分查找. 时间复杂度O(logx), 空间复杂度O(1).
		/*
		int low = 0, high = 46340;
		while (low <= high)
		{
			if (low * low == x)return low;
			if (high * high == x)return high;
			int mid = (low + high) / 2;
			int CurX = mid * mid;
			if (CurX == x || (CurX < x && (unsigned int)(CurX) + 2 * mid + 1 > x))
			{
				return mid;
			}
			if (CurX < x)
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
		return -1;
		*/
	}
	//x的平方根(结果有精度要求), accuracy为0.1, 0.01, 0.001...
	double mySqrt(double x, double accuracy)
	{
		//牛顿迭代法. 时间复杂度O(logx), 空间复杂度O(1).
		//实际上是求解Y=X^2-x的零点, 首先令X的初值为x0, 函数在x处的点坐标就是(x0, x0^2-x), 在该点处的切线方程为: Y=2*x0*X-x0^2-x, 该切线方程与X轴的交点为((x0+x/x0)/2, 0).
		if (x < 0)return -1;
		if (fabs(x) <= 1e-5)return 0;
		double x0 = x;
		while (true)
		{
			double xi = 0.5 * (x0 + x / x0);
			if (fabs(xi - x0) <= accuracy)
			{
				return xi;
			}
			x0 = xi;
		}

		//浮点数二分法.
		/*
		if (x < 0)return -1;
		if (fabs(x) <= 1e-5)return 0; //x为0和1的情况要特别处理
		if (fabs(x - 1.0) <= 1e-5)return 1;
		double low = 1, high = x; //对于x>1的情况
		if (x < 1) //对于x<1的情况
		{
			low = 0;
			high = 1;
		}
		while (low < high)
		{
			double mid = low + (high - low) / 2.0;
			double CurX = mid * mid;
			if (CurX <= x && CurX + 2 * mid * accuracy + accuracy * accuracy > x)
			{
				double ProbablyResult = ceil(mid); //避免出现81求平方根得到8.99888671875这种错误
				return ProbablyResult * ProbablyResult <= x ? ProbablyResult : mid;
			}
			if (CurX > x)
			{
				high = mid;
			}
			else
			{
				low = mid + accuracy;
			}
		}
		return -1;
		*/
	}
	//8.字符串转换整数 (atoi)
	int myAtoi(string s)
	{
		//时间复杂度O(n), 空间复杂度O(1). 统一按正数处理, 最后输出结果时再看是否要反号.
		bool IsPositive = true; //是否为正数
		bool IsInitial = false; //是否已经确定了正负号
		int re = 0;
		for (char& c : s)
		{
			if (!IsInitial)
			{
				if (c == ' ') //跳过前置空格
				{
					continue;
				}
				else if (c == '+' || isdigit(c)) //还没初始化的时候就碰到了+号, 或者碰到了一个数字, 说明当前是一个正数
				{
					IsInitial = true;
					IsPositive = true;
					if (isdigit(c))
					{
						re = (c - '0');
					}
				}
				else if (c == '-') //还没初始化的时候就碰到了-号, 说明当前是一个负数
				{
					IsInitial = true;
					IsPositive = false;
				}
				else //还没初始化的时候就碰到了特殊字符, 说明是无效字符串
				{
					return 0;
				}
			}
			else
			{
				if (!isdigit(c)) //初始化之后碰到了非数字字符, 说明有效部分到此为止了
				{
					break;
				}
				if (IsPositive && (re > 214748364 || (re == 214748364 && c >= '7'))) //判断加入当前数字后是否会超过INT_MAX
				{
					return INT_MAX;
				}
				if (!IsPositive && (re > 214748364 || (re == 214748364 && c >= '8'))) //判断加入当前数字后是否会超过INT_MIN
				{
					return INT_MIN;
				}
				re = re * 10 + (c - '0');
			}
		}
		return (IsPositive ? re : -re);


		//一个投机取巧的解法.
		/*
		stringstream ss(s);
		int re = 0;
		ss >> re;
		return re;
		*/

	}
	//剑指 Offer 22. 链表中倒数第k个节点
	ListNode* getKthFromEnd(ListNode* head, int k)
	{
		//前后双指针法. 时间复杂度O(n), 空间复杂度O(1).
		ListNode* re = head;
		ListNode* tail = head;
		while (k > 1)
		{
			tail = tail->next;
			k--;
		}
		while (tail->next)
		{
			tail = tail->next;
			re = re->next;
		}
		return re;
	}
	//32.最长有效括号: 找出最长有效（格式正确且连续）括号子串的长度. 例如"(()"返回2, ")()())"返回4, "((()())("返回6
	int longestValidParentheses(string s)
	{
		//贪心思想: 向左向右两次遍历, 分别记录当前左右括号的数量, 当左右括号数相等时, 更新结果. 时间复杂度O(n), 空间复杂度O(1).
		int n = s.size();
		if (n <= 1)return 0;
		int CurLeft = 0, CurRight = 0; //左右括号的数量
		int re = 0;
		for (int i = 0; i < n; i++) //先从左往右遍历
		{
			if (s[i] == '(')CurLeft++;
			else CurRight++;
			if (CurLeft == CurRight) //如果当前左右括号数相等, 更新结果
			{
				re = max(re, 2 * CurRight);
			}
			else if (CurRight > CurLeft) //如果到当前位置时, 右括号数量更多, 就丢弃之前的部分, 从下一个字符重新考虑
			{
				CurLeft = CurRight = 0;
			}
		}
		//如果不做第二次从右往左的遍历的话, 像"(()"这种左括号永远多于右括号的情况, 是不会有结果的, 所以要再来一次从右往左的遍历
		CurLeft = CurRight = 0;
		for (int i = n - 1; i >= 0; i--)
		{
			if (s[i] == '(')CurLeft++;
			else CurRight++;
			if (CurLeft == CurRight)
			{
				re = max(re, 2 * CurRight);
			}
			else if (CurLeft > CurRight) //如果到当前位置时, 左括号数量更多, 就丢弃右边的部分, 从左边的下一个字符重新考虑
			{
				CurLeft = CurRight = 0;
			}
		}
		return re;

		//动态规划. 时间复杂度O(n), 空间复杂度O(n).
		/*
		int n = s.size();
		if (n <= 1)return 0;
		vector<int> dp(n, 0); //dp[i]表示: 以s[i]结尾的最长有效括号的长度
		for (int i = 1; i < n; i++) //从下标1处开始遍历, 是因为dp[0]肯定为0.
		{
			if (s[i] == '(')continue; //如果当前位置是左括号, 那么肯定不会有哪个有效括号子串以当前位置结尾, 所以当前位置的dp肯定是0
			//运行到这里, 说明当前位置是右括号
			if (s[i - 1] == '(') //如果前一个位置是左括号, 那么就是"???()"的形式
			{   //dp[i]至少是2, 在此基础上, 如果再前一位(dp[i-2])大于0(也就是说, 是"??)()"的形式, 而且i-2处的右括号可以跟前面的一部分形成有效括号), 那么还要加上dp[i-2](因为题目要求的是最长的连续有效括号)
				dp[i] = 2 + (i >= 2 && dp[i - 2] > 0 ? dp[i - 2] : 0);
			}
			else //如果前一个位置也是右括号, 那么就是"???))"的形式
			{   //首先要找到可能与当前位置配对的下标MatchedIndex, 如果这里正好是左括号, 那么就是"?(????))"的形式, 所以dp[i]至少就是dp[i-1]+2(加上的2就是s[MatchedIndex]与s[i]处配对的左右括号), 同样是因为要求连续性, 也要考虑dp[MatchedIndex-1]
				int MatchedIndex = i - dp[i - 1] - 1; //从dp[i-1]可以知道: 与i-1处配对的括号在第i-dp[i-1]处, 那么可能与第i处配对的括号只能在第i-dp[i-1]-1处.
				if (MatchedIndex >= 0 && s[MatchedIndex] == '(')
				{
					dp[i] = dp[i - 1] + 2 + (MatchedIndex >= 1 ? dp[MatchedIndex - 1] : 0);
				}
			}
		}
		return *max_element(dp.begin(), dp.end()); //返回dp数组中的最大值
		*/

		//栈模拟. 时间复杂度O(n), 空间复杂度O(n).
		/*
		int n = s.size(), re = 0;
		if (n <= 1)return 0;
		stack<int> stack; //栈里面存放的是下标位置. 始终保持栈底元素为: 离当前位置(i)最近的没有找到配对的右括号的位置
		stack.push(-1); //如果不加这一个, 假如s[0]为左括号的话, 如果下面直接把0放入栈中, 那么栈底存放的就不是"右括号的位置"了, 所以为了统一起见, 一开始放入-1
		for (int i = 0; i < n; i++)
		{
			if (s[i] == '(') //当前是左括号的话, 直接把下标入栈
			{
				stack.push(i);
			}
			else //当前是右括号
			{
				stack.pop(); //先把栈顶的下标出栈, 表示: 栈顶下标的元素试着与当前右括号配对
				if (stack.empty()) //如果栈顶出栈之后栈就空了, 表明出栈的那个下标对应的元素是之前的"未配对右括号", 而当前最新的"未配对右括号"应该就是当前的元素了, 所以就把当前位置入栈
				{
					stack.push(i);
				}
				else // 栈顶出栈之后栈里面还有元素, 说明"尝试配对"成功, 更新此时的长度.
				{
					re = max(re, i - stack.top());
				}
			}
		}
		return re;
		*/

	}
	//78.子集: {1,2}的子集: {{},{1},{2},{1,2}}
	void Do(vector<int>& nums, int CurPos, vector<int>& Cur, vector<vector<int>>& re) //CurPos表示当前的递归深度, Cur表示当前处理的子集
	{
		if (CurPos == nums.size()) //当前是递归最后一层
		{
			re.push_back(Cur);
			return;
		}
		Cur.push_back(nums[CurPos]); //考虑选择当前位置
		Do(nums, CurPos + 1, Cur, re);
		Cur.pop_back(); //考虑不选择当前位置
		Do(nums, CurPos + 1, Cur, re);
	}
	vector<vector<int>> subsets(vector<int>& nums)
	{
		//利用二进制位进行枚举, 使用位运算. 时间复杂度O(n*(2^n)), 空间复杂度O(1). 
		/*
		int n = nums.size();
		int ResultSize = 1 << n; //长度为n的数组, 子集大小一定为2^n
		vector<vector<int>> re(ResultSize); //先创建2^n个空数组
		//假设nums为{1,2,3}, CurMask当前为6, 二进制为110, 那么表示nums[0]填, nums[1]填, nums[2]不填, 所以当前(re[CurMask])对应的子集应该是{1,2}
		for (int CurMask = 0; CurMask < ResultSize; CurMask++) //从0到ResultSize-1, 遍历每一种掩膜可能性
		{
			for (int i = 0; i < n; i++) //nums从左到右依次判断nums[i]是否应该填入当前子集re[CurMask]
			{   //当且仅当CurMask对应的二进制从左到右的第i位为1时, 才把nums[i]填入子集
				int offset = n - i - 1;
				if (CurMask & (1 << offset)) //取出CurMask的二进制从左到右第i位的方法: CurMask & (1 << (n - i - 1)), 使用"按位与"运算
				{
					re[CurMask].push_back(nums[i]);
				}
			}
		}
		return re;
		*/

		//递归. 时间复杂度O(n*(2^n)), 空间复杂度O(n).
		//假设nums为{1,2,3}, 那么加入re的顺序为: {1,2,3}, {1,2}, {1,3}, {1}, {2,3}, {2}, {3}, {}
		vector<vector<int>> re;
		vector<int> Cur;
		Do(nums, 0, Cur, re);
		return re;

		//逐个枚举. 时间复杂度O(n*(2^n)), 空间复杂度O(1). 
		/*
		int n = nums.size();
		vector<vector<int>> re = { {} }; //刚开始时空数组
		for (int num : nums) //遍历nums, 把当前re中的每个子集(数组)的末尾都加上当前的数num
		{
			int CurSize = re.size(); //re中的当前子集数
			for (int i = 0; i < CurSize; i++) //遍历当前的所有子集
			{
				re.push_back(re[i]); //先把re[i]加入到re最后面
				re.back().push_back(num);
			}
		}
		return re;
		*/
	}
	//105.从前序与中序遍历序列构造二叉树
	TreeNode* Do(unordered_map<int, int>& FindPos, vector<int>& preorder, int pre1, int pre2, vector<int>& inorder, int in1, int in2)
	{
		if (pre1 > pre2)return nullptr;
		int n = preorder.size();
		TreeNode* re = new TreeNode(preorder[pre1]); //前序遍历preorder当前的第一个(pre1)一定是当前子树的根节点
		int in_pos = FindPos[preorder[pre1]]; //在中序遍历中, 找到根节点的位置in_pos,
		//此时, 中序遍历inorder中的[in1, in_pos-1]一定就是当前子树的左边部分, [in_pos+1,in2]一定就是当前子树的右边部分
		int LeftNum = in_pos - in1; //当前子树的左边部分的节点数, 
		//此时, 前序遍历preorder中的[pre1+1, pre1+1+(LeftNum-1)]一定就是当前子树的左边部分, [pre1+1+(LeftNum-1)+1,pre2]一定就是当前子树的右边部分
		re->left = Do(FindPos, preorder, pre1 + 1, pre1 + LeftNum, inorder, in1, in_pos - 1); //递归, 构造左子树
		re->right = Do(FindPos, preorder, pre1 + LeftNum + 1, pre2, inorder, in_pos + 1, in2); //递归, 构造右子树
		return re;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		//迭代+栈. 时间复杂度O(n), 空间复杂度O(n).
		int n = preorder.size();
		if (n == 0)return nullptr;
		stack<TreeNode*> s; //栈中的节点表示: 还没有考虑过【是否存在右孩子】的节点, 栈中节点的顺序为: 从根到叶子
		int InOrderIndex = 0; //中序遍历序列当前的位置
		TreeNode* re = new TreeNode(preorder[0]); //根节点
		s.push(re);
		for (int PreOrderIndex = 1; PreOrderIndex < n; PreOrderIndex++) //从前序遍历的第1位(除去了第0位的根节点)往后构建树
		{
			TreeNode* CurNode = new TreeNode(preorder[PreOrderIndex]); //当前节点
			if (!s.empty() && s.top()->val == inorder[InOrderIndex]) //如果当前inorder[InOrderIndex]与栈顶节点的值相同, 就说明【当前节点】一定是栈中某个节点的右孩子
			{
				TreeNode* LastPop = nullptr; //需要找到【当前节点】具体是栈中哪个节点的右孩子
				while (!s.empty() && s.top()->val == inorder[InOrderIndex]) //只要当前inorder[InOrderIndex]与栈顶节点的值相同, 那么就出栈, 并且InOrderIndex右移
				{
					LastPop = s.top();
					s.pop();
					InOrderIndex++;
				}
				//运行到这里, LastPop就是刚刚上一次出栈的节点, LastPop的右孩子就一定是【当前节点】
				LastPop->right = CurNode;
			}
			else //如果不相同, 那么就说明【当前节点】是上一个节点(s.top())的左孩子
			{
				s.top()->left = CurNode;
			}
			s.push(CurNode); //不管怎么样, 【当前节点】最后都要入栈, 因为【当前节点】还没考虑过【是否存在右孩子】
		}
		return re;

		//递归. 时间复杂度O(n), 空间复杂度O(n).
		/*
		int n = preorder.size();
		if (n == 0)return nullptr;
		if (n == 1)return new TreeNode(preorder[0]);
		unordered_map<int, int> FindPos; //FindPos[i]表示: 中序遍历inorder中, 数字i所在的位置(索引). 根据数来找位置
		for (int i = 0; i < inorder.size(); i++)
		{
			FindPos[inorder[i]] = i;
		}
		return Do(FindPos, preorder, 0, n - 1, inorder, 0, n - 1);
		*/
	}
	//151.反转字符串中的单词: " the   sky is  blue " → "blue is sky the"
	string reverseWords(string s)
	{
		//原地修改. 时间复杂度O(n), 空间复杂度O(1).
		reverse(s.begin(), s.end()); //首先把整个字符串反转
		int n = s.size(), CurIndex = 0; //s的[0, CurIndex-1]区间为当前完成修改的有效区间, CurIndex永远表示【下一个字母】应该放的位置
		for (int i = 0; i < n; i++)
		{
			if (s[i] == ' ')continue;
			//运行到这里, 说明s[i]是有效字符, 也就是说当前s[i]是一个【新单词的首字母】
			if (CurIndex != 0) //如果CurIndex不为0, 表示当前的s[i]并不是【第一个单词】的首字母, 也就是说当前需要【在前一个单词的尾字母后面开辟一个新的单词】, 所以要加一个空格
			{
				s[CurIndex++] = ' ';
			}
			s[CurIndex++] = s[i]; //s[i]为【当前单词】的首字母, 把它拷贝到CurIndex处, 然后CurIndex右移
			int WordLen = 1; //当前单词长度为1(当前唯一的一个字母就是s[i])
			while (i + WordLen < n && s[i + WordLen] != ' ') //只要s[i+WordLen]不为空格, 那么就说明s[i+WordLen]也是【当前单词】的字母, 把它拷贝到CurIndex处, 然后CurIndex右移
			{
				s[CurIndex++] = s[i + WordLen];
				WordLen++; //单词长度加一
			}
			//运行到这里, 说明s[i+WordLen]是空格, 单词原来位于s[i, i+WordLen-1]区间, 现在位于s[CurIndex-WordLen ,CurIndex-1]区间
			reverse(s.begin() + (CurIndex - WordLen), s.begin() + CurIndex); //把当前单词(s[CurIndex-WordLen ,CurIndex-1]区间)反转回来
			i += WordLen; //下一个单词的首字母起始查找位置
		}
		s.erase(s.begin() + CurIndex, s.end()); //s[0, CurIndex-1]区间为有效区间, 所以要删除s[CurIndex, :]区间
		return s;
	}
	//110.平衡二叉树
	int TreeHeight(TreeNode* root)
	{
		if (!root)return 0;
		return 1 + max(TreeHeight(root->left), TreeHeight(root->right));
	}
	int TreeHeight_2(TreeNode* root)
	{   //把【求当前子树高度】和【判断当前子树是否是平衡二叉树】两个功能综合起来. 如果当前子树不是平衡二叉树则返回-1, 如果是平衡二叉树则返回大于等于0的值
		if (!root)return 0;
		int LeftHeight = TreeHeight_2(root->left);
		if (LeftHeight == -1)return -1; //左子树不是平衡二叉树, 那么不用判断右子树了, 直接返回-1
		int RightHeight = TreeHeight_2(root->right);
		if (RightHeight == -1)return -1;
		if (abs(LeftHeight - RightHeight) > 1)return -1;
		return 1 + max(LeftHeight, RightHeight);
	}
	bool isBalanced(TreeNode* root)
	{
		//自底向上递归. 时间复杂度O(n), 空间复杂度O(n)
		//自底向上递归就是及时止损, 自顶向下递归就是不管三七二十一先把所有的高度算一遍
		return TreeHeight_2(root) != -1;

		//自顶向下递归. 平均(高度等于logn)时间复杂度O(nlogn), 最坏(链式:高度等于n)时间复杂度O(n^2). 空间复杂度O(n).
		/*
		if (!root)return true;
		if (!root->left && !root->right)return true;
		//树为平衡二叉树的充要条件: 左子树高度与右子树高度差的绝对值不超过1, 而且左右子树也都是平衡二叉树
		return abs(TreeHeight(root->left) - TreeHeight(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
		*/
	}




};




int main(int argc, char* argv[])
{
	vector<int> preorder({ 3,9,20,15,7 });
	vector<int> inorder({ 9,3,15,20,7 });

	Solution solution;
	auto result = solution.buildTree(preorder, inorder);

	return 0;
}