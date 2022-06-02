#include "pch.h"
#include "RBtree.h"
#include <iostream>
#include <windows.h>

void TreeOut(RBtree<int, int>* test, HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "[      Keys] ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	List<int> keys = test->get_keys();
	keys.print();

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "[     Value] ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	List<int> value = test->get_values();
	value.print();
}

void PrintTabs(HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "[          ] ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);
}

TEST(InputTest, insert) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	RBtree<int, int> tree;
	for (auto num : nums)
		tree.insert(num, num);

	TreeOut(&tree, hStdOut);

	List<int> value = tree.get_values();
	ListNode<int>* v = value.take_head();
	vector<int> n{ 60,30,10,20,40,50,80,70,90,100 };
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(v->val, n[i]);
		v = v->next;
	}

	tree.insert(0, 0);
	value = tree.get_values();
	v = value.take_head();
	vector<int> m{ 60,30,10,0,20,40,50,80,70,90,100 };
	for (int i = 0; i < 11; i++) {
		ASSERT_EQ(v->val, m[i]);
		v = v->next;
	}
}

TEST(DeleteTest, remove) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	RBtree<int, int> tree;
	for (auto num : nums)
		tree.insert(num, num);

	TreeOut(&tree, hStdOut);

	tree.remove(10);

	List<int> value = tree.get_values();
	ListNode<int>* v = value.take_head();
	vector<int> n{ 60,30,20,40,50,80,70,90,100 };
	for (int i = 0; i < 9; i++) {
		ASSERT_EQ(v->val, n[i]);
		v = v->next;
	}
}

TEST(DeleteTest, clear) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	RBtree<int, int> tree;
	for (auto num : nums)
		tree.insert(num, num);

	TreeOut(&tree, hStdOut);

	tree.clear();
	PrintTabs(hStdOut);
	List<int> value = tree.get_values();
	ListNode<int>* v = value.take_head();
	ASSERT_EQ(v, nullptr);
}

TEST(OutputTest, get_keys) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	RBtree<int, int> tree;
	for (auto num : nums)
		tree.insert(num, num);

	TreeOut(&tree, hStdOut);

	List<int> key = tree.get_keys();
	ListNode<int>* k = key.take_head();
	vector<int> n{ 60,30,10,20,40,50,80,70,90,100 };
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(k->val, n[i]);
		k = k->next;
	}
}

TEST(OutputTest, get_values) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	RBtree<int, int> tree;
	for (auto num : nums)
		tree.insert(num, num);

	TreeOut(&tree, hStdOut);

	List<int> value = tree.get_values();
	ListNode<int>* v = value.take_head();
	vector<int> n{ 60,30,10,20,40,50,80,70,90,100 };
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(v->val, n[i]);
		v = v->next;
	}
}

TEST(SearchTest, find) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	RBtree<int, int> tree;
	for (auto num : nums)
		tree.insert(num, num);

	TreeOut(&tree, hStdOut);

	for (int i = 10; i <= 100; i += 10) {
		ASSERT_EQ(tree.find(i)->value, i);
	}
}