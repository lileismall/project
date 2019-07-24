#pragma once

#include <iostream>



class MutexLock
{
public:
    MutexLock();
    ~MutexLock();


    void lock();
    void unlock();

private:
    pthread_mutex_t _mutex;
};

