#pragma once
#include <iostream>
#include <vector>
#include "List.h"

using namespace std;

enum RBColor { Black, Red };

template<typename  T, typename V>
struct Node {
	T key;
	V value;
	RBColor color;
	Node<T, V>* left = nullptr;
	Node<T, V>* right = nullptr;
	Node<T, V>* parent = nullptr;

	Node(T key, V value, RBColor color, Node* left, Node* right, Node* parent) :
		key(key), value(value), color(color), left(left), right(right), parent(parent) {};
};

template <typename T, typename V>
class RBtree {
public:

	RBtree() : root(nullptr) {
		root = nullptr;
	};
	~RBtree() {
		clear();
	};

	void insert(T key, V value) {
		Node<T, V>* node = new Node<T, V>(key, value, Red, nullptr, nullptr, nullptr);
		insert(root, node);
	};
	void remove(T key) {
		Node<T, V>* deletenode = find(root, key);
		if (deletenode != nullptr)
			remove(root, deletenode);
	};
	Node<T, V>* find(T key) {
		return find(root, key);
	};
	void clear() {
		destory(root);
	};
	List<T> get_keys() {
		List<T>* list = new List<T>();
		if (root == nullptr)
			cout << "empty RBtree\n";
		else {
			return *get_keys(root, list);
		}
		return *list;
	};
	List<V> get_values() {
		List<V>* list = new List<V>();
		if (root == nullptr)
			cout << "empty RBtree\n";
		else {
			return *get_values(root, list);
		}
		return *list;
	};
	void print() {
		if (root == nullptr)
			cout << "empty RBtree\n";
		else
			print(root);
	};

private:
	Node <T, V>* root;

	void insert(Node<T, V>*& root, Node<T, V>* node) {
		Node<T, V>* x = root;
		Node<T, V>* y = nullptr;
		while (x != nullptr)
		{
			y = x;
			if (node->key > x->key)
				x = x->right;
			else
				x = x->left;
		}
		node->parent = y;
		if (y != nullptr)
		{
			if (node->key > y->key)
				y->right = node;
			else
				y->left = node;
		}
		else
			root = node;
		node->color = Red;
		InsertFixUp(root, node);
	};
	void InsertFixUp(Node<T, V>*& root, Node<T, V>* node) {
		Node<T, V>* parent;
		parent = node->parent;
		while (node != RBtree::root && parent->color == Red)
		{
			Node<T, V>* gparent = parent->parent;
			if (gparent->left == parent)
			{
				Node<T, V>* uncle = gparent->right;
				if (uncle != nullptr && uncle->color == Red)
				{
					parent->color = Black;
					uncle->color = Black;
					gparent->color = Red;
					node = gparent;
					parent = node->parent;
				}
				else
				{
					if (parent->right == node)
					{
						leftRotate(root, parent);
						swap(node, parent);
					}
					rightRotate(root, gparent);
					gparent->color = Red;
					parent->color = Black;
					break;
				}
			}
			else
			{
				Node<T, V>* uncle = gparent->left;
				if (uncle != nullptr && uncle->color == Red)
				{
					gparent->color = Red;
					parent->color = Black;
					uncle->color = Black;

					node = gparent;
					parent = node->parent;
				}
				else
				{
					if (parent->left == node)
					{
						rightRotate(root, parent);
						swap(parent, node);
					}
					leftRotate(root, gparent);
					parent->color = Black;
					gparent->color = Red;
					break;
				}
			}
		}
		root->color = Black;
	};

	void leftRotate(Node<T, V>*& root, Node<T, V>* x) {
		Node<T, V>* y = x->right;
		x->right = y->left;
		if (y->left != nullptr)
			y->left->parent = x;

		y->parent = x->parent;
		if (x->parent == nullptr)
			root = y;
		else {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	};
	void rightRotate(Node<T, V>*& root, Node<T, V>* y) {
		Node<T, V>* x = y->left;
		y->left = x->right;
		if (x->right != nullptr)
			x->right->parent = y;

		x->parent = y->parent;
		if (y->parent == nullptr)
			root = x;
		else {
			if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	};

	void remove(Node<T, V>*& root, Node<T, V>* node) {
		Node<T, V>* child, * parent;
		RBColor color;

		if (node->left != NULL && node->right != NULL)
		{
			Node<T, V>* replace = node;

			replace = node->right;
			while (replace->left != NULL)
			{
				replace = replace->left;
			}

			if (node->parent != NULL)
			{
				if (node->parent->left == node)
					node->parent->left = replace;
				else
					node->parent->right = replace;
			}

			else
				root = replace;

			child = replace->right;
			parent = replace->parent;
			color = replace->color;

			if (parent == node)
				parent = replace;
			else
			{
				if (child != NULL)
					child->parent = parent;
				parent->left = child;

				replace->right = node->right;
				node->right->parent = replace;
			}
			replace->parent = node->parent;
			replace->color = node->color;
			replace->left = node->left;
			node->left->parent = replace;
			if (color == Black)
				removeFixUp(root, child, parent);

			delete node;
			return;
		}

		if (node->left != NULL)
			child = node->left;
		else
			child = node->right;

		parent = node->parent;
		color = node->color;
		if (child)
		{
			child->parent = parent;
		}

		if (parent)
		{
			if (node == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			RBtree::root = child;

		if (color == Black)
		{
			removeFixUp(root, child, parent);
		}
		delete node;
	};
	void removeFixUp(Node<T, V>*& root, Node<T, V>* node, Node<T, V>* parent) {
		Node<T, V>* othernode;
		while ((!node) || node->color == Black && node != RBtree::root)
		{
			if (parent->left == node)
			{
				othernode = parent->right;
				if (othernode->color == Red)
				{
					othernode->color = Black;
					parent->color = Red;
					leftRotate(root, parent);
					othernode = parent->right;
				}
				else
				{
					if (!(othernode->right) || othernode->right->color == Black)
					{
						othernode->left->color = Black;
						othernode->color = Red;
						rightRotate(root, othernode);
						othernode = parent->right;
					}
					othernode->color = parent->color;
					parent->color = Black;
					othernode->right->color = Black;
					leftRotate(root, parent);
					node = root;
					break;
				}
			}
			else
			{
				othernode = parent->left;
				if (othernode->color == Red)
				{
					othernode->color = Black;
					parent->color = Red;
					rightRotate(root, parent);
					othernode = parent->left;
				}
				if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
				{
					othernode->color = Red;
					node = parent;
					parent = node->parent;
				}
				else
				{
					if (!(othernode->left) || othernode->left->color == Black)
					{
						othernode->right->color = Black;
						othernode->color = Red;
						leftRotate(root, othernode);
						othernode = parent->left;
					}
					othernode->color = parent->color;
					parent->color = Black;
					othernode->left->color = Black;
					rightRotate(root, parent);
					node = root;
					break;
				}
			}
		}
		if (node)
			node->color = Black;
	};
	void destory(Node<T, V>*& node) {
		if (node == nullptr)
			return;
		destory(node->left);
		destory(node->right);
		delete node;
		node = nullptr;
	};

	Node<T, V>* find(Node<T, V>* node, T key) const {
		if (node == nullptr || node->key == key)
			return node;
		else
			if (key > node->key)
				return find(node->right, key);
			else
				return find(node->left, key);
	};
	void print(Node<T, V>* node)const {
		if (node == nullptr)
			return;
		if (node->parent == nullptr)
			cout << node->key << "(" << node->color << ") is root value = " << node->value << endl;
		else if (node->parent->left == node)
		{
			cout << node->key << "(" << node->color << ") is " << node->parent->key << " " << "left child value = " << node->value << endl;
		}
		else
		{
			cout << node->key << "(" << node->color << ") is " << node->parent->key << " " << "right child value = " << node->value << endl;
		}
		print(node->left);
		print(node->right);
	};

	List<T>* get_keys(Node<T, V>* node, List<T>* list) {
		if (node == nullptr)
			return list;
		list->push_back(node->key);
		get_keys(node->left, list);
		get_keys(node->right, list);
		return list;
	};
	List<V>* get_values(Node<T, V>* node, List<V>* list) {
		if (node == nullptr)
			return list;
		list->push_back(node->value);
		get_values(node->left, list);
		get_values(node->right, list);
		return list;
	};
};