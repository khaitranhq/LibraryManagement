#pragma once
#include <string>
#include <cstring>
#include "Vector.h"
#include "Queue.h"
using namespace std;

template <class T> class Trie{
    private:
        class Node{
            private:
                T obj;
                int next[26];
                bool isLeaf;
            public:
                Node(){
                    memset(next, -1, sizeof(next));
                    isLeaf = 0;
                }
        };

        Vector<Node> Tree;
    public:
        Trie();
        void insert(const string& s, const T& obj); //Insert a string into Trie Tree
        Vector<T> query(const string& s); //Return list of object
};

/*===========Definition of Trie Class==============*/

template <class T> Trie<T>::Trie(){
    Tree.push_back(Node());
}

template <class T> void Trie<T>::insert(const string& s, const T& obj){
    int cur = 0;
    for(int i = 0 ; i < s.size() ; ++i) {
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

template <class T> Vector<T> Trie<T>::query(const string &s){
    Vector<T> ans;
    int cur = 0;
    for(int i = 0 ; i < s.size() ; ++i){
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

