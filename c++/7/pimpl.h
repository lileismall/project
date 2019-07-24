#pragma once

#include <iostream>

class Test
{
private:
    class Impl;

public:
   Test(int a);
    ~Test();
    void print() const;

private:

    Impl *_pimpl;

};

