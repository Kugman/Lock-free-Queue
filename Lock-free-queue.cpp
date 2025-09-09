// Lock-free-queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include "LockFreeQueue.h"

using namespace std;

mutex coumtMutex;

void printLine(const string& msg) {
    lock_guard<mutex> lock(coumtMutex);
    cout << msg << endl;
}


int main()
{
    LockFreeQueue<int> q(10);
    
    thread producer([&]() {
        
        for (int i = 0; i < 20; i++) {
            while (!q.enqueue(i));
            printLine("Produced: " + to_string(i));
        }
    });

    thread consumer([&]() {

        for (int i = 0; i < 20; i++) {
            int value;
            while (!q.dequeue(value));
            printLine("Consumed: " + to_string(value));
        }
    });

    producer.join();
    consumer.join();
}
