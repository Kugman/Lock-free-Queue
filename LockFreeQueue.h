#pragma once
#include <vector>
#include <atomic>

using namespace std;

template<typename T>
class LockFreeQueue
{
private:	
	size_t size_;
	vector<T> buffer_;
	atomic<size_t> head_;
	atomic<size_t> tail_;


public:

	explicit LockFreeQueue(size_t size) : size_(size), buffer_(size) {
		head_.store(0);
		tail_.store(0);
	}
	 
	bool enqueue(const T& item) {
		size_t tail = tail_.load(memory_order_relaxed);
		size_t next_tail = (tail + 1) % size_;

		//the queue id full
		if (next_tail == head_.load(memory_order_acquire)) return false;

		buffer_[tail] = item;
		tail_.store(next_tail, memory_order_release);
		return true;
	}

	bool dequeue(T& item) {
		size_t head = head_.load(memory_order_relaxed);

		//the queue is empty
		if (head == tail_.load(memory_order_acquire)) return false;

		item = buffer_[head];
		head_.store((head + 1) % size_, memory_order_release);
		return true;
	}

};


