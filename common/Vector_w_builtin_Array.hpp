#pragma once
#include <algorithm>
#include <stdexcept>

template <typename E>
class ArrayVector {
private:
    int capacity; // current array size
    int n; // number of elements in vector
    E* A; // the built in array storing elements
public:
    ArrayVector();
    int size() const;
    bool empty() const;
    E& operator[](int i);
    E& at(int i);
    void erase(int i);
    void insert(int i, const E& e);
    void reserve(int N);
    ~ArrayVector();
};

template <typename E>
ArrayVector<E>::ArrayVector()
    : capacity(0)
    , n(0)
    , A(nullptr)
{
}

template <typename E>
int ArrayVector<E>::size() const
{
    return n;
}

template <typename E>
bool ArrayVector<E>::empty() const
{
    return n == 0;
}

template <typename E>
E& ArrayVector<E>::operator[](int i)
{
    if (i < 0 || i >= n) {
        throw std::runtime_error("Illegal index supplied to operator.");
    }
    return A[i];
}

template <typename E>
E& ArrayVector<E>::at(int i)
{
    if (i < 0 || i >= n) {
        throw std::runtime_error("Illegal index supplied to function.");
    }
    return A[i];
}

template <typename E>
void ArrayVector<E>::erase(int i)
{
    if (i < 0 || i >= n) {
        throw std::runtime_error("Illegal index supplied to function.");
    }
    for (int j = i + 1; j < n; j++) {
        A[j - 1] = A[j];
    }
    n--;
}

template <typename E>
void ArrayVector<E>::reserve(int N)
{
    if (capacity >= N) {
        return;
    }
    E* B = new E[N];
    for (int j = 0; j < n; j++) {
        B[j] = A[j];
    }
    if (A != nullptr) {
        delete[] A;
    }
    A = B;
    capacity = N;
}

template <typename E>
void ArrayVector<E>::insert(int i, const E& e)
{
    if (n >= capacity) {
        reserve(std::max(1, 2 * capacity));
    }
    for (int j = n - 1; j >= i; j--) {
        A[j + 1] = A[j];
    }
    A[i] = e;
    n++;
}

template <typename E>
ArrayVector<E>::~ArrayVector()
{
}
