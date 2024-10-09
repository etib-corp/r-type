/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameClock
*/

#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <functional>
#include <unordered_map>

class GameClock {
public:
    using Callback = std::function<void()>;

    GameClock() : running_(false)
    {}

    void addCallback(Callback cb, int intervalMs)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.emplace_back(cb, intervalMs, std::chrono::steady_clock::now());
    }

    void start(void)
    {
        running_ = true;
        clockThread_ = std::thread([this]() { this->run(); });
    }

    void stop(void)
    {
        running_ = false;
        if (clockThread_.joinable())
        {
            clockThread_.join();
        }
    }

    ~GameClock()
    {
        stop();
    }

private:
    struct TimedCallback {
        Callback cb;
        int intervalMs;
        std::chrono::steady_clock::time_point lastExecution;

        TimedCallback(Callback c, int interval, std::chrono::steady_clock::time_point lastExec)
            : cb(c), intervalMs(interval), lastExecution(lastExec) {}
    };

    std::vector<TimedCallback> callbacks_;
    std::mutex mutex_;
    std::thread clockThread_;
    bool running_;

    void run(void)
    {
        while (running_)
        {
            auto now = std::chrono::steady_clock::now();

            std::lock_guard<std::mutex> lock(mutex_);
            for (auto& callback : callbacks_)
            {
                auto durationSinceLastExecution = std::chrono::duration_cast<std::chrono::milliseconds>(now - callback.lastExecution);
                if (durationSinceLastExecution.count() >= callback.intervalMs)
                {
                    callback.cb();
                    callback.lastExecution = now;
                }
            }
        }
    }
};

#endif /* !GAMECLOCK_HPP_ */
