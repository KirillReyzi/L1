#pragma once
#include<iostream>

using namespace std;
template<typename  T>
struct ListNode {
	T val;
	ListNode<T>* next;
	ListNode(T _val) : val(_val), next(nullptr) {}
};

template<typename  T>
class List {
public:
	List() : head(nullptr), tail(nullptr) {};

	bool is_empty() {
		return head == nullptr;
	};

	void push_back(T _val) {
		ListNode<T>* p = new ListNode<T>(_val);
		if (is_empty()) {
			head = p;
			tail = p;
			return;
		}
		tail->next = p;
		tail = p;
	};

	void print() {
		if (is_empty()) return;
		ListNode<T>* p = head;
		while (p) {
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}

	ListNode<T>* take_head() {
		return head;
	}

private:
	ListNode<T>* head;
	ListNode<T>* tail;
};