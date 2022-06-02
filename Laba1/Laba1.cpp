#include"RBtree.h"
#include<iostream>

using namespace std;
int main()
{
	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	vector<char> symbols{ 'q','w','e','r','t','y','u','i','o','p'};
	RBtree<int, char> tree;
	for (int i = 0; i < 10; i++)
		tree.insert(nums[i], symbols[i]);
	tree.print();
	cout << endl;

	List<int> listInt = tree.get_keys();
	cout << "List keys: ";
	listInt.print();
	cout << endl;

	List<char> listChar = tree.get_values();
	cout << "List values: ";
	listChar.print();
	cout << endl;

	Node<int, char>* node = tree.find(10);
	cout << "node with key = " << node->key << " value = " << node->value << endl;
	cout << endl;
	
	tree.remove(10);
	cout << "remove node with key = 10 " << endl;
	node = tree.find(10);
	cout << "node equal nullptr = " << (node == nullptr) << endl;
	cout << endl;

	cout << "delete tree" << endl;
	tree.clear();
	tree.print();

	return 0;
}