#include<iostream>
#include "PriorityQueue.h"

#include <stdlib.h>
#include <time.h>
#include<chrono>

using namespace std::chrono;

int main()
{
    //PRUEBA 1
    auto start = high_resolution_clock::now();
    PQ<int,1> A;
    srand(time(NULL));
    for (int i = 0; i < 12; i++) {
        A.push(rand()%100+1);
    }
    A.print();
    A.pop();
    A.pop();
    A.pop();
    A.pop();
    A.print();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "duracion de la prueba 1: "<< duration.count() << endl;
    //PRUEBA 2 (sin print por ser grande)
    start = high_resolution_clock::now();
    PQ<int, 0> B;
    for (int i = 0; i < 1000; i++) {
        B.push(rand() % 1000 + 1);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "duracion de la prueba 2: " << duration.count() << endl;
    while(true){
        
    }
}
