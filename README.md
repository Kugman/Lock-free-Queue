# Overview

This project implements a Single Producer / Single Consumer (SPSC) lock-free queue in modern C++.
The queue uses atomic operations instead of traditional mutex-based synchronization, allowing concurrent access with minimal latency and non-blocking behavior.

Lock-free data structures are critical in real-time systems, high-performance computing, and low-latency applications such as networking, robotics, and finance.

# Features

Template-based implementation: supports any data type.

Fixed-size circular buffer with atomic head and tail pointers.

enqueue() and dequeue() operations with non-blocking behavior.

Demonstrates real-time safe concurrency patterns.

# Usage

Include the LockFreeQueue.h file in your project:

#include "LockFreeQueue.h"
#include <iostream>
#include <thread>

int main() {
    LockFreeQueue<int> q(10);

    std::thread producer([&]() {
        for(int i = 0; i < 20; ++i) {
            while(!q.enqueue(i)) {}
            std::cout << "Produced: " << i << std::endl;
        }
    });

    std::thread consumer([&]() {
        for(int i = 0; i < 20; ++i) {
            int value;
            while(!q.dequeue(value)) {}
            std::cout << "Consumed: " << value << std::endl;
        }
    });

    producer.join();
    consumer.join();
}
