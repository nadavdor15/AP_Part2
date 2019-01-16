#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <queue>
#include <atomic>				
#include <mutex>
#include <condition_variable>

using namespace std::chrono_literals;

class Task {
public:
	virtual void execute() = 0;	
	virtual ~Task() {}
};

class TasksQueue {
	std::atomic<bool> stop_queue;
	std::queue<Task*> tasks;
	mutable std::condition_variable queue_cond_var;
	mutable std::mutex mut;
public:
	TasksQueue() {
		stop_queue = false;
	}
	Task* pop() {
		std::lock_guard<std::mutex> g(mut);
		if (tasks.empty()) {
			return nullptr;
		}
		auto task = tasks.front();
		tasks.pop();
		return task;
	}

	bool empty() const {
		std::lock_guard<std::mutex> g(mut);
		return tasks.empty();
	}

	void push(Task* task) {
		if (task == nullptr) {
			throw std::invalid_argument("Task should not be null");
		}
		std::lock_guard<std::mutex> g(mut);
		tasks.push(task);
		queue_cond_var.notify_one();
	}

	void wait() const {
		std::unique_lock<std::mutex> ul(mut);
		if (stop_queue) return;
		queue_cond_var.wait(ul);
	}

	bool stop() const {
		return stop_queue;
	}

	void exit() {
		std::lock_guard<std::mutex> g(mut);
		stop_queue = true;
		queue_cond_var.notify_all();
	}
};

#endif