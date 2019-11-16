#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename T> 
class Context {
private: 
    list<pair<string, T>> clist;
public: 
    Context();
    void add_context(pair<string, T>);
    void add_context(string, T&&);
    int get_context_size();
    void resize_context(int);
    T& get_value(string s);
    ~Context();
};

template <typename T>
Context<T>::Context() {}

template <typename T>
void Context<T>::add_context(pair<string, T> m) {
    clist.push_front(m);
}

template <typename T>
void Context<T>::add_context(string s, T&& m) {
    clist.push_front(make_pair(s, std::move(m)));
}

template <typename T>
T& Context<T>::get_value(string s) {
    for(auto&z: clist) {
        if(s == z.first) {
            return z.second;
        }
    }
    cerr << "Undefined reference to "<<s<<endl;
    exit(0);
}

template <typename T>
int Context<T>::get_context_size() {
    return clist.size();
}

template <typename T>
void Context<T>::resize_context(int sz) {
    assert((int)clist.size() >= sz);
    while(sz != (int)clist.size()) {
        clist.pop_front();
    }
}

template <typename T>
Context<T>::~Context() {}