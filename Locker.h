//
//  Locker.h
//  lab3_guryeva
//
//  Created by Polina Guryeva on 19/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#ifndef Locker_h
#define Locker_h

class Locker {
    pthread_mutex_t mutex;
public:
    Locker() {
        mutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&mutex, NULL);
    }
    
    void lock() {
        pthread_mutex_lock(&mutex);
    }
    
    void unlock() {
        pthread_mutex_unlock(&mutex);
    }
};

#endif /* Locker_h */
