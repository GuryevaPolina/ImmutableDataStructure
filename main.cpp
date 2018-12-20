//
//  main.cpp
//  lab3_guryeva
//
//  Created by Polina Guryeva on 19/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#include <iostream>
#include "CGSet.h"
#include "OSSet.h"

#define N 200
int n1 = 0, n2 = 1, n3 = 2;

using namespace std;

CGSet<int> *cgSet = new CGSet<int>();
OSSet<int> *osSet = new OSSet<int>();

int arr[N];

void* writeToCGSet(void* threadNumber) {
    for(int i = *((int*)threadNumber); i < N; i+=3) {
        cgSet->add(arr[i]);
    }
    pthread_exit(0);
}

bool test1_1() {
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, writeToCGSet, (void*)&n1);
    pthread_create(&th2, NULL, writeToCGSet, (void*)&n2);
    pthread_create(&th3, NULL, writeToCGSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    for (int i = 0; i < N; i++) {
        if (cgSet->contains(arr[i]) == false) {
            return false;
        }
    }
    if (cgSet->count() != N) {
        return false;
    }
    return true;
}

void* readFromCGSet(void* threadNumber) {
    for(int i = *((int*)threadNumber); i < N; i+=3) {
        cgSet->remove(arr[i]);
    }
    pthread_exit(0);
}


bool test2_1() {
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, readFromCGSet, (void*)&n1);
    pthread_create(&th2, NULL, readFromCGSet, (void*)&n2);
    pthread_create(&th3, NULL, readFromCGSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    for (int i = 0; i < N; i++) {
        if (cgSet->contains(arr[i]) == true) {
            return false;
        }
    }
    if (cgSet->count() != 0) {
        return false;
    }
    return true;
}

bool test3_1() {
    for (int i = 0; i < N; i++) {
        arr[i] = 2 * i;
    }
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, writeToCGSet, (void*)&n1);
    pthread_create(&th2, NULL, writeToCGSet, (void*)&n2);
    pthread_create(&th3, NULL, writeToCGSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    if (cgSet->count() != N) {
        return false;
    }
    
    pthread_create(&th1, NULL, readFromCGSet, (void*)&n1);
    pthread_create(&th2, NULL, readFromCGSet, (void*)&n2);
    pthread_create(&th3, NULL, readFromCGSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    if (cgSet->count() != 0) {
        return false;
    }
    
    return true;
}

void* writeToOSSet(void* threadNumber) {
    for(int i = *((int*)threadNumber); i < N; i+=3) {
        osSet->add(arr[i]);
    }
    pthread_exit(0);
}

bool test1_2() {
    for (int i = 0; i < N; i++) {
        arr[i] = 3 * i;
    }
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, writeToOSSet, (void*)&n1);
    pthread_create(&th2, NULL, writeToOSSet, (void*)&n2);
    pthread_create(&th3, NULL, writeToOSSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    for (int i = 0; i < N; i++) {
        if (osSet->contains(arr[i]) == false) {
            return false;
        }
    }
    if (osSet->count() != N) {
        return false;
    }
    return true;
}

void* readFromOSSet(void* threadNumber) {
    for(int i = *((int*)threadNumber); i < N; i+=3) {
        osSet->remove(arr[i]);
    }
    pthread_exit(0);
}


bool test2_2() {
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, readFromOSSet, (void*)&n1);
    pthread_create(&th2, NULL, readFromOSSet, (void*)&n2);
    pthread_create(&th3, NULL, readFromOSSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    for (int i = 0; i < N; i++) {
        if (osSet->contains(arr[i]) == true) {
            return false;
        }
    }
    if (osSet->count() != 0) {
        return false;
    }
    return true;
}

bool test3_2() {
    for (int i = 0; i < N; i++) {
        arr[i] = 4 * i;
    }
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, writeToOSSet, (void*)&n1);
    pthread_create(&th2, NULL, writeToOSSet, (void*)&n2);
    pthread_create(&th3, NULL, writeToOSSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    if (osSet->count() != N) {
        return false;
    }
    
    pthread_create(&th1, NULL, readFromOSSet, (void*)&n1);
    pthread_create(&th2, NULL, readFromOSSet, (void*)&n2);
    pthread_create(&th3, NULL, readFromOSSet, (void*)&n3);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    
    if (osSet->count() != 0) {
        return false;
    }
    
    return true;
}

void timeTest() {
    clock_t begin = clock();
    test3_1();
    clock_t end = clock();
    double t1 = double(end - begin) / CLOCKS_PER_SEC;
    cout << "CGSet time is: " << t1 << endl;
    
    begin = clock();
    test3_2();
    end = clock();
    double t2 = double(end - begin) / CLOCKS_PER_SEC;
    cout << "OSSet time is: " << t2 << endl;

    if (t1 > t2) {
        cout << "OSSet is FASTER" << endl;
    } else {
        cout << "CGSet is FASTER" << endl;
    }
}

int main(int argc, const char * argv[]) {
    
    if(test1_1() == true) {
        cout << "test 1 for CGSet passed" << endl;
    } else {
        cout << "test 1 for CGSet failed" << endl;
    }
    
    if(test2_1() == true) {
        cout << "test 2 for CGSet passed" << endl;
    } else {
        cout << "test 2 for CGSet failed" << endl;
    }
    
    if(test3_1() == true) {
        cout << "test 3 for CGSet passed" << endl;
    } else {
        cout << "test 3 for CGSet failed" << endl;
    }
    
    if(test1_2() == true) {
        cout << "test 1 for OSSet passed" << endl;
    } else {
        cout << "test 1 for OSSet failed" << endl;
    }
    
    if(test2_2() == true) {
        cout << "test 2 for OSSet passed" << endl;
    } else {
        cout << "test 2 for OSSet failed" << endl;
    }
    
    if(test3_2() == true) {
        cout << "test 3 for OSSet passed" << endl;
    } else {
        cout << "test 3 for OSSet failed" << endl;
    }
    
    timeTest();
    
    return 0;
}
