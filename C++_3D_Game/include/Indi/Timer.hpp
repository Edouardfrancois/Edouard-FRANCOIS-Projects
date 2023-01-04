/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <chrono>
#include <ctime>

class Timer {
public:
    void Start()
    {
        _TimeStart = std::chrono::system_clock::now();
        _IsRuning = true;
    }
    
    void Stop() {
        _TimeStop = std::chrono::system_clock::now();
        _IsRuning = false;
    }

    void Reset() {
        Stop();
        Start();
    }

    bool GetIsRunning() const {return this->_IsRuning;};

    double GetTimerInMillisecond() {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if(_IsRuning)
            endTime = std::chrono::system_clock::now();
        else
            endTime = _TimeStop;
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - _TimeStart).count();
    }
    double GetTimerInSeconds() {
        return GetTimerInMillisecond() / 1000;
    }

    private:
        std::chrono::time_point<std::chrono::system_clock> _TimeStart;
        std::chrono::time_point<std::chrono::system_clock> _TimeStop;
        bool _IsRuning = false;
};

#endif /* !TIMER_HPP_ */
