#pragma once
#include <string>
#include <cstring>
//#include "vector.h"
#include <vector>
#include "Queue.h"
using namespace std;

template <typename T> class Trie{
    private:
		struct Node {
			T* obj;
			int next[26];
			bool isLeaf;

			Node() {
				memset(next, -1, sizeof(next));
				isLeaf = 0;
			}
		};

		vector<Node> Tree;
    public:
        Trie();
        void insert(const string& s, T* obj); //Insert a string into Trie Tree
        vector<T*> query(const string& s); //Return list of object
};

/*===========Definition of Trie Class==============*/

template <typename T> Trie<T>::Trie(){
    Tree.push_back(Node());
}

template <typename T> void Trie<T>::insert(const string& s, T* obj){
    int cur = 0;
    for(int i = 0 ; i < s.size() ; ++i) {
		if (s[i] == ' ') continue;
        int j = s[i] - 'A';
        if (Tree[cur].next[j] == -1){
            Tree.push_back(Node());
            Tree[cur].next[j] = Tree.size() - 1;
        }
        cur = Tree[cur].next[j];
    }
    Tree[cur].isLeaf = 1;
    Tree[cur].obj = obj;
}

template <typename T> vector<T*> Trie<T>::query(const string &s){
    vector<T*> ans;
    int cur = 0;
    for(int i = 0 ; i < s.size() ; ++i){
		if (s[i] == ' ') continue;
        int j = s[i] - 'A';
        if (Tree[cur].next[j] == -1) return ans;
        cur = Tree[cur].next[j];
    }

    Queue q;
    q.push_back(cur);
    while(q.size()){
        int u = q.front(); q.pop_front();
        if (Tree[u].isLeaf) ans.push_back(Tree[u].obj);

        for(int i = 0 ; i < 26 ; ++i)
            if (Tree[u].next[i] != -1)
                q.push_back(Tree[u].next[i]);
    }
    return ans;
}

