#include <bits/stdc++.h>

template <typename T>
class Container {
private: 
    std::unique_ptr<T[]> obj;
    int shapex, shapey;
public: 
    Container();
    Container(int _shapex);
    Container(int _shapex, int _shapey);
    Container(Container&& other);
    Container& operator=(Container<T>&& other);
    T& get_reference();
    T& get_reference(int posx);
    T& get_reference(int posx, int posy);
    ~Container();
};

template <typename T>
Container<T>::Container(Container<T>&& other) {
   obj = std::move(other.obj);
   shapex = other.shapex;
   shapey = other.shapey;
}

template <typename T>
Container<T>& Container<T>::operator=(Container<T>&& other) {
   obj = std::move(other.obj);
   shapex = other.shapex;
   shapey = other.shapey;
   return *this;
}

template <typename T>
Container<T>::Container() {
    obj = std::make_unique<T[]>(1);
    shapex = 1;
    shapey = 1;
}

template <typename T>
Container<T>::Container(int _shapex) {
    obj = std::make_unique<T[]>(_shapex);
    shapex = _shapex;
    shapey = 1;
}

template <typename T>
Container<T>::Container(int _shapex, int _shapey) {
    obj = std::make_unique<T[]>(_shapex*_shapey);
    shapex = _shapex;
    shapey = _shapey;
}

template <typename T>
T& Container<T>::get_reference() {
    return *obj.get();
}

template <typename T>
T& Container<T>::get_reference(int posx) {
    if(posx >= shapex) {
        cerr << "Runtime error: Array index out of range.";
        exit(0);
    }
    return *(obj.get() + posx);
}

template <typename T>
T& Container<T>::get_reference(int posx, int posy) {
    if(posx >= shapex or posy >= shapey) {
        cerr << "Runtime error: Array index out of range.";
        exit(0);
    }
    return *(obj.get() + posx*shapey + posy);
}

template <typename T>
Container<T>::~Container() {}