#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename U, typename T>
class Context {
private:
    list<pair<U, T>> clist;
public:
    Context();
    void add_context(pair<U, T>);
    void add_context(const U&, T&&);
    int get_context_size();
    void resize_context(int);
    T& get_value(const U &s);
    ~Context();
};

template <typename U, typename T>
Context<U, T>::Context() {}

template <typename U, typename T>
void Context<U, T>::add_context(pair<U, T> m) {
    clist.push_front(m);
}

template <typename U, typename T>
void Context<U, T>::add_context(const U &s, T&& m) {
    clist.push_front(make_pair(s, std::move(m)));
}

template <typename U, typename T>
T& Context<U, T>::get_value(const U &s) {
    for(auto&z: clist) {
        if(s == z.first) {
            return z.second;
        }
    }
    cerr << "Undefined reference to "<<s<<endl;
    exit(0);
}

template <typename U, typename T>
int Context<U, T>::get_context_size() {
    return clist.size();
}

template <typename U, typename T>
void Context<U, T>::resize_context(int sz) {
    assert((int)clist.size() >= sz);
    while(sz != (int)clist.size()) {
        clist.pop_front();
    }
}

template <typename U, typename T>
Context<U, T>::~Context() {}


template <typename U, typename T>
class ContextNoError {
private:
    list<pair<U, T>> clist;
public:
    ContextNoError();
    void add_context(pair<U, T>);
    void add_context(const U&, T&&);
    int get_context_size();
    void resize_context(int);
    T get_value(const U &s, T);
    ~ContextNoError();
};

template <typename U, typename T>
ContextNoError<U, T>::ContextNoError() {}

template <typename U, typename T>
void ContextNoError<U, T>::add_context(pair<U, T> m) {
    clist.push_front(m);
}

template <typename U, typename T>
void ContextNoError<U, T>::add_context(const U &s, T&& m) {
    clist.push_front(make_pair(s, std::move(m)));
}

template <typename U, typename T>
T ContextNoError<U, T>::get_value(const U &s, T default_val) {
    for(auto&z: clist) {
        if(s == z.first) {
            return z.second;
        }
    }
    return default_val;
}

template <typename U, typename T>
int ContextNoError<U, T>::get_context_size() {
    return clist.size();
}

template <typename U, typename T>
void ContextNoError<U, T>::resize_context(int sz) {
    assert((int)clist.size() >= sz);
    while(sz != (int)clist.size()) {
        clist.pop_front();
    }
}

template <typename U, typename T>
ContextNoError<U, T>::~ContextNoError() {}