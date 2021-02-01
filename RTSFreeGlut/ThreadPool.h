#pragma once
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
#define maxThreads 1
class ThreadPool {
public:
	ThreadPool() {
		workers[0] = thread(&workerThreadFunction,&run);
	}
	~ThreadPool() {
		run = false;
		for (int i = 0; i < maxThreads; i++) {
			workers[i].join();
		}
	}
	void stop() {

	}

private:
	bool run = false;
	void workerThreadFunction(bool *r) {
		while (*r) {
			this_thread::sleep_for(chrono::milliseconds(3));
		}
	}
	thread workers[maxThreads];
};