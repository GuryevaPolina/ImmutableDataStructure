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

template <class Elem>
class OSSet {
    class Node {
    public:
        Elem data;
        Node *next;
        Locker * locker;
        
        Node() {
            locker = new Locker();
        }
        
        ~Node() {
            delete locker;
        }
    };
    Node *head = NULL;
    
public:
    OSSet() {
        head = NULL;
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
        Node *iter = head;
        while (iter != NULL) {
            if (iter->data == item) {
                return false;
            }
            iter = iter->next;
        }
        
        Node *oldHead = head;
        if(oldHead != NULL) {
            oldHead->locker->lock();
        }
        head = new Node();
        head->locker->lock();
        
        head->data = item;
        head->next = oldHead;
        
        head->locker->unlock();
        if (oldHead != NULL) {
            oldHead->locker->unlock();
        }
        return true;
    }
    
    bool remove(const Elem &item) {
        if (head == NULL) {
            return false;
        }
        Node *iter = head, *prev = NULL;
        while(iter != NULL && iter->data != item) {
            prev = iter;
            iter = iter->next;
        }
        if (iter == NULL ) {
            return false;
        }
        if (prev == NULL){
            Node *tmp = head;
            Node *head_next = head->next;
            
            tmp->locker->lock();
            if (head_next != NULL) {
                head_next->locker->lock();
            }
            
            head = head_next;
            delete tmp;
            if (head_next != NULL) {
                head_next->locker->unlock();
            }
            return true;
        }
        prev->locker->lock();
        iter->locker->lock();
        
        prev->next = iter->next;
        delete iter;
        
        prev->locker->unlock();
        return true;
    }
    
    
    bool contains(const Elem &item) {
        Node *iter  = head;
        while (iter != NULL) {
            if (iter->data == item) {
                return true;
            }
            iter = iter->next;
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
