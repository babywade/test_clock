// test_clock.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <array>
#include <algorithm>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

//时间单位1ms

const unsigned int TESTSIZE = 200000;

bool FindIf(int val) {
	return val > 10000;
}

bool FindIfmap(pair<int, int> valpair) {
	return valpair.second > 10000;
}

// array<int, TESTSIZE> ci;
// 在这里声明时TESTSIZE大小可以到500000而不会溢出，array是没有溢出报错的；

void TestArray() {
	array<int, TESTSIZE> ci; //array 声明在全局变量时会比局部变量大小可以相对更大
	cout << "Array: " << endl;
	clock_t tbegin = clock();
	for (int i = 0; i < TESTSIZE; i++) {
		ci[i] = rand();
	}
	clock_t tend = clock();
	cout << "写入的时间： " << tend - tbegin << endl;

	tbegin = clock();
	sort(ci.begin(), ci.end());
	tend = clock();
	cout << "排序的时间： " << tend - tbegin << endl;

	tbegin = clock();
	count_if(ci.begin(), ci.end(), FindIf);
	tend = clock();
	cout << "查找的时间： " << tend - tbegin << endl;
}

void TestVector() {
	cout << "vector: " << endl;
	vector<int> vi;
	clock_t tbegin = clock();
	for (int i = 0; i < TESTSIZE; i++) {
		vi.push_back(rand());
	}
	clock_t tend = clock();
	cout << "写入的时间： " << tend - tbegin << endl;

	tbegin = clock();
	sort(vi.begin(), vi.end());
	tend = clock();
	cout << "排序的时间： " << tend - tbegin << endl;

	tbegin = clock();
	count_if(vi.begin(), vi.end(), FindIf);
	tend = clock();
	cout << "查找的时间： " << tend - tbegin << endl;
}

//测试结果，vector扩充时需要做内存申请，所以写入时间较长
//Array:
//写入的时间： 19
//排序的时间： 378
//查找的时间： 5
//
//vector :
//	写入的时间： 155
//	排序的时间： 341
//	查找的时间： 5

void TestList() {
	cout << "list: " << endl;
	list<int> li;
	clock_t tbegin = clock();
	for (int i = 0; i < TESTSIZE; i++) {
		li.push_back(rand());
	}
	clock_t tend = clock();
	cout << "写入的时间： " << tend - tbegin << endl;

	// STL中的List不支持排序，排序需要使用双向迭代器
	//tbegin = clock();
	//sort(li.begin(), li.end());
	//tend = clock();
	//cout << "排序的时间： " << tend - tbegin << endl;

	tbegin = clock();
	count_if(li.begin(), li.end(), FindIf);
	tend = clock();
	cout << "查找的时间： " << tend - tbegin << endl;
}

//list写入和访问都很慢，但是从中间插入会快
//list:
//写入的时间： 213
//查找的时间： 28

void TestForwardList() {
	cout << "ForwardList: " << endl;
	forward_list<int> fli;
	clock_t tbegin = clock();
	for (int i = 0; i < TESTSIZE; i++) {
		fli.push_front(rand()); //前向链表，只能从前面插入
	}
	clock_t tend = clock();
	cout << "写入的时间： " << tend - tbegin << endl;

	// STL中的List不支持排序，排序需要使用双向迭代器
	//tbegin = clock();
	//sort(li.begin(), li.end());
	//tend = clock();
	//cout << "排序的时间： " << tend - tbegin << endl;

	tbegin = clock();
	count_if(fli.begin(), fli.end(), FindIf);
	tend = clock();
	cout << "查找的时间： " << tend - tbegin << endl;
}

//因为要后移，写入效率更低
//ForwardList:
//写入的时间： 275
//查找的时间： 28

void TestDeque() {
	cout << "deque: " << endl;
	deque<int> di;
	clock_t tbegin = clock();
	for (int i = 0; i < TESTSIZE; i++) {
		di.push_back(rand());
	}
	clock_t tend = clock();
	cout << "写入的时间： " << tend - tbegin << endl;

	tbegin = clock();
	sort(di.begin(), di.end());
	tend = clock();
	cout << "排序的时间： " << tend - tbegin << endl;

	tbegin = clock();
	count_if(di.begin(), di.end(), FindIf);
	tend = clock();
	cout << "查找的时间： " << tend - tbegin << endl;
}

//写入排序查找都慢
//deque:
//写入的时间： 195
//排序的时间： 1690
//查找的时间： 31

void TestSet()//关联容器
{
	std::cout << "set:" << std::endl;
	std::set<int> fli;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		fli.insert(rand());
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(fli.begin(), fli.end(), FindIf);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}

//插入很慢，查找遍历很快，set里面是一个二叉树
//set:
//写入的时间：878
//查找时间：6

void TestMultiSet()//与set差别不大，但是map和multimap的差别非常大。
{
	std::cout << "multiset:" << std::endl;
	std::multiset<int> fli;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		fli.insert(rand());
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(fli.begin(), fli.end(), FindIf);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}

//multiset写入查找比set都会慢一些

void Testmap()//与set差别不大，但是map和multimap的差别非常大。
{
	std::cout << "map:" << std::endl;
	std::map<int, int> mp;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		mp.insert(std::pair<int, int>(i, rand()));//这个插入会比较慢，因为每次都需要构建一个对象
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(mp.begin(), mp.end(), FindIfmap);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}

//map写入时更慢，因为涉及到pair的构造

void Testmultimap()//与set差别不大，但是map和multimap的差别非常大。
{
	std::cout << "multimap:" << std::endl;
	std::multimap<int, int> mp;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		mp.insert(std::pair<int, int>(i, rand()));//这个插入会比较慢，因为每次都需要构建一个对象
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(mp.begin(), mp.end(), FindIfmap);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}

void Testunorderedset()//关联容器
{
	std::cout << "unordered_set:" << std::endl;
	std::unordered_set<int> fli;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		fli.insert(rand());
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(fli.begin(), fli.end(), FindIf);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}

void TestunorderedMultiset()//关联容器
{
	std::cout << "unordered_multiset:" << std::endl;
	std::unordered_multiset<int> fli;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		fli.insert(rand());
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(fli.begin(), fli.end(), FindIf);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}

void TestUnorderedmap()//与set差别不大，但是map和multimap的差别非常大。
{
	std::cout << "underedmap:" << std::endl;
	std::unordered_map<int, int> mp;
	std::clock_t tbegin = std::clock();//单位100ns
	for (int i = 0; i < TESTSIZE; ++i)
	{
		mp.insert(std::pair<int, int>(i, rand()));//这个插入会比较慢，因为每次都需要构建一个对象
	}
	std::clock_t tend = std::clock();//单位100ns
	std::cout << "写入的时间：" << tend - tbegin << std::endl;//写入数据

	tbegin = std::clock();
	std::count_if(mp.begin(), mp.end(), FindIfmap);//这是找到第一个就退出。
	tend = std::clock();
	std::cout << "查找时间：" << tend - tbegin << std::endl;//查找
}



int main()
{
	TestArray();
	cout << endl;
	TestVector();
	cout << endl;
	TestList();
	cout << endl;
	TestForwardList();
	cout << endl;
	TestDeque();
	cout << endl;
	TestSet();
	cout << endl;
	TestMultiSet();
	cout << endl;
	Testmap();
	cout << endl;
	Testmultimap();
	cout << endl;
	Testunorderedset();
	cout << endl;
	TestunorderedMultiset();
	cout << endl;
	TestUnorderedmap();
	cout << endl;
    return 0;
}

