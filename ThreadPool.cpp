/*
#include "ThreadPool.h"

ThreadPool::ThreadPool(const uint32_t num_threads) {
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(&ThreadPool::run, this);
    }
}

void ThreadPool::wait(const uint64_t task_id) {
    std::unique_lock<std::mutex> lock(tasks_info_mtx);
    tasks_info_cv.wait(lock, [this, task_id]()->bool {
        return task_id < last_idx && tasks_info[task_id].status == TaskStatus::completed;
    });
}

void ThreadPool::wait_all() {
    std::unique_lock<std::mutex> lock(tasks_info_mtx);
    wait_all_cv.wait(lock, [this]()->bool { return cnt_completed_tasks == last_idx; });
}

bool ThreadPool::calculated(const uint64_t task_id) {
    std::lock_guard<std::mutex> lock(tasks_info_mtx);
    return task_id < last_idx&& tasks_info[task_id].status == TaskStatus::completed;
}

ThreadPool::~ThreadPool() {
    quite = true;
    q_cv.notify_all();
    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
}

void ThreadPool::run() {
    while (!quite) {
        std::unique_lock<std::mutex> lock(q_mtx);
        q_cv.wait(lock, [this]()->bool { return !q.empty() || quite; });

        if (!q.empty() && !quite) {
            std::pair<Task, uint64_t> task = std::move(q.front());
            q.pop();
            lock.unlock();

            task.first();

            std::lock_guard<std::mutex> lock(tasks_info_mtx);
            if (task.first.has_result()) {
                tasks_info[task.second].result = task.first.get_result();
            }
            tasks_info[task.second].status = TaskStatus::completed;
            ++cnt_completed_tasks;
        }
        wait_all_cv.notify_all();
        tasks_info_cv.notify_all(); // notify for wait function
    }
}

std::any ThreadPool::wait_result(const uint64_t task_id) {
    std::unique_lock<std::mutex> lock(tasks_info_mtx);
    tasks_info_cv.wait(lock, [this, task_id]()->bool {
        return task_id < last_idx && tasks_info[task_id].status == TaskStatus::completed;
    });
    return tasks_info[task_id].result;
}

template<class T>
void ThreadPool::wait_result(const uint64_t task_id, T &value) {
    std::unique_lock<std::mutex> lock(tasks_info_mtx);
    tasks_info_cv.wait(lock, [this, task_id]()->bool {
        return task_id < last_idx && tasks_info[task_id].status == TaskStatus::completed;
    });
    value = std::any_cast<T>(tasks_info[task_id].result);
}

template<typename Func, typename... Args, typename... FuncTypes>
uint64_t ThreadPool::add_task(Func (*func)(FuncTypes...), Args &&... args) {

    const uint64_t task_id = last_idx++;

    std::unique_lock<std::mutex> lock(tasks_info_mtx);
    tasks_info[task_id] = TaskInfo();
    lock.unlock();

    std::lock_guard<std::mutex> q_lock(q_mtx);
    q.emplace(Task(func, std::forward<Args>(args)...), task_id);
    q_cv.notify_one();
    return task_id;
}
*/
