//
//  OSSet.h
//  lab3_guryeva
//
//  Created by Polina Guryeva on 21/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#ifndef OSSet_h
#define OSSet_h

#include "Locker.h"
#include <stdio.h>
using namespace std;

template <class Elem>
class OSSet {
    class Node {
    public:
        Elem data;
        Node *next;
        int key;
        pthread_mutex_t mutex;
        
        Node(const Elem &item) {
            data = item;
            key = (int)hash<Elem>()(item);
            next = NULL;
            mutex = PTHREAD_MUTEX_INITIALIZER;
        }
        
        Node(int _key, void *param) {
            key = _key;
        }
        
        void lock() {
            pthread_mutex_lock(&mutex);
        }
        
        void unlock() {
            pthread_mutex_unlock(&mutex);
        }
    };
    Node *head = NULL;
    
public:
    OSSet() {
        head = new Node(INT_MIN, NULL);
        head->next = new Node(INT_MAX, NULL);
        head->next->next = NULL;
    }
    
    OSSet(const CGSet<Elem> *anotherSet) {
        head = anotherSet->head;
    }
    
    ~OSSet() {
        Node *iter = head;
        while (iter != NULL) {
            Node * tmp = iter;
            iter = iter->next;
            delete tmp;
        }
    }
    
    bool add(const Elem &item) {
        int key = (int)hash<Elem>()(item);
        while (true) {
            Node *pred = head;
            Node *curr = pred->next;
            while (curr->key <= key) {
                pred = curr;
                curr = curr->next;
            }
            pred->lock();
            curr->lock();
            if (validate(pred, curr)){
                if (curr->key == key) {
                    pred->unlock();
                    curr->unlock();
                    return false;
                } else {
                    Node *node = new Node(item);
                    node->next = curr;
                    pred->next = node;
                    pred->unlock();
                    curr->unlock();
                    return true;
                }
            }
        }
    }
    
    bool remove(const Elem &item) {
        int key = (int)hash<Elem>()(item);
        while (true) {
            Node* pred = head;
            Node* curr = pred->next;
            while (curr->key < key) {
                pred = curr;
                curr = curr->next;
            }
            pred->lock();
            curr->lock();
            if (validate(pred, curr)){
                if (curr->key == key) {
                    pred->next = curr->next;
                    delete curr;
                    pred->unlock();
                    curr->unlock();
                    return true;
                } else {
                    pred->unlock();
                    curr->unlock();
                    return false;
                }
            }
        }
    }
    
    
    bool contains(const Elem &item) {
        int key = (int)hash<Elem>()(item);
        while (true) {
            Node *pred = head;
            Node *curr = pred->next;
            while (curr->key < key) {
                pred = curr;
                curr = curr->next;
            }
            pred->lock();
            curr->lock();
            if (validate(pred, curr)) {
                bool res = (curr->key == key);
                pred->unlock();
                curr->unlock();
                return res;
            }
        }
    }
    
    bool validate(Node *pred, Node *curr) {
        Node *node = head;
        while (node->key <= pred->key) {
            if (node == pred){
                return (pred->next == curr);
            }
            node = node->next;
        }
        return false;
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
    
};


#endif /* OSSet_h */
