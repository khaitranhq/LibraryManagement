#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "vector.h"
//#include <vector>
#include "Queue.h"
using namespace std;

template <typename T> class TrieNumber {
private:
	struct Node {
		T* obj;
		int next[10];
		bool isLeaf;

		Node() {
			memset(next, -1, sizeof(next));
			isLeaf = 0;
		}
	};

	vector<Node> Tree;
public:
	TrieNumber();
	void insert(const string& s, T* obj); //Insert a string into TrieNumber Tree
	T* query(const string& s); //Return list of object
	void erase(const string& s);
};

/*===========Definition of TrieNumber Class==============*/

template <typename T> TrieNumber<T>::TrieNumber() {
	Tree.push_back(Node());
}

template <typename T> void TrieNumber<T>::insert(const string& s, T* obj) {
	int cur = 0;
	for (int i = 0; i < 9; ++i) {
		if (s[i] == ' ') continue;
		int j = s[i] - '0';
		if (Tree[cur].next[j] == -1) {
			Tree.push_back(Node());
			Tree[cur].next[j] = Tree.size() - 1;
		}
		cur = Tree[cur].next[j];
	}
	Tree[cur].isLeaf = 1;
	Tree[cur].obj = obj;
}

template <typename T> T* TrieNumber<T>::query(const string& s) {
	int cur = 0;
	for (int i = 0; i < 9; ++i) {
		if (s[i] == ' ') continue;
		int j = s[i] - '0';
		if (Tree[cur].next[j] == -1) return NULL;
		cur = Tree[cur].next[j];
	}
	return Tree[cur].obj;
}

template <typename T> void TrieNumber<T>::erase(const string& s) {
	int cur = 0;
	vector<int> stack;
	for (int i = 0; i < 9; ++i) {
		int j = s[i] - '0';
		stack.push_back(Tree[cur].next[j]);
		cur = stack.back();
	}

	for (int i = stack.size() - 1; i >= 0; --i) {
		bool isDelete = 1;
		int cur = stack[i];
		int digit = s[i] - '0';
		for (int j = 0; j < 10; ++j)
			if (Tree[cur].next[j] != -1) isDelete &= 0;
		if (isDelete)
			Tree.erase(cur);
	}
}