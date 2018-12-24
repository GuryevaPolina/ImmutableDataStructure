//
//  CGSet.h
//  lab3_guryeva
//
//  Created by Polina Guryeva on 19/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#ifndef CGSet_h
#define CGSet_h

#include <stdio.h>
#include "Locker.h"
using namespace std;

template <class Elem>
class CGSet {
    class Node {
    public:
        Elem data;
        int key;
        Node *next;
        
        Node(const Elem &item) {
            data = item;
            key = (int)hash<Elem>()(item);
            next = NULL;
        }
        
        Node(int _key, void *param){
            key = _key;
        }
        
    };
    Node *head;
    pthread_mutex_t mutex;
    
public:
    CGSet() {
        head = new Node(INT_MIN, NULL);
        head->next = new Node(INT_MAX, NULL);
        head->next->next = NULL;
        mutex = PTHREAD_MUTEX_INITIALIZER;
    }
    
    CGSet(const CGSet<Elem> *anotherSet) {
        head = anotherSet->head;
    }
    
    ~CGSet() {
        Node *iter = head;
        while (iter != NULL) {
            Node * tmp = iter;
            iter = iter->next;
            delete tmp;
        }
    }
    
    bool add(const Elem &item) {
        Node *pred, *curr;
        int key = (int)hash<Elem>()(item);
        lock();
        
        pred = head;
        curr = pred->next;
        while(curr->key < key){
            pred = curr;
            curr = curr->next;
        }
        if(curr->key == key){
            unlock();
            return false;
        } else {
            Node *node = new Node(item);
            node->next = curr;
            pred->next = node;
            unlock();
            return true;
        }
    }
    
    bool remove(const Elem &item) {
        Node *pred, *curr;
        int key = (int)hash<Elem>()(item);
        lock();
        
        pred = head;
        curr = pred->next;
        while (curr->key < key) {
            pred = curr;
            curr = curr->next;
        }
        if (key == curr->key)
        {
            pred->next = curr->next;
            delete curr;
            unlock();
            return true;
        } else {
            unlock();
            return false;
        }
    }
    
    
    bool contains(const Elem &item) {
        Node *curr;
        int key = (int)hash<Elem>()(item);
        lock();
        
        curr = head;
        while(curr->key < key){
            curr = curr->next;
        }
        unlock();
        return (curr->key == key);
    }
    
    int count() {
        int cnt = 0;
        Node *iter = head;
        while (iter != NULL) {
            cnt += 1;
            iter = iter->next;
        }
        return cnt;
    }
    
    void lock() {
        pthread_mutex_lock(&mutex);
    }
    
    void unlock() {
        pthread_mutex_unlock(&mutex);
    }
    
};


#endif /* CGSet_h */
