#pragma once

#include <stdio.h>

class Node{
    public:
        int value;
        Node* before;
        Node* next;
};

class Queue: public Node{
    private:
        Node *begin;
        Node *end;
        int capacity;

    public:
        Queue();
        ~Queue();
        int front();
        int back();

        void push_back(const int& x);
        void pop_front();

        int size();
};

/* ==================== Definition of method's class==================*/

Queue::Queue(){
    begin = NULL;
    end = NULL;
    capacity = 0;
}

Queue::~Queue(){
    while(begin != NULL){
        Node *tmp = begin -> next;
        delete begin;
        begin = tmp;
    }
}

int Queue::front() {return begin -> value;}
int Queue::back() {return end -> value;}

void Queue::push_back(const int& x){
    ++capacity;
    Node *p = new Node;
    p -> value = x;
    p -> next = NULL;
    if (begin == NULL){
        begin = p;
        end = p;
        p -> before = NULL;
    } else {
        end -> next = p;
        p -> before = end;
        end = p;
    }
}

void Queue::pop_front(){
    --capacity;
    Node *p = begin;
    begin = begin -> next;
    delete p;
}

int Queue::size(){
    return capacity;
}
