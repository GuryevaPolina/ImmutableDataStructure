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

template <class Elem>
class CGSet {
    class Node {
    public:
        Elem data;
        Node *next;
    };
    Node *head;
    Locker *locker;
    
public:
    CGSet() {
        head = NULL;
        locker = new Locker();
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
        delete locker;
    }
    
    bool add(const Elem &item) {
        locker->lock();
        Node *iter = head;
        while (iter != NULL) {
            if (iter->data == item) {
                locker->unlock();
                return false;
            }
            iter = iter->next;
        }
        
        Node *oldHead = head;
        head = new Node();
        head->data = item;
        head->next = oldHead;
        locker->unlock();
        return true;
    }
    
    bool remove(const Elem &item) {
        locker->lock();
        if (head == NULL) {
            locker->unlock();
            return false;
        }
        
        Node *iter = head, *prev = NULL;
        while(iter != NULL && iter->data != item) {
            prev = iter;
            iter = iter->next;
        }
        if (iter == NULL ) {
            locker->unlock();
            return false;
        }
        if (prev == NULL){
            Node *tmp = head;
            head = head->next;
            delete tmp;
            locker->unlock();
            return true;
        }
        prev->next = iter->next;
        delete iter;
        locker->unlock();
        return true;
    }
    
    
    bool contains(const Elem &item) {
        locker->lock();
        Node *iter  = head;
        while (iter != NULL) {
            if (iter->data == item) {
                locker->unlock();
                return true;
            }
            iter = iter->next;
        }
        locker->unlock();
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


#endif /* CGSet_h */
