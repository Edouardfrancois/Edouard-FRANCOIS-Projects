/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <iostream>
#include <mutex>
#include <queue>
#include <vector>

namespace utils
{
    template <typename bill>
    class SafeQueue
    {
    public:
        SafeQueue()
        {
        }
        ~SafeQueue()
        {
        }

        /**
         * @brief try to pop an element safely;
         * can be safely used with threads
         *
         * @param task puts the popped value in task
         * @return true if popped
         * @return false if failed to pop
         */
        bool try_pop(bill &task)
        {
            m.lock();
            if (this->_queue.empty())
            {
                m.unlock();
                return false;
            }
            task = this->_queue.front();
            this->_queue.pop();
            m.unlock();
            return true;
        }

        /**
         * @brief puts a reference to task in the queue
         * can be used with thread safely
         *
         * @param task
         */
        void add(bill &task)
        {
            m.lock();
            this->_queue.push(task);
            m.unlock();
        }

        /**
         * @brief Get the Size object
         *
         * @return int
         */
        int getSize()
        {
            m.lock();
            int size = this->_queue.size();
            m.unlock();
            return size;
        }

        /**
         * @brief Is Empty Queue
         *
         * @return true
         * @return false
         */
        bool is_empty()
        {
            m.lock();
            bool is_empty = this->_queue.empty();
            m.unlock();
            return is_empty;
        }

        /**
         * @brief Clear the Queue
         *
         */
        void ClearQueue()
        {
            m.lock();
            while (!this->_queue.empty())
            {
                this->_queue.pop();
            }
            m.unlock();
        }

        std::vector<bill> preview() const
        {
            // std::vector<bill> res;
            // m.lock();
            // std::queue<bill> blueprint = std::queue<bill>(this->_queue);
            // m.unlock();
            //
            // for (int i = 0; i < this->_queue.size(); ++i)
            // {
            // res.push_back(blueprint.front());
            // blueprint.pop();
            // }
            // return res;
        }

    private:
        std::queue<bill> _queue;
        std::mutex m;
    };
}

#endif /* !SAFEQUEUE_HPP_ */
