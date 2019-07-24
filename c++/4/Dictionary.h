#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;


void adjustDown(int *a,int parent,int size);

class Dictionary
{
public:
    Dictionary() {}
    ~Dictionary() {}

    void read(const std::string & filename);
    void rread(const std::string & filename);
    void store(const std::string & filename);
    void Atoa(const std::string str);
    void print();


private:
    vector<string> _vec;
    int a[10];
    map<string,size_t> _mapp;

};









