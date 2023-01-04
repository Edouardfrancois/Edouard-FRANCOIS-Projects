/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-pierre.tran
** File description:
** ManageCooks
*/

#pragma once

#include <thread>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <map>

#include <iostream>

#include "utils/convert_function.hpp"

class ThreadPool
{
public:
    static int default_n_threads()
    {
        return std::thread::hardware_concurrency();
    }

    ThreadPool(bool is_detached, bool concurrent_modify) : _detached_pool(is_detached), _should_kill(false)
    {
        int const n_threads = std::thread::hardware_concurrency();
        this->_concurent_mod = concurrent_modify;
        for (int i = 0; i < n_threads; i += 1)
        {
            _pool.push_back(std::thread(&ThreadPool::ThreadLoop, this));
            if (is_detached)
            {
                _pool.back().detach();
            }
        }
    }

    ThreadPool(int nbFreds, bool is_detached, bool concurrent_modify) : _detached_pool(is_detached), _should_kill(false)
    {
        this->_concurent_mod = concurrent_modify;
        for (int i = 0; i < nbFreds; i += 1)
        {
            _pool.push_back(std::thread(&ThreadPool::ThreadLoop, this));
            if (is_detached)
            {
                _pool.back().detach();
            }
        }
    }

    ~ThreadPool()
    {
        this->_should_kill = true;
        _con_var.notify_all();
        if (!_detached_pool)
        {
            for (size_t i = 0; i < this->_pool.size(); ++i)
            {
                if (this->_pool.at(i).joinable())
                {
                    this->_pool.at(i).join();
                }
            }
        }
    }

    /**
     * @brief Get the Status of the ThreadPool
     *
     * @return true if it's stopped
     * @return false if it's running
     */
    bool getStatus() const
    {
        return this->_should_kill;
    }

    /**
     * @brief place a task in the queue. lambda version
     *
     * @tparam Function_type template
     * @param f this function accept lambda type functions
     */
    template <typename Function_type>
    void attributeTasks(Function_type f)
    {
        std::unique_lock<std::mutex> lock(this->_queue);
        _jobs.push(std::function<void()>(f));
        lock.unlock();

        _con_var.notify_one();
    }

    /**
     * @brief place a task in the queue,
     * takes a function name, and its arguments
     *
     * @tparam Function_type
     * @tparam Params
     * @param f function
     * @param tp arguments
     */
    template <typename Fun_type, class... Params>
    void attributeTasks(Fun_type f, Params &&...tp)
    {
        std::unique_lock<std::mutex> lock(this->_queue);
        _jobs.push(utils::convert_function(f, std::forward<Params>(tp)...));
        lock.unlock();

        _con_var.notify_one();
    }

    /**
     * @brief gives the order to stop the thread pool
     *
     */
    void Stop()
    {
        this->_should_kill = true;
        _con_var.notify_all();
        if (!_detached_pool)
        {
            for (size_t i = 0; i < this->_pool.size(); ++i)
            {
                if (this->_pool.at(i).joinable())
                {
                    this->_pool.at(i).join();
                }
            }
        }
    }

private:
    /**
     * @brief worker thread
     *
     */
    void ThreadLoop(void)
    {
        std::function<void()> currJob;
        std::unique_lock<std::mutex> currLock;

        while (true)
        {
            // ignore wait is it needs to be killed or if there a job to do
            currLock = std::unique_lock<std::mutex>(_queue);
            _con_var.wait(currLock, [this]
                          { return this->_should_kill || !(this->_jobs.empty()); });
            if (_should_kill)
            {
                return;
            }
            // assigne the oldest job as currJob
            currJob = this->_jobs.front();
            this->_jobs.pop();
            if (!_concurent_mod)
                currLock.unlock();
            currJob();
            if (_concurent_mod)
                currLock.unlock();
        }
    }

    std::condition_variable _con_var;
    std::mutex _queue;
    std::vector<std::thread> _pool;
    std::queue<std::function<void()>> _jobs;
    bool _concurent_mod;
    bool _detached_pool;
    bool _should_kill;
};