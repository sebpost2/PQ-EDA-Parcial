#pragma once
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int bi_exp(int a, int b) {
    int res = 1;
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    int T = bi_exp(a, b / 2);
    return T * T * bi_exp(a, b % 2);
}

template<typename T, bool max>
struct PQ {
    PQ();
    T front() const;
    bool empty() const;
    void full();
    void pop();
    void push(T const a);
    void swap(const int i, const int j);
    void print()const;
    bool find(T const n, int i)const;
    bool findinsert(T const n, int i)const;

private:
    int resize, heigth, elements, pot;
    vector<T> data;
};

template<typename T, bool max>
PQ<T, max>::PQ() {
    data.resize(4);
    resize = 2;
    heigth = 1;
    elements = 4;
    pot = 0;
}

template<typename T, bool max>
T PQ<T, max>::front() const {
    return data[0];
}

template<typename T, bool max>
bool PQ<T, max>::empty() const{
    if (elements==1)
        return 1;
    return 0;
}

template<typename T, bool max>
void PQ<T, max>::full() {
    heigth++;
    pot = bi_exp(2, resize + 1);
    data.resize(data.size() + pot);
    resize++;
}

template<typename T, bool max>
void PQ<T, max>::pop() {
    data[1] = data[--elements];
    data[elements] = 0;
    if (elements<pot/2)
        heigth--;
    int size = 1, maxt=0,maxi=0,it=0;
    if (max == 1) {
        for (int i = 0; i < heigth; i++) {
            maxt = -100000000;
            for (int j = 0; j < 2; j++) {
                it = 2 * size + j;
                if (maxt < data[it]) {
                    maxt = data[it];
                    maxi = it;
                }
            }
            if (data[size] < data[maxi] && data[maxi] != 0) {
                swap(size, maxi);
                size = maxi;
                continue;
            }
            break;
        }
    }
    else {
        maxt = 100000000;
        for (int i = 0; i < heigth; i++) {
            for (int j = 0; j < 2; j++) {
                it = 2 * size + j;
                if (maxt >= data[it]) {
                    maxt = data[it];
                    maxi = it;
                }
            }
            if (data[size] >= data[maxi] && data[maxi]!=0) {
                swap(size, maxi);
                size = maxi;
                continue;
            }
            break;
        }
    }
}

template<typename T, bool max>
void PQ<T, max>::push(T const a) {

    if (findinsert(a,1)) {
        return;
    }

    if (elements == 1) {
        data[elements++] = a;
        return;
    }

    if (data.capacity() == elements)
        full();

    int size = elements;
    data[size] = a;
    if (max == 1) {
        for (int i = 0; i < heigth; i++) {
            if (data[size] >= data[size / 2]) {
                swap(size, size / 2);
                size = size / 2;
                continue;
            }
            break;
        }
    }
    else {
        for (int i = 0; i < heigth; i++) {
            if (data[size] < data[size / 2]) {
                swap(size, size / 2);
                size = size / 2;
                continue;
            }
            break;
        }
    }
    elements++;
}

template<typename T, bool max>
void PQ<T, max>::swap(const int i, const int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

template<typename T, bool max>
void PQ<T, max>::print() const {
    int count = 0, i=0, insert=0;
    while (count+1 < elements) {
        int pot = bi_exp(2, i);
        while (pot+insert != count && count+1<elements) {
            cout << " | " << data[count+1];
            count++;
        }
        cout << " |\n";
        insert = count;
        i++;
    }
}

template<typename T, bool max>
bool PQ<T, max>::find(const T n, int i)const {
    if (i >= elements)
        return false;

    if (data[i] == n) {
        cout << "\nEl elemento fue encontrado en la posicion: " << i << "\n";
        return true;
    }
    else if (max == 1) {
        if (data[i] <= n) {
            return false;
        }
    }
    else {
        if (data[i] > n) {
            return false;
        }
    }
    if (find(n, i * 2) || find(n, i * 2 + 1))
        return true;
}


template<typename T, bool max>
bool PQ<T, max>::findinsert(const T n, int i)const {
    if (i >= elements)
        return false;

    if (data[i] == n) {
        return true;
    }
    else if (max == 1) {
        if (data[i] <= n) {
            return false;
        }
    }
    else {
        if (data[i] > n) {
            return false;
        }
    }
    if (findinsert(n, i * 2) || findinsert(n, i * 2 + 1))
        return true;
}